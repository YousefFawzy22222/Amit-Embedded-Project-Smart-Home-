/*
 * eldod_Interrupt.c
 *
 * Created: 10/11/2023 10:18:54 AM
 *  Author: Andrew Walid
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "STD_Types.h"
#include "STD_Macros.h"
#include "main_config.h"
#include "Admin Mode.h"
#include "User Mode.h"
#include "eldod_Interrupt.h"
#include "TimerPWM.h"
#include "ADC.h"
#include "EEPROM.h"
#include "main_config.h"
#include "DIO_config_master.h"
#include "compare.h"
#include "eldod_UART.h"
#include "Keypad_interface.h"
#include "LCD_interface.h"

volatile uint64 count = 0;
uint8 block_mode_flag= false;
volatile uint8 interrupt1_Flag = false;

uint8 adminChoice= 0xFF;
uint8 userChoice= KPD_NOT_Pressed;

void externalInterrupt_init(uint16 ExInt)
{
	sei();//       enable global interrupt (GIE)
	
	switch(ExInt)//      enable the interrupt request depending on which is given to the function
	{
	  case 0:
	  setBit(GICR,INT0);//    enable interrupt request 0 and set its pin as input
	  clrBit(DDRD, 2);
	  //                         _
	  setBit(MCUCR,ISC00);//      |  interrupt flag will set in the rising edge
	  setBit(MCUCR,ISC01);//     _|
	  break;
	  
	  case 1:
	  setBit(GICR, INT1);
	  setBit(DDRD, 3);
	  //                         _
	  setBit(MCUCR,ISC10);//      |  interrupt flag will set in the rising edge
	  clrBit(MCUCR,ISC11);//     _|
	  break;//    enable interrupt request 1 and set its pin as input
	  
	  case 2: setBit(GICR, INT2);
	  clrBit(DDRB, 2);
	  break;//    enable interrupt request 2 and set its pin as input
	}
}



ISR(TIMER0_COMP_vect)
{
	if(block_mode_flag== TRUE){
		Timer1B_Set_Duty_Cycle(0);
		setbit(DDRB,7);
		setbit(PORTB,7);
		while(1);
	}
	count++;
	
	if(readBit(PIND, 2) && admin_validityFlag== TRUE){        // While there is still a bluetooth connection and access was allowed (flag is 1)
		//admin_funcChoice();                                      // Ask Admin what does he want to do
		if(readBit(UCSRA, RXC)) adminChoice= UART_receive();                             // Store the number of function he wants to do
		if(adminChoice!= 0xFF) admin_callFunc(adminChoice);                             // Activate the function asked for
		adminChoice= 0xFF;
	}
	else if(!readBit(PIND, 2)) admin_validityFlag= false;             // Once connection is lost remove access again (flag is 0)
	
	if(/*!readBit(PIND, 3) &&*/ user_validityFlag== TRUE){
		userChoice= KPD_VidGetPressedKey();
		if(userChoice!= KPD_NOT_Pressed){
			user_callFunc(userChoice);
		}
	}
	if (count % 5000 == 0)
	{
		calculate_Temperature();
		// Control the fan speed based on temperature conditions
		if (temperature <= 20)
		{
			Timer1B_Set_Duty_Cycle(0); // Fan off
		}
		else if (temperature >= 28 && temperature < 35)
		{
			Timer1B_Set_Duty_Cycle(0.25); // Set fan speed to 25%
		}
		else if (temperature >= 35 && temperature < 40)
		{
			Timer1B_Set_Duty_Cycle(0.5); // Set fan speed to 50%
		}
		else if (temperature >= 40 && temperature < 45)
		{
			Timer1B_Set_Duty_Cycle(0.75); // Set fan speed to 75%
		}
		else if (temperature >= 45)
		{
			Timer1B_Set_Duty_Cycle(1); // Set fan speed to 100%
		}
	}
}


