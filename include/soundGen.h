/**
 ******************************************************************************
 * File Name          : soundGen.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SOUNDGEN_H
#define __SOUNDGEN_H
/*--------------------- Global Defines ------------------------ */

#define PARTIALS_NUMBER		15 // number of computed harmonics in the additive generator
#define DECAY_FACTOR		0.99975f // initial multiplying factor for the envelope decay
#define VIBRATO_AMP			0.01f
#define VIBRATO_FREQ		4.5f

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "CONSTANTS.h"
#include "random.h"
#include "drifter.h"
#include "delay.h"
#include "chorusFD.h"
#include "sinetable.h"
#include "notesTables.h"
#include "LPfilter.h"

typedef struct
{
	uint8_t		sound; // waveform function number
	double 	amp;
	double		last_amp;
	double 	freq;
	double 	phase;
	double		phi0;
	double		decayFactor;
	double 	out;

} Oscillator;

typedef struct
{
	double 	s[9];		// summit values, s[8] = s[0]
	double 	coeff[8];	// intermediate coefficients to accelerate computing
	bool 		autom;		// random notes ?
	bool		glide;		// glissando between notes ?
	bool		chRequest;
	bool		someNotesMuted;
	uint8_t		step;
	uint8_t 	stage; // from 0 to 7
	uint8_t 	oldstage;
	double 	max;
	double 	amp;
	double 	freq;
	double 	phase;
	double 	out;

} EightSegGenerator;

/* Exported functions ------------------------------------------------------- */
void toggleVibrato(void);
void toggleSynthOut(void);
void AdditiveGen_newWaveform(void);
void transpUp(void);
void transpDown(void);
void nextScale(void);
void prevScale(void);
void incSynthOut(void);
void decSynthOut(void);
void toggleDelay(void);
void toggleFilter(void);
void toggleChorus(void);
void incDecay(void);
void decDecay(void);
void nextSound(void);
void prevSound(void);
void pitchGenInit(void);
void pitchGenChangePoints(void);
void pitchGenRequestChangePoints(void);
void pitchGen_setMaxFreq( double fr);
void automatic_or_manual(void);
void toggleGlide(void);
void muteSomeNotes(void);
void doubleTempo(void);
void halfTempo(void);
void incTempo(void);
void decTempo(void);
void incMaxFreq(void);
void decMaxFreq(void);
void pitchGenSetFreq (double f);
void pitchGenResetPhase(void);
void soundGenInit(void);
void soundGenNewWave(void);
void Synth_Init(void);
void make_sound(uint16_t offset, uint16_t len);
void OpsRandFreq(void);

#endif /* __SOUNDGEN_H */
