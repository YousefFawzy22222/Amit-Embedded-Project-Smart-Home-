/*
 * User_Mode.c
 *
 * Created: 1/8/2024 12:43:17 PM
 *  Author: Hp
 */ 


#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "STD_Types.h"
#include "STD_Macros.h"
#include "main_config.h"
#include "eldod_Interrupt.h"
#include "EEPROM.h"
#include "LCD_interface.h"
//#include "eldod_LCD.h"
#include "Keypad_interface.h"
//#include "eldod_KeyPad.h"
#include "ADC.h"
#include "TimerPWM.h"
#include "lights.h"

uint8 user_validityFlag= FALSE;
volatile uint32 count1=1;
uint8 tog=2;

void user_funcChoice(void)
{
	LCD_voidClearScreen();
	LCD_voidSendString("1:Temp Monitor");
	LCD_voidGoToRowColumn(1, 0);
	LCD_voidSendString("2:Control Lights");
}
void user_callFunc(uint8 num)
{
	user_funcChoice();
	uint8 key= KPD_NOT_Pressed;
	switch(num)
	{
		case '1':
		LCD_voidClearScreen();
		LCD_voidSendString(" 9: To Go Back");
		LCD_voidGoToRowColumn(1, 0);
		LCD_voidSendString(" Temperature= ");
		while(1){
			calculate_Temperature();
			LCD_voidGoToRowColumn(1, 14); LCD_voidPrintNumber(temperature);
			key= KPD_VidGetPressedKey();
			if(key== '9') break;
		}
		break;
		
		case '2':
		LCD_voidClearScreen();
		LCD_voidSendString("9 Go Back, Pick");
		LCD_voidGoToRowColumn(1, 0);
		LCD_voidSendString("LED 1->5, 6 Dimm");
		LCD_voidGoToRowColumn(0, 17);
		LCD_voidSendString("7: Turn All On");
		LCD_voidGoToRowColumn(1, 17);
		LCD_voidSendString("8: Turn All Off");
		count1=1;
		tog=1;
		while(1){
			count1++;
			key= KPD_NOT_Pressed;
			uint8 key2= KPD_NOT_Pressed;
			if((count1%500)==0 && tog==1){
				LCD_voidShiftDisplayLeft(17);
				count1=1;
				tog=2;
			}
			else if((count1%600)==0 && tog==2){
				LCD_voidClearScreen();
				LCD_voidSendString("9 Go Back,Choose");
				LCD_voidGoToRowColumn(1, 0);
				LCD_voidSendString("LED 1->5, 6 Dimm");
				LCD_voidGoToRowColumn(0, 17);
				LCD_voidSendString("7: Turn All On");
				LCD_voidGoToRowColumn(1, 17);
				LCD_voidSendString("8: Turn All Off");
				count1=1;
				tog=1;
			}
			key= KPD_VidGetPressedKey();
			if(key!= KPD_NOT_Pressed){
				if(key== '9') break;
				else if(key>='1' && key<='5'){
					LCD_voidClearScreen();
					LCD_voidSendString("1: Turn On");
					LCD_voidGoToRowColumn(1, 0);
					LCD_voidSendString("2: Turn Off");
					key2= KPD_VidGetPressedKeyLoop();
					lights_On_Off(key, key2);
				}
				else if(key== '6'){
					LCD_voidClearScreen();
					LCD_voidSendString("Choose brightness");
					LCD_voidGoToRowColumn(1, 0);
					LCD_voidSendString("from 0 to 9");
					key2= KPD_VidGetPressedKeyLoop();
					control_dimmer_light(key2);
				}
				else if(key== '7' || key== '8'){
					all_lights(key);
				}
				else LCD_voidSendString("Invalid Choice");
				count1= 599;
				tog=2;
				LCD_voidClearScreen();
			}
		}
		default: LCD_voidClearScreen(); LCD_voidSendString("Invvalid Choice"); _delay_ms(500);
	}
}


