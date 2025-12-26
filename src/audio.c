/**
 ******************************************************************************
 * File Name		: audio.c
 * Date				:
 * Author			: Xavier Halgand
 * Description		: Ported to STM32H7 + PCM5102
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "audio.h"

// Audio Buffer in RAM_D2 (SRAM2) for DMA accessibility
__attribute__((section(".sram2"))) uint16_t audiobuff[BUFF_LEN];

static uint8_t		volume = VOL;
static bool			sound = true;

// I2S Handle
extern I2S_HandleTypeDef hi2s2;

void audio_init(void)
{
    // Start DMA transmission
    // We assume hi2s2 is initialized in main.c
    if (HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t*)audiobuff, BUFF_LEN) != HAL_OK)
    {
        // Error Handler
    }
}

//---------------------------------------------------------------------------
/**
 * @brief  Manages the DMA Half Transfer complete interrupt.
 * @param  hi2s: I2S handle
 * @retval None
 */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->Instance == SPI2)
    {
        // Invalidate Cache for the first half of the buffer so CPU can write to it safely (if needed)
        // Actually, we are WRITING to the buffer from CPU, and DMA Reads from it.
        // So we need to Clean the D-Cache (Flush) after writing new data.

        // 1. Calculate pointer to the first half
        uint16_t *pBuffer = audiobuff;

        // 2. Generate Sound
        make_sound(0, BUFF_LEN_DIV2); // Fill first half (Wait, original code said BUFF_LEN_DIV4?)
        // Original: make_sound(0, BUFF_LEN_DIV4); in HalfTransfer
        // BUFF_LEN is 4*BUFF_LEN_DIV4.
        // Half Transfer means half of buffer (2*BUFF_LEN_DIV4) is sent?
        // Usually:
        // HalfTransfer: First half sent. Refill First half.
        // TransferComplete: Second half sent. Refill Second half.

        // Let's check original Logic:
        // EVAL_AUDIO_HalfTransfer_CallBack -> make_sound(0, BUFF_LEN_DIV4);
        // EVAL_AUDIO_TransferComplete_CallBack -> make_sound(BUFF_LEN_DIV2, BUFF_LEN_DIV4);

        // Wait, BUFF_LEN is 4*BUFF_LEN_DIV4.
        // The buffer seems to be treated as stereo interleaved.
        // If BUFF_LEN is in "samples" (uint16_t), and stereo, then 1 frame = 2 samples.
        // If BUFF_LEN_DIV4 is used as length argument to make_sound...
        // make_sound takes (offset, len).

        // Original code:
        // HT: offset 0, len BUFF_LEN_DIV4
        // TC: offset BUFF_LEN_DIV2, len BUFF_LEN_DIV4

        // BUFF_LEN_DIV2 is 2*BUFF_LEN_DIV4.
        // So it skips the middle part?
        // 0..DIV4 filled.
        // DIV2..(DIV2+DIV4) filled.
        // What about DIV4..DIV2 and (DIV2+DIV4)..BUFF_LEN ?

        // Ah, maybe the original buffer was 2x bigger or something?
        // CONSTANTS.h: BUFF_LEN = 4 * BUFF_LEN_DIV4.

        // If make_sound generates stereo samples, "len" might be "frames" or "samples"?
        // make_sound:
        // outp = audiobuff + offset;
        // for (pos = 0; pos < len; pos++) { ... *outp++ = left; *outp++ = right; }
        // So it writes 2 * len uint16_t's.

        // So make_sound(0, BUFF_LEN_DIV4) writes 2 * BUFF_LEN_DIV4 uint16_t's.
        // That is exactly BUFF_LEN_DIV2 items.
        // So it fills audiobuff[0] to audiobuff[BUFF_LEN_DIV2 - 1].

        // make_sound(BUFF_LEN_DIV2, BUFF_LEN_DIV4) writes 2 * BUFF_LEN_DIV4 items.
        // Starting at offset BUFF_LEN_DIV2.
        // So it fills audiobuff[BUFF_LEN_DIV2] to audiobuff[BUFF_LEN - 1].

        // This covers the entire buffer correctly!

        // So:
        // HT Callback (First Half Sent, ready to refill First Half? NO.
        // In Circular Mode:
        // HT event: First half of buffer has been transferred to peripheral. We can now safely modify the First Half.
        // TC event: Second half has been transferred. We can now safely modify the Second Half.

        // So logic matches.

        make_sound(0, BUFF_LEN_DIV4);

        // 3. Clean D-Cache to ensure DMA sees the new data
        // We modified audiobuff[0] ... audiobuff[BUFF_LEN_DIV2 - 1]
        SCB_CleanDCache_by_Addr((uint32_t*)audiobuff, BUFF_LEN_DIV2 * sizeof(uint16_t));
    }
}

//---------------------------------------------------------------------------
/**
 * @brief  Manages the DMA Complete Transfer complete interrupt.
 * @param  hi2s: I2S handle
 * @retval None
 */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->Instance == SPI2)
    {
        // TC event: Second half transferred. Refill Second Half.

        make_sound(BUFF_LEN_DIV2, BUFF_LEN_DIV4);

        // Clean D-Cache for the second half
        SCB_CleanDCache_by_Addr((uint32_t*)&audiobuff[BUFF_LEN_DIV2], BUFF_LEN_DIV2 * sizeof(uint16_t));
    }
}


//--------------------------------- toggle ON/OFF volume ------------------------------------------
void toggleSound(void)
{
	if ( ! sound )
	{
		pitchGenResetPhase();
		//EVAL_AUDIO_VolumeCtl(volume); // Not supported by PCM5102
		sound = true;
	}
	else
	{
		//EVAL_AUDIO_VolumeCtl(0);
		sound = false;
        // Ideally zero out buffer?
	}
}
//------------------------------- increase output DAC volume --------------------------------------------
void incVol(void)
{
	if (volume < MAXVOL)
	{
		volume++;
		//EVAL_AUDIO_VolumeCtl(volume);
	}
}
//-------------------------------- decrease output DAC volume ------------------------------------------
void decVol(void)
{
	if (volume > 0)
	{
		volume--;
		//EVAL_AUDIO_VolumeCtl(volume);
	}
}
