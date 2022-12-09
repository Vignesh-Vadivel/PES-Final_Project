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
 * Initialization for ON-BOARD LEDs were taken from  Alexander G Dean
 *
 */

// ******************************************************* LIBARRIES FROM THIS PROJECT ******************************************************* //
#include "LEDs.h"

void Init_RGB_LEDs(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;            // Enable clock to ports B and D //

	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;                      // Enable Green LED //
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);

	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;                       // Enable Blue LED //
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);

	PTB->PDDR |= MASK(GREEN_LED_POS);                                     // Set Port B to outputs //
	PTD->PDDR |= MASK(BLUE_LED_POS);                                      // Set Port D to outputs //
}

