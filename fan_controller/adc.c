/*
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: The source file that contain the function definitions from adc.h
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 */
#include"adc.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"

/*Global Variables */
volatile static uint16 * ADC_g_digitalValue = NULL_PTR;
volatile static uint8 * ADC_g_doneFlag = NULL_PTR;
static uint8 ADC_g_initialized = FALSE;

/*
 * @brief will be called once the ADC module finish reading a channel
 * */
ISR(ADC_vect)
{
	/*ADC flag is being cleared automatically*/

	if(ADC_g_digitalValue != NULL_PTR && ADC_g_doneFlag != NULL_PTR )
	{
		/*To prevent a run-time error is some cases */
		*ADC_g_digitalValue = ADC; /*save the digital value in the user passed variable */
		*ADC_g_doneFlag = ADC_CONVERSION_COMPLETED;/*Mark the users flag as COMPLETED*/

		ADC_g_doneFlag = NULL_PTR;/*Reset the global flag to NULL to be used next time*/
		ADC_g_digitalValue = NULL_PTR; /*Reset the pointer for next usage*/
	}

}

/*
 * @brief initialize the ADC module
 *
 * @param a_config contain the dynamic configuration for the module
 *
 * @return void
 * */
void ADC_init(const ADC_configType * a_config)
{

	/*
	 * Apply the selected vref.
	 * Clear channel selecting bits.
	 * Clear adjust left
	 * */
	ADMUX = (a_config->vref << REFS0);
	/*
	 * ADC Enable
	 * Apply the selected prescaler
	 * Apply the working mode (polling or interrupt)
	 * */
	ADCSRA = (1 << ADEN) | (a_config->prescaler << ADPS0) | (a_config->mode << ADIE);

	if(a_config->mode == ADC_INTERRUPT)
	{
		/*To ensure interrupt compatibility*/

		SREG |= (1 << SREG_I);/*Set the i-bit*/
	}

	ADC_g_initialized = TRUE;/*Used for error checking*/

}


/*
 * @brief undo the initialization on the ADC module
 *
 * @return void
 * */
void ADC_Deinit(void)
{
	ADMUX = 0; /*Clearing the selected vref*/
	ADCSRA = 0; /*Disabling the ADC module*/
	ADC_g_digitalValue = NULL_PTR;/*reset to the initial value */
	ADC_g_doneFlag = NULL_PTR;/*reset to the initial value */
	ADC_g_initialized = FALSE;/*reset to the initial value */
}


/**
 * @brief return wither the ADC is initialized or not.
 *
 * @param void
 *
 * @return uint8 TRUE or FALSE based on ADC_initialized value
 *
 * */
uint8 ADC_isInitialized(void)
{
	/*This function provide a read-only on ADC_g_initialized for upper modules to handle errors */
	/*Also, To ensure reliability that only the ADC module will init this variable */
    return ADC_g_initialized;
}

/**
 * @brief return wither the ADC_mode is interrupt mode or polling mode
 *
 * @param void
 *
 * @return uint8 TRUE if the mode is polling
 *
 * @return uint8 FALSE if ht mode is interrupt
 *
 * */
uint8 ADC_isPolling(void)
{
	return GET_BIT(ADCSRA, ADIE) == 0? TRUE:FALSE;
}

/*
 *
 * @brief read the digital value on the passed channel.
 *
 * @param a_channel the channel to be read from
 *
 * @param a_doneFlag a pointer to mark as completed or not
 *
 * @param a_result a pointer to the result variable
 *
 * @return uint8 to indicate the an error or a SUCCESS of the process.
 * */
uint8 ADC_readChannelPolling(uint8 a_channel, uint8 * a_doneFlag, uint16 * a_result)
{
	/*validate the configurations*/
	if(ADC_g_initialized == FALSE)
	{
		/*ADC module was not initialized */
		return ADC_ERROR_NOT_INIT;
	}
	if(ADC_isPolling() == FALSE)
	{
		/*the user is trying to use interrupt mode with polling mode*/
		return ADC_ERROR_WRONG_MODE;
	}

	/*Validate user input*/
	if(a_channel >= ADC_CHANNELS)
	{
		/*User sent wrong channel */
		return ADC_ERROR_WRONG_CHANNEL;
	}
	if(a_doneFlag == NULL_PTR || a_result == NULL_PTR)
	{
		/*The user sent a null pointer*/
		return ADC_ERROR_NULL_PTR;
	}
	ADMUX = (ADMUX & 0xE0) | (a_channel & 0x1F) ; /*Selecting the channel from the argument*/
	*a_doneFlag = ADC_CONVERSION_STARTED;	/*Indicate the conversion starting*/
	SET_BIT(ADCSRA,  ADSC);/*starting the adc*/
	while(GET_BIT(ADCSRA, ADIF) == 0); /* polling until the reading is over*/
	SET_BIT(ADCSRA, ADIF); /*Clear the ADC flag by writing 1 to it*/
	*a_doneFlag = ADC_CONVERSION_COMPLETED;
	*a_result = ADC; /*save the read value*/
	return ADC_SUCCESS;/*The function handled the request successfully*/
}

/*
 * @brief start the ADC on the passed channel with interrupt mode.
 * the digital value read by the ADC module will be handled on ISR
 *
 * @param a_channel the channel to be read from
 *
 * @param a_doneFlag a pointer to mark as completed or not
 *
 * @param a_result a pointer to the result variable
 *
 * @return uint8 to indicate the an error or a SUCCESS of the process.
 * */
uint8 ADC_readChannelInterrupt(uint8 a_channel, uint8 * a_doneFlag, uint16 * a_result)
{
	/*validate the configurations*/
	if(ADC_g_initialized == FALSE)
	{
		/*ADC module was not initialized */
		return ADC_ERROR_NOT_INIT;
	}
	if(ADC_isPolling() == FALSE)
	{
		/*the user is trying to use interrupt mode with polling mode*/
		return ADC_ERROR_WRONG_MODE;
	}

	/*Validate user input*/
	if(a_channel >= ADC_CHANNELS)
	{
		/*User sent wrong channel */
		return ADC_ERROR_WRONG_CHANNEL;
	}
	if(a_doneFlag == NULL_PTR || a_result == NULL_PTR)
	{
		/*The user sent a null pointer*/
		return ADC_ERROR_NULL_PTR;
	}

	ADMUX = (ADMUX & 0xE0) | (a_channel & 0x1F) ; /*Selecting the channel from the argument*/
	ADC_g_doneFlag = a_doneFlag;	/*Save the user passed flag*/
	*ADC_g_doneFlag = ADC_CONVERSION_STARTED; /*Indicate the conversion starting*/

	ADC_g_digitalValue = a_result; /*Save the user passed result*/
	SET_BIT(ADCSRA,  ADSC);/*starting the adc*/
	return ADC_SUCCESS;/*The function handled the request successfully*/
}


