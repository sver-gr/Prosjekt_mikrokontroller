/*
 * PINS_ISR.c
 *
 * Created: 07.05.2021 21:52:09
 *  Author: Sverre_Graffer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t SERVO_active;	// this was necessary to not get error
ISR(INT0_vect){
	SERVO_active = !SERVO_active;
	// enable or disable servo with button
}