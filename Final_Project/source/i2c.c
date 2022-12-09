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
 * Few functions in this module were taken from Alexander G Dean book and Vignesh Vadivel has understood the working of I2C driver
 * This file has all functions and API's needed to initialize and utilize I2C Communication
 *
 *
 */

// *************************************************** LIBARRIES FROM THIS PROJECT *************************************************** //
#include <MKL25Z4.H>
#include "i2c.h"

// ******************************************************* GLOBAL VARIABLES ******************************************************* //
int lock_detect=0;
int i2c_lock=0;

// ************************************************************* MACROS ************************************************************* //
#define I2C_PIN_1 24
#define I2C_PIN_2 25

void I2C_init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;                    // Clock i2c peripheral and port E //
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	PORTE->PCR[I2C_PIN_1] |= PORT_PCR_MUX(5);             // set pins to I2C function //
	PORTE->PCR[I2C_PIN_2] |= PORT_PCR_MUX(5);

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));
	I2C0->C1 |= (I2C_C1_IICEN_MASK);                      // enable i2c and set to master mode //

	I2C0->C2 |= (I2C_C2_HDRS_MASK);                       // Select high drive mode //
}

void i2c_busy(void){

	lock_detect=0;                                        // Start Signal //
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;                                          // Start I2C //
	I2C0->C1 |=  I2C_C1_IICEN_MASK;

	I2C0->C1 |= I2C_C1_MST_MASK;                          // set MASTER mode //
	I2C0->C1 |= I2C_C1_TX_MASK;                           // Set transmit (TX) mode //
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {          // Wait interrupt //
	}
	I2C0->S |= I2C_S_IICIF_MASK;                          // clear interrupt bit //

	I2C0->S |= I2C_S_ARBL_MASK;                           // Clear arbitration error flag //

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;						  // Send start //
	I2C0->C1 |= I2C_C1_TX_MASK;                           // Set transmit (TX) mode //
	I2C0->C1 |= I2C_C1_MST_MASK;                          // START signal generated //

	I2C0->C1 |= I2C_C1_IICEN_MASK;                        // Wait until start is send //

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;                       // Send stop //
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK;                         // set SLAVE mode //
	I2C0->C1 &= ~I2C_C1_TX_MASK;                          // Set Rx //
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->S |= I2C_S_IICIF_MASK;						  // Clear interrupt flag //
	I2C0->S |= I2C_S_ARBL_MASK;                           // Clear arbitration error //
	lock_detect=0;
	i2c_lock=1;
}

void i2c_wait(void) {
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200)) {
		lock_detect++;
	}
	if (lock_detect >= 200)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}

void i2c_start()
{
	I2C_TRAN;							                 // set to transmit mode //
	I2C_M_START;					                     // send start  //
}

void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;			                             // send dev address //
	I2C_WAIT							                 // wait for completion //

	I2C0->D =  address;		                             // send read address	//
	I2C_WAIT							                 // wait for completion //

	I2C_M_RSTART;				                         // repeated start //
	I2C0->D = (dev|0x1);	                             // send dev address (read)	//
	I2C_WAIT							                 // wait for completion //

	I2C_REC;						                     // set to receive mode //

}

uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;
	lock_detect = 0;
	if(isLastRead)	{
		NACK;								             // set NACK after read	//
	} else	{
		ACK;	             							 // ACK after read	//
	}

	data = I2C0->D;				                         // dummy read  //
	I2C_WAIT							                 // wait for completion //
	if(isLastRead)	{
		I2C_M_STOP;					                     // send stop	//
	}
	data = I2C0->D;				                         // read data	//
	return  data;
}

uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;							                 // set to transmit mode //
	I2C_M_START;					                     // send start //
	I2C0->D = dev;			                             // send dev address //
	I2C_WAIT							                 // wait for completion //

	I2C0->D =  address;		                             // send read address	//
	I2C_WAIT							                 // wait for completion //

	I2C_M_RSTART;				                         // repeated start //
	I2C0->D = (dev|0x1);	                             // send dev address (read)	//
	I2C_WAIT							                 // wait for completion //

	I2C_REC;						                     // set to recieve mode //
	NACK;									             // set NACK after read	//

	data = I2C0->D;					                     // dummy read //
	I2C_WAIT								             // wait for completion //

	I2C_M_STOP;							                 // send stop	//
	data = I2C0->D;					                     // read data	//
	return data;
}

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	I2C_TRAN;							                 // set to transmit mode //
	I2C_M_START;					                     // send start	//
	I2C0->D = dev;			                             // send dev address //
	I2C_WAIT						                     // wait for ack //

	I2C0->D =  address;		                             // send write address //
	I2C_WAIT                                             // wait for completion //

	I2C0->D = data;				                         // send data	//
	I2C_WAIT                                             // wait for completion //
	I2C_M_STOP;                                          // I2C Stop //
}