ISR(INT1_vect)
{
	uint8 key_pressed = KPD_NOT_Pressed;
	uint8 pass_counter=0;
	uint8 pass_tries_count=0;                                                     //counts the entered key of the password from the keypad
	uint32 User_Num;
	uint8 user_Name[USER_SIZE];
	uint8 tog=1;
	if(user_validityFlag==TRUE){
		LCD_voidClearScreen();
		user_validityFlag= FALSE;
		tog= 2;
	}
	//===============================================================================================================================
	while(tog==1)
	{
		uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};          //temporarily hold the entire password that will be entered by the user to be check
		LCD_voidClearScreen();
		LCD_voidSendString("Enter pass:");
		_delay_ms(200);															 //Halt the system for the given time in (ms)
		pass_counter=0;															 //counts the number of entered characters
		while(pass_counter<PASS_SIZE)
		{
			while (key_pressed == KPD_NOT_Pressed)									 //repeat till the user press any key
			{
				key_pressed = KPD_VidGetPressedKey();							 //if the user pressed any button in keypad save the value in key_pressed
			}
			pass[pass_counter] = key_pressed;									 //add the pressed key to the password string
			LCD_voidGoToRowColumn(0, 11+pass_counter);
			LCD_voidSendData(key_pressed);										 //print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);									 //Halt the system for the given time in (ms)
			LCD_voidGoToRowColumn(0,11+pass_counter);									 //return the cursor to the location of the previous character to replace it with the password sign
			LCD_voidSendData(PASSWORD_SYMBOL);								     // to display (Password sign *)
			pass_counter++;														 //increase the password counter that count the characters of the pass
			_delay_ms(50);														 //Halt the system for the given time in (ms)
			key_pressed = KPD_NOT_Pressed;											 //return the variable that holds the pressed key from keypad to its initial value
		}
		//EEPROM_vReadBlockFromAddress(EEPROM_GUEST_ADDRESS,stored_pass,PASS_SIZE);//Save the entire password in the EEPROM
		//======================================================================================================================================
		
		/*compare passwords*/
		if (EEPROM_ui8CheckIfPassExist2(pass) == -1)					         //in case of right password
		{
			user_validityFlag= FALSE;
			pass_tries_count++;													 //increase the number of wrong tries to block login if it exceeds the allowed tries
			//login_mode = NO_MODE;												 //set the mode as not logged in
			LCD_voidClearScreen();													 //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			LCD_voidSendString("Wrong pass");
			if (pass_tries_count>=TRIES_ALLOWED)								 //if the condition of the block mode is true
			{
				_delay_ms(500);
				LCD_voidClearScreen();
				LCD_voidSendString("You Been Blocked");
				LCD_voidGoToRowColumn(1, 0);
				LCD_voidSendString("Reset The System");
				EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);          //write to the EEPROM TRUE to the the block mode address
				block_mode_flag = TRUE;											 //turn on block mode
				break;														     //breaks the loop of insert guest password #while(login_mode != GUEST)# line 228
			}          //end of if that check if the number of tries exceeds the maximum tries allowed
			//LCD_movecursor(2,0);
			LCD_voidGoToRowColumn(1, 0);
			LCD_voidSendData((TRIES_ALLOWED-pass_tries_count)+ASCII_ZERO);			 //print the number of tries left before block mode to be activated
			LCD_voidSendString(" Trial(s) left");
			_delay_ms(1000);													 //Halt the system for the given time in (ms)
			LCD_voidClearScreen();													 //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		}
		else																	 //in case of wrong password
		{
			User_Num = EEPROM_ui8CheckIfPassExist2(pass);
			LCD_voidClearScreen();
			LCD_voidSendString("Correct pass");
			EEPROM_vReadBlockFromAddress(GUEST_USER_ADDRESS[User_Num], user_Name, USER_SIZE);
			LCD_voidGoToRowColumn(1, 1);
			LCD_voidSendString("Welcome  ");
			LCD_voidSendString(user_Name);
			_delay_ms(1000);
			LCD_voidClearScreen();
			user_validityFlag= TRUE;
			user_funcChoice();
			break;
		}
	}
}