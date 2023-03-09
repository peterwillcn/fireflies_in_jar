/*
	File: io.h

	Contains function defintions for interacting with the IO pins on Atmel 
	microcontrollers.

	Created: 28/10/2014

	Copyright (c) 2014, Jordan Less'ard-Springett. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	
	1. 	Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.

	2. 	Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

	3. 	Neither the name of the copyright holders nor the names of
     	contributors may be used to endorse or promote products derived
     	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef IO_H
#define IO_H

#include <avr/io.h>

// The microcontroller we are using.
#define ATMEGA328

typedef enum {
	LOW = 0,
	HIGH = 1
} pin_output_t;

typedef enum {
	OUTPUT = 1,
	INPUT = 0
} pin_mode_t;

/*
	Contains the correct ports for the right microcontroller.
 */
#ifdef ATMEGA328
	typedef enum {
		PORT_B = 0,
		PORT_C = 1,
		PORT_D = 2,
		_PORT_LAST = 3
	} port_t;
#elif defined(ATTINY85)
	typedef enum {
		PORT_B = 0,
		_PORT_LAST = 1
	} port_t;
#else
	typedef enum {
		_PORT_LAST = 0
	} port_T;
#endif



/**********************************************************************************
 * If the pin is configured as a output pin and HIGH(1) is written to it then the 
 * port pin is driven high. IF the pin is configured as a input pin then the 
 * pull-up resistors are activated.
 * 
 * @param port   			The port the pin belongs to.
 * @param pin    			The pin on the port.
 * @param output 			HIGH(1) or LOW(0).
 * 
 *********************************************************************************/
void io_write(unsigned int port, unsigned int pin, pin_output_t output);

/**********************************************************************************
 * Reads the value of the pin
 * 
 * @param port   			The port the pin belongs to.
 * @param pin    			The pin on the port.
 * @param output 			HIGH(1) or LOW(0).
 * 
 *********************************************************************************/
pin_output_t io_read(unsigned int port, unsigned int pin);

/**********************************************************************************
 * Configures the pin to the desired pin mode as set by 'mode'.
 * 
 * @param port   			The port the pin belongs to.
 * @param pin    			The pin on the port.
 * @param mode 				OUTPUT(1) or INPUT(0)
 * 
 *********************************************************************************/
void io_set_mode(unsigned int port, unsigned int pin, pin_mode_t mode);

#endif