/*
 * Admin_Mode.h
 *
 * Created: 12/13/2023 2:59:27 PM
 *  Author: Andrew Walid
 */ 
typedef enum Bool{
	false= 0,
	true= 1
}bool;

#ifndef ADMIN_MODE_H_
#define ADMIN_MODE_H_


extern uint8 admin_validityFlag;

void system_breakdown(void);
void admin_funcChoice(void);
void admin_callFunc(uint8 num);


#endif /* ADMIN MODE_H_ */