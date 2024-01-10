/*
 * STD_Macros.h
 *
 * Created: 9/6/2023 4:59:37 AM
 *  Author: Andrew Walid
 */

/*
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
*/

#ifndef STD_MACROS_H_INCLUDED
#define STD_MACROS_H_INCLUDED

#define setBit(reg,bit) reg|= (1<<bit)              // to set a bit to one without affecting the rest of the register we OR it with a one shifted to the position of the bit wanted (so only that bit wanted would be affected and be one whatever its current state)
#define clrBit(reg, bit) reg&= ~(1<<bit)            // to clear a bit to zero without affecting the rest of the register we AND it with the opposite (NOT) of one shifted to the position of the bit (so only that bit wanted would be affected and be zero whatever its current state)
#define togBit(reg, bit) reg^= (1<<bit)             // to toggle a bit state to another without affecting the rest of the register we XOR it with one so shifted to the position of the bit (so only that bit wanted would be affected and change state whatever its current state)
#define readBit(reg, bit) ((reg>>bit) & 1)            // since it's only for reading so it doesn't put the value back in the reg it only reads whatever the bit chosen state by shifting it to the begining and clearing all the rest to zero

#define setbit(reg, bit) setBit(reg, bit)
#define clearbit(reg, bit) clrBit(reg, bit)
#define togglebit(reg, bit) togBit(reg, bit)
#define readbit(reg, bit) readBit(reg, bit)

#define clrbit(reg, bit) clrBit(reg, bit)
#define togbit(reg, bit) togBit(reg, bit)

#define SET_BIT(reg, bit) setBit(reg, bit)
#define CLR_BIT(reg, bit) clrBit(reg, bit)
#define TOGGLE_BIT(reg, bit) togBit(reg, bit)
#define READ_BIT(reg, bit) readBit(reg, bit)

#define Clear_bit(reg, bit) clrBit(reg, bit)
#define Set_bit(reg, bit) setBit(reg, bit)
#define Get_bit(reg, bit) readBit(reg, bit)

#endif // STD_MACROS_H_INCLUDED
