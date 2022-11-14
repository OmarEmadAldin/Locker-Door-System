/*
 * Main_HMI.c
 *
 *  Created on: 31 Oct 2022
 *      Author: Omar Ben Emad
 */
#include"keypad.h"
#include"lcd.h"
#include <util/delay.h>
#include"std_types.h"
#include"HMI_MainFunc.h"
#include "USART.h"

USART_Config uartIntialization = {Disabled,Size8,Asynchronous,oneBit,BaudRate9600};

int main(void){
	uint8 key ;
	SREG|=(1<<7);
	UART_init(&uartIntialization);
	LCD_init();
	UART_sendByte(MC_Ready);
	key = (UART_recieveByte());
	if( key != UART_setPass){
		set_pass();
	};
	while(1){
		uint8 option;
		mainOptions();
		do{
			option = KEYPAD_getPressedKey();
		}while(option != '-' && option != '+');
		if (option == '-'){
			openDoorOption();
		}
		else if (option == '+'){
			changePassOption();
		}

	}
}
