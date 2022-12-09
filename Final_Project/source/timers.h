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
 * Few initialization parameters in this module were taken from Alexander G Dean book
 * This header file has all functions needed to initialize TPM module
 *
 */
#ifndef TIMERS_H
#define TIMERS_H

// ******************************************************* LIBARRIES FOR KL25Z ******************************************************* //
#include "MKL25Z4.h"

// ************************************************************** MACROS ************************************************************* //
#define DAC_SAMPLING_FREQUENCY    48000
/*
 * Function to initialize TPM
 * Parameters:
 *     void
 *
 * Return Type:
 *     None
 *
 * */
void Init_TPM(void);

/*
 * Function to start TPM
 * Parameters:
 *     void
 *
 * Return Type:
 *     None
 *
 * */
void Start_TPM(void);


#endif
