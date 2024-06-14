/*
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: The header file for the ADC module. The file should contain the function prototypes
 * required by the ADC Module.
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 */

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"

#define ADC_BITS					10
#define ADC_MAX						1023 /* ( 2 to the power of ADC_BITS ) - 1 */
#define ADC_CHANNELS				8
#define ADC_CONVERSION_COMPLETED	LOGIC_HIGH
#define ADC_CONVERSION_STARTED		LOGIC_LOW
#define ADC_VREF					2.56

#define ADC_SUCCESS					0
#define ADC_ERROR_NOT_INIT			ADC_SUCCESS + 1
#define ADC_ERROR_WRONG_CHANNEL		ADC_ERROR_NOT_INIT + 1
#define ADC_ERROR_WRONG_MODE		ADC_ERROR_WRONG_CHANNEL + 1
#define ADC_ERROR_NULL_PTR			ADC_ERROR_WRONG_MODE + 1

typedef uint8 ADC_ErrorType;

typedef enum
{
	ADC_AREF = 0, ADC_AVCC = 1, ADC_INTERNAL = 3
} ADC_VrefType;

typedef enum
{
	ADC_POLLING, ADC_INTERRUPT
} ADC_WorkingModeType;

typedef enum
{
	ADC_PRESCALER_2 = 1, ADC_PRESCALER_4 = 2, ADC_PRESCALER_8 = 3,
	ADC_PRESCALER_16 = 4, ADC_PRESCALER_32 = 5, ADC_PRESCALER_64 = 6,
	ADC_PRESCALER_128 = 7
} ADC_prescalerType;

typedef struct
{
	ADC_VrefType vref;
	ADC_WorkingModeType mode;
	ADC_prescalerType prescaler;

}ADC_configType;

/*Global Shared Data*/


/*
 * @brief initialize the ADC module
 *
 * @param a_config contain the dynamic configuration for the module
 *
 * @return void
 * */
void ADC_init(const ADC_configType * a_config);

/*
 * @brief undo the initialization on the ADC module
 *
 * @return void
 * */
void ADC_Deinit(void);

/**
 * @brief return wither the ADC is initialized or not.
 *
 * @param void
 *
 * @return uint8 TRUE or FALSE based on ADC_initialized value
 *
 * */
uint8 ADC_isInitialized(void);

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
uint8 ADC_isPolling(void);

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
ADC_ErrorType ADC_readChannelPolling(uint8 a_channel, uint8 * a_doneFlag, uint16 * a_result);

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
ADC_ErrorType ADC_readChannelInterrupt(uint8 a_channel, uint8 * a_doneFlag, uint16 * a_result);

#endif /* ADC_H_ */
