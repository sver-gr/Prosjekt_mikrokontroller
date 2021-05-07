/*
 * UART_init.h
 *
 * Created: 05.05.2021 19:27:38
 *  Author: Sverre_Graffer
 */ 


#ifndef UART_INIT_H_
#define UART_INIT_H_

void UART_init();
void UART_test();
void UART_transmit_number_as_str(int number, int number_length);
void UART_transmit_CRLF();



#endif /* UART_INIT_H_ */