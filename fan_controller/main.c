/*
 *
 * Module: App
 *
 * File Name: main.c
 *
 * Description: Source file for the fan controller application
 *
 * Layer: Application Layer
 *
 * Author: Abdullah Mahmoud
 *
 * */


#include"main.h"

/*
 * @brief initializes the application and it required modules
 * */
void MAIN_init(void)
{

	LM35_init();/*Temperature sensor init*/
	LCD_init();/*LCD init*/
	DC_MOTOR_Init();/*Fan motor init*/

	/*initial messages on the screen*/
	LCD_displayString("Fan is ");
	LCD_moveCursor(1,0);
	LCD_displayString("Temp is ");
}

/*
 * @brief this function will display the fan state on the LCD screen
 * assuming the LCD was initialized properly.
 *
 * @param uint8 a_fanState indicate the current fan state
 *
 * @param uint8* a_oldFanState a pointer indicate the old(on the display) fan state
 * */
void MAIN_displayFanMessage(uint8 a_fanState, uint8 *a_oldFanState)
{
	if(a_fanState == *a_oldFanState)
	{
		/*if both states are equal then no need to update the LCD*/
		return;
	}
	*a_oldFanState = a_fanState;
	LCD_displayStringRowColumn(0,7,"   ");/*clear the LCD current fan state*/
	LCD_moveCursor(0,7); /*back to the correct position to write the new state */
	if(a_fanState == FAN_OFF)
	{
		LCD_displayString("OFF");/*Off state*/
	}
	else
	{
		LCD_displayString("ON ");/*on state*/
	}
	LCD_moveCursor(1,0);/*Move the cursor to the next row */

}

/*
 * @brief this function will display the temperature on the LCD screen
 * assuming the LCD was initialized properly.
 *
 * @param uint8 a_temprature indicate the new number
 *
 * @param uint8* a_oldTemp apointer indicate the old(on the display) number
 * */
void MAIN_displayTemperatureMessage(uint8 a_temprature, uint8* a_oldTemp)
{
	if(a_temprature == *a_oldTemp)
	{
		/*if both numbers are equal then no need to update it */
		return;
	}
	*a_oldTemp = a_temprature;
	LCD_displayStringRowColumn(1,8,"   ");/*clear the old number*/
	LCD_moveCursor(1,8);
	LCD_intgerToString(a_temprature);/*Write the new number*/
}

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
void MAIN_updateFanSpeed(uint8 a_newSpeed, uint8* a_oldSpeed, uint8* a_fanStatus)
{
	if(a_newSpeed == *a_oldSpeed)
	{
		/*if the current fan speed is equal to the new read speed*/
		/*then no need to re apply the same speed */
		return;
	}

	/*if both speed are different*/
	*a_oldSpeed = a_newSpeed;/*set the fan speed to the new read speed */

	DC_MOTOR_Rotate(FAN_DIRECTION, a_newSpeed); /*apply the new speed to the motor*/
	*a_fanStatus = FAN_ON;/*adjust the fan state*/
}

int main(void)
{
	uint8 temperature = 0, fanState = FAN_INIT,
			lcd_temparture = 0,
			fanSpeed = 0, newFanSpeed = 0;

	MAIN_init();
	
	while(1)
	{
		temperature = LM35_getTemperature();/*Read the sensor temperature*/
		MAIN_displayTemperatureMessage(temperature, &lcd_temparture); /*Display the temperature read*/
		if(temperature < 30)
		{
			MAIN_displayFanMessage(FALSE, &fanState);/*Turn off FAN*/
			fanSpeed = 0; /*Set the current fan speed to 0*/
			DC_MOTOR_Rotate(DC_MOTOR_STOP, 0);/*stopping the motor*/
		}
		else
		{
			MAIN_displayFanMessage(TRUE, &fanState);/*Turn on FAN*/

			/*adjust the new fan read based on the temperature*/
			if(temperature >= 120)
			{
				newFanSpeed = 100;
			}
			else if(temperature >= 90)
			{
				newFanSpeed = 75;
			}
			else if(temperature >= 60)
			{
				newFanSpeed = 50;
			}
			else if(temperature >= 30)
			{
				newFanSpeed = 25;
			}
			MAIN_updateFanSpeed(newFanSpeed, &fanSpeed, &fanState);
		}

	}
}
