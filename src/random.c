/**
 ******************************************************************************
 * File Name          : random.c
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
#include "random.h"

RNG_HandleTypeDef hrng;

/*----------------------------------------------------------------------------------------------*/
void 	randomGen_init(void)
{
	/* Enable RNG clock source */
	__HAL_RCC_RNG_CLK_ENABLE();

	/* RNG Peripheral enable */
    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);

    // Seed standard rand()
    uint32_t seed;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &seed) == HAL_OK) {
        srand(seed);
    } else {
        srand(12345);
    }
}

/*----------------------------------------------------------------------------------------------*/
/*
   Returns a random float in [a, b]
*/
double 	frand_a_b (double a, double b)
{
	return ( rand()/(double)RAND_MAX ) * (b-a) + a ;
}

/*----------------------------------------------------------------------------------------------*/
double 	randomNum (void)
{
	double random = 1.0;
    uint32_t val;

    if (HAL_RNG_GenerateRandomNumber(&hrng, &val) == HAL_OK) {
        random = (double) (val / 4294967294.0);
    } else {
        random = (double) rand() / (double) RAND_MAX;
    }

	return random;
}
