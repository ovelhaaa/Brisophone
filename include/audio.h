/**
 ******************************************************************************
 * File Name          : audio.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_H
#define __AUDIO_H


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "stm32h7xx_hal.h"
#include "soundGen.h"

/* Exported functions ------------------------------------------------------- */
void audio_init(void);
void toggleSound(void);
void incVol(void);
void decVol(void);

// DMA Callbacks
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s);

#endif /* __AUDIO_H */
