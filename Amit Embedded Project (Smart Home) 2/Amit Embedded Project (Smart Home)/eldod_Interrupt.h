/*
 * eldod_Interrupt.h
 *
 * Created: 10/11/2023 10:19:41 AM
 *  Author: Andrew Walid
 */ 

#ifndef ELDOD_INTERRUPT_H_
#define ELDOD_INTERRUPT_H_

#include "STD_Types.h"

extern volatile uint64 count;
extern uint8 block_mode_flag;
extern volatile uint8 interrupt1_Flag;

void externalInterrupt_init(uint16 ExInt);



#endif /* ELDOD_INTERRUPT_H_ */