#include "STD_Types.h"
#include "STD_Macros.h"
#include "DIO_interface.h"
#include "Keypad_interface.h"

#define F_CPU 1000000UL // for performance reasons in Proteus


void KPD_VidInit()
{
    // Set the pin directions for the columns as output
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL1PIN, Output);
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL2PIN, Output);
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL3PIN, Output);

    // Set the pin directions for the rows as input
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW1PIN, Input);
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW2PIN, Input);
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW3PIN, Input);
	
	// Internal Pull Up for columns pins
	setbit(PORTA,KPD_COL1PIN);
	setbit(PORTA,KPD_COL2PIN);
	setbit(PORTA,KPD_COL3PIN);
	
	// set default for the out pins to be 1
	setbit(PORTA,KPD_ROW1PIN);
	setbit(PORTA,KPD_ROW2PIN);
	setbit(PORTA,KPD_ROW3PIN);

}

uint8 KPD_VidGetPressedKey()
{
    uint8 Key_Pressed_Value = KPD_NOT_Pressed; // if the value has not been changed from KPD_NOT_Pressed, then no key is pressed
    uint8 Key_Pressed_State;                   // used in DIO_VidGetPinValue

    static uint8 Column_arr[] = {KPD_COL1PIN, KPD_COL2PIN, KPD_COL3PIN};
    static uint8 Row_arr[] = {KPD_ROW1PIN, KPD_ROW2PIN, KPD_ROW3PIN};
    static uint8 Local_Keypad_arr[KPD_Row_Number][KPD_Column_Number] = KPD_Arr;

    for (uint8 Column = 0; Column < KPD_Column_Number; Column++)
    {
        // Set the current column pin to low
        DIO_VidSetPinValue(KPD_PORT, Column_arr[Column], PinLow);

        for (uint8 Row = 0; Row < KPD_Row_Number; Row++)
        {
            // Get the state of the current row pin
            DIO_VidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);

            if (Key_Pressed_State == PinLow) // when a key is pressed it has a low value
            {
                Key_Pressed_Value = Local_Keypad_arr[Row][Column];

                // Wait until the key is released
                while (Key_Pressed_State == PinLow) // polling, while the key is still pressed, don't do anything.
                {
                    DIO_VidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);
                }
                return Key_Pressed_Value;
            }
        }
        // Set the current column pin back to high
        DIO_VidSetPinValue(KPD_PORT, Column_arr[Column], PinHigh);
    }

    return Key_Pressed_Value;
}

uint8 KPD_VidGetPressedKeyLoop()
{
	uint8 key= KPD_NOT_Pressed;
	while(key== KPD_NOT_Pressed){
		key= KPD_VidGetPressedKey();
	}
	return key;
}