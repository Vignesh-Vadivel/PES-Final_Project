/*
 *
 * Author     : Vignesh Vadivel
 * E-Mail     : viva9969@colorado.edu
 * Subject    : Principles of Embedded Software
 * Date       : 06-Dec-2022
 * University : University of Colorado at Boulder
 * Assignment : Final Project
 *
 * While systick Initialization was referred from Alexander G Dean, rest other functions in this module were written by Vignesh Vadivel
 *
 */

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "systick.h"

volatile ticktime_t overallTime, elapsedTime;                          // Global variables to keep track of OverAll and Elapsed time //
volatile uint8_t ind=0;                                                // To keep track of frequencies of different tones //

// ********************************************************* MACROS ********************************************************* //
#define HALF_SECOND_DELAY        10
#define NUMBER_OF_FREQUENCIES    20

/*
 * FUNCTION which would be called every time, whenever SysTick Interrupt is invoked
 * This is one of the callback functions.
 *
 * Input Parameters : None
 * Return Type      : void
 * The function returns nothing.
 */
void SysTick_Handler(){                                                // The function calls once in every 50 milliseconds //
	++overallTime;                                                     // Update the overall time for every 50 milliseconds interrupt //
    ++elapsedTime;                                                     // Update the elapsed time for every 50 milliseconds interrupt //
	if (elapsedTime>=HALF_SECOND_DELAY){
	    ind++;                                                         // Update frequency after every second //
	    elapsedTime = 0;                                               // Reset elapsed Time //
	    if (ind>=NUMBER_OF_FREQUENCIES){                               // Reset the index //
		   ind=0;
	    }
	}
}

void SetIndex(){
	ind = 0;                                                           // Set Index to zero //
}

uint8_t getCurrentFreq(){
	return ind;                                                        // Return current frequency //
}

void Init_SysTick(){                                                   // Initialize SysTick //
    SysTick_Config(INTERNAL_CLOCK_FREQUENCY/FREQUENCY_DIVISION);       // Makes the SysTick interrupt to trigger for every 50 milliseconds //
 	overallTime = 0; elapsedTime = 0;                                  // Initialize global variables for the first time //
}
