#ifndef COMPARE_H_
#define COMPARE_H_

#include "main_config.h"
#include "STD_Types.h"

/*
	Function Name        : ui8ComparePass
	Function Returns     : uint8
	Function Arguments   : const uint8* pass1,const uint8* pass2,const uint8 size
	Function Description : Compare two arrays of bytes and return True in case they are identical and return false in case they are different .
*/
uint8 ui8Compare(const uint8* pass1, const uint8* pass2, const uint8 size);

#define ui8ComparePass ui8Compare
#endif /* MENU_H_ */