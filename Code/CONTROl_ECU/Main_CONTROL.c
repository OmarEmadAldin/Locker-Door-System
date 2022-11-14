/*
 * Main_CONTROL.c
 *
 *  Created on: 2 Nov 2022
 *      Author: Omar Ben Emad
 */

#include"CONTROL_MainFuncs.h"
#include"USART.h"
#include"Motor.h"
#include"Buzzer.h"
#include"twi.h"

USART_Config uartIntialization = {Disabled,Size8,Asynchronous,oneBit,BaudRate9600};
TWI_ConfigType twi_Intialization = {400,NormalMode};
int main(){
	SREG|=(1<<7);
	TWI_init(&twi_Intialization);
	UART_init(&uartIntialization);
	DcMotor_Init();
	while((UART_recieveByte()) != (MC_Ready)){};
	PassIsSetinEEPROM();

	while(1){
		uint8 recieveUnit = (UART_recieveByte());
		switch(recieveUnit){
		case(UART_sendPass):
				updatePassword();
				break;
		case(UART_Motor):
				openDoor();
				break;
		case(UART_Buzzer):
				BuzzerError();
				break;
		case(UART_check):
				passChecked();
				break;
		}
	}
}

