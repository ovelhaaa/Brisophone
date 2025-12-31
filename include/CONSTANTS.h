/**
 ******************************************************************************
 * File Name          : CONSTANTS.h
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <math.h>

#define SAMPLERATE              48000
#define Fs             			((double)(SAMPLERATE))	// samplerate
#define Ts						(1.0/Fs)  // sample period
#define _2PI                    6.283185307179586476925286766559
#define _PI                    	3.1415926535897932384626433832795

#define BUFF_LEN_DIV4           64 // Reduced buffer size for lower latency on H7
#define BUFF_LEN_DIV2           (2*BUFF_LEN_DIV4)
#define BUFF_LEN                (4*BUFF_LEN_DIV4)  // Audio buffer length : count in 16bits half-words
#define VOL                     70 // initial output DAC volume
#define MAXVOL                  100 // maximal output DAC volume

#define SYSTICK_FREQ			500 // system tick interruption frequency in Hz
#define PARAM_MAX				21 // maximal parameter index, starting at 0

// On H7 we use SRAM1/2/3 or D2 domain for DMA buffers usually, but this macro was for CCM
// We will define a new one for H7 or just use attributes directly in code.
#define _RAM_D2_				__attribute__((section(".sram2")))

/************************************************************************************/
#endif  /*__CONSTANTS_H__ */
