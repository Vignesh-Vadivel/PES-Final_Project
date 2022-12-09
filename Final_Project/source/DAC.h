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
 * This header file has function prototypes to initialize the DAC module
 *
 */
#ifndef DAC_H
#define DAC_H

// ****************************************************** LIBARRIES FOR KL25Z ****************************************************** //
#include "MKL25Z4.h"

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "user_defs.h"

/*
 * Function to initialize DAC in KL25Z
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 * */
void Init_DAC();
#endif // DAC_H
