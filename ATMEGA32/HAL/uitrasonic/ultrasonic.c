/*
 * ultrasonic.c
 *
 * Created: 7/4/2024 11:14:44 PM
 *  Author: Ahmed shaban
 */ 
#include <util/delay.h>
#include "ultrasonic.h"


void Ultrasonic_Init() {

	DIO_setup_Pin_Direction(triggerPort,triggerPin,OUTPUT);
	TIMER1_Init();
	ICU_Init();
}

uint16 Ultrasonic_ReadDistance(void) {
	uint16 a, b,high, distance;

	// Debug output to check if variables are correct
	DIO_write_Pin(triggerPort, triggerPin, OUTPUT);
	_delay_us(20);
	DIO_write_Pin(triggerPort, triggerPin, INPUT);


	ICU_RisingTriggerEdge();



	// Wait for input  rising edge
	while (!ICU_GetFlag());
	a = ICU_GetICUvalue();
	ICU_ClearFlag();


	ICU_FallingTriggerEdge();
	//  input  falling edge
	while (!ICU_GetFlag());
	b = ICU_GetICUvalue();
	ICU_ClearFlag();

	if(b > a)
	{
		high = b - a;
	}
	else
	{
		high = b + OCR1A - a;
	}


	// Calculate the distance in cm
	distance = (((uint32)high * 34600) *presc_T1/ (F_CPU * 2));

	return distance;
}

