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
 * Header to Initialize ON-BOARD LEDs
 *
 */

#ifndef __LED_S__
#define __LED_S__
// ******************************************************* LIBARRIES FROM THIS PROJECT ******************************************************* //
#include "MKL25Z4.h"
#include "user_defs.h"

// ************************************************************* MACROS ************************************************************* //
#define GREEN_LED_POS      (19)	         // on port B //
#define BLUE_LED_POS       (1)		     // on port D //

/*
 * Function to initialize all RGB LEDs
 * Parameter:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void Init_RGB_LEDs();

#endif // __LED_S__
