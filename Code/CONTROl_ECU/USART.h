/*
 * USART.h
 *
 *  Created on: 16 Oct 2022
 *      Author: Omar Ben Emad
 */
/**********************************************************************************/
#ifndef USART_H_
#define USART_H_

#include "std_types.h"
#include<avr/io.h>

typedef enum{
	 Disabled, Enabled_oddParity , Enabled_evenParity
}parityCheck;

typedef enum{
	Size5, Size6,Size7,Size8,Size9
}charactreSize;

typedef enum{
	Synchronous,Asynchronous
}modeSelect;

typedef enum{
	oneBit , twoBit
}stopSelect;

typedef enum{
	BaudRate2400 = 2400 , BaudRate4800 = 4800 , BaudRate9600 = 9600 ,\
	BaudRate14400 = 14400 , BaudRate19200 = 19200
}BaudRate;

typedef struct {
	parityCheck parity ;
	charactreSize ch ;
	modeSelect mode;
	stopSelect stop ;
	BaudRate rate ;
}USART_Config;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const USART_Config * Config_Ptr);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #


#endif /* USART_H_ */
