#include "TIMER0.h"
#include "../../HAL/LCD/LCD.h"

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (*TIMER0_OVF_CallBack)(void) = {NULL};

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (*TIMER0_COMP_CallBack)(void) = {NULL};

volatile uint16 TIMER0_Counter = 0;


/*___________________________________________________________________________________________________*/
void TIMER0_Init( void )
{
	/*Initialization the TIMER0 Based on TIMER0_config.h File Choices*/

	/* Check on TIMER0 Waveform Generation Mode (Timer Mode) */
	#if	  TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE


		/* TIMER0 Normal Mode */
		CLR_BIT( TCCR0 , WGM01 ); CLR_BIT( TCCR0 , WGM00 );

		/* Check on Compare Output Mode (OC0 Pin Mode) */
		#if   TIMER0_OC0_MODE == TIMER0_COM_DISCONNECT_OC0

			/* Normal Port Operation, OC0 Disconnected */
			CLR_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

		#elif TIMER0_OC0_MODE == TIMER0_COM_TOGGLE_OC0

			/* Toggle OC0 PIN on Compare Match */
			CLR_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_CLEAR_OC0

			/* Clear OC0 PIN on Compare Match */
			SET_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_SET_OC0

			/* Set OC0 PIN on Compare Match */
			SET_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER0_OC0_MODE\" configuration option"
		#endif

		/* Set TCNT0 Preload Value from configuration file */
		TCNT0 = TIMER0_TCNT0_PRELOAD;


		#if TIMER0_OVF_INT_STATUS == TIMER0_OVF_INT_ENABLE

			/* Clear the Timer0 Overflow Interrupt Flag */
			SET_BIT( TIFR , TOV0 );

			/* Enable the Timer0 Overflow Interrupt */
			SET_BIT( TIMSK , TOIE0 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


		#if TIMER0_COMP_INT_STATUS == TIMER0_COMP_INT_ENABLE

			/* Set OCR0 Preload Value from configuration file */
			OCR0 = TIMER0_OCR0_PRELOAD;

			/* Clear the Compare Match Interrupt Flag */
			SET_BIT( TIFR , OCF0 );

			/* Enable the Compare Match Interrupt */
			SET_BIT( TIMSK , OCIE0 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE


		/* TIMER0 PWM (Phase Correct) Mode */
		CLR_BIT( TCCR0 , WGM01 ); SET_BIT( TCCR0 , WGM00 );

		/* Check on Compare Output Mode (OC0 Pin Mode) */
		#if   TIMER0_OC0_MODE == TIMER0_COM_DISCONNECT_OC0

			/* Normal Port Operation, OC0 Disconnected */
			CLR_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

		#elif TIMER0_OC0_MODE == TIMER0_COM_NON_INVERTING_OC0

			/* Clear OC0 PIN on Up-Counting Match, Set OC0 on Down-Counting Match */
			SET_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_INVERTING_OC0

			/* Set OC0 PIN on Up-Counting Match, Clear OC0 on Down-Counting Match */
			SET_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER0_OC0_MODE\" configuration option"
		#endif

		/* Set OCR0 Preload Value from configuration file */
		OCR0 = TIMER0_OCR0_PRELOAD;


	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE


		/* TIMER0 CTC Mode */
		SET_BIT( TCCR0 , WGM01 ); CLR_BIT( TCCR0 , WGM00 );

		/* Check on Compare Output Mode (OC0 Pin Mode) */
		#if   TIMER0_OC0_MODE == TIMER0_COM_DISCONNECT_OC0

			/* Normal Port Operation, OC0 Disconnected */
			CLR_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

		#elif TIMER0_OC0_MODE == TIMER0_COM_TOGGLE_OC0

			/* Toggle OC0 PIN on Compare Match */
			CLR_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_CLEAR_OC0

			/* Clear OC0 PIN on Compare Match */
			SET_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_SET_OC0

			/* Set OC0 PIN on Compare Match */
			SET_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER0_OC0_MODE\" configuration option"
		#endif


		#if TIMER0_COMP_INT_STATUS == TIMER0_COMP_INT_ENABLE

			/* Set OCR0 Preload Value from configuration file */
			OCR0 = TIMER0_OCR0_PRELOAD;

			/* Clear the Compare Match Interrupt Flag */
			SET_BIT( TIFR , OCF0 );

			/* Enable the Compare Match Interrupt */
			SET_BIT( TIMSK , OCIE0 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE


		/* TIMER0 CTC Mode */
		SET_BIT( TCCR0 , WGM01 ); SET_BIT( TCCR0 , WGM00 );

		/* Check on Compare Output Mode (OC0 Pin Mode) */
		#if   TIMER0_OC0_MODE == TIMER0_COM_DISCONNECT_OC0

			/* Normal Port Operation, OC0 Disconnected */
			CLR_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

		#elif TIMER0_OC0_MODE == TIMER0_COM_NON_INVERTING_OC0

			/* Clear OC0 PIN on Compare Match, Set OC0 at TOP */
			SET_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#elif TIMER0_OC0_MODE == TIMER0_COM_INVERTING_OC0

			/* Set OC0 PIN on Compare Match, Clear OC0 at TOP */
			SET_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

			/* Direction OC0 PIN as Output */
			SET_BIT( DDRB , OC0_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER0_OC0_MODE\" configuration option"
		#endif

		/* Set OCR0 Preload Value from configuration file */
		OCR0 = TIMER0_OCR0_PRELOAD;

	#else
		/* Make an Error */
		#error "Wrong \"TIMER0_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif

	/* Clear the Clock Source Select Bits */
	TCCR0 &= TIMER0_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR0 |= TIMER0_CLOCK_SOURCE_msk;

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_SetCompareValue( uint8 CompareValue )
{
	/* Take the Compare Value to Set it in OCR0 Register */
	OCR0 = CompareValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_SetTimerValue( uint8 TimerValue )
{
	/* Take the Timer Value to Set it in TCNT0 Register */
	TCNT0 = TimerValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 TIMER0_GetTimerValue( void )
{
	/* Return the Value of the TCNT0 Register */
	return TCNT0;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_OVF_InterruptDisable( void )
{
	/* Disable the TIMER0 Overflow Interrupt */
	CLR_BIT( TIMSK , TOIE0 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_OVF_InterruptEnable( void )
{
	/* Enable the TIMER0 Overflow Interrupt */
	SET_BIT( TIMSK , TOIE0 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_COMP_InterruptDisable( void )
{
	/* Disable the TIMER0 Compare Match Interrupt */
	CLR_BIT( TIMSK , OCIE0 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_COMP_InterruptEnable( void )
{
	/* Enable the TIMER0 Compare Match Interrupt */
	SET_BIT( TIMSK , OCIE0 );
}
/*___________________________________________________________________________________________________*/



#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE || TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE
/*___________________________________________________________________________________________________*/
void TIMER0_SetPWMDutyCycle( uint8 DutyCycle )
{
	/* Set the Duty Cycle of the PWM [0:255] */
	OCR0 = DutyCycle;
}
/*___________________________________________________________________________________________________*/
#else

#if TIMER0_COUNT_MODE == TIMER0_COUNT_ENABLE
/*___________________________________________________________________________________________________*/
uint32 TIMER0_GetTime_ms( void )
{
	/* Return Total Time for When Timer Start Count (if no thing change the timer TCNT0 and TIMER0_TCNT0_PRELOAD = 0) */

	#if	  TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE
		return (uint32)((TCNT0 + (((uint32)TIMER0_Counter) << 8))*(presc_T0*1000.0/F_CPU));
	#else
		return (uint32)((TCNT0 + TIMER0_Counter*OCR0)*(presc_T0*1000.0/F_CPU));
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_RESET( void )
{
	/* Set TCNT0 and TIMER0_Counter to 0 */

	TCNT0 = 0;
	TIMER0_Counter = 0;
}
/*___________________________________________________________________________________________________*/
#endif


#if TIMER0_CLOCK_SOURCE_msk >= TIMER0_NO_PRESCALER && TIMER0_CLOCK_SOURCE_msk <= TIMER0_PRESCALER_1024
/*___________________________________________________________________________________________________*/
uint16 TIMER0_Set_INT_Time_ms( uint32 milliseconds )
{
	/* Return Number of Counting for the Given Time (in milliseconds) */
	

	#if   TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE

		float32 CountsNumber = ((float32)milliseconds*F_CPU)/(FREQ_DIVIDER_T0) ;
		uint8 TCNT0_value = (1 - (CountsNumber - (uint32)CountsNumber))*256;

		TCNT0 = TCNT0_value;

		if (CountsNumber > (uint32)CountsNumber)
		{
			CountsNumber = (uint32)CountsNumber + 1;
		}

		return CountsNumber;

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE

		float32 CountsNumber = ((float32)milliseconds*F_CPU)/(OCR0*presc_T0*1000.0) ;

		uint8 TCNT0_value = (1 - (CountsNumber - (uint16)CountsNumber))*OCR0;

		if (TCNT0_value == OCR0)
		{
			TCNT0_value = 0;
		}

		TCNT0 = TCNT0_value;

		if (CountsNumber > (int)CountsNumber)
		{
			CountsNumber = (int)CountsNumber + 1;
		}
		return CountsNumber;

	#endif

}
/*___________________________________________________________________________________________________*/
#endif
#endif

/*___________________________________________________________________________________________________*/
void TIMER0_Set_OVF_Callback( void (*CopyFuncPtr)(void) )
{
	/* Set Call Back Function for the Overflow (OVF) Interrupt */

		/* Copy the Function Pointer */
		TIMER0_OVF_CallBack = CopyFuncPtr ;

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER0_Set_COMP_Callback( void (*CopyFuncPtr)(void) )
{
	/* Set Call Back Function for the Compare Match (COMP) Interrupt */

	/* Check that the Pointer is Valid */
	if( CopyFuncPtr != NULL ){

		/* Copy the Function Pointer */
		TIMER0_COMP_CallBack = CopyFuncPtr ;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_10 (void)		__attribute__ ((signal)) ;
void __vector_10 (void)
{
	/* ISR for Timer0 Compare Match (COMP) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER0_COMP_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER0_COMP_CallBack();
	}

	#if	  TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE		&&	\
		TIMER0_COUNT_MODE == TIMER0_COUNT_ENABLE

		TIMER0_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_11 (void)		__attribute__ ((signal)) ;
void __vector_11 (void)
{
	/* ISR for Timer0 Overflow (OVF) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER0_OVF_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER0_OVF_CallBack();
	}

	#if		TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE		&&	\
			TIMER0_COUNT_MODE == TIMER0_COUNT_ENABLE

		TIMER0_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/


