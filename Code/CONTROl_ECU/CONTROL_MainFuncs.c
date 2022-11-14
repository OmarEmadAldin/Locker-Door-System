/*
 * CONTROL_MainFuncs.c
 *
 *  Created on: 31 Oct 2022
 *      Author: Omar Ben Emad
 */
#include"CONTROL_MainFuncs.h"
#include"std_types.h"

#define Size 5

boolean Check_State ;
boolean Motor_State;

uint8 UART_String[20];
uint16 passwordOne[Size];

uint8 buzzerFlag;
uint8 motorFlag ;

uint8 trial =3;
uint8 i ;
uint8 g_tick;

uint8 PassState;

Timer1_ConfigType Sec = {0 , 7813 , Prescaler1024 , Compare };

void PassIsSetinEEPROM(){
	EEPROM_readByte(PasswordaddressFlag, &PassState);
	UART_sendByte(PassState);
}

void readPassFromEEPROM(){
	for(i=0 ; i<Size ; i++){
		EEPROM_readByte( (Passwordaddress+i), (passwordOne+i) );
	}
}

void updatePassword(){
	for( i = 0 ; i < Size ; i++)
		{
			passwordOne[i] = UART_recieveByte(); /* Getting the new password from MCU1 */
			EEPROM_writeByte((passwordOne+i), passwordOne[i]); /* Write it in the EEPROM */
		}
		EEPROM_writeByte(PasswordaddressFlag, PasswordSet);
}

void passChecked(){
	uint8 checkPass[Size];
	for(i = 0 ; i< Size ; i++){
		checkPass[i] = UART_recieveByte();
		UART_sendByte(MC_Ready);
	}
	for(i = 0 ; i< Size ; i++){
		if(passwordOne[i] != *(checkPass+i)){
			UART_sendByte(UART_missMatchPass);
			return;
		}
	}
	UART_sendByte(UART_matchPass);
}
void BuzzerError(){
	g_tick = 0;
	buzzerFlag = 0 ;
	Buzzer_on();
	TIMER1_COMP_setCallBack(oneMinute);
	while(buzzerFlag == 0){};
	Buzzer_off();
}
void openDoor(){
	g_tick = 0;
	motorFlag=0;
	TIMER1_COMP_setCallBack(Timer1_15Sec);
	DcMotor_Rotate(CW,255);
	while(motorFlag==0);
}
void Timer1_3Sec(){
	g_tick++;
	if(g_tick==3){
		g_tick =0 ;
		UART_recieveByte();
		DcMotor_Rotate(A_CW,255);
		TIMER1_COMP_setCallBack(Timer1_15Sec);

	}
}
void Timer1_15Sec(){
	g_tick++;
	if(g_tick==15){
		g_tick =0 ;
		if(Motor_State == TRUE){
			UART_recieveByte();
			DcMotor_Rotate(STOP,255);
			TIMER1_COMP_setCallBack(Timer1_3Sec);
			Motor_State = FALSE;
		}
		else if(Motor_State == FALSE){
				Motor_State = TRUE;
				buzzerFlag = 0;
				DcMotor_Rotate(STOP,255);
				Timer1_deInit();
		}
	}
}
void oneMinute(){
	g_tick ++;
	if(g_tick == 60){
		g_tick = 0;
		buzzerFlag = 0;
		Timer1_deInit();
	}
}
