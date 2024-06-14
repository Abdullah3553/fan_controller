/*
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: The function definitions for the functions in gpio.h file
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */

/******************Includes******************/
#include"gpio.h"
#include"common_macros.h"
#include<avr/io.h>

/******************Global Variables******************/

/*None*/

/******************Function Definitions******************/

/*
 * Description:
 * The function will take the port id and the pin id and setup that pin as PIN_INPUT or PIN_OUTPUT
 * if the port id or the pin id are not correct, the function will return without doing anything
 *
 * Possible return value:
 * void
 * */
void GPIO_setupPinDirection(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId, \
		GPIO_PinDirectionType a_direction)
{
	/*Check the Correctness of port_id and pin_id*/
	if( a_portId >= PORTS_NUM || a_portId < 0
		||a_pinId >= PINS_PER_PORT_NUM || a_pinId < 0)
	{
		/*invalid input*/
		return;/*Not handling the request*/
	}
	else
	{
		/*Valid input*/

		/*Choose the port*/
		switch(a_portId)
		{
		case PORTA_ID:
			if(a_direction == PIN_INPUT) /*if the direction is input*/
			{
				/*bit should be 0 for input*/
				CLEAR_BIT(DDRA, a_pinId);
			}
			else /*Direction is output (not input)*/
			{
				/*bit should be 1 for output*/
				SET_BIT(DDRA, a_pinId);
			}
			break;
		case PORTB_ID:
			if(a_direction == PIN_INPUT) /*if the direction is input*/
			{
				/*bit should be 0 for input*/
				CLEAR_BIT(DDRB, a_pinId);
			}
			else /*Direction is output (not input)*/
			{
				/*bit should be 1 for output*/
				SET_BIT(DDRB, a_pinId);
			}
			break;
		case PORTC_ID:
			if(a_direction == PIN_INPUT) /*if the direction is input*/
			{
				/*bit should be 0 for input*/
				CLEAR_BIT(DDRC, a_pinId);
			}
			else /*Direction is output (not input)*/
			{
				/*bit should be 1 for output*/
				SET_BIT(DDRC, a_pinId);
			}
			break;
		case PORTD_ID:
			if(a_direction == PIN_INPUT) /*if the direction is input*/
			{
				/*bit should be 0 for input*/
				CLEAR_BIT(DDRD, a_pinId);
			}
			else /*Direction is output (not input)*/
			{
				/*bit should be 1 for output*/
				SET_BIT(DDRD, a_pinId);
			}
			break;
		default:
			/*doing nothing*/
			break;
		}
	}
	return;
}

/*
 * Description:
 * The function will take port id and setup that port as PORT_INPUT or PORT_OUTPUT.
 * If the port id is not correct, the function will return without doing anything.
 *
 * Possible return value:
 * void
 * */
void GPIO_setupPortDirection(GPIO_PortIdType a_portId, GPIO_PortDirectionType a_direction)
{
	/*Check the Correctness of port_id and pin_id*/
	if( a_portId >= PORTS_NUM || a_portId < 0)
	{
		/*invalid input*/
		return;/*Not handling the request*/
	}
	else
	{
		/*Valid input*/
		switch(a_portId)
		{
		case PORTA_ID:
			if(a_direction == PORT_INPUT) /*if the direction is input*/
			{
				DDRA = PORT_INPUT; /*set the port with PORT_INPUT*/
			}
			else /*if the direction is output (not input)*/
			{
				DDRA = PORT_OUTPUT;/*set the port with PORT_OUTPUT*/
			}
			break;
		case PORTB_ID:
			if(a_direction == PORT_INPUT) /*if the direction is input*/
			{
				DDRB = PORT_INPUT; /*set the port with PORT_INPUT*/
			}
			else /*if the direction is output (not input)*/
			{
				DDRB = PORT_OUTPUT;/*set the port with PORT_OUTPUT*/
			}
			break;
		case PORTC_ID:
			if(a_direction == PORT_INPUT) /*if the direction is input*/
			{
				DDRC = PORT_INPUT; /*set the port with PORT_INPUT*/
			}
			else /*if the direction is output (not input)*/
			{
				DDRC = PORT_OUTPUT;/*set the port with PORT_OUTPUT*/
			}
			break;
		case PORTD_ID:
			if(a_direction == PORT_INPUT) /*if the direction is input*/
			{
				DDRD = PORT_INPUT; /*set the port with PORT_INPUT*/
			}
			else /*if the direction is output (not input)*/
			{
				DDRD = PORT_OUTPUT;/*set the port with PORT_OUTPUT*/
			}
			break;
		default:
			/*Doing nothing*/
			break;
		}
	}
	return;
}

/*
 * Description:
 * The function will read pin id from the port in port id and return the read value.
 * if port id or pin id was not correct, the function will return LOGIC_LOW
 *
 * Possible return values:
 * LOGIC_LOW, the pin value from the port (0, 255)
 * */
