#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H



#define KPD_PORT Port_A

#define KPD_COL1PIN Pin2
#define KPD_COL2PIN Pin3
#define KPD_COL3PIN Pin4

#define KPD_ROW1PIN Pin5
#define KPD_ROW2PIN Pin6
#define KPD_ROW3PIN Pin7

#define KPD_Column_Number 3
#define KPD_Row_Number 3

#define KPD_NOT_Pressed 0xFF

#define KPD_Arr                                                                                  \
{                                                                                            \
	{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'} \
}

#define NOT_PRESSED 0xff

// Initializes the keypad
void KPD_VidInit();

// Returns the value of the pressed key
uint8 KPD_VidGetPressedKey();

#define keypad_vInit KPD_VidInit

#define keypad_u8check_press KPD_VidGetPressedKey

#endif
