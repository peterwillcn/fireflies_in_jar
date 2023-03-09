/* Firefly Matrix Controller
 * Adam Greig, October 2008
 *
 * CC BY-SA-NC 3.0
 *
 * Hardware:	12 LEDs connected between pins PB0 to PB4 of an ATtiny45
 * 		with one LED in each direction. Six LEDs connect PB0 to
 *		PB1, 2, 3 and 4 while six LEDs connect PB1 to PB2, 3 and 4.
 */

#define F_CPU 960000UL

#include "binary.h"

#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h>

//DDR state for each firefly
char firefly_ddr[14] = {
	B00011,
	B00011,
	B00101,
	B00101,
	B01001,
	B01001,
	B10001,
	B10001,
	B00110,
	B00110,
	B01010,
	B01010,
	B10010,
	B10010
};

//Output state for each firefly
char firefly_port[14] = {
	B00001,
	B00010,
	B00001,
	B00100,
	B00001,
	B01000,
	B00001,
	B10000,
	B00010,
	B00100,
	B00010,
	B01000,
	B00010,
	B10000
};

//Intensity points of a firefly pulse (from real data)
char firefly_pulse[20] = {
	0,16,25,35,55,65,85,98,101,101,93,84,70,60,50,40,35,25,16,11
};

//theoretical other pulses that could be used
//char firefly_pulse_med[32] = {
//	0,1,2,5,10,13,20,27,38,58,82,105,125,146,157,163,164,156,144,135,121,100,86,70,60,47,31,22,16,10,5,0
//};

//char firefly_pulse_high[32] = {
//	0,4,11,16,24,34,59,93,123,162,202,225,238,255,238,225,207,175,150,128,99,79,64,49,35,25,18,14,12,10,5,0
//};


char port;

//Pulse selected firefly using hardware PWM
void light_firefly( short int firefly ) {
	if( firefly > 13 || firefly < 0 ) return;
	
	DDRB	= firefly_ddr[ firefly ];
	PORTB	= firefly_port[ firefly];
	//DDRB	= (1<<PB0) | (1<<PB1);
	//PORTB	= (0<<PB0) | (0<<PB1);
	
	if( DDRB & B01 ) {
		if( PORTB & B01 )
			TCCR0A	= (1<<COM0A1) | (0<<COM0A0) | (1<<WGM00) | (1<<WGM01);
		else
			TCCR0A	= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM00) | (1<<WGM01);
	} else {
		if( PORTB & B10 )
			TCCR0A	= (1<<COM0B1) | (0<<COM0B0) | (1<<WGM00) | (1<<WGM01);
		else
			TCCR0A	= (1<<COM0B1) | (1<<COM0B0) | (1<<WGM00) | (1<<WGM01);
	}
	
	TCCR0B	= (1<<CS00);
	
	if( DDRB & B01 )
		OCR0A	= 0;
	else
		OCR0B	= 0;
	
	for( unsigned char i = 0; i < 20; i++ ) {
		
		if( DDRB & B01 )
			OCR0A = firefly_pulse[i];
		else
			OCR0B = firefly_pulse[i];
		
		_delay_ms( 30 );
	}
	
	if( DDRB & B01 )
		OCR0A	= 0;
	else
		OCR0B	= 0;
	
	TCCR0A	= (0<<COM0A1) | (0<<COM0A0) | (0<<WGM00) | (0<<WGM01);
	TCCR0B	= (0<<CS00);
	PORTB	= 0;
	
	_delay_ms( 255 );
	
}

int main(void) {
	
	short int seed;
	
	// Read the seed value from EEPROM 0x00, use it, increment and store it.
	
	EEARL	= 0x00;
	EECR	|= (1<<EERE);
	seed	= EEDR;
	seed++;
	srand( (int)seed );
	EECR	= (0<<EEPM1)|(0>>EEPM0);
	EEARL	= 0x00;
	EEDR	= seed;
	EECR	|= (1<<EEMPE);
	EECR	|= (1<<EEPE);
	
	// Keep choosing a  firefly, flash it, wait, flash another one, etc
	short int firefly, repeat_1, repeat_2, wait;
	for(;;) {
		repeat_1 = rand() % 2;
		repeat_2 = rand() % 2;
		wait     = rand() % 30;
		firefly  = rand() % 14;
		//wait     = 10;
		
		light_firefly( firefly );
		
		if( repeat_1 )
			light_firefly( firefly );
		if( repeat_2 )
			light_firefly( firefly );
		
		for( short int i = 0; i < wait; i++ ) {
			_delay_ms( 255 );
		}
	}
}
