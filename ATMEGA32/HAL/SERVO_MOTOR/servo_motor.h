#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER1/TIMER1.h"

#define servo_motor_port		PORTD_ID
#define servo_motor_pin			PIN4_ID

void Servo_motor_degree(double degree);

#endif
