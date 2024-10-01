#include "EXTI.h"

/*
	Pointer to Function => Carry the Address of ISR Function From the main Function
	Hint : EXTI_SetCallback( & External_Interrupt_0_Function , 0 );
*/
void (*EXTI_CallBack[3])(void) = {NULL};


/*___________________________________________________________________________________________________*/
void EXTI_Init( void )
{
	/*Initialization the External Interrupt based on EXIT_config.h file Choices*/

	/* Disable Global Interrupt */
	CLR_BIT( SREG , I );

	/* Disable ALL External Interrupts */
	CLR_BIT( GICR , INT0 );
	CLR_BIT( GICR , INT1 );
	CLR_BIT( GICR , INT2 );

	/********  External Interrupt 0   ********/

	/* Check that NO Errors in configuration of External Interrupt 0 */
	#ifdef	INTERRUPT_0_STATUS

			/* Check if the External Interrupt 0 is Enable */
			#if	 INTERRUPT_0_STATUS == EXTI_ENABLE

					/* Check the External Interrupt 0 PIN mode */
					#if	  INTERRUPT_0_PIN_MODE == EXTI_INPUT || INTERRUPT_0_PIN_MODE == EXTI_INPUT_PULLUP

						/* Set External Interrupt 0 PIN mode */
						DIO_setup_Pin_Direction( INT0_PORT , INT0_PIN , INTERRUPT_0_PIN_MODE );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_0_PIN_MODE\" configuration option"
					#endif


					/* Check the External Interrupt 0 Sense Control */
					#if	  INTERRUPT_0_SENSE_CONTROL == EXTI_THE_LOW_LEVEL

						/* The Low Level Generates an Interrupt Request */
						CLR_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 );

					#elif INTERRUPT_0_SENSE_CONTROL == EXTI_ANY_LOGIC_CHANGE

						/* Any Logical Change Generates an Interrupt Request */
						CLR_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );

					#elif INTERRUPT_0_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

						/* The Falling Edge Generates an Interrupt Request */
						SET_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 );

					#elif INTERRUPT_0_SENSE_CONTROL == EXTI_THE_RISING_EDGE

						/* The Rising Edge generates an Interrupt Request */
						SET_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_0_SENSE_CONTROL\" configuration option"
					#endif

					/* Clear the External Interrupt 0 Flag */
					SET_BIT( GIFR , INTF0 );

					/* Enable the External Interrupts 0 */
					SET_BIT( GICR , INT0 );

			#endif

	#else
		/* Make an Error */
		#error	"Wrong in \"INTERRUPT_0_STATUS\" configuration"
	#endif


	/********   External Interrupt 1   ********/

	/* Check that NO Errors in configuration of External Interrupt 1 */
	#ifdef	INTERRUPT_1_STATUS

			/* Check if the External Interrupt 1 is Enable */
			#if	 INTERRUPT_1_STATUS == EXTI_ENABLE

					/* Check the External Interrupt 1 PIN mode */
					#if	  INTERRUPT_1_PIN_MODE == EXTI_INPUT || INTERRUPT_1_PIN_MODE == EXTI_INPUT_PULLUP

						/* Set External Interrupt 1 PIN mode */
						DIO_setup_Pin_Direction( INT1_PORT , INT1_PIN , INTERRUPT_1_PIN_MODE );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_1_PIN_MODE\" configuration option"
					#endif


					/* Check the External Interrupt 1 Sense Control */
					#if	  INTERRUPT_1_SENSE_CONTROL == EXTI_THE_LOW_LEVEL

						/* The Low Level Generates an Interrupt Request */
						CLR_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 );

					#elif INTERRUPT_1_SENSE_CONTROL == EXTI_ANY_LOGIC_CHANGE

						/* Any Logical Change Generates an Interrupt Request */
						CLR_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );

					#elif INTERRUPT_1_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

						/* The Falling Edge Generates an Interrupt Request */
						SET_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 );

					#elif INTERRUPT_1_SENSE_CONTROL == EXTI_THE_RISING_EDGE

						/* The Rising Edge generates an Interrupt Request */
						SET_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_1_SENSE_CONTROL\" configuration option"
					#endif

					/* Clear the External Interrupt 1 Flag */
					SET_BIT( GIFR , INTF1 );

					/* Enable the External Interrupts 1 */
					SET_BIT( GICR , INT1 );


			#endif

	#else
		/* Make an Error */
		#error	"Wrong in \"INTERRUPT_1_STATUS\" configuration"
	#endif


	/********   External Interrupt 2   ********/

	/* Check that NO Errors in configuration of External Interrupt 2 */
	#ifdef	INTERRUPT_2_STATUS

			/* Check if the External Interrupt 2 is Enable */
			#if	 INTERRUPT_2_STATUS == EXTI_ENABLE

					/* Check the External Interrupt PIN mode */
					#if	  INTERRUPT_2_PIN_MODE == EXTI_INPUT || INTERRUPT_2_PIN_MODE == EXTI_INPUT_PULLUP

						/* Set External Interrupt 2 PIN mode */
						DIO_setup_Pin_Direction( INT2_PORT , INT2_PIN , INTERRUPT_2_PIN_MODE );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_2_PIN_MODE\" configuration option"
					#endif


					/* Check the External Interrupt 2 Sense Control */
					#if INTERRUPT_2_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

						/* The Falling Edge Generates an Interrupt Request */
						CLR_BIT( MCUCSR , ISC2 );

					#elif INTERRUPT_2_SENSE_CONTROL == EXTI_THE_RISING_EDGE

						/* The Rising Edge generates an Interrupt Request */
						SET_BIT( MCUCSR , ISC2 );

					#else
						/* Make an Error */
						#error "Wrong \"INTERRUPT_2_SENSE_CONTROL\" configuration option"
					#endif

					/* Clear the External Interrupt 2 Flag */
					SET_BIT( GIFR , INTF2 );

					/* Enable the External Interrupts 2 */
					SET_BIT( GICR , INT2 );


			#endif

	#else
		/* Make an Error */
		#error	"Wrong in \"INTERRUPT_2_STATUS\" configuration"
	#endif


	/* Enable Global Interrupt */
	SET_BIT( SREG , I );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void EXTI_DisableInterrupt( uint8 EXIT_interrupt_label )
{
	/*Disable the Specified External Interrupt*/

	/* Check the External Interrupt Number */
	switch (EXIT_interrupt_label)
	{
		/* Disable External Interrupt 0 */
		case EXTI_INT0_LABEL: CLR_BIT( GICR  , INT0 ); break;

		/* Disable External Interrupt 1 */
		case EXTI_INT1_LABEL: CLR_BIT( GICR  , INT1 ); break;

		/* Disable External Interrupt 2 */
		case EXTI_INT2_LABEL: CLR_BIT( GICR  , INT2 ); break;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void EXTI_EnableInterrupt( uint8 EXIT_interrupt_label )
{
	/*Enable the Specified External Interrupt*/

	/* Check the External Interrupt Number */
	switch (EXIT_interrupt_label)
	{
		/* Enable External Interrupt 0 */
		case EXTI_INT0_LABEL: SET_BIT( GICR  , INT0 ); break;

		/* Enable External Interrupt 1 */
		case EXTI_INT1_LABEL: SET_BIT( GICR  , INT1 ); break;

		/* Enable External Interrupt 2 */
		case EXTI_INT2_LABEL: SET_BIT( GICR  , INT2 ); break;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void EXTI_ChangeSenseControl( uint8 mode , uint8 EXIT_interrupt_label )
{
	/*Change the Sense Control in Run Time Exists in EXIT_Init function already (not necessary to use)*/

	/* Check the External Interrupt Number */
	switch (EXIT_interrupt_label)
	{
		/*  External Interrupt 0   */
		case EXTI_INT0_LABEL:

			/* Check the External Interrupt 0 Sense Control */
			switch (mode)
			{
				/* The Low Level Generates an Interrupt Request */
				case EXTI_THE_LOW_LEVEL:	CLR_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 ); break;

				/* Any Logical Change Generates an Interrupt Request */
				case EXTI_ANY_LOGIC_CHANGE: CLR_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );	break;

				/* The Falling Edge Generates an Interrupt Request */
				case EXTI_THE_FALLING_EDGE: SET_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 );	break;

				/* The Rising Edge generates an Interrupt Request */
				case EXTI_THE_RISING_EDGE:  SET_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );	break;
			}
			break;


		/*  External Interrupt 1   */
		case EXTI_INT1_LABEL:

			/* Check the External Interrupt 1 Sense Control */
			switch (mode)
			{
				/* The Low Level Generates an Interrupt Request */
				case EXTI_THE_LOW_LEVEL:	CLR_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 ); break;

				/* Any Logical Change Generates an Interrupt Request */
				case EXTI_ANY_LOGIC_CHANGE: CLR_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );	break;

				/* The Falling Edge Generates an Interrupt Request */
				case EXTI_THE_FALLING_EDGE: SET_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 );	break;

				/* The Rising Edge generates an Interrupt Request */
				case EXTI_THE_RISING_EDGE:  SET_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );	break;
			}
			break;


		/*  External Interrupt 2   */
		case EXTI_INT2_LABEL:

			/* Check the External Interrupt 2 Sense Control */
			switch (mode)
			{
				/* The Falling Edge Generates an Interrupt Request */
				case EXTI_THE_FALLING_EDGE: CLR_BIT( MCUCSR , ISC2 );	break;

				/* The Rising Edge generates an Interrupt Request */
				case EXTI_THE_RISING_EDGE:  SET_BIT( MCUCSR , ISC2 );	break;
			}
			break;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void EXTI_SetCallback( void (*CopyFuncPtr)(void) , uint8 EXIT_interrupt_label)
{
	/* Set Call Back Function for the Specified External Interrupt */

	/* Check that the Pointer is Valid */
	if( CopyFuncPtr != NULL && EXIT_interrupt_label < 3)
	{
		/* Copy the Function Pointer */
		EXTI_CallBack[EXIT_interrupt_label] = CopyFuncPtr;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	/* ISR for External Interrupt 0 */

	/* Check that the Pointer is Valid */
	if( EXTI_CallBack[0] != NULL )
	{
		/* Call The Global Pointer to Function */
		EXTI_CallBack[0]();
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	/* ISR for External Interrupt 1 */

	/* Check that the Pointer is Valid */
	if( EXTI_CallBack[1] != NULL )
	{
		/* Call The Global Pointer to Function */
		EXTI_CallBack[1]();
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	/* ISR for External Interrupt 2 */

	/* Check that the Pointer is Valid */
	if( EXTI_CallBack[2] != NULL )
	{
		/* Call The Global Pointer to Function */
		EXTI_CallBack[2]();
	}
}
/*___________________________________________________________________________________________________*/

