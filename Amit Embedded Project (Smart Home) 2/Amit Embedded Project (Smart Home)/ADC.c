/*
 * ADC.c
 *
 * Created: 9/23/2023 2:40:45 PM
 *  Author: a3abd
 */ 

#define F_CPU 1000000ul
#include "STD_MacRos.h"
#include "ADC.h"
#include "STD_Types.h"
#include <avr/io.h>
#include <util/delay.h>

uint32 x = 0;                      //Variable to store ADC reading
sint16 volt = 0, temperature = 0; // Variables to store calculated voltage and temperature

void ADC_Init()
{
	clrbit(DDRA,0);            // Configure pin 0 of port A as input for the temperature sensor

	setbit(ADMUX,REFS0);       //Internal 2.56V voltage reference
	setbit(ADMUX,REFS1);
	setbit(ADCSRA,ADEN);       //Enable ADC
	setbit(ADCSRA,ADPS2);      //Set Prescaler to 16
}

uint32 ADC_Read(uint8 ch)
{
	uint16 value = 0;
	if(ch>=0 && ch<=8)
	{
		ADMUX = (ADMUX & 0xE0) | ch; //channel selection 
		setbit(ADCSRA,ADSC);//Start conversion to be able to read
		while(readbit(ADCSRA,ADIF) != 1);
		_delay_ms(1);
		value = (uint16)ADCL + (uint16)ADCH * 256;
	}
	return value; //Return calculated value
}

void calculate_Temperature()
{
	x = ADC_Read(0);             // Read the ADC value from channel 0
	volt = (2560 * x) / 1024;    // Calculate voltage from ADC reading
	temperature = volt / 10;     // Calculate temperature from voltage
}