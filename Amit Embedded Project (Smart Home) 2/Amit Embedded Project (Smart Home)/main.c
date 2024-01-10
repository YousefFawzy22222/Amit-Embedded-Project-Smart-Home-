/*
 * Amit Embedded Project (TTL-Bluetooth).c
 *
 * Created: 12/13/2023 2:57:48 PM
 * Author : Andrew Walid
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "STD_Types.h"
#include "STD_Macros.h"
#include "main_config.h"
#include "eldod_Interrupt.h"
#include "eldod_UART.h"
#include "LCD_interface.h"
//#include "eldod_LCD.h"
#include "Keypad_interface.h"
//#include "eldod_KeyPad.h"
#include "Admin Mode.h"
#include "User Mode.h"
#include "TimerPWM.h"
#include "ADC.h"
#include "lights.h"
#include "compare.h"
#include "EEPROM.h"


int main(void)
{
	
	UART_init(4800, 1000000);
	timer0_initializeCTC();
	Timer2_Fast_PWM_INIT();
	externalInterrupt_init(0);
	externalInterrupt_init(1);
	ADC_Init();
	lights_init();
	LCD_voidInit();
	KPD_VidInit();
	
	Timer1A_Set_Duty_Cycle(0);
	
	EEPROM_vWriteByteToAddress(GUESTS_NUM_ADDRESS, 0);
	/*
	uint8 adminChoice;
	uint8 userChoice= KPD_NOT_Pressed;
	*/
	
    /* Replace with your application code */
    while (1)
    {/*
		if(readBit(PIND, 2) && admin_validityFlag== TRUE){        // While there is still a bluetooth connection and access was allowed (flag is 1)
			//admin_funcChoice();                                      // Ask Admin what does he want to do
			if(readBit(UCSRA, RXC)) adminChoice= UART_receive();                             // Store the number of function he wants to do
			UART_printText("\r\n");
			if(adminChoice!= 0xFF) admin_callFunc(adminChoice);                             // Activate the function asked for
			adminChoice= 0xFF;
		}
		else if(!readBit(PIND, 2)) admin_validityFlag= false;             // Once connection is lost remove access again (flag is 0)
		
		if(user_validityFlag== TRUE){
			userChoice= KPD_VidGetPressedKey();
			if(userChoice!= KPD_NOT_Pressed){
				user_callFunc(userChoice);
			}
		}
    */}
}