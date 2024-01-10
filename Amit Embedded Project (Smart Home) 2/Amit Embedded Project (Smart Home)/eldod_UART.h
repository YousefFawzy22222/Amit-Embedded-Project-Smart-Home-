/*
 * eldod_UART.h
 *
 * Created: 11/2/2023 10:59:05 AM
 *  Author: Andrew Walid
 */ 


#ifndef ELDOD_UART_H_
#define ELDOD_UART_H_

//extern char string[20];
#include "STD_Types.h"

#define UART_dataAvailable readBit(UCSRA, RXC)

void UART_init(uint32 baud, uint64 freq);
uint8 UART_receive(void);
void UART_transmit(uint8 data);
void UART_readString(uint8 length, uint8 *text);
void UART_printText(char text[]);
void UART_printNum(sint16 num);

#define UART_Rx() UART_receive()
#define UART_Tx(p) UART_transmit(p)
#define UART_STR(p) UART_printText(p)




#endif /* ELDOD_UART_H_ */