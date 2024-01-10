/*
 * lights.c
 *
 * Created: 1/4/2024 10:59:31 PM
 *  Author: Abdelrahmen
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Types.h"
#include "STD_Macros.h"
#include "lights.h"
#include "TimerPWM.h"

uint8 leds[LED_NUM]= {0, 1, 2, 4, 5};

void lights_init(void)
{
	for(int i= 0; i<LED_NUM; i++){
		setBit(LED_DDR, leds[i]);
	}
	Timer1_Fast_PWM_INIT();
}

void lights_On_Off(uint8 ledNum, uint8 ledStat)
{
	uint16 led= (ledNum-'1');
	if(ledStat== LED_ON) setBit(LED_PORT, leds[led]);
	else if(ledStat== LED_OFF) clrBit(LED_PORT, leds[led]);
}

void control_dimmer_light(uint32 brightness)
{
	Timer1A_Set_Duty_Cycle((float64)(brightness-'0')/9);
}

void all_lights(uint8 action)
{
	if(action== '7'){
		for(uint16 i= 0; i<LED_NUM; i++){
			setBit(LED_PORT, leds[i]);
		}
		Timer1A_Set_Duty_Cycle(1);
	}
	else if(action== '8'){
		for(uint16 i= 0; i<LED_NUM; i++){
			clrBit(LED_PORT, leds[i]);
		}
		Timer1A_Set_Duty_Cycle(0);
	}
}