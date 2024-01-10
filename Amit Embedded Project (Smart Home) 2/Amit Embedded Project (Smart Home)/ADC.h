/*
 * ADC.h
 *
 * Created: 9/23/2023 2:40:59 PM
 *  Author: a3abd
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "STD_Types.h"

void ADC_Init();
uint32 ADC_Read(uint8 ch);
void calculate_Temperature();

extern sint16 temperature;



#endif /* ADC_H_ */