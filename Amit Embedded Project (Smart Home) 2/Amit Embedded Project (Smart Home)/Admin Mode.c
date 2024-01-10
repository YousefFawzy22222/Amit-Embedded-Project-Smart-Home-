/*
 * Admin_Mode.c
 *
 * Created: 12/13/2023 2:58:42 PM
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
#include "eldod_Interrupt.h"
#include "eldod_UART.h"
#include "EEPROM.h"
#include "TimerPWM.h"
#include "ADC.h"
#include "lights.h"
#include "compare.h"

uint8 admin_validityFlag= false;

void admin_funcChoice(void)
{
	UART_printText("\r\n\r\n");
	UART_printText("Press the following number for the function you need");
	UART_printText("\r\n");
	UART_printText("1: control the door");
	UART_printText("\r\n");
	UART_printText("2: control the lights");
	UART_printText("\r\n");
	UART_printText("3: monitor the temperature");
	UART_printText("\r\n");
	UART_printText("4: edit the list of users");
	UART_printText("\r\n");
}

void admin_callFunc(uint8 num)
{
	UART_printText("\r\n");
	switch(num)
	{
		case '1':
		while(1){
			UART_printText("\r\n0: go back \r\n1: open the door \r\n2: close door \r\n");
			uint8 action= UART_receive();
			if(action== '0') break;
			else controlDoor(action);
			UART_printText("\r\n");
		}
		break;
		
		case '2':
		while(1){
			UART_printText("\r\n0: go back \r\nchoose led 1 to 5 or 6 for dimmer led \r\n7: turn all on    8: turn all off \r\n");
			uint8 ledNum= UART_receive();
			UART_printText("\r\n");
			if(ledNum== '0') break;
			else if(ledNum>='1' && ledNum<='5'){
				UART_printText("1: turn on \r\n2: turn off \r\n");
				lights_On_Off(ledNum, UART_receive());
				UART_printText("\r\n");
		    }
			else if(ledNum== '6'){
				static uint16 ledBrightness= '0'; 
				UART_printText("Choose brightness you want from 0 to 9 now it's at ");
				UART_printNum(ledBrightness-'0');
				UART_printText("\r\n");
				ledBrightness= UART_receive();
				control_dimmer_light(ledBrightness);
				UART_printText("\r\n");
			}
			else if(ledNum== '7' || ledNum== '8'){
				all_lights(ledNum);
			}
			else UART_printText("invalid choice \r\n");
		}
		break;
		
		case '3':
		UART_printText("press 0: to go back to the list \r\n");
		while(1){
			calculate_Temperature();
			UART_printText("Temp: "); UART_printNum(temperature); UART_printText("\r\n");
			_delay_ms(300);
			if(UART_dataAvailable) if(UART_receive()== '0') break;
		}
		break;
		
		case '4':
		while(1){
			uint8 last_userNum= EEPROM_ui8ReadByteFromAddress(GUESTS_NUM_ADDRESS);
			UART_printText("\r\n0: go back \r\n1: add user   2: remove user   3: change user's password \r\n");
			uint8 choice= UART_receive();
			uint8 user[USER_SIZE], pass[PASS_SIZE];
			if(choice== '0') break;
			else if(choice== '1'){
				if(last_userNum<GUESTS_MAX_NUM){
				   	UART_printText("\r\nEnter the 6-characters name of the new user: ");
					UART_readString(USER_SIZE, user);
					if(EEPROM_ui8CheckIfUserExist(user)) UART_printText("\r\nThis user already exist \r\n");
					else{
						UART_printText("\r\nEnter a 4-characters password for the new user: ");
						while(1){
							UART_readString(PASS_SIZE, pass);
							if(EEPROM_ui8CheckIfPassExist(pass)) UART_printText("\r\nAnother user is using the same password, try another one: ");
							else{ EEPROM_vAddUser(user, pass); UART_printText("\r\n"); break;}
						}
					}
				}
				else UART_printText("\r\nThe list is Full \r\n");
			}
			else if(choice== '2'){
				if(last_userNum>0){
					UART_printText("\r\nEnter the 6-characters name of the user: ");
					UART_readString(USER_SIZE, user);
					if(EEPROM_ui8CheckIfUserExist(user)) EEPROM_vDeleteUser(user);
					else UART_printText("\r\nThe user is not found \r\n");
				}
				else UART_printText("\r\nThe list is Empty \r\n");
			}
			else if(choice== '3'){
				if(last_userNum>0){
					UART_printText("\r\nEnter the 6-characters name of the user: ");
					UART_readString(USER_SIZE, user);
					if(EEPROM_ui8CheckIfUserExist(user)){
						UART_printText("\r\nEnter the new 4-characters password you want to change it to: ");
						while(1){
							UART_readString(PASS_SIZE, pass);
							if(EEPROM_ui8CheckIfPassExist(pass)) UART_printText("\r\nAnother user is using the same password, try another one: ");
							else{ EEPROM_vAddUser(user, pass); UART_printText("\r\n"); break;}
						}
					}
					else UART_printText("\r\nThe user is not found \r\n");
				}
				else UART_printText("\r\nThe list is Empty \r\n");
			}
		}
		/*EEPROM editing*/
		break;
		
		default: UART_printText("invalid choice \r\n"); break;
	}
	admin_funcChoice();                                      // Ask Admin what does he want to do next
}

