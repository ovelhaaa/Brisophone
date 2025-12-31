/**
 ******************************************************************************
 * File Name		: buttons.h
 * Author			: Xavier Halgand
 * Date				:
 * Description		:
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTONS_H
#define __BUTTONS_H


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "audio.h"
#include "soundGen.h"
#include "bargraph.h"
#include "stm32h7xx_hal.h"

/* Exported functions ------------------------------------------------------- */
void action_ButtonPressed1(void);
void action_ButtonReleased1(void);
void action_ButtonPressed2(void);
void action_ButtonReleased2(void);
void action_ButtonPressed3(void);
void action_ButtonReleased3(void);
void action_ButtonPressed4(void);
void action_ButtonReleased4(void);

// Polling function to be called from main loop
void buttons_Update(void);

#endif /* __BUTTONS_H */
