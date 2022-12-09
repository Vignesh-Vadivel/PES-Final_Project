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
 * Initialization for TPM were taken from  Alexander G Dean
 *
 */

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "timers.h"

// ******************************************************* LIBARRIES FOR KL25Z ******************************************************* //
#include "MKL25Z4.h"

// ************************************************************* MACROS ************************************************************* //
#define SYSTEM_CORE_FREQUENCY     48000000

void Init_TPM()
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;                                        // Turn on clock to TPM0 //

	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);           // Set clock source for tpm //

	TPM0->SC = 0;                                                             // Disable TPM0 //

	TPM0->MOD = TPM_MOD_MOD(SYSTEM_CORE_FREQUENCY/DAC_SAMPLING_FREQUENCY);    // Mod for TPM0 //

	TPM0->SC = (TPM_SC_DMA_MASK | TPM_SC_PS(0));                              // Set Prescaler as 1 for TPM0 and enable TPM Mask //

}

void Start_TPM(void) {
	TPM0->SC |= TPM_SC_CMOD(1);                                               // Enable counter //
}

