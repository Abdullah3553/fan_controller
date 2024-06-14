/*
 * Module: LM35 sensor
 *
 * File name: lm35.c
 *
 * Description: THe source file for the LM35 sonsor
 *
 * Layer: Hardware Abstraction Layer (HAL)
 *
 * Author: Abdullah Mahmoud
 * */
#include"lm35.h"
#include"adc.h"


/*
 * Description:
 * init the sensor's channel for the adc.
 * */
void LM35_init(void)
{
	/*Some other configuration maybe implemented here */
	ADC_configType config = {ADC_INTERNAL, ADC_POLLING, ADC_PRESCALER_8};
	ADC_init(&config);
}

/*
 * Description:
 * The function will read an ADC channel for LM35 temperature sensor.
 * Returns the temperature read by the sensor
 * possible return values :
 * a number from LM35_MIN_DEGREE -> LM35_MAX_DEGREE
 * */
uint8 LM35_getTemperature(void)
{
	/*Read the ADC value*/
	uint16 digitalValue = 0;
	uint8 temperature = 0, adcDoneFlag = 0;
	ADC_readChannelPolling(LM35_CHANNEL,&adcDoneFlag, &digitalValue );

	/*Calculate the temperature */
	temperature = (uint8)((float32)digitalValue  * ((float32)ADC_VREF / ADC_MAX) / (LM35_V_PER_DEGREE));
	/*Return the value */
	return temperature;
}
