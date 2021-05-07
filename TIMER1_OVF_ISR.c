/*
 * TIMER1_OVF_ISR.c
 *
 * Created: 07.05.2021 13:06:20
 *  Author: Sverre_Graffer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TIMER.h"
uint8_t SERVO_active;	// this was necessary to not get error
ISR(TIMER1_OVF_vect){
	
	static int a = 0;
	static int PWM_threshold = 625;
	
	int steps = 30;
	
	if(SERVO_active){	// only move servo if needed
		SERVO_set(PWM_threshold);
	}
	
	
	
	if(a < steps){
		if(a%2 == 0){
			a += 1;
			PWM_threshold -= 17;
		}
		else{
			a += 1;
			PWM_threshold -= 18;
		}
		// cant use 17.5 so this should work
		
	}
	else{
		a = 0;
		PWM_threshold = 625;
		PORTB ^= (1 << PB7);	// toggle onboard-LED
	}
	
	reset_timer_1s_left_to_overflow();
}

