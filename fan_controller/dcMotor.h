/*
 *
 * Module: DC motor
 *
 * File Name: dcMototr.h
 *
 * Description: Header file for the AVR DC motor driver
 *
 * Layer: Hardware Abstraction Layer (HAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include"std_types.h"

#define DC_MOTOR_MAX_SPEED		100
#define DC_MOTOR_MIN_SPEED		0
#define DC_MOTOR_PORT			PORTD_ID
#define DC_MOTOR_PIN1			PIN5_ID
#define DC_MOTOR_PIN2			PIN6_ID

/*Error messages */
#define DC_MOTOR_NO_ERROR_MSG		((uint8*)"Function success")
#define DC_MOTOR_ERROR_STATE_MSG	((uint8*)"Incorrect Motor state")
#define DC_MOTOR_ERROR_SPEED_MSG	((uint8*)"Incorrect Motor speed")

typedef struct {
	enum
	{
		DC_MOTOR_NO_ERROR, DC_MOTOR_ERROR_STATE, DC_MOTOR_ERROR_SPEED
	}code;
	uint8* message;
}DC_MOTOR_ErrorType;

typedef enum {

	DC_MOTOR_STOP = 0, DC_MOTOR_ACW = 1, DC_MOTOR_CW = 2

}DcMotor_State;

/*
 * @brief the function will setup the pins of the motor
 * using gpio
 * */
DC_MOTOR_ErrorType DC_MOTOR_Init(void);

/*
 * @brief the function will spin the motor based on
 * the state and the speed of the motor
 *
 * @param DcMotor_State a state of Clock wise or anti clock wise
 *
 * @param uint8 speed it the speed of the motor
 * */
DC_MOTOR_ErrorType DC_MOTOR_Rotate(DcMotor_State a_state,uint8 a_speed);

#endif /* DCMOTOR_H_ */
