/*
 *
 * Author     : Vignesh Vadivel
 * E-Mail     : viva9969@colorado.edu
 * Subject    : Principles of Embedded Software
 * Date       : 06-Dec-2022
 * University : University of Colorado at Boulder
 * Assignment : Final Project
 *
 * Reference : Alexander G Dean
 *
 * This header file has function prototypes and Macros needed to read data from Accelerometer
 *
 */

#ifndef MMA8451_H
#define MMA8451_H

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <stdint.h>

// ************************************************************* MACROS ************************************************************* //
#define MMA_ADDR       0x3A
#define REG_XHI        0x01
#define REG_XLO        0x02
#define REG_YHI        0x03
#define REG_YLO        0x04
#define REG_ZHI	       0x05
#define REG_ZLO        0x06
#define REG_WHOAMI     0x0D
#define REG_CTRL1      0x2A
#define REG_CTRL4      0x2D
#define WHOAMI         0x1A

#define COUNTS_PER_G  (4096.0)
#define M_PI          (3.14159265)

/*
 * Function needed to initialize MMA Accelerometer
 * Parameters:
 *      None
 *
 * Return Type:
 *      int => Returns 1 - FUNCTION_SUCCESS
 *
 */
int Init_mma(void);

/*
 * Function to read 6 bytes of data from the accelerometer and store it in the global variables
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void read_full_xyz(void);

/*
 * Function to read x,y,z values from the accelerometer and store it in the global variables
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void read_xyz(void);

/*
 * Function used to convert x,y,z values to roll and pitch
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void convert_xyz_to_roll_pitch();

// ********************************************************** EXTERN VARIABLES ********************************************************** //
extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;

#endif
