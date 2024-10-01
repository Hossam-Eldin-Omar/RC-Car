/*File Guard*/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include  "../../MCAL/DIO/DIO.h"

/*Number of Motors you Will Use*/
#define MOTORS_NUMBER		2


/* steering */
#define DC_MOTOR_STOP_MOTOR_2		0	/*Make one Motor Moves Forward and the other Moves Backward*/
#define DC_MOTOR_BACKWARD_MOTOR_2	1	/*Make one Motor Moves Forward and the other Moves Stop*/

/*Set Steering mode
 * choose between
 * 1. DC_MOTOR_STOP_MOTOR_2
 * 2. DC_MOTOR_BACKWARD_MOTOR_2
 */
#define DC_MOTOR_STEERING_MODE		DC_MOTOR_BACKWARD_MOTOR_2

/*DC MOTOR Directions (for DC_MOTOR_SET_Direction functions)*/
#define DC_MOTOR_FORWARD_Direction				1
#define DC_MOTOR_BACKWARD_Direction				2
#define DC_MOTOR_STOP_Direction					3
#define DC_MOTOR_STEER_RIGHT_Direction			4
#define DC_MOTOR_STEER_LEFT_Direction			5

struct motor
{
	uint8 PORT : 2;
	uint8 FPIN : 3;
	uint8 SPIN : 3;
};

/*Initialization the DC MOTOR Pins as Output and save its ID as MOTOR_ID*/
void DC_MOTOR_init( uint8 MOTOR_ID , uint8 PORT_ID , uint8 FIRST_PIN_ID , uint8 SECOND_PIN_ID);

/*Make one DC MOTOR (that have the passed ID) Move Forward*/
void DC_MOTOR_FORWARD_ONE( uint8 MOTOR_ID );

/*Make one DC MOTOR (that have the passed ID) Move Backward*/
void DC_MOTOR_BACKWARD_ONE( uint8 MOTOR_ID );

/*Make one DC MOTOR (that have the passed ID) Stop Moving*/
void DC_MOTOR_STOP_ONE( uint8 MOTOR_ID );


#if MOTORS_NUMBER > 1

/*Make the Two DC MOTOR Move Forward*/
void DC_MOTOR_FORWARD( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID );

/*Make the Two DC MOTOR Move Backward*/
void DC_MOTOR_BACKWARD( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID );

/*Make the Two DC MOTOR Stop Moving*/
void DC_MOTOR_STOP( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID );

/*Control the Two DC MOTOR to Make them Move Right*/
void DC_MOTOR_STEER_Right( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID );

/*Control the Two DC MOTOR to Make them Move Left*/
void DC_MOTOR_STEER_Left( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID );

/*Make the Two DC MOTOR Move as the passed Direction*/
void DC_MOTOR_SET_Direction( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID , uint8 MOTOR_Direction );

#endif

#endif /* DC_MOTOR_H_ */
