/*
 * lights.h
 *
 * Created: 1/4/2024 11:01:53 PM
 *  Author: Abdelrahmen
 */ 


#ifndef LIGHTS_H_
#define LIGHTS_H_

extern uint8 leds[];
#define LED_DDR *(&DDRB)
#define LED_PORT *(&PORTB)
#define LED_NUM 5
#define LED_ON '1'
#define LED_OFF '2'


void lights_init(void);
void lights_On_Off(uint8 ledNum, uint8 ledStat);
void control_dimmer_light(uint32 brightness);
void all_lights(uint8 action);



#endif /* LIGHTS_H_ */