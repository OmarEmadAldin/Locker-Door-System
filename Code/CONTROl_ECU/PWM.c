 /******************************************************************************
 * PWM.c
 *
 *  Created on: 5 Oct 2022
 *      Author: Omar Ben Emad
 *******************************************************************************/
#include"PWM.h"
#include"std_types.h"
#include"common_macros.h"
#include"Motor.h"

void PWM_Timer0_Start(uint8 duty_cycle){
	Timer0Initialvalue = LOGIC_LOW;
	compareValue = duty_cycle;
	/*	first two lines are used to select the wave form
	 *	we chose Fats PWM Mode
	 *	WGM01 = 1 && WGM00 = 1
	 */
	if(duty_cycle == 0 ){
		Timer0_CounterControlRegister = LOGIC_LOW;
	}
	else{
	GPIO_setupPinDirection(Timer0ComparePort,Enable_Pin,PIN_OUTPUT);

	SET_BIT(Timer0_CounterControlRegister,WaveformGenerationMode0);
	SET_BIT(Timer0_CounterControlRegister,WaveformGenerationMode1);
	/*	To select the prescaler
	 * 	Here it's 8
	 * 	CS01 = 1 , CS00= 0 , CS02=0
	 */
	SET_BIT(Timer0_CounterControlRegister,Timer0Clock1);
	CLEAR_BIT(Timer0_CounterControlRegister,Timer0Clock0);
	CLEAR_BIT(Timer0_CounterControlRegister,Timer0Clock2);
	/*	We access to bits to select the mode
	 * 	here the non inverting mode is selected
	 * 	So , COM01 = 1 && COM00 = 0
	 * */
	CLEAR_BIT(Timer0_CounterControlRegister,CompareOutputModePWM0);
	SET_BIT(Timer0_CounterControlRegister,CompareOutputModePWM1);
	/*	FCO0 is zero when we use PWM
	 * 	So bit is cleared
	 * */
	CLEAR_BIT(Timer0_CounterControlRegister,ForceOutputCompare);
	/*	To set the enable pin that change the motor speed
	 * 	it's defined as PB3 Pin
	 * */
	}
}

