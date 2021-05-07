/*
 * PINS.c
 *
 * Created: 06.05.2021 19:17:53
 *  Author: Sverre_Graffer
 */ 

#include <avr/io.h>

void PINS_init(){
	// LED array pins
	DDRA = 0xFF;
	PORTA = 0;
	
	// LED servo pin
	DDRB |= (1 << PB7);
	
	// PWM servo pin
	DDRE |= (1 << PE3);
	
	// use pin as button sensor
	PORTD |= (1 << PD0);
	// enable interrupt on relase/rising edge
	EIMSK = (1<<INT0); // enable interrupt on INT0
	EICRA |= (1 << ISC00) | (1 << ISC01); // use falling edge to trigger interrupt
}