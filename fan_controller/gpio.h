/*
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Layer: Micro controller Abstraction Layer (MCAL)
 *
 * Author: Abdullah Mahmoud
 *
 * */
#ifndef GPIO_H_
#define GPIO_H_

/******************Includes******************/
#include"std_types.h"

/******************Definitions******************/
#define PORTS_NUM			4
#define PINS_PER_PORT_NUM	8

/******************Types declarations******************/
typedef enum{
	PIN_INPUT, PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum{
	PORT_INPUT, PORT_OUTPUT= ((uint8)(~0UL >> PINS_PER_PORT_NUM))
}GPIO_PortDirectionType;

typedef enum{
	PIN0_ID, PIN1_ID, PIN2_ID, PIN3_ID, PIN4_ID, PIN5_ID, PIN6_ID, PIN7_ID
}GPIO_PinIdType;

typedef enum{
	PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID
}GPIO_PortIdType;

/******************Shared Global Variables******************/

/*None*/

/******************Function Prototypes******************/

/*
 * Description:
 * The function will take the port_id and the pin_id and setup that pin as PIN_INPUT or PIN_OUTPUT
 * if the port_id or the pin_id are not correct, the function will return without doing anything
 *
 * Possible return value:
 * void
 * */
void GPIO_setupPinDirection(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId, \
		GPIO_PinDirectionType a_direction);

/*
 * Description:
 * The function will take port_id and setup that port as PORT_INPUT or PORT_OUTPUT.
 * If the port_id is not correct, the function will return without doing anything.
 *
 * Possible return value:
 * void
 * */
void GPIO_setupPortDirection(GPIO_PortIdType a_portId, GPIO_PortDirectionType a_direction);

/*
 * Description:
 * The function will read pin_id from the port in port_id and return the read value.
 * if port_id or pin_id was not correct, the function will return LOGIC_LOW
 *
 * Possible return values:
 * LOGIC_LOW, the pin value from the port (0, 255)
 * */
uint8 GPIO_readPin(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId);

/*
 * Description:
 * The function will read the value on the port in port_id.
 * If the port_id was not correct, the function will return LOGIC_LOW
 *
 * Possible return values:
 * LOGIC_LOW, the port value (0, 255)
 * */
uint8 GPIO_readPort(GPIO_PortIdType a_portId);

/*
 * Description:
 * The function will write the pin_value on the pin labeled in pin_id inside the port labeled in port_id.
 * if pin_id or port_id was not correct, the function will return without writing any value
 *
 * Possible return values:
 * void
 * */
void GPIO_writePin(GPIO_PortIdType a_portId, GPIO_PinIdType a_pinId, uint8 a_pinValue);

/*
 * Description:
 * The function will write the port_value in the port labeled in port_id.
 * If the port_id was not correct, the function will return without writing anything to the port.
 *
 * possible return values:
 * void
 * */
void GPIO_writePort(GPIO_PortIdType a_portId, uint8 a_portValue);


#endif /* GPIO_H_ */
