/**
 ******************************************************************************
 * File Name          : bargraph.h
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
#ifndef __BARGRAPH_H__
#define __BARGRAPH_H__

#include <stdint.h>
#include "stm32h7xx_hal.h"

// Note: Physical Bargraph pins are no longer used.
// Visualization is done via SSD1306 Display.

struct bargraph {
	uint16_t state;
	uint16_t mask;
	uint8_t current;
};

void bargraphInit(void);
void bargraphWrite(uint16_t data);
void bargraphUpdate(void);

#endif /* __BARGRAPH_H__ */
