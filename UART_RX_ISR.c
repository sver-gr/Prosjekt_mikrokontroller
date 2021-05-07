/*
 * UART_RX_ISR.c
 *
 * Created: 06.05.2021 18:59:35
 *  Author: Sverre_Graffer
 */ 

#define F_CPU 16000000UL // System clock

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>


void wait(){
	while(!(UCSR0A & (1<<RXC0))){}	// wait for input to arrive
}


ISR(USART0_RX_vect){	// wait for incoming data
	
	char input_str[4];
	int a = 0;
	while(a < 3){
		wait();
		int input_part = UDR0;
		if(input_part != '\r'){	//discard CR
			input_str[a] = input_part;
		}
		else{
			input_str[a] = '\0';
			continue;
		}
	//_delay_ms(1);	// this should be enough to let the next character from UART recieve
	a += 1;
	}
	
	wait();
	a = UDR0;	// just discarding fourth character
	//a = UDR0;	// just discarding fifth character
	uint8_t serial_input = atoi(input_str);	//Put recieved data in variable
	PORTA = serial_input;
}