/*
 * Timer1.c
 *
 *  Created on: 29 Oct 2022
 *      Author: Omar Ben Emad
 */
#include"Timer1.h"
#include "avr/interrupt.h"
#include"std_types.h"
#include"common_macros.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
Timer1_ConfigType *init;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;
/*******************************************************************************
 *                             	    ISR		   		                           *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}
/*******************************************************************************
 *                               Functions		                               *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	TCNT1 = Config_Ptr->initial_value;
	switch(Config_Ptr->mode){
	case(Compare):
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			OCR1A = Config_Ptr->compare_value;
			SET_BIT(TIMSK,OCIE1A);
			break;
	case(Normal):
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			SET_BIT(TIMSK,TOIE1);
			break;
	}
	switch(Config_Ptr->prescaler){
	case(Prescaler1):
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
		break;
	case(Prescaler8):
		CLEAR_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
		break;
	case(Prescaler64):
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
		break;
	case(Prescaler256):
		CLEAR_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
		break;
	case(Prescaler1024):
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
		break;
	}
}
void Timer1_deInit(void){
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}
void TIMER1_COMP_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr1 = a_ptr;
}

void TIMER1_OVF_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr2 = a_ptr;
}
