/*
 * CONTROL_MainFuncs.h
 *
 *  Created on: 31 Oct 2022
 *      Author: Omar Ben Emad
 */

#ifndef CONTROL_MAINFUNCS_H_
#define CONTROL_MAINFUNCS_H_

#include"external_eeprom.h"
#include<util/delay.h>
#include"USART.h"
#include"Timer1.h"
#include"std_types.h"
#include"Motor.h"
#include"Buzzer.h"

#define PasswordaddressFlag     0x320
#define Passwordaddress 		0x350
#define PasswordSet				0xFF

#define MC_Ready				0x99	/*to enable uart to receive*/
#define UART_setPass 			0x01	/*Set Pass indicator*/
/* used these three to check if the password is matched with the saved one in EEPROM*/
#define UART_check 				0x10	/*to tell uart */
#define UART_matchPass  		0x02 	/*indication of matched passwords*/
#define UART_missMatchPass  	0x04 	/*Not important but can be used*/


#define UART_sendPass			0x08
#define UART_Motor				0x12
#define UART_Buzzer				0x20

void PassIsSetinEEPROM();
void readPassFromEEPROM();
void passChecked();
void updatePassword();
void BuzzerError();
void openDoor();
void Timer1_3Sec();
void Timer1_15Sec();
void oneMinute();


#endif /* CONTROL_MAINFUNCS_H_ */
