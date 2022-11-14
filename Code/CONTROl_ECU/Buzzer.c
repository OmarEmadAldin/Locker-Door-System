/*
 * Buzzer.c
 *
 *  Created on: 29 Oct 2022
 *      Author: Omar Ben Emad
 */
#include"Buzzer.h"
#include"gpio.h"
#include"common_macros.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the Buzzer device by:
 * 1. Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * 2.Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void){
	/*
	 * To make the buzzer output pin as needed*/
	GPIO_setupPinDirection(BuzzerPort,BuzzerPin,PIN_OUTPUT);
	/*To disable the Buzzer at the first
	 * by initializing its pin by zero
	 * */
	GPIO_writePin(BuzzerPort,BuzzerPin,BuzzerDisable);
}
/*
 * Description :
 * Function used to turn on the buzzer by using GPIO
 * */
void Buzzer_on(void){
	GPIO_writePin(BuzzerPort,BuzzerPin,BuzzerEnable);
}
/*
 * Description :
 * Function used to turn off the buzzer by using GPIO
 * */
void Buzzer_off(void){
	GPIO_writePin(BuzzerPort,BuzzerPin,BuzzerDisable);
}
