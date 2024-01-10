
#include <avr/io.h>
#include "EEPROM.h"
#include "main_config.h"
#include "compare.h"

uint16 GUEST_STATUS_ADDRESS[GUESTS_MAX_NUM]= {0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x11A};
uint16 GUEST_USER_ADDRESS[GUESTS_MAX_NUM]= {0x120, 0x130, 0x140, 0x150, 0x160, 0x170, 0x180, 0x190, 0x1A0, 0x1B0};
uint16 GUEST_PASS_ADDRESS[GUESTS_MAX_NUM]= {0x126, 0x136, 0x146, 0x156, 0x166, 0x176, 0x186, 0x196, 0x1A6, 0x1B6};

uint8 EEPROM_ui8ReadByteFromAddress(const uint16 u16Address)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
	;
	/* Set up address register */
	EEAR = u16Address;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_vReadBlockFromAddress(const uint16 uiAddress, uint8* dist,const uint16 size)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
	;

	uint16 counter = 0;//the counter of bytes that are read

	while (counter < size) //loop until move all bytes to the given array
	{
		/* Set up address register */
		EEAR = uiAddress + counter;
		/* Start EEPROM read by writing EERE */
		EECR |= (1 << EERE);
		/* move data from data register to the array */
		*(dist + counter) = EEDR;

		counter++;//increase the bytes counter
	}
}

void EEPROM_vWriteByteToAddress(const uint16 uiAddress, const uint8 uiData)
{

	/* Wait for completion of previous write process*/
	while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
	;
	/* Set up address register */
	EEAR = uiAddress;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EERE);
	if (EEDR != uiData)//compare the value read to the value to be written
	{//if they are not equal then write the data 
		EEDR = uiData;//move the data to EEDR

		/* Write logical one to EEMWE */
		EECR |= (1 << EEMWE);
		/* Start EEPROM write by setting EEWE */
		EECR |= (1 << EEWE);
	}
	else
	{

	}

}

void EEPROM_vWriteBlockToAddress(const uint16 uiAddress, const uint8* uiData,const uint16 size)
{
	uint16 counter = 0;//Bytes write counter
	while (counter < size)
	{
		/* Wait for completion of previous write process*/
		while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
		;
		/* Set up address register */
		EEAR = uiAddress + counter;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EERE);
		if (EEDR != (*(uiData + counter)))//compare the value read to the value to be written
		{//if they are not equal then write the data 
			EEDR = *(uiData + counter);//move the data to EEDR

			/* Write logical one to EEMWE */
			EECR |= (1 << EEMWE);
			/* Start EEPROM write by setting EEWE */
			EECR |= (1 << EEWE);
		}
		else
		{

		}
		counter++;//increase bytes counter
	}
}

uint8 EEPROM_ui8CheckIfUserExist(const uint8* user)
{
	uint8 ret_Value= FALSE;
	uint8 stored_user[USER_SIZE];
	for(uint16 i= 0; i<GUESTS_MAX_NUM; i++){
		EEPROM_vReadBlockFromAddress(GUEST_USER_ADDRESS[i], stored_user, USER_SIZE);
		if(ui8Compare(user, stored_user, USER_SIZE)){
			ret_Value= TRUE;
			break;
		}
	}
	return ret_Value;
}

uint8 EEPROM_ui8CheckIfPassExist(const uint8* pass)
{
	uint8 ret_Value= FALSE;
	uint8 stored_pass[PASS_SIZE];
	for(uint16 i= 0; i<GUESTS_MAX_NUM; i++){
		EEPROM_vReadBlockFromAddress(GUEST_PASS_ADDRESS[i], stored_pass, PASS_SIZE);
		if(ui8Compare(pass, stored_pass, PASS_SIZE)){
			ret_Value= TRUE;
			break;
		}
	}
	return ret_Value;
}

sint16 EEPROM_ui8CheckIfPassExist2(const uint8* pass)
{
	sint8 ret_Value= -1;
	uint8 stored_pass[PASS_SIZE];
	for(uint16 i= 0; i<GUESTS_MAX_NUM; i++){
		EEPROM_vReadBlockFromAddress(GUEST_PASS_ADDRESS[i], stored_pass, PASS_SIZE);
		if(ui8Compare(pass, stored_pass, PASS_SIZE)){
			ret_Value = i;
			break;
		}
	}
	return ret_Value;
}

void EEPROM_vAddUser(const uint8* user, const uint8* pass)
{
	uint8 last_userNum= EEPROM_ui8ReadByteFromAddress(GUESTS_NUM_ADDRESS);
	EEPROM_vWriteBlockToAddress(GUEST_USER_ADDRESS[last_userNum], user, USER_SIZE);
	EEPROM_vWriteBlockToAddress(GUEST_PASS_ADDRESS[last_userNum], pass, PASS_SIZE);
	EEPROM_vWriteByteToAddress(GUEST_STATUS_ADDRESS[last_userNum], PASS_SET);
	EEPROM_vWriteByteToAddress(GUESTS_NUM_ADDRESS, last_userNum+1);
}

void EEPROM_vDeleteUser(const uint8* user)
{
	uint8 last_userNum= EEPROM_ui8ReadByteFromAddress(GUESTS_NUM_ADDRESS);
	uint8 emptyUserPass[USER_SIZE+PASS_SIZE]= {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED};
	uint8 stored_user[USER_SIZE], last_user[USER_SIZE+PASS_SIZE];
	for(uint16 i= 0; i<USER_SIZE; i++){
		EEPROM_vReadBlockFromAddress(GUEST_USER_ADDRESS[i], stored_user, USER_SIZE);
		if(ui8Compare(user, stored_user, USER_SIZE)){
			if(i== last_userNum){
				EEPROM_vWriteBlockToAddress(GUEST_USER_ADDRESS[i], emptyUserPass, USER_SIZE+PASS_SIZE);
			}
			else{
				EEPROM_vReadBlockFromAddress(GUEST_USER_ADDRESS[last_userNum], last_user, USER_SIZE+PASS_SIZE);
				EEPROM_vWriteBlockToAddress(GUEST_USER_ADDRESS[i], last_user, USER_SIZE+PASS_SIZE);
				break;
			}
			EEPROM_vWriteByteToAddress(GUESTS_NUM_ADDRESS, last_userNum-1);
			EEPROM_vWriteByteToAddress(GUEST_STATUS_ADDRESS[last_userNum], PASS_NOT_SET);
		}
	}
}

void EEPROM_vEditUserPass(const uint8* user, const uint8* newPass)
{
	uint8 stored_user[USER_SIZE];
	for(uint16 i= 0; i<USER_SIZE; i++){
		EEPROM_vReadBlockFromAddress(GUEST_USER_ADDRESS[i], stored_user, USER_SIZE);
		if(ui8Compare(user, stored_user, USER_SIZE)){
			EEPROM_vWriteBlockToAddress(GUEST_PASS_ADDRESS[i], newPass, PASS_SIZE);
			break;
		}
	}
}