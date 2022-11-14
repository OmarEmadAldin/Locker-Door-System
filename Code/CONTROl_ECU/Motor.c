 /******************************************************************************
  * Motor.c
 *
 *  Created on: 5 Oct 2022
 *      Author: Omar Ben Emad
 *******************************************************************************/
#include "gpio.h"
#include "Motor.h"
#include "common_macros.h"
#include"PWM.h"
void DcMotor_Init(void){
	GPIO_writePin(PORTA_ID,Motor_inputPin1,LOGIC_LOW);
	GPIO_writePin(PORTA_ID,Motor_inputPin2,LOGIC_LOW);
	GPIO_setupPinDirection(PORTA_ID,Motor_inputPin1,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,Motor_inputPin2,PIN_OUTPUT);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch(state){
	case(STOP):
		GPIO_writePin(PORTA_ID,Motor_inputPin1,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,Motor_inputPin2,LOGIC_LOW);
		break;
	case(CW):
		GPIO_writePin(PORTA_ID,Motor_inputPin1,LOGIC_HIGH);
		GPIO_writePin(PORTA_ID,Motor_inputPin2,LOGIC_LOW);
		break;
	case(A_CW):
		GPIO_writePin(PORTA_ID,Motor_inputPin1,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,Motor_inputPin2,LOGIC_HIGH);
		break;
	}
	switch(speed){
		case (25):
			PWM_Timer0_Start(64);
			break;
		case (50):
			PWM_Timer0_Start(128);
			break;
		case (75):
			PWM_Timer0_Start(192);
			break;
		case (100):
			PWM_Timer0_Start(255);
			break;
		default:
			PWM_Timer0_Start(0);
			break;
	}
}
