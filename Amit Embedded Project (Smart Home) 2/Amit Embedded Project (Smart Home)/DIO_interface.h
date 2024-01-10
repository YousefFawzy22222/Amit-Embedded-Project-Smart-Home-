#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "STD_Types.h"

#define PORTA *((volatile uint8 *)0x3B)
#define DDRA *((volatile uint8 *)0x3A)
#define PINA *((volatile uint8 *)0x39)

#define PORTB *((volatile uint8 *)0x38)
#define DDRB *((volatile uint8 *)0x37)
#define PINB *((volatile uint8 *)0x36)

#define PORTC *((volatile uint8 *)0x35)
#define DDRC *((volatile uint8 *)0x34)
#define PINC *((volatile uint8 *)0x33)

#define PORTD *((volatile uint8 *)0x32)
#define DDRD *((volatile uint8 *)0x31)
#define PIND *((volatile uint8 *)0x30)

typedef enum
{
    Port_A,
    Port_B,
    Port_C,
    Port_D
} et_Port;

typedef enum
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
} et_Pin;

typedef enum
{
    Input,
    Output
} et_Direction;

typedef enum
{
    PinLow,
    PinHigh
} et_Status;

// setting Pin direction
void DIO_VidSetPinDirection(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Direction);

// setting Pin value
void DIO_VidSetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value);

// getting Pin value
void DIO_VidGetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 *pu8Data);

// setting Port direction
void DIO_VidSetPortDirection(uint8 Copy_u8Port, uint8 Copy_u8Direction);

// setting Port value
void DIO_VidSetPortValue(uint8 Copy_u8Port, uint8 Copy_u8Value);

// getting Port value
void DIO_VidGetPortValue(uint8 Copy_u8Port, uint8 *pu8Data);

/*
	Function Name        : DIO_vconnectpullup
	Function Returns     : void
	Function Arguments   : uint8 portname ,uint8 pinnumber, uint8 connect_pullup
	Function Description : Connect and disconnect pull up resistor to the given pin at the given port 
*/

#define DIO_vsetPINDir DIO_VidSetPinDirection

#define DIO_write

#define DIO_u8read

#define DIO_toggle

#define DIO_write_port DIO_VidSetPortValue

#define clear_high_nibble 

#define dio_write_highnibble



#endif