#include "DIO_interface.h"
#include "STD_Types.h"
#include "STD_Macros.h"


void DIO_VidSetPinDirection(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Direction)
{
    if (Copy_u8Direction == Input)
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            DDRA = Clear_bit(DDRA, Copy_u8Pin);
            break;

        case Port_B:
            DDRB = Clear_bit(DDRB, Copy_u8Pin);
            break;

        case Port_C:
            DDRC = Clear_bit(DDRC, Copy_u8Pin);
            break;

        case Port_D:
            DDRD = Clear_bit(DDRD, Copy_u8Pin);
            break;
        }
    }
    else
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            DDRA = Set_bit(DDRA, Copy_u8Pin);
            break;

        case Port_B:
            DDRB = Set_bit(DDRB, Copy_u8Pin);
            break;

        case Port_C:
            DDRC = Set_bit(DDRC, Copy_u8Pin);
            break;

        case Port_D:
            DDRD = Set_bit(DDRD, Copy_u8Pin);
            break;
        }
    }
}

void DIO_VidSetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value)
{
    if (Copy_u8Value == PinHigh)
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            PORTA = Set_bit(PORTA, Copy_u8Pin);
            break;

        case Port_B:
            PORTB = Set_bit(PORTB, Copy_u8Pin);
            break;

        case Port_C:
            PORTC = Set_bit(PORTC, Copy_u8Pin);
            break;

        case Port_D:
            PORTD = Set_bit(PORTD, Copy_u8Pin);
            break;
        }
    }
    else
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            PORTA = Clear_bit(PORTA, Copy_u8Pin);
            break;

        case Port_B:
            PORTB = Clear_bit(PORTB, Copy_u8Pin);
            break;

        case Port_C:
            PORTC = Clear_bit(PORTC, Copy_u8Pin);
            break;

        case Port_D:
            PORTD = Clear_bit(PORTD, Copy_u8Pin);
            break;
        }
    }
}

void DIO_VidGetPinValue(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 *pu8Data)
{
    switch (Copy_u8Port)
    {
    case Port_A:
        *pu8Data = Get_bit(PINA, Copy_u8Pin);
        break;

    case Port_B:
        *pu8Data = Get_bit(PINB, Copy_u8Pin);
        break;

    case Port_C:
        *pu8Data = Get_bit(PINC, Copy_u8Pin);
        break;

    case Port_D:
        *pu8Data = Get_bit(PIND, Copy_u8Pin);
        break;
    }
}

void DIO_VidSetPortDirection(uint8 Copy_u8Port, uint8 Copy_u8Direction)
{
    if (Copy_u8Direction == Input)
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            DDRA = 0x00;
            break;

        case Port_B:
            DDRB = 0x00;
            break;

        case Port_C:
            DDRC = 0x00;
            break;

        case Port_D:
            DDRD = 0x00;
            break;
        }
    }
    else
    {
        switch (Copy_u8Port)
        {
        case Port_A:
            DDRA = 0xFF;
            break;

        case Port_B:
            DDRB = 0xFF;
            break;

        case Port_C:
            DDRC = 0xFF;
            break;

        case Port_D:
            DDRD = 0xFF;
            break;
        }
    }
}

void DIO_VidSetPortValue(uint8 Copy_u8Port, uint8 Copy_u8Value)
{

    switch (Copy_u8Port)
    {
    case Port_A:
        PORTA = Copy_u8Value;
        break;
    case Port_B:
        PORTB = Copy_u8Value;
        break;

    case Port_C:
        PORTC = Copy_u8Value;
        break;

    case Port_D:
        PORTD = Copy_u8Value;
        break;
    }
}

void DIO_VidGetPortValue(uint8 Copy_u8Port, uint8 *pu8Data)
{
    switch (Copy_u8Port)
    {
    case Port_A:
        *pu8Data = PINA;
        break;

    case Port_B:
        *pu8Data = PINB;
        break;

    case Port_C:
        *pu8Data = PINC;
        break;

    case Port_D:
        *pu8Data = PIND;
        break;
    }
}

