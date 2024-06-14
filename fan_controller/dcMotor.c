/*
 *
 * Module: DC motor
 *
 * File Name: dcMototr.c
 *
 * Description: Source file for the AVR DC motor driver
 *
 * Layer: Hardware Abstraction Layer (HAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */
#include"dcMotor.h"
#include"gpio.h"
#include"pwm.h"


/*
 * @brief the function will stop the motor.
 * */
static void DC_MOTOR_stopMotor(void)
{
	GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN1, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN2, LOGIC_LOW);
	PWM_deInit();
}
/*
 * @brief the function will setup the pins of the motor
 * using gpio. Also it will initlize the pwm Mode
 * */
DC_MOTOR_ErrorType DC_MOTOR_Init(void)
{
	DC_MOTOR_ErrorType response = {DC_MOTOR_NO_ERROR, DC_MOTOR_NO_ERROR_MSG};
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN2, PIN_OUTPUT);
	PWM_Timer0_Start(0);
	return response;
}

/*
 * @brief the function will spin the motor based on
 * the state and the speed of the motor
 *
 * @param DcMotor_State a state of Clock wise or anti clock wise
 *
 * @param uint8 speed it the speed of the motor
 * */
DC_MOTOR_ErrorType DC_MOTOR_Rotate(DcMotor_State a_state,uint8 a_speed)
{
	DC_MOTOR_ErrorType response = {DC_MOTOR_NO_ERROR, DC_MOTOR_NO_ERROR_MSG};
	uint16 compareValue = 0;
	/*Input validation*/

	/*Check if states are correct*/
	if(a_state > DC_MOTOR_CW)
	{
		/*if true then the state is incorrect */
		response.code = DC_MOTOR_ERROR_STATE;
		response.message = DC_MOTOR_ERROR_STATE_MSG;
		return response;
	}

	/*Check if the speed within the speed limits */
	if(a_speed > DC_MOTOR_MAX_SPEED)
	{
		/*If true that means the speed is not correct*/
		response.code = DC_MOTOR_ERROR_SPEED;
		response.message = DC_MOTOR_ERROR_SPEED_MSG;
		return response;
	}

	/*If we reach this area that means the function is safe to be executed
	 * using these arguments */

	/*
	 * if the state is DC_MOTOR_STOP(in other words 0)
	 * 	then we will write 00 to the both PINS
	 *
	 * if the state is DC_MOTOR_ACW(in other words 1)
	 * 	then we will write
	 * 	LOGIC_LOW to DC_MOTOR_PIN1
	 * 	and
	 * 	LOGIC_HIGH to DC_MOTOR_PIN2
	 *
	 * if the state is DC_MOTOR_CW(in other words 2)
	 * 	then we will write
	 * 	LOGIC_HIGH to DC_MOTOR_PIN1
	 * 	and
	 * 	LOGIC_LOW to DC_MOTOR_PIN2
	 * */
	switch(a_state)
	{
	case DC_MOTOR_ACW:
		GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN2, LOGIC_HIGH);
		break;
	case DC_MOTOR_CW:
		GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN2, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_PIN1, LOGIC_HIGH);
		break;
	default:
		DC_MOTOR_stopMotor();
		return response;
	}

	/*
	 * to find the required compare value based on the speed :
	 *
	 * 					user_input			MAX_VALUE
	 * 	motor_speed		50					100
	 *
	 * 	PWM_compare		x					255
	 *
	 * 					---- Solve for x ----
	 *
	 * 	x = (50 * 255) / 100
	 * 	x = 127 (50% duty cycle)
	 * */
	compareValue = (((uint16)a_speed * PWM_MAX_VALUE)/DC_MOTOR_MAX_SPEED);

	PWM_Timer0_Start((uint8)compareValue);
	return response;
}
