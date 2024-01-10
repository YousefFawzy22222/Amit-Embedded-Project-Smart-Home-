#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_DATA_PORT Port_C

//#define LCD_CTRL_PORT Port_A
#define LCD_CTRL_PORT_RS Port_A
#define LCD_CTRL_PORT_RW Port_D
#define LCD_CTRL_PORT_E Port_B

#define LCD_RS_PIN Pin1
#define LCD_RW_PIN Pin6
#define LCD_E_PIN Pin6

#define CLR_SCREEN           0X01
#define DISPLAY_ON_CURSOR_ON 0X0E
#define EIGHT_BIT_MODE       0X38
#define FOUR_BIT_MODE_I      0X02
#define FOUR_BIT_MODE_II     0X28

#include "STD_Types.h"

// Sends a command to the LCD
void LCD_voidSendCommand(uint8 Copy_u8Command);

// Sends data to be displayed on the LCD
void LCD_voidSendData(uint8 Copy_u8Data);

// Initializes the LCD
void LCD_voidInit(void);

// Sends a string to be displayed on the LCD
void LCD_voidSendString(char str[]);

// Moves the cursor to the specified row and column on the LCD
void LCD_voidGoToRowColumn(unsigned char Row, unsigned char Column);

// Prints a number on the LCD
void LCD_voidPrintNumber(int num);

// Defines and sends an extra custom character to the LCD
struct Extra_Character
{
    uint8 *copy_u8Pattern;
    uint8 copy_u8PatternNumber;
    uint8 copy_u8Row;
    uint8 copy_u8Column;
};
void LCD_voidSendExtraChar(struct Extra_Character copy_character);

// Reads data from the LCD
void LCD_voidReadData(uint8 *data);

// Deletes the last character displayed on the LCD
void LCD_voidDeleteLastCharacter(void);

// Clears the entire screen of the LCD
void LCD_voidClearScreen();

// To shift to the data shown on left of display
void LCD_voidShiftDisplayLeft(uint16 digits);

#define LCD_vInit() LCD_voidInit()

#define LCD_vSend_cmd(cmd) LCD_voidSendCommand(cmd)

#define LCD_vSend_char(ch) LCD_voidSendData(ch)

#define LCD_vSend_string(str) LCD_voidSendString(str)

#define LCD_clearscreen(void) LCD_voidClearScreen(void)

#define LCD_movecursor(r, c) LCD_voidGoToRowColumn(r, c)

#endif
