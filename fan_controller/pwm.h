/*
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the AVR PWM driver
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"

#define PWM_OUTPUT_PORT		PORTB_ID
#define PWM_OUTPUT_PIN		PIN3_ID
#define PWM_MAX_VALUE		0xff

/*
 * @brief the function will start timer 0 with pwm mode based on the duty cycle
 *
 * @param uint8 a_dutyCycle the required duty cycle
 *
 * @return void
 * */
void PWM_Timer0_Start(uint8 a_dutyCycle);

/*
 * @brief reset registers to 0
 * */
void PWM_deInit(void);

#endif /* PWM_H_ */
