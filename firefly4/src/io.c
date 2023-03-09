/*
	File: io.c

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

#include "io.h"

/**********************************************************************************
 * IO registers.
 * 
 */
#ifdef ATMEGA328
	volatile static unsigned char* _ports[] = {
		&PORTB, &PORTC, &PORTD
	};

	volatile static unsigned char* _ddr[] = {
		&DDRB, &DDRC, &DDRD
	};
#elif defined(ATTINY85)
	volatile static unsigned char* _ports[] = {
		&PORTB
	};

	volatile static unsigned char* _ddr[] = {
		&DDRB
	};
#else
	volatile static unsigned char* _ports[] = { };

	volatile static unsigned char* _ddr[] = { };
#endif
	

//////////////////////////////////////////////////////////////////////////
void io_write(unsigned int port, unsigned int pin, pin_output_t output)
{
	// port doesn't exist
	if(!(port < _PORT_LAST)) {
		return;
	}

	if(output == HIGH) {
		*_ports[port] |= (1 << pin);
	} else {
		*_ports[port] &= ~(1 << pin);
	}
}

//////////////////////////////////////////////////////////////////////////
pin_output_t io_read(unsigned int port, unsigned int pin)
{
	// port doesn't exist
	if(!(port < _PORT_LAST)) {
		return LOW;
	}

	return (*_ports[port] & (1 << pin)) ? HIGH : LOW;
}

//////////////////////////////////////////////////////////////////////////
void io_set_mode(unsigned int port, unsigned int pin, pin_mode_t mode)
{
	// port doesn't exist
	if(!(port < _PORT_LAST)) {
		return;
	}

	if(mode == OUTPUT) {
		*_ddr[port] |= (1 << pin);
	} else {
		*_ddr[port] &= ~(1 << pin);
	}
}