/*
 * UART_init.c
 *
 * Created: 05.05.2021 19:26:41
 *  Author: Sverre_Graffer
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL // System clock
#define USART_BAUDRATE 9600 // desired baud rate for UART
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) // UBRR value

char *itoa (int __val, char *__s, int __radix);

// Functions that are used by functions in this file
void UART_wait_while_transmitting(){
	while(!(UCSR0A & (1<<UDRE0))){}; // Wait for incoming data
}

//	Functions that are used in other files

// Initializes UART
void UART_init(){
	UBRR0 = BAUD_PRESCALE; // Set UBBR according to system clock and desired baud rate
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Turn on the transmission and reception circuitry
}

// Sends the UTF8-character "Å"
void UART_test(){
	UDR0 = 0xc3;
	UART_wait_while_transmitting();
	UDR0 = 0x85;
	UART_wait_while_transmitting();
}

// Transmits the provided number as a string on UART
void UART_transmit_number_as_str(int number, int array_length){
	char number_str[array_length];	// create a string to transmit via UART.
	itoa(number, number_str, 10);	// converts it to a base 10 string
	int str_length = sizeof(number_str)/sizeof(number_str[0]);	// Finds the length of the created string
	
	// Sends the string on UART
	for (int a = 0; a <= (str_length-2); a += 1)	// -2 so the null character at the end is not send
	{
		UDR0 = number_str[a];
		UART_wait_while_transmitting();
	}
	
}

// Move the cursor to the next line.
void UART_transmit_CRLF(){
	UDR0 = '\r';	// CR
	UART_wait_while_transmitting();
	UDR0 = '\n';	// LF
	UART_wait_while_transmitting();
}