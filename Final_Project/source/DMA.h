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
 * This header file has function prototypes for Direct Memory Access
 *
 */
#ifndef DMA_H
#define DMA_H

// ************************************************************* MACROS ************************************************************* //
#define NUMBER_OF_TONES      12

/*
 * Function to Initialize DMA for DAC input
 * Parameters:
 *     int      => Frequency index
 *     uint8_t  => Accelerometer status
 *
 * Return Type:
 *     void
 *
 * */
void Init_DMA_For_Playback(int, uint8_t);

/*
 * Function to start DMA by copying Source and Destination address
 * Parameters:
 *     void
 *
 * Return Type:
 *     void
 *
 * */
void Start_DMA_Playback(void);

/*
 * Function to get samples for all frequencies with Maximum volume
 * Parameters:
 *     int => Array Index representing the frequency to be sampled
 *
 * Return Type:
 *     void
 *
 * */
void Init_Tones(int);

/*
 * Function to get samples for all frequencies with Minimum volume
 * Parameters:
 *     int => Array Index representing the frequency to be sampled
 *
 * Return Type:
 *     void
 *
 * */
void Init_Tones_Less_Sound(int);

#endif
