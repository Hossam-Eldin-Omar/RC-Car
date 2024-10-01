#include "DC_MOTOR.h"

struct motor MOTORS_ARRAY[MOTORS_NUMBER];


/*___________________________________________________________________________________________________*/
void DC_MOTOR_init( uint8 MOTOR_ID , uint8 PORT_ID , uint8 FIRST_PIN_ID , uint8 SECOND_PIN_ID)
{
	/* Initialization the DC MOTOR Pins as Output and Save its ID as MOTOR_ID */

	/* Save Pins Port ID For This Motor */
	MOTORS_ARRAY[MOTOR_ID].PORT = PORT_ID;

	/* Save the First Pins ID For This Motor */
	MOTORS_ARRAY[MOTOR_ID].FPIN = FIRST_PIN_ID;

	/* Save the Second Pins ID For This Motor */
	MOTORS_ARRAY[MOTOR_ID].SPIN = SECOND_PIN_ID;

	/* Set the First Pin Direction as Output */
	DIO_setup_Pin_Direction( PORT_ID , FIRST_PIN_ID ,OUTPUT);

	/* Set the Second Pin Direction as Output */
	DIO_setup_Pin_Direction( PORT_ID , SECOND_PIN_ID ,OUTPUT);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_FORWARD_ONE( uint8 MOTOR_ID )
{
	/* Make the DC MOTOR (that have the passed ID) Move Forward */

	/* set the First Pin as High Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].FPIN , HIGH );

	/* set the Second Pin as Low Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].SPIN , LOW );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_BACKWARD_ONE( uint8 MOTOR_ID )
{
	/* Make the DC MOTOR (that have the passed ID) Move Backward */

	/* set the First Pin as Low Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].FPIN , LOW );

	/* set the Second Pin as High Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].SPIN , HIGH );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_STOP_ONE( uint8 MOTOR_ID )
{
	/* Make the DC MOTOR (that have the passed ID) Stop Moving */

	/* set the First Pin as Low Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].FPIN , LOW );

	/* set the Second Pin as Low Value */
	DIO_write_Pin( MOTORS_ARRAY[MOTOR_ID].PORT , MOTORS_ARRAY[MOTOR_ID].SPIN , LOW );
}
/*___________________________________________________________________________________________________*/


#if MOTORS_NUMBER > 1
/*___________________________________________________________________________________________________*/
void DC_MOTOR_FORWARD( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID )
{
	/* Make the Two DC MOTOR Move Forward */

	/* Make the LEFT DC MOTOR Move Forward */
	DC_MOTOR_FORWARD_ONE(LEFT_MOTOR_ID);

	/* Make the RIGHT DC MOTOR Move Forward */
	DC_MOTOR_FORWARD_ONE(RIGHT_MOTOR_ID);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_BACKWARD( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID )
{
	/* Make the Two DC MOTOR Move Backward */

	/* Make the LEFT DC MOTOR Move Backward */
	DC_MOTOR_BACKWARD_ONE(LEFT_MOTOR_ID);

	/* Make the RIGHT DC MOTOR Move Backward */
	DC_MOTOR_BACKWARD_ONE(RIGHT_MOTOR_ID);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_STOP( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID )
{
	/* Make the Two DC MOTOR Stop Moving */

	/* Make the LEFT DC MOTOR Stop Moving */
	DC_MOTOR_STOP_ONE(LEFT_MOTOR_ID);

	/* Make the RIGHT DC MOTOR Stop Moving */
	DC_MOTOR_STOP_ONE(RIGHT_MOTOR_ID);

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_STEER_Right( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID )
{
	/* Control the Two DC MOTOR to Make them Move Right */

	/* Make the LEFT DC MOTOR Move Forward */
	DC_MOTOR_FORWARD_ONE(LEFT_MOTOR_ID);

	#if		DC_MOTOR_STEERING_MODE == DC_MOTOR_STOP_MOTOR_2

		/* Make the RIGHT DC MOTOR Stop Moving */
		DC_MOTOR_STOP_ONE(RIGHT_MOTOR_ID);

	#elif	DC_MOTOR_STEERING_MODE == DC_MOTOR_BACKWARD_MOTOR_2

		/* Make the RIGHT DC MOTOR Move Backward */
		DC_MOTOR_BACKWARD_ONE(RIGHT_MOTOR_ID);

	#else
		/* Make an Error */
		#error "Wrong \"DC_MOTOR_STEERING_MODE\" configuration option"
	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_STEER_Left( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID )
{
	/* Control the Two DC MOTOR to Make them Move Left */

	/* Make the RIGHT DC MOTOR Move Forward */
	DC_MOTOR_FORWARD_ONE(RIGHT_MOTOR_ID);

	#if		DC_MOTOR_STEERING_MODE == DC_MOTOR_STOP_MOTOR_2

		/* Make the LEFT DC MOTOR  Stop Moving */
		DC_MOTOR_STOP_ONE(LEFT_MOTOR_ID);

	#elif	DC_MOTOR_STEERING_MODE == DC_MOTOR_BACKWARD_MOTOR_2

		/* Make the LEFT DC MOTOR Move Backward */
		DC_MOTOR_BACKWARD_ONE(LEFT_MOTOR_ID);

	#else
		/* Make an Error */
		#error "Wrong \"DC_MOTOR_STEERING_MODE\" configuration option"
	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void DC_MOTOR_SET_Direction( uint8 RIGHT_MOTOR_ID , uint8 LEFT_MOTOR_ID , uint8 MOTOR_Direction )
{
	/*Make the Two DC MOTOR Move as the passed Direction*/

	/* Check on MOTOR Direction */
	if(MOTOR_Direction == DC_MOTOR_FORWARD_Direction)
	{
		/* Make the Two DC MOTOR Move Forward */
		DC_MOTOR_FORWARD(RIGHT_MOTOR_ID,LEFT_MOTOR_ID);

	}
	else if(MOTOR_Direction == DC_MOTOR_BACKWARD_Direction)
	{
		/* Make the Two DC MOTOR Move Backward */
		DC_MOTOR_BACKWARD(RIGHT_MOTOR_ID,LEFT_MOTOR_ID);
	}
	else if(MOTOR_Direction == DC_MOTOR_STEER_RIGHT_Direction)
	{
		/* Control the Two DC MOTOR to Make them Move Right */
		DC_MOTOR_STEER_Right(RIGHT_MOTOR_ID,LEFT_MOTOR_ID);
	}
	else if(MOTOR_Direction == DC_MOTOR_STEER_LEFT_Direction)
	{
		/* Control the Two DC MOTOR to Make them Move Left */
		DC_MOTOR_STEER_Left(RIGHT_MOTOR_ID,LEFT_MOTOR_ID);
	}
	else
	{
		/* Make the Two DC MOTOR Stop Moving */
		DC_MOTOR_STOP(RIGHT_MOTOR_ID,LEFT_MOTOR_ID);
	}
}
/*___________________________________________________________________________________________________*/
#endif
