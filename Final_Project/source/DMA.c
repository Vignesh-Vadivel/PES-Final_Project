/*
 *
 * Author     : Vignesh Vadivel
 * E-Mail     : viva9969@colorado.edu
 * Subject    : Principles of Embedded Software
 * Date       : 06-Dec-2022
 * University : University of Colorado at Boulder
 * Assignment : Final Project
 *
 *
 * This module would initialize DMA and required interrupts for the DMA and also fill the initial values for 20 different tones with different volumes
 * DMA initialization part of the module were referred from the Alexander G Dean book
 * And the rest other functions and methods in this module were written by Vignesh Vadivel.
 *
 *
 */

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// ******************************************************* LIBARRIES FOR KL25Z ******************************************************* //
#include <MKL25Z4.h>

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "timers.h"
#include "DMA.h"
#include "fp_trig.h"

// ************************************************************* MACROS ************************************************************* //
#define C4                      262                                                                            // C4 to B4 are to generate Happy Birthday tone with KL25Z //
#define C4_1                    277
#define D4                      294
#define D4_1                    311
#define E4                      330
#define F4                      349
#define F4_1                    370
#define G4                      392
#define G4_1                    415
#define A4                      440
#define A4_1                    466
#define B4                      494
#define MAX_DAC_CODE            4095
#define DMA_SSIZE               2
#define TPM_OVRFLOW             54
#define INTEGER_WORD_SIZE       4
#define REDUCE_VOLUME           4
#define HAPPY_BIRTHDAY_SAMPLES  20

// ******************************************************* GLOBAL VARIABLES ******************************************************* //
// ************************* Array name ending with _4 are used to store the samples for lower volume ************************* //
uint16_t Freq_C4[(DAC_SAMPLING_FREQUENCY/C4)+1], Freq_C4_4[(DAC_SAMPLING_FREQUENCY/C4)+1];                     // Buffer to store samples for 262 frequency for both higher and lower volume respectively //
uint16_t Freq_C4_1[(DAC_SAMPLING_FREQUENCY/C4_1)+1], Freq_C4_1_4[(DAC_SAMPLING_FREQUENCY/C4_1)+1];             // Buffer to store samples for 277 frequency for both higher and lower volume respectively //
uint16_t Freq_D4[(DAC_SAMPLING_FREQUENCY/D4)+1],Freq_D4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                      // Buffer to store samples for 294 frequency for both higher and lower volume respectively //
uint16_t Freq_D4_1[(DAC_SAMPLING_FREQUENCY/D4_1)+1], Freq_D4_1_4[(DAC_SAMPLING_FREQUENCY/D4)+1];               // Buffer to store samples for 311 frequency for both higher and lower volume respectively //
uint16_t Freq_E4[(DAC_SAMPLING_FREQUENCY/E4)+1], Freq_E4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                     // Buffer to store samples for 330 frequency for both higher and lower volume respectively //
uint16_t Freq_F4[(DAC_SAMPLING_FREQUENCY/F4)+1], Freq_F4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                     // Buffer to store samples for 349 frequency for both higher and lower volume respectively //
uint16_t Freq_F4_1[(DAC_SAMPLING_FREQUENCY/F4_1)+1], Freq_F4_1_4[(DAC_SAMPLING_FREQUENCY/D4)+1];               // Buffer to store samples for 370 frequency for both higher and lower volume respectively //
uint16_t Freq_G4[(DAC_SAMPLING_FREQUENCY/G4)+1], Freq_G4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                     // Buffer to store samples for 392 frequency for both higher and lower volume respectively //
uint16_t Freq_G4_1[(DAC_SAMPLING_FREQUENCY/G4_1)+1], Freq_G4_1_4[(DAC_SAMPLING_FREQUENCY/D4)+1];               // Buffer to store samples for 415 frequency for both higher and lower volume respectively //
uint16_t Freq_A4[(DAC_SAMPLING_FREQUENCY/A4)+1], Freq_A4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                     // Buffer to store samples for 440 frequency for both higher and lower volume respectively //
uint16_t Freq_A4_1[(DAC_SAMPLING_FREQUENCY/A4_1)+1], Freq_A4_1_4[(DAC_SAMPLING_FREQUENCY/D4)+1];               // Buffer to store samples for 466 frequency for both higher and lower volume respectively //
uint16_t Freq_B4[(DAC_SAMPLING_FREQUENCY/B4)+1], Freq_B4_4[(DAC_SAMPLING_FREQUENCY/D4)+1];                     // Buffer to store samples for 494 frequency for both higher and lower volume respectively //

