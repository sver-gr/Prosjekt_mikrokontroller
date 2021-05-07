/*
 * TIMER_init.c
 *
 * Created: 05.05.2021 19:32:10
 *  Author: Sverre_Graffer
 */ 

#define F_CPU 16000000UL // System clock
#include <avr/io.h>


void reset_timer_1s_left_to_overflow(){
	TCNT1 = 49911;	// 16e6/1024 = 15625, 2^16 = 65536, 65536 - 15625 = 49911
}

void SERVO_set(int a){
	OCR3A = a;
	// position 0.4ms 1.45ms 2.5ms, (5000/20ms)*x*ms = 100 362.5 625, about pi/2 rotation
	// (625 - 100)/30 = 17.5
}

void TIMER_init(){
	// timer1 used for servo
	TCCR1B |= (1 << CS10) | (1 << CS12);	// set prescaler to 1024
	TIMSK1 |= (1 << TOIE1);	// activate interrupt on overflow
	reset_timer_1s_left_to_overflow();
	
	// timer3 used for PWM for servo
	TCNT3 = 0;	// set timer3 to 0
	ICR3 = 5000;	// highest possible count 16e6/64  = 250e3, 250e3*.02 = 5000, sets frequency
	// WGMn 1, 2 and 3 means fast PWM with ICRn as highest count
	// COM3A1 means compare output mode for the A channel, clear OC3A at threshold
	TCCR3A |= (1 << COM3A1) | (1 << WGM31);
	// CS30 and CS31 sets prescaler to 64
	TCCR3B |= (1 << CS30) | (1 << CS31) | (1 << WGM32) | (1 << WGM33);
	
	SERVO_set(363);	
	
}

