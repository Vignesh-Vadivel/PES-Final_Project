/*
 *
 * Author     : Vignesh Vadivel
 * E-Mail     : viva9969@colorado.edu
 * Subject    : Principles of Embedded Software
 * Date       : 06-Dec-2022
 * University : University of Colorado at Boulder
 * Assignment : Final Project
 *
 * MAIN Function
 *  => To Initialize all peripherals
 *  => Check for accelerometer Input for every five seconds
 *  => To start DMA copy every 500 milliseconds
 *
 *
 *  This File was fully written by Vignesh Vadivel
 *
 */

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <stdio.h>

// ******************************************************* LIBARRIES FOR KL25Z ******************************************************* //
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "DMA.h"
#include "timers.h"
#include "fp_trig.h"
#include "systick.h"
#include "user_defs.h"
#include "DAC.h"
#include "i2c.h"
#include "mma8451.h"
#include "LEDs.h"

// ************************************************************* MACROS ************************************************************* //
#define ROLL_THRESHOLD    50
#define PITCH_THRESHOLD   50

/*
 * Function to sample all the input frequencies with maximum and lower volumes.
 * Parameters:
 *     int*  => Pointer to an integer array which stores number of samples for all input frequencies
 *
 * Return Type:
 *     void
 *
 */
void tone_to_samples(){
	for (int i=0; i<NUMBER_OF_TONES; i++){
        Init_Tones(i);
	}
	for (int i=0; i<NUMBER_OF_TONES; i++){
	    Init_Tones_Less_Sound(i);
	}
}

int main(void) {
    /* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    tone_to_samples();                                                                          // Store Number of samples for all frequencies //
    I2C_init();						                             							    // Initialize I2C //
    Init_RGB_LEDs();                                                                            // Initialize RGB LEDs //
    Init_mma();                                                                                 // Initialize on-board Accelerometer //
    Init_DAC();                                                                                 // Initialize DAC //
    Init_DMA_For_Playback(0,0);                                                                 // Initialize DMA //
    Init_TPM();                                                                                 // Initialize TPM Timer //
    Start_TPM();                                                                                // Start TPM Timer //
    Init_SysTick();                                                                             // Initialize Systick //
    SetIndex();                                                                                 // Initially Set Index to Zero in Systick handler //
    Start_DMA_Playback();                                                                       // Start DMA Playback //
    uint8_t prev_frequency = 0;                                                                 // Previous Frequency //
	uint8_t currentFreq=0;                                                                      // Current Frequency //
    uint8_t accelerometerFlag=0;                                                                // Check accelerometer status //
	while(1){
    	if (prev_frequency != getCurrentFreq()){                                                // Check if previous and current frequency are same //
    		read_full_xyz();                                                                    // Read current orientation of the board //
    		convert_xyz_to_roll_pitch();                                                        // Convert the orientation into the pitch //
    		if (roll > ROLL_THRESHOLD || pitch > PITCH_THRESHOLD){                              // Check for the current orientation //
    			accelerometerFlag = 1;                                                          // Set the flag //
    			PTB->PCOR = MASK(GREEN_LED_POS);                                                // Set Green color //
    			PTD->PSOR = MASK(BLUE_LED_POS);                                                 // Reset Blue color //
    		}
    		else{
    			accelerometerFlag = 0;                                                          // Reset the flag //
    			PTD->PCOR = MASK(BLUE_LED_POS);                                                 // Set Blue color //
    			PTB->PSOR = MASK(GREEN_LED_POS);                                                // Reset Green Color //
    		}
            Init_DMA_For_Playback(getCurrentFreq(), accelerometerFlag);                         // Initialize DMA again with new frequency index and the accelerometer status //
            Start_DMA_Playback();                                                               // Start DMA copy //

    		currentFreq = getCurrentFreq();                                                     // Get current Frequency //
        	prev_frequency = currentFreq;                                                       // Update the previous frequency //
   	}
    }
    return 0 ;
}
