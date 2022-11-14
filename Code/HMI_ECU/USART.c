/*
 * USART.c
 *
 *  Created on: 16 Oct 2022
 *      Author: Omar Ben Emad
 */


#include "USART.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const USART_Config * Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	SET_BIT(UCSRA,U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	SET_BIT(UCSRB,URSEL);

	switch(Config_Ptr->parity){
	case (Disabled) :
		CLEAR_BIT(UCSRC,UPM0);
		CLEAR_BIT(UCSRC,UPM1);
		break;
	case (Enabled_oddParity):
		SET_BIT(UCSRC,UPM0);
		CLEAR_BIT(UCSRC,UPM1);
		break;
	case (Enabled_evenParity):
		CLEAR_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;
	}
	switch(Config_Ptr->stop){
		case (oneBit) :
			CLEAR_BIT(UCSRC,USBS);
			break;
		case (twoBit):
			SET_BIT(UCSRC,USBS);
			break;
		}
	switch(Config_Ptr->ch){
		case(Size5) :
			CLEAR_BIT(UCSRC,UCSZ0);
			CLEAR_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			break;
		case(Size6) :
			SET_BIT(UCSRC,UCSZ0);
			CLEAR_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			break;
		case(Size7) :
			CLEAR_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			break;
		case(Size8) :
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			break;
		case(Size9) :
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			SET_BIT(UCSRC,UCSZ2);
			break;
	}
	switch(Config_Ptr->mode){
		case(Synchronous):
			SET_BIT(UCSRC,UMSEL);
			break;
		case(Asynchronous):
			CLEAR_BIT(UCSRC,UMSEL);
			break;
	}
	switch(Config_Ptr->rate){
	case(BaudRate2400):
			ubrr_value = (uint16)(((F_CPU / (BaudRate2400 * 8UL))) - 1);
			UBRRH = ubrr_value>>8;
			UBRRL = ubrr_value;
			break;
	case(BaudRate4800):
			ubrr_value = (uint16)(((F_CPU / (BaudRate4800 * 8UL))) - 1);
			UBRRH = ubrr_value>>8;
			UBRRL = ubrr_value;
			break;
	case(BaudRate9600):
			ubrr_value = (uint16)(((F_CPU / (BaudRate9600 * 8UL))) - 1);
			UBRRH = ubrr_value>>8;
			UBRRL = ubrr_value;
			break;
	case(BaudRate14400):
			ubrr_value = (uint16)(((F_CPU / (BaudRate9600 * 8UL))) - 1);
			UBRRH = ubrr_value>>8;
			UBRRL = ubrr_value;
			break;
	case(BaudRate19200):
			ubrr_value = (uint16)(((F_CPU / (BaudRate19200 * 8UL))) - 1);
			UBRRH = ubrr_value>>8;
			UBRRL = ubrr_value;
			break;
	}

}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
