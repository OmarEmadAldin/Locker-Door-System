/*
 * HMI_MainFunc.h
 *
 *  Created on: 31 Oct 2022
 *      Author: Omar Ben Emad
 */

#include"lcd.h"
#include"keypad.h"
#include<util/delay.h>
#include"USART.h"
#include"Timer1.h"
#include"std_types.h"

#define Size 5


#define MC_Ready				0x99	/*to enable uart to receive*/
#define UART_setPass 			0x01	/*Set Pass indicator*/
/* used these three to check if the password is matched with the saved one in EEPROM*/
#define UART_check 				0x10	/*to tell uart */
#define UART_matchPass  		0x02 	/*indication of matched passwords*/
#define UART_missMatchPass  	0x04 	/*Not important but can be used*/


#define UART_sendPass			0x08
#define UART_Motor				0x12
#define UART_Buzzer				0x20

/*******************************************************************************
 *                               Functions prototypes                          *
 *******************************************************************************/
/*
 * used to set the pass and store it in the EEPROM
 * we enter it two times and check matched or not
 * */
void set_pass();
/*
 * Function that used to check if the pass matched with
 * the stored one
 * it returnes matched or missmatched byte to the uart*/
uint8 CheckPass();
/*
 * display function
 * displays the only two man options after set of the pass*/
void mainOptions();
/*
 * counts 3 sec
 * for the hold process of the door*/
void Timer1_3Sec();
/*
 * same as the previous but different time span*/
void Timer1_15Sec();
/*
 * for counting one minute for the error function*/
void oneMinute();
/*
 * func that is responsible for enabling the buzzer
 * as an alarm for one minute if the pass is entered three times wrong*/
void errorAlarm();
/*
 * second option on the main screen function*/
void changePassOption();
/*
 * first option on the main screen function
 * Motor on so the door is unlocking */
void openDoorOption();

