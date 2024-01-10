
#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#include "STD_Types.h"

#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF

#define BLOCK_MODE_TIME		   (uint32)20000
#define CHARACTER_PREVIEW_TIME (uint16)300
#define DEGREES_SYMBOL		   (uint8)0xDF

/*********************************** PIN Configuration ***********************************/
#define USER_SIZE       (uint8)6
#define PASS_SIZE       (uint8)4
#define TRIES_ALLOWED   (uint8)3
#define PASSWORD_SYMBOL (uint8)'*'
#define ASCII_ZERO      (uint8)'0'

#define PASS_NOT_SET (uint8)0xFF
#define PASS_SET     (uint8)0x01

#define ADMIN_PASS_STATUS_ADDRESS (uint16)0X100
#define EEPROM_ADMIN_ADDRESS      (uint16)0X101
#define EEPROM_GUEST_ADDRESS      (uint16)0X106
#define GUESTS_MAX_NUM            (uint16)10
#define GUESTS_NUM_ADDRESS        (uint16)0x011F
extern uint16 GUEST_STATUS_ADDRESS[];
extern uint16 GUEST_USER_ADDRESS[];
extern uint16 GUEST_PASS_ADDRESS[];

#define LOGIN_BLOCKED_ADDRESS             (uint16)0X10
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define NO_MODE (uint8)0
#define ADMIN   (uint8)1
#define GUEST   (uint8)2
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE   (uint8)0
#define TRUE    (uint8)1
/*****************************************************************************************/

#define CHECK_ADMIN_MODE        (uint8)'0'
#define CHECK_GUEST_MODE        (uint8)'1'

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT (uint16)3000
#define GUEST_TIMEOUT (uint16)2000
/*****************************************************************************************/

#endif /* MAIN_CONFIG_H_ */