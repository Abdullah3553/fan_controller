/*
 *
 * Module: App
 *
 * File Name: main.h
 *
 * Description: Header file for the fan controller application
 *
 * Layer: Application Layer
 *
 * Author: Abdullah Mahmoud
 *
 * */

#ifndef MAIN_H_
#define MAIN_H_

#include "dcMotor.h"
#include"lcd.h"
#include"lm35.h"
#define FAN_OFF 		FALSE
#define FAN_ON			TRUE
#define FAN_INIT		0x02
#define FAN_DIRECTION 	DC_MOTOR_CW

/*
 * @brief initializes the application and it required modules
 * */
void MAIN_init(void);

/*
 * @brief this function will display the fan state on the LCD screen
 * assuming the LCD was initialized properly.
 *
 * @param uint8 a_fanState indicate the current fan state
 *
 * @param uint8* a_oldFanState a pointer indicate the old(on the display) fan state
 * */
void MAIN_displayFanMessage(uint8 a_fanState, uint8 *a_oldFanState);

/*
 * @brief this function will display the temperature on the LCD screen
 * assuming the LCD was initialized properly.
 *
 * @param uint8 a_temprature indicate the new number
 *
 * @param uint8* a_oldTemp apointer indicate the old(on the display) number
 * */
void MAIN_displayTemperatureMessage(uint8 a_temprature, uint8* a_oldTemp);

/*
 * @brief this function adjust the fan speed based on the
 * current read speed and the current speed of the fan and update
 * the fan status based on both new, old speed
 *
 * @param uint8 a_newSpeed the current read speed
 *
 * @param uint8* a_oldSpeed a pointer to the current fan speed
 *
 * @param uint8* a_fanStatus a pointer to the fanStatus
 * */
void MAIN_updateFanSpeed(uint8 a_newSpeed, uint8* a_oldSpeed, uint8* a_fanStatus);
#endif /* MAIN_H_ */
