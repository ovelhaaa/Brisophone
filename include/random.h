/**
 ******************************************************************************
 * File Name          : random.h
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdint.h>
#include <stdlib.h>
#include "CONSTANTS.h"
#include "stm32h7xx_hal.h"

void 		randomGen_init(void);
double 	frand_a_b (double a, double b);
double 	randomNum (void);

#endif