uint8 GPIO_readPin(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId)
{
	uint8 pinValue = 0x00; /*To store the return value*/
	/*Check the Correctness of port_id and pin_id*/
	if( a_portId >= PORTS_NUM || a_portId < 0
		||a_pinId >= PINS_PER_PORT_NUM || a_pinId < 0)
	{
		/*invalid input*/
		pinValue = LOGIC_LOW;/*setting the return value*/
	}
	else
	{
		/*Valid input*/

		switch(a_portId)
		{
		case PORTA_ID:
			pinValue = READ_BIT(PINA, a_pinId);/*Reading the pin_id from PORTA*/
			break;
		case PORTB_ID:
			pinValue = READ_BIT(PINB, a_pinId);/*Reading the pin_id from PORTB*/
			break;
		case PORTC_ID:
			pinValue = READ_BIT(PINC, a_pinId);/*Reading the pin_id from PORTC*/
			break;
		case PORTD_ID:
			pinValue = READ_BIT(PIND, a_pinId);/*Reading the pin_id from PORTD*/
			break;
		default:
			/*Doing nothing*/
			break;
		}
		if(pinValue != LOGIC_LOW)/*if the value is not LOGIC_LOW*/
		{
			/*set the value to be LOGIC_HIGH*/
			pinValue = LOGIC_HIGH;
		}
		/*but if the value was LOGIC_LOW then dont change it*/
	}
	return pinValue;
}

/*
 * Description:
 * The function will read the value on the port in port id.
 * If the port id was not correct, the function will return LOGIC_LOW
 *
 * Possible return values:
 * LOGIC_LOW, the port value (0, 255)
 * */
uint8 GPIO_readPort(GPIO_PortIdType a_portId)
{
	uint8 portValue = 0x00; /*To store the return value*/
	/*Check the Correctness of port_id and pin_id*/
	if( a_portId >= PORTS_NUM || a_portId < 0)
	{
		/*invalid input*/
		portValue = LOGIC_LOW;/*setting the return value*/
	}
	else
	{
		/*Valid input*/
		switch(a_portId)
		{
		case PORTA_ID:
			portValue = PINA;/*Reading the pin_id from PORTA*/
			break;
		case PORTB_ID:
			portValue = PINB;/*Reading the pin_id from PORTB*/
			break;
		case PORTC_ID:
			portValue = PINC;/*Reading the pin_id from PORTC*/
			break;
		case PORTD_ID:
			portValue = PIND;/*Reading the pin_id from PORTD*/
			break;
		default:
			/*Doing nothing*/
			break;
		}
	}
	return portValue;
}

/*
 * Description:
 * The function will write the pin value on the pin labeled in pin_id inside the port labeled in port id.
 * if pin id or port id was not correct, the function will return without writing any value
 *
 * Possible return values:
 * void
 * */
void GPIO_writePin(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId, uint8 a_pinValue)
{
	if( a_portId >= PORTS_NUM || a_portId < 0
		||a_pinId >= PINS_PER_PORT_NUM || a_pinId < 0
		||a_pinValue > 1)
	{
		/*invalid input*/
		return;/*not handling the request*/
	}
	else
	{
		/*Valid input*/
		switch(a_portId)
		{
		case PORTA_ID:
			if(a_pinValue == LOGIC_LOW)
			{
				/* write 0 to the pin */
				CLEAR_BIT(PORTA, a_pinId);
			}
			else
			{
				/* Write 1 to the pin */
				SET_BIT(PORTA, a_pinId);
			}
			break;
		case PORTB_ID:
			if(a_pinValue == LOGIC_LOW)
			{
				/* write 0 to the pin */
				CLEAR_BIT(PORTB, a_pinId);
			}
			else
			{
				/* Write 1 to the pin */
				SET_BIT(PORTB, a_pinId);
			}
			break;
		case PORTC_ID:
			if(a_pinValue == LOGIC_LOW)
			{
				/* write 0 to the pin */
				CLEAR_BIT(PORTC, a_pinId);
			}
			else
			{
				/* Write 1 to the pin */
				SET_BIT(PORTC, a_pinId);
			}
			break;
		case PORTD_ID:
			if(a_pinValue == LOGIC_LOW)
			{
				/* write 0 to the pin */
				CLEAR_BIT(PORTD, a_pinId);
			}
			else
			{
				/* Write 1 to the pin */
				SET_BIT(PORTD, a_pinId);
			}
			break;
		default:
			/*Doing nothing*/
			break;
		}
	}
	return;
}

/*
 * Description:
 * The function will write the port value in the port labeled in port id.
 * If the port id was not correct, the function will return without writing anything to the port.
 *
 * possible return values:
 * void
 * */
void GPIO_writePort(GPIO_PortIdType a_portId, uint8 a_portValue)
{
	/*Check the Correctness of port_id and pin_id*/
	if( a_portId >= PORTS_NUM || a_portId < 0)
	{
		/*invalid input*/
		return;/*setting the return value*/
	}
	else
	{
		/*Valid input*/
		switch(a_portId)
		{
		case PORTA_ID:
			PORTA = a_portValue;
			break;
		case PORTB_ID:
			PORTB = a_portValue;
			break;
		case PORTC_ID:
			PORTC = a_portValue;
			break;
		case PORTD_ID:
			PORTD = a_portValue;
			break;
		default:
			/*Doing nothing*/
			break;
		}
	}
	return;
}

