/*
 * TimerPWM.h
 *
 * Created: 9/30/2023 2:16:02 PM
 *  Author: EGYPT
 */ 


#ifndef TIMERPWM_H_
#define TIMERPWM_H_

#include "STD_Types.h"
#include "STD_Macros.h"

void timer0_initializeCTC(void);
void Timer0_Fast_PWM_INIT(void);
void Timer1_Fast_PWM_INIT(void);
void Timer2_Fast_PWM_INIT(void);
void Timer0_Set_Duty_Cycle(float64 DC);
void Timer1A_Set_Duty_Cycle(float64 DC);
void Timer1B_Set_Duty_Cycle(float64 DC);
void Timer2_Set_Duty_Cycle(float64 DC);

void servo_angle(float64 angle);
void controlDoor(uint8 action);
uint16 read_brightness();


#endif /* TIMERPWM_H_ */