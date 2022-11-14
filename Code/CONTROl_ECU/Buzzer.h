/*
 * Buzzer.h
 *
 *  Created on: 28 Oct 2022
 *      Author: Omar Ben Emad
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"


#define BuzzerPort				PORTB_ID
#define BuzzerPin				PIN0_ID
#define BuzzerEnable			(1u)
#define BuzzerDisable			(0u)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
