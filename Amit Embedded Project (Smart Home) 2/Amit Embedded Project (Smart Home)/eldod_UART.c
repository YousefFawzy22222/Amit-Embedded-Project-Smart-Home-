/*
 * eldod_UART.c
 *
 * Created: 11/2/2023 10:58:50 AM
 *  Author: Andrew Walid
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "STD_Macros.h"
#include "eldod_UART.h"
#include "STD_Types.h"


/* function to initialize UART communication protocol */

void UART_init(uint32 baud, uint64 freq)
{
	uint32 ubrr= round((float64)freq/(16*(float64)baud))-1;//           calculation for the UBRRL and UBRRH values to achieve the wanted baud rate with the used frequency
	
	clrBit(DDRD, 0);//                 setting Rx pin (receiver) to input
	setBit(DDRD, 1);//                 setting Tx pin (transmitter) to output
	
	if(ubrr<255) UBRRL= (uint8)ubrr;//     if ubrr value less than 255 the it can be stored directly in UBRRL register only
	else{//                                   _    else if it is bigger than 255
		UBRRH= (uint8)ubrr;//          |
		UBRRL= (uint8)(ubrr>>8);//    _|   ubrr value will need to be divided in two parts bits with resolution>8 in UBRRH and rest in UBRRL
	}
	
	UCSRA|= (0<<U2X) /*normal transmission speed*/;
	
	UCSRB|= (1<<TXEN) | (1<<RXEN) /*enabling transmitting and receiving*/
	| (0<<UCSZ2) /*part of setting data bits to be 8*/;
	
	UCSRC|= (1<<URSEL) /*writing on UCSRC not UBRRH*/ | (0<<UMSEL) /*choosing asynchronous mode*/| (1<<UCSZ0) | (1<<UCSZ1) /*setting data bit to be 8*/| (0<<UPM0) | (0<<UPM1) /*using odd parity check*/| (0<<USBS) /*1 bit for stop*/;
}

/* function to receive data through UART communication protocol */

uint8 UART_receive(void)
{
	while(!readBit(UCSRA, RXC));//              hold program till making sure that the data to be received are waiting on the buffer
	return UDR;//                               return the data received
}

/* function to transmit data through UART communication protocol */

void UART_transmit(uint8 data)
{
	while(!readBit(UCSRA, UDRE));//             hold program till making sure that UDR not in a current process and ready to take data
	UDR= data;//                                store the data on the UDR register
	while(!readBit(UCSRA, TXC));//              hold program till making sure that the UDR is empty and all the data bits has been sent
}

void UART_readString(uint8 length, uint8 *text)    /* function used to read multiple characters through UART communication at once*/
{
	while(readBit(UCSRA, RXC)) UART_receive();
	uint32 i;
	for(i=0; i<length; i++){
		text[i] = UART_receive();
	}
}

void UART_printText(char text[])
{
	for(uint32 i=0; text[i]!='\0'; i++){
		UART_transmit(text[i]);
	}
}

void UART_printNum(sint16 num)
{
	int i;
	int arr[20];
	if(num<0){
		UART_transmit('-');
		num*= -1;
	}
	else if(num==0){
		UART_transmit('0');
	}
	for(i=0; num!=0; i++){
		arr[i]= num%10;
		num/=10;
	}
	for(i-=1; i>=0; i--){
		UART_transmit('0'+arr[i]);
	}
}