/*
 * HMI_MainFunc.c
 *
 *  Created on: 31 Oct 2022
 *      Author: Omar Ben Emad
 */
#include"HMI_MainFunc.h"

#define Size 5

boolean Password_Set_State ; /*password check flag*/
boolean Motor_State; /*Motor check state flag*/

uint8 PassStateCheck;  /* used in check pass function*/
uint8 buzzerFlag ; /*flag for alarm exit*/
uint8 motorFlag ; /*flag to motor exit*/
uint8 trial = 3; /*number of trails that allowed before error alarm*/

/*Arrays that used to store two passwords for setting pass and check*/
uint16 passwordOne[Size];
uint16 passwordTwo[Size];

uint8 g_tick; /*used to make the counts in timer functions*/
uint8 i ;/*global variable for all iterations*/
/*
 * Initialzation of the timer as it will be used in the functions
 * 3Sec , 15Sec and one minute */
Timer1_ConfigType Sec = {0 , 7813 , Prescaler1024 , Compare };
/*
 * Function for setting password
 * as  the user will enter it two times and see if the two times are equal*/
void set_pass(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"  Enter ur Pass");
	_delay_ms(2000);
	LCD_clearScreen();
	UART_sendByte(UART_setPass);
	do{
	Password_Set_State = TRUE;
	LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");
	LCD_moveCursor(1,0);
	for(i=0 ; i<Size ; i++){
		*(passwordOne+i) = KEYPAD_getPressedKey();

		if((*(passwordOne+i) <= 9) && (*(passwordOne+i) >= 0))
		{
			LCD_displayCharacter('*');   /* display the pressed keypad switch */
		}
		else
		{
			i--;
		}

		_delay_ms(500); /* Press time */
		}

	while(KEYPAD_getPressedKey() != '='){};

	LCD_clearScreen();
	LCD_displayString("   Processing");
	_delay_ms(500);

	LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");
	LCD_displayStringRowColumn(1,0,"Again:");
	LCD_moveCursor(1,7);

	for(i=0 ; i<Size ; i++){
		*(passwordTwo+i) = KEYPAD_getPressedKey();

		if((*(passwordTwo+i) <= 9) && (*(passwordTwo+i) >= 0))
		{
			LCD_displayCharacter('*');   /* display the pressed keypad switch */
		}
		else
		{
			i--;
		}

		_delay_ms(500); /* Press time */
	}

	while(KEYPAD_getPressedKey() != '='){};

	for(i=0 ; i<Size ; i++){
		if(*(passwordTwo+i) != *(passwordOne+i))
			Password_Set_State=FALSE;
	}

	if(Password_Set_State == TRUE){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Completed");
		for(uint8 i = 0 ; i < Size ; i++)
		{
			UART_sendByte(passwordOne[i]);
			_delay_ms(50);

		}
	}
	else if(Password_Set_State == FALSE){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Try Again");

	}
	LCD_clearScreen();
} while(Password_Set_State == FALSE);
}
/*
 * Function used to check if the entered password
 * is the same as the stored in the EEPROM
 * and if it is unmatched three times it will enable the buzzer for error*/
uint8 CheckPass(){
	do{
		Password_Set_State = TRUE;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");
		LCD_displayStringRowColumn(1,0,"Again:");
		for(i=0 ; i<Size ; i++){
		*(passwordTwo+i) = KEYPAD_getPressedKey();

		if((*(passwordTwo+i) <= 9) && (*(passwordTwo+i) >= 0))
		{
			*(passwordTwo+i)=KEYPAD_getPressedKey();
			LCD_displayCharacter('*');   /* display the pressed keypad switch */
		}
		else
		{
			i--;
		}
		_delay_ms(500);
		}
	while(KEYPAD_getPressedKey() != '='){};

	UART_sendByte(UART_check); /*to let the UART know that what action it has to do*/
	for(i = 0 ; i < Size	; i++)
		{
			UART_sendByte(*(passwordTwo+i));
			while(UART_recieveByte() != (MC_Ready));
		}

	if(UART_recieveByte()==UART_matchPass){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"	Matched");
		return UART_matchPass;
	}
	else{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"  Try again");
		trial -- ;
		PassStateCheck = UART_missMatchPass;
	}
	}while((trial > 0));
	return PassStateCheck;
}
void mainOptions(){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change pass");

}
void Timer1_3Sec(){
	g_tick++;
	if(g_tick==3){
		g_tick =0 ;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"    Motor Held");
		UART_sendByte(MC_Ready);
		TIMER1_COMP_setCallBack(Timer1_15Sec);

	}
}
void Timer1_15Sec(){
	g_tick++;
	if(g_tick==15){
		g_tick =0 ;
		LCD_clearScreen();
		if(Motor_State == FALSE){
			LCD_displayStringRowColumn(0,0,"    Opening");
			UART_sendByte(MC_Ready);
			TIMER1_COMP_setCallBack(Timer1_3Sec);
			Motor_State = TRUE;
		}
		else if(Motor_State == TRUE){
				Motor_State = FALSE;
				motorFlag = 1;
				Timer1_deInit();
		}
	}
}
/*Function mainly made to be used in alarm*/
void oneMinute(){
	g_tick ++;
	if(g_tick == 60){
		g_tick = 0;
		buzzerFlag = 1;
		Timer1_deInit();
	}
}
void errorAlarm(){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "	ERROR");
	UART_sendByte(UART_Buzzer);
	buzzerFlag = 0 ;
	g_tick = 0;
	TIMER1_COMP_setCallBack(oneMinute);
	while(buzzerFlag != 1);
}

void changePassOption(){
	uint8 pass = CheckPass();
	if(pass== UART_matchPass){
		set_pass();
	}
	else {
		errorAlarm();
	}
}

void openDoorOption(){
	uint8 pass = CheckPass();
	if(pass== UART_matchPass){
		g_tick=0;
		motorFlag = 0 ;
		UART_sendByte(UART_Motor);
		TIMER1_COMP_setCallBack(Timer1_15Sec);
		LCD_displayStringRowColumn(0, 0, "Door Unlocking");
		while(motorFlag!=1){};
	}
	else errorAlarm();
}

