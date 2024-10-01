#include "../../LIB/std_types.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER1/TIMER1.h"

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define triggerPort			PORTD_ID
#define triggerPin			PIN7_ID

void Ultrasonic_Init();
uint16 Ultrasonic_ReadDistance(void);

#endif 
