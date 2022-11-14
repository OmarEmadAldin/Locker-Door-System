 /******************************************************************************
 * Motor.h
 *
 *  Created on: 5 Oct 2022
 *      Author: Omar Ben Emad
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

/***************************************************************************************
 * 							 Types Declaration
 ***************************************************************************************/
typedef enum {
	STOP , A_CW , CW
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Motor_inputPin1		PIN0_ID
#define Motor_inputPin2		PIN1_ID
#define Motor_enablePin		PIN3_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DcMotor_Init(void);
/*
 * 	Functions used to initialise motor variables
 *  The Function responsible for setup the direction
 *  for the two motor pins through the GPIO driver.
 *  Stop at the DC-Motor at the beginning through the GPIO driver.
 *
*/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
/*
 * The function responsible for rotate the DC Motor CW/ or A-CW
 * or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 *
 */
#endif