ISR(INT0_vect)
{
	/*uint8 tog=1;
	if(admin_validityFlag==TRUE){
		admin_validityFlag= FALSE;
		tog= 2;
	}*/
	if ( (EEPROM_ui8ReadByteFromAddress(ADMIN_PASS_STATUS_ADDRESS)!=PASS_SET))
	{
		EEPROM_vWriteByteToAddress(GUESTS_NUM_ADDRESS, 0);
		UART_printText("Login for first time \r\nSet your password: ");
		/********************************* setting Admin password **********************************************/
		
		uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};        //the array where it stored the password
		UART_readString(PASS_SIZE, pass);
		UART_printText("\r\n");
		
		EEPROM_vWriteBlockToAddress(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);           //save the entire password as a block to the EEPROM
		EEPROM_vWriteByteToAddress(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);             //write the status of pass as it is set
		UART_printText("Confirmation, ");
	}
	
	uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};          //temporarily hold the entire password that will be entered by the user to be check
	uint8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};   //temporarily hold the entire stored password that is written by the user for the first time

	EEPROM_vReadBlockFromAddress(EEPROM_ADMIN_ADDRESS,stored_pass,PASS_SIZE);   //read the stored pass from the EEPROM
	uint8 pass_tries_count=0;                                                     //stores how many times the user tried to log in to the system and failed
	
	UART_printText("Enter your password: ");
	while(1){
		if(!readBit(PIND, 2)) break;
		
		UART_readString(PASS_SIZE, pass);
		UART_printText("\r\n");
		if(ui8Compare(pass, stored_pass, PASS_SIZE)){
			UART_printText("Right Password, Welcome Admin \r\n");
			admin_validityFlag= true;                        // compare if given "pass" match his password in the list if yes toggle the right password 'led2' and put the access flag to 1 to allow access
			pass_tries_count=0;                                                  //clear the counter of wrong tries
			admin_funcChoice();                                      // Ask Admin what does he want to do
			break;
		}
		else{
			UART_printText("Wrong Password");
			admin_validityFlag= false;                                                          // else if given password is wrong toggle the wrong password 'led0' and put the access flag to 0 for no access
			pass_tries_count++;													 //increase the number of wrong tries to block login if it exceeds the allowed tries
			if (pass_tries_count>=TRIES_ALLOWED)								 //if the condition of the block mode is true
			{
				UART_printText(", You have been blocked \r\n\r\nReset The System");
				EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);			 //write to the EEPROM TRUE to the the block mode address
				block_mode_flag = true;										     //turn on block mode
				break;
			}
			UART_printText(", You have ");
			UART_printNum(TRIES_ALLOWED-pass_tries_count);
			UART_printText(" trial(s) left \r\nTry again: ");
		}
	}
}