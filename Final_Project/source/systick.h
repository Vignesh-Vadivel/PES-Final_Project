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
 *
 * HEADER FILE THAT IS RESPONSIBLE FOR ALL THE SYSTICK RELATED FUNCTIONS
 */

#ifndef __MY_SYSTICK_HANDLER_HEADER_
#define __MY_SYSTICK_HANDLER_HEADER_

// ******************************************************* LIBARRIES FROM THIS PROJECT ******************************************************* //
#include "MKL25Z4.h"
#include "DMA.h"

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <stdio.h>

// ******************************************************* MACROS ******************************************************* //
#define INTERNAL_CLOCK_FREQUENCY  48000000                                     // SystemCoreClock
#define FREQUENCY_DIVISION        20                                           // Required Frequency division for 50 milliseconds
#define TIME_RESOLUTION           50                                           // Resolution in which division would happe
#define SYSTICK_FREQUENCY         INTERNAL_CLOCK_FREQUENCY/FREQUENCY_DIVISION
typedef uint32_t ticktime_t;                                                   // Used to calculate the time, whenever SysTick interrupt happens

/*
 *
 * FUNCTION used to Enable and Configure the SysTick Timer
 *
 * Parameters :
 *     void
 *
 * Return Type :
 *     void
 * The function returns nothing.
 *
 */
void Init_SysTick();

/*
 * Function which would return the index of current frequency
 * Parameter:
 *     None
 *
 * Return Type:
 *     int => Index of current frequency
 *
 * */
uint8_t getCurrentFreq();

/*
 * Function to set the frequency index to zero
 * Parameter:
 *     None
 *
 * Return Type:
 *     void
 * */
void SetIndex();
#endif // __MY_SYSTICK_HANDLER_HEADER_
