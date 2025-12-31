/**
 ******************************************************************************
 * File Name			: main.h
 * Author				: Xavier Halgand
 * Date					:
 * Description			:
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include "CONSTANTS.h"
#include "random.h"
#include "soundGen.h"
#include "delay.h"
#include "chorusFD.h"
#include "drifter.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void toggleSound(void);

#endif /* __MAIN_H */
