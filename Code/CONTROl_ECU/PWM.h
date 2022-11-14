 /******************************************************************************
 * PWM.h
 *
 *  Created on: 5 Oct 2022
 *      Author: Omar Ben Emad
 *******************************************************************************/
#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>
#include"gpio.h"

/*******************************************************************************
 *                          Registers Definitions                                  *
 *******************************************************************************/
#define Timer0Initialvalue				TCNT0
#define Timer0_CounterControlRegister	TCCR0
#define ForceOutputCompare				FOC0
#define WaveformGenerationMode0			WGM00
#define WaveformGenerationMode1			WGM01
#define Timer0Clock0					CS00
#define Timer0Clock1					CS01
#define Timer0Clock2					CS02
#define Timer0ComparePort				PORTB_ID
#define Enable_Pin						PIN3_ID
#define compareValue					OCR0
#define CompareOutputModePWM0			COM00
#define CompareOutputModePWM1			COM01
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the Timer for PWM use to control
 * The speed of the motor or any actuator .
 */
void PWM_Timer0_Start(uint8 duty_cycle);
#endif /* PWM_H_ */