uint16_t ToneFreq[NUMBER_OF_TONES] = {C4, C4_1, D4, D4_1, E4, F4, F4_1, G4, G4_1, A4, A4_1, B4};               // Array to store all frequency value //
uint16_t *Tones[NUMBER_OF_TONES] = {Freq_C4, Freq_C4_1, Freq_D4, Freq_D4_1, Freq_E4, Freq_F4, Freq_F4_1, Freq_G4, Freq_G4_1, Freq_A4, Freq_A4_1, Freq_B4};        // Array to store samples of all frequencies for higher volume //
uint16_t *MyTones[HAPPY_BIRTHDAY_SAMPLES] = {Freq_C4, Freq_D4, Freq_C4, Freq_F4, Freq_E4, Freq_C4, Freq_D4, Freq_C4, Freq_G4, Freq_F4, Freq_C4, Freq_A4, Freq_F4, Freq_E4, Freq_D4, Freq_A4_1, Freq_A4, Freq_F4, Freq_G4, Freq_F4};   // Order in which data would be sampled to get the required tone with high volume //

uint16_t samplingToneFreq[20] = {C4, D4, C4, F4, E4, C4, D4, C4, G4, F4, C4, A4, F4, E4, D4, A4_1, A4, F4, G4, F4};     // Order in which the Happy birthday song would be played, also used to get Bytes required for DMA in order //
uint16_t *Tones_Less_Sound[NUMBER_OF_TONES] = {Freq_C4_4, Freq_C4_1_4, Freq_D4_4, Freq_D4_1_4, Freq_E4_4, Freq_F4_4, Freq_F4_1_4, Freq_G4_4, Freq_G4_1_4, Freq_A4_4, Freq_A4_1_4, Freq_B4_4};        // Array to store samples of all frequencies for lower volume //
uint16_t *MyTones_Less_Sound[HAPPY_BIRTHDAY_SAMPLES] = {Freq_C4_4, Freq_D4_4, Freq_C4_4, Freq_F4_4, Freq_E4_4, Freq_C4_4, Freq_D4_4, Freq_C4_4, Freq_G4_4, Freq_F4_4, Freq_C4_4, Freq_A4_4, Freq_F4_4, Freq_E4_4, Freq_D4_4, Freq_A4_1_4, Freq_A4_4, Freq_F4_4, Freq_G4_4, Freq_F4_4};  // Order in which data would be sampled to get the required tone with low volume //

uint16_t *Reload_DMA_Source=0;                                                             // Pointer used to load a new tone //
uint32_t Reload_DMA_Byte_Count=0;                                                          // Variable used to reload Byte count for a particular frequency //

void Init_DMA_For_Playback(int i, uint8_t accelerometerData) {
	// Save reload information
	if (accelerometerData)
	    Reload_DMA_Source = MyTones[i];                                                    // Array with the High Volume samples //
	else
		Reload_DMA_Source = MyTones_Less_Sound[i];                                         // Array with the low Volume samples //
	Reload_DMA_Byte_Count = (DAC_SAMPLING_FREQUENCY/samplingToneFreq[i])*2;                // Number of bytes to copy //

	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;                                                      // Gate clocks to DMA //
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                                                   // Gate clocks to DMAMUX //

	DMAMUX0->CHCFG[0] = 0;                                                                 // Disable DMA channel to allow configuration //

	// Generate DMA interrupt when done
	// Increment source, transfer words (16 bits)
	// Enable peripheral request
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK |
					   DMA_DCR_SSIZE(DMA_SSIZE) | DMA_DCR_DSIZE(DMA_SSIZE) |
					   DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

	// Configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(TPM_OVRFLOW);                                   // Enable DMA MUX channel with TPM0 overflow as trigger //
}

void Start_DMA_Playback() {
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);                           // Initialize Source Address //
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));                           // Initialize Destination address //
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_Count);                          // Byte Count //
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;                                         // Clear Done flag //
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;                                            // set enable flag //

}

void DMA0_IRQHandler(void) {
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;                                          // Clear done flag //
	Start_DMA_Playback();                                                                   // Start the next DMA playback cycle //
}

void Init_Tones(int freq_index){
    for (int i=0; i<((DAC_SAMPLING_FREQUENCY/ToneFreq[freq_index])+1); i++){
    	Tones[freq_index][i] = fp_sin((TWO_PI*i)/(DAC_SAMPLING_FREQUENCY/ToneFreq[freq_index])) + TRIG_SCALE_FACTOR;             // Calculate samples for all frequencies with higher volume //
    }
}

void Init_Tones_Less_Sound(int freq_index){
    for (int i=0; i<((DAC_SAMPLING_FREQUENCY/ToneFreq[freq_index])+1); i++){
    	Tones_Less_Sound[freq_index][i] = fp_sin((TWO_PI*i)/(DAC_SAMPLING_FREQUENCY/ToneFreq[freq_index])) + TRIG_SCALE_FACTOR;  // Calculate samples for all frequencies //
    	Tones_Less_Sound[freq_index][i] = Tones_Less_Sound[freq_index][i]/REDUCE_VOLUME;                                         // Volume reduction //
    }
}
