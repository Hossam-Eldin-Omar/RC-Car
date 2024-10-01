#include "servo_motor.h"


void Servo_motor_degree(double degree) {

	TIMER1_SetPWM_OC1B_DutyCycle(19.125 + (degree*0.07083333333333));

}
