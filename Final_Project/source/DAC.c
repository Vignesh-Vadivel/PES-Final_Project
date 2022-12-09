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
 * Few initialization parameters for DAC in this module were taken from Alexander G Dean book
 *
 */

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "DAC.h"

void Init_DAC(){
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;                                  // Enable Clock Gating register for DAC0 //
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;                                 // Enable PORTE for DAC output //

	PORTE->PCR[DAC_POS] &= ~PORT_PCR_MUX_MASK;                          // Set Analog Output to PortE Pin 30 //
	PORTE->PCR[DAC_POS] |= PORT_PCR_MUX(0);

	DAC0->C1 = 0;                                                       // Clear C1 register //
	DAC0->C2 = 0;                                                       // Clear C2 register //

	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;                  // Enable DAC //
}
