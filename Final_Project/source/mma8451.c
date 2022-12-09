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
 * This file has functions which reads data from the accelerometer registers and used for further processing
 *
 */

// ******************************************************* LIBARRIES FOR KL25Z ******************************************************* //
#include <MKL25Z4.H>

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include "mma8451.h"
#include "i2c.h"

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <math.h>

// ************************************************************* MACROS ************************************************************* //
#define REPEATED_READ    5
#define TOTAL_AXIS       3
#define ALIGN_BITS       4

int16_t acc_X=0, acc_Y=0, acc_Z=0;                    // To store X, Y, Z values //
float roll=0.0, pitch=0.0;                            // To store roll, pitch values //

extern uint32_t DATA_READY;                           // MMA data ready //

int Init_mma()                                        // i2c has to already be enabled //
{
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);        // Set active mode, 14 bit samples and 800 Hz ODR //
	return 1;
}

void read_full_xyz()
{
	int i;
	uint8_t data[6];                                  // To store 6 bytes data read from the accelerometer //
	int16_t temp[3];                                  // To store X, Y, Z values //

	i2c_start();                                      // Start I2C //
	i2c_read_setup(MMA_ADDR , REG_XHI);               // Setup I2C //

	for( i=0; i<REPEATED_READ; i++)	{
		data[i] = i2c_repeated_read(0);               // Read five bytes in repeated mode //
	}

	data[i] = i2c_repeated_read(1);                   // Read last byte ending repeated mode //

	for ( i=0; i<TOTAL_AXIS; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);    // Store X, Y, Z values //
	}

	acc_X = temp[0]/ALIGN_BITS;                       // Align for 14 bits //
	acc_Y = temp[1]/ALIGN_BITS;                       // Align for 14 bits //
	acc_Z = temp[2]/ALIGN_BITS;                       // Align for 14 bits //
}

void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);     // Read X //
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);     // Read Y //
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);     // Read Z //

}

void convert_xyz_to_roll_pitch() {
	float ax = acc_X/COUNTS_PER_G,
				ay = acc_Y/COUNTS_PER_G,
				az = acc_Z/COUNTS_PER_G;

	roll = atan2(ay, az)*180/M_PI;                         // Calculate  ROLL //
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;       // Calculate  PITCH //
}
