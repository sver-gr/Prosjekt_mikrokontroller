/*
 * ADC_init.c
 *
 * Created: 05.05.2021 19:33:20
 *  Author: Sverre_Graffer
 */ 

#include <avr/io.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN);	// Turn on ADC.
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);	// Set prescaler to divide clock by 128. 16MHz/128=125kHz
	ADMUX = (1 << REFS0);	// Use AVCC as analog reference.
	// I use ADC0 which is the default, so there is no need to set ADCSRB register. At least not yet.
	ADCSRB |= (1 << ACME);	// enable multiplexer
}

int ADC_read(){
	ADCSRA |= (1 << ADSC);			// Start ACD conversion.
	while (ADCSRA & (1 << ADSC)) {}	// Wait for the conversion to finish.
	uint8_t LSB_from_ADC = ADCL;	// Read the least significant bits first.
	uint8_t MSB_from_ADC = ADCH;	// Then read the most significant bits.
	int All_bits_from_ADC = LSB_from_ADC + (MSB_from_ADC << 8);	// Combine them into one variable.
	uint8_t eight_MSB_from_ADC = (All_bits_from_ADC >> 2);// Right shift the bits two positions to get the eight most significant bits to port A.
	
	
	
	return All_bits_from_ADC;
}

void ADC_change_pin_to_LDR(){
	ADMUX |= (1 << MUX0);
}
void ADC_change_pin_to_POT(){
	ADMUX &= ~(1 << MUX0);
}