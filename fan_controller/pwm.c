/*
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the AVR PWM driver
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */

#include"pwm.h"
#include"avr/io.h"

/*
 * @brief the function will start timer 0 with pwm mode based on the duty cycle
 *
 * @param uint8 a_dutyCycle the required duty cycle
 *
 * @return void
 * */
void PWM_Timer0_Start(uint8 a_dutyCycle)
{
	/*
	 * Description:
	 * Generate a PWM signal with frequency 500Hz
	 * Timer0 will be used with pre-scaler F_CPU/8
	 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
	 * 64  -> 25 Duty Cycle
	 * 128 -> 50 Duty Cycle
	 * 192 -> 75 Duty Cycle
	 * 255 -> 100 Duty Cycle
	 */
	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = a_dutyCycle; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

/*
 * @brief reset registers to 0
 * */
void PWM_deInit(void)
{
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	DDRB = DDRB & ~(1 << PB3);
}
