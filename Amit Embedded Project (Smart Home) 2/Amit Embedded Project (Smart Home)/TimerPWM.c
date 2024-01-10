/*
 * TimerPWM.c
 *
 * Created: 9/30/2023 2:15:26 PM
 *  Author: EGYPT
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>
#include "STD_Types.h"
#include "TimerPWM.h"
#include "eldod_UART.h"
#include "ADC.h"


void timer0_initializeCTC(void)
{
	//Set timer mode
	//Set the mode as Compare match
	SET_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, WGM00);
	
	//Configure clock
	//set as clk/1024
	CLR_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	
	//Enable timer 0 interrupt for compare match
	SET_BIT(TIMSK, OCIE0);
	
	//OCR0 = the value to compare with
	OCR0 = 128; //altering tick value to achieve lab equal to 1 msec
	TCNT0 = 0;
	
}

void Timer0_Fast_PWM_INIT(void)
{
	setbit(TCCR0,WGM00);// Set mode to Fast PWM
	setbit(TCCR0,WGM01);
	
	setbit(TCCR0,CS00);// PreScalar = 64
	setbit(TCCR0,CS01);
	clrbit(TCCR0,CS02);
	
	clrbit(TCCR0,COM00);// nin_Inverting mode
	setbit(TCCR0,COM01);
	
	setbit(TIMSK, OCIE0);//    interrupt of comp
	
	setbit(DDRB,3);// Set OC0 as output
	
	OCR0 = 0;
}

void Timer1_Fast_PWM_INIT(void) 
{
	setbit(TCCR1A, WGM10);        // Set mode to Fast PWM (8-bit mode)
	clrbit(TCCR1A, WGM11);
	setbit(TCCR1B, WGM12);
	
	setbit(DDRD, 5);              // Set OC1A (PB1) and OC1B (PB2) as outputs
	setbit(DDRD, 4);
	
	setbit(TCCR1B, CS10);         // Set prescaler to 64
	setbit(TCCR1B, CS11);
	clrbit(TCCR1B, CS12);

	setbit(TCCR1A, COM1A1);       // Non-Inverting mode for OC1A and OC1B
	clrbit(TCCR1A, COM1A0);
	setbit(TCCR1A, COM1B1);
	clrbit(TCCR1A, COM1B0);
	
	//setbit(TIMSK, OCIE1A);        // Enable Timer/Counter1 Output Compare A and B Match Interrupts
	//setbit(TIMSK, OCIE1B);

	OCR1A = 0;
	OCR1B = 0;
}

void Timer2_Fast_PWM_INIT(void)
{
	setbit(TCCR2,WGM20);
	setbit(TCCR2,WGM21);
	
	clrbit(TCCR2,CS20);
	setbit(TCCR2,COM21);
	
	clrbit(TCCR2,CS21);
	setbit(TCCR2,CS22);
	
	setbit(DDRD,7);
	
	OCR2= 0;
}



void Timer0_Set_Duty_Cycle(float64 DC)
{
	if (DC <= 0.000)
	{
		OCR0 = 0;
	}
	else if ( DC >= 1.000)
	{
		OCR0 = 255;
	}
	else
	{
		OCR0 = (DC*255);
	}
}

void Timer1A_Set_Duty_Cycle(float64 DC)
{
	if (DC <= 0.000)
	{
		OCR1A = 0;
	}
	else if ( DC >= 1.000)
	{
		OCR1A = 255;
	}
	else
	{
		OCR1A = (DC*255);
	}
}

void Timer1B_Set_Duty_Cycle(float64 DC)
{
	if (DC <= 0.000)
	{
		OCR1B = 0;
	}
	else if ( DC >= 1.000)
	{
		OCR1B = 255;
	}
	else
	{
		OCR1B = (DC*255);
	}
}

void Timer2_Set_Duty_Cycle(float64 DC)
{
	if (DC <= 0.000)
	{
		OCR2 = 0;
	}
	else if ( DC >= 1.000)
	{
		OCR2 = 255;
	}
	else
	{
		OCR2 = (DC*255);
	}
}

void servo_angle(float64 angle)
{
	float64 dutyCycle= (((angle/180)*0.07)+0.055);
	Timer2_Set_Duty_Cycle(dutyCycle);
}

void controlDoor(uint8 action)
{
	if(action == '1')
	{
		servo_angle(90);
	}
	else if (action == '2')
	{
		servo_angle(0);
	}
	else
	{
		UART_STR("invalid choice \r\n");
	}
}

uint16 read_brightness()
{
	return round((float64)((float64)OCR1A/255)*9);
}

