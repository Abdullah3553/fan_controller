/*
 * Module: LM35 sensor
 *
 * File name: lm35.h
 *
 * Description: Header file of the lm35 temperature module
 *
 * Layer: Hardware Abstraction Layer (HAL)
 *
 * Author: Abdullah Mahmoud
 * */

#ifndef LM35_H
#define LM35_H

#include"std_types.h"

#define LM35_CHANNEL		2
#define LM35_MV_PER_DEGREE	10
#define LM35_V_PER_DEGREE	((float32) LM35_MV_PER_DEGREE / 1000)


/*
 * Description:
 * init the sensor's channel for the adc.
 * */
void LM35_init(void);

/*
 * Description:
 * The function will read an ADC channel for LM35 temperature sensor.
 * Returns the temperature read by the sensor
 * possible return values :
 * a number from LM35_MIN_DEGREE -> LM35_MAX_DEGREE
 * */
uint8 LM35_getTemperature(void);

#endif
