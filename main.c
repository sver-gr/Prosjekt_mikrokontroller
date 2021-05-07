/*
 * Prosjekt.c
 *
 * Created: 05.05.2021 19:14:51
 * Author : Sverre_Graffer
 */ 

#define F_CPU 16000000UL // System clock
#define USART_BAUDRATE 9600 // desired baud rate for UART
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) // UBRR value

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Functions for UART, TIMER and ADC
#include "UART.h"
#include "TIMER.h"
#include "ADC.h"
#include "PINS.h"

volatile uint8_t SERVO_active = 0;

int main(void)
{
    /* My application code */
	UART_init();	// initialize everything
	TIMER_init();
	ADC_init();
	PINS_init();
	PORTE |= (1 << PE3);	// set PWM pin as output
	sei();	// enable global interrupts
    while (1) 
    {
		// read potmeter and transmit to PC
		ADC_change_pin_to_POT();
		_delay_ms(1000);
		int ADC_value = ADC_read();
		UART_transmit_number_as_str(ADC_value, 5);
		UART_transmit_CRLF();
		
		// read LDR and transmit to PC
		ADC_change_pin_to_LDR();
		_delay_ms(1000);
		ADC_value = ADC_read();
		UART_transmit_number_as_str(ADC_value, 5);
		UART_transmit_CRLF();
		UART_transmit_CRLF();	// create extra space
    }
}


// ISR's
//#include "UART_RX_ISR.c"
//#include "TIMER1_OVF_ISR.c "

//	turned out it was not necessary to include these.