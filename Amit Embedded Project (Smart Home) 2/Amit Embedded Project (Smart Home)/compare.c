#include "compare.h"

extern volatile uint16 session_counter;//Stores the session time
extern uint8 timeout_flag;//stores if the session is still valid or outdated

uint8 ui8Compare(const uint8* pass1, const uint8* pass2, const uint8 size)
{
	uint8 pin_counter=0;//the offset of the character of the pin
	uint8 ret_value = TRUE;
	while (pin_counter<size)//loop till the pin is fully entered
	{
		if (*(pass1+pin_counter)!=*(pass2+pin_counter))//if the two characters of the entered pin and the stored pin are not equal
		{
			ret_value= FALSE;//returns false that means the two PINs are not equal
			break;//break the loop
		}
		pin_counter++;//increase thee offset by one
	}
	return ret_value;//returns false that means the two PINs are equal since all characters of the PINs are equal
}
