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
 * Reference : Alexander G Dean book
 * This file has header for all functions used for I2C communication
 *
 */

#ifndef __I2C__
#define __I2C__

// ******************************************************* STANDARD C LIBARRIES ******************************************************* //
#include <stdint.h>

// ************************************************************* MACROS ************************************************************* //
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK
#define I2C_TRAN	    I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK
#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 		i2c_wait();
#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK             I2C0->C1 &= ~I2C_C1_TXAK_MASK

/*
 * Function to initialize I2C Communication
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void I2C_init(void);

/*
 * Function to start I2C Communication
 * Parameters:
 *     None
 *
 * Return Type:
 *     void
 *
 */
void i2c_start(void);

/*
 * Function to setup the read operation
 * Parameters:
 *     uint8_t => Device address
 *     uint8_t => Register address
 *
 * Return Type:
 *     void
 *
 */
void i2c_read_setup(uint8_t dev, uint8_t address);

/*
 * Function to do repeated read from I2C bus
 * Parameters:
 *     uint8_t => check previous read
 *
 * Return Type:
 *     uint8_t => Data read from I2C bus
 *
 */
uint8_t i2c_repeated_read(uint8_t);

/*
 * Function to Read a Byte
 * Parameters:
 *     uint8_t =>  Device Address
 *     uint8_t =>  Register address
 *
 * Return Type:
 *     uint8_t =>  Data read from I2C bus
 *
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/*
 * Function to Write a Byte
 * Parameters:
 *     uint8_t =>  Device Address
 *     uint8_t =>  Register address
 *     uint8_t =>  data to be written
 *
 * Return Type:
 *     void
 *
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif // __I2C__
