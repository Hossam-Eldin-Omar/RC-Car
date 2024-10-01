#include "TIMER2.h"

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (*TIMER2_OVF_CallBack)(void) = {NULL};

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (*TIMER2_COMP_CallBack)(void) = {NULL};

volatile uint16 TIMER2_Counter = 0;


/*___________________________________________________________________________________________________*/
void TIMER2_Init( void )
{
	/*Initialization the TIMER2 Based on TIMER2_config.h File Choices*/

	/* Check on TIMER2 Waveform Generation Mode (Timer Mode) */
	#if	  TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE


		/* TIMER2 Normal Mode */
		CLR_BIT( TCCR2 , WGM21 ); CLR_BIT( TCCR2 , WGM20 );

		/* Check on Compare Output Mode (OC2 Pin Mode) */
		#if   TIMER2_OC2_MODE == TIMER2_COM_DISCONNECT_OC2

			/* Normal Port Operation, OC2 Disconnected */
			CLR_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

		#elif TIMER2_OC2_MODE == TIMER2_COM_TOGGLE_OC2

			/* Toggle OC2 PIN on Compare Match */
			CLR_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_CLEAR_OC2

			/* Clear OC2 PIN on Compare Match */
			SET_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_SET_OC2

			/* Set OC2 PIN on Compare Match */
			SET_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER2_OC2_MODE\" configuration option"
		#endif

		/* Set TCNT2 Preload Value from configuration file */
		TCNT2 = TIMER2_TCNT2_PRELOAD;


		#if TIMER2_OVF_INT_STATUS == TIMER2_OVF_INT_ENABLE

			/* Clear the TIMER2 Overflow Interrupt Flag */
			SET_BIT( TIFR , TOV2 );

			/* Enable the TIMER2 Overflow Interrupt */
			SET_BIT( TIMSK , TOIE2 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


		#if TIMER2_COMP_INT_STATUS == TIMER2_COMP_INT_ENABLE

			/* Set OCR2 Preload Value from configuration file */
			OCR2 = TIMER2_OCR2_PRELOAD;

			/* Clear the Compare Match Interrupt Flag */
			SET_BIT( TIFR , OCF2 );

			/* Enable the Compare Match Interrupt */
			SET_BIT( TIMSK , OCIE2 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE


		/* TIMER2 PWM (Phase Correct) Mode */
		CLR_BIT( TCCR2 , WGM21 ); SET_BIT( TCCR2 , WGM20 );

		/* Check on Compare Output Mode (OC2 Pin Mode) */
		#if   TIMER2_OC2_MODE == TIMER2_COM_DISCONNECT_OC2

			/* Normal Port Operation, OC2 Disconnected */
			CLR_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

		#elif TIMER2_OC2_MODE == TIMER2_COM_NON_INVERTING_OC2

			/* Clear OC2 PIN on Up-Counting Match, Set OC2 on Down-Counting Match */
			SET_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_INVERTING_OC2

			/* Set OC2 PIN on Up-Counting Match, Clear OC2 on Down-Counting Match */
			SET_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER2_OC2_MODE\" configuration option"
		#endif

		/* Set OCR2 Preload Value from configuration file */
		OCR2 = TIMER2_OCR2_PRELOAD;


	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE


		/* TIMER2 CTC Mode */
		SET_BIT( TCCR2 , WGM21 ); CLR_BIT( TCCR2 , WGM20 );

		/* Check on Compare Output Mode (OC2 Pin Mode) */
		#if   TIMER2_OC2_MODE == TIMER2_COM_DISCONNECT_OC2

			/* Normal Port Operation, OC2 Disconnected */
			CLR_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

		#elif TIMER2_OC2_MODE == TIMER2_COM_TOGGLE_OC2

			/* Toggle OC2 PIN on Compare Match */
			CLR_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_CLEAR_OC2

			/* Clear OC2 PIN on Compare Match */
			SET_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_SET_OC2

			/* Set OC2 PIN on Compare Match */
			SET_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER2_OC2_MODE\" configuration option"
		#endif


		#if TIMER2_COMP_INT_STATUS == TIMER2_COMP_INT_ENABLE

			/* Set OCR2 Preload Value from configuration file */
			OCR2 = TIMER2_OCR2_PRELOAD;

			/* Clear the Compare Match Interrupt Flag */
			SET_BIT( TIFR , OCF2 );

			/* Enable the Compare Match Interrupt */
			SET_BIT( TIMSK , OCIE2 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

		#endif


	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE


		/* TIMER2 CTC Mode */
		SET_BIT( TCCR2 , WGM21 ); SET_BIT( TCCR2 , WGM20 );

		/* Check on Compare Output Mode (OC2 Pin Mode) */
		#if   TIMER2_OC2_MODE == TIMER2_COM_DISCONNECT_OC2

			/* Normal Port Operation, OC2 Disconnected */
			CLR_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

		#elif TIMER2_OC2_MODE == TIMER2_COM_NON_INVERTING_OC2

			/* Clear OC2 PIN on Compare Match, Set OC2 at TOP */
			SET_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#elif TIMER2_OC2_MODE == TIMER2_COM_INVERTING_OC2

			/* Set OC2 PIN on Compare Match, Clear OC2 at TOP */
			SET_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

			/* Direction OC2 PIN as Output */
			SET_BIT( DDRD , OC2_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"TIMER2_OC2_MODE\" configuration option"
		#endif

		/* Set OCR2 Preload Value from configuration file */
		OCR2 = TIMER2_OCR2_PRELOAD;

	#else
		/* Make an Error */
		#error "Wrong \"TIMER2_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif

	/* Clear the Clock Source Select Bits */
	TCCR2 &= TIMER2_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR2 |= TIMER2_CLOCK_SOURCE_msk;

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_SetCompareValue( uint8 CompareValue )
{
	/* Take the Compare Value to Set it in OCR2 Register */
	OCR2 = CompareValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_SetTimerValue( uint8 TimerValue )
{
	/* Take the Timer Value to Set it in TCNT2 Register */
	TCNT2 = TimerValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 TIMER2_GetTimerValue( void )
{
	/* Return the Value of the TCNT2 Register */
	return TCNT2;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_OVF_InterruptDisable( void )
{
	/* Disable the TIMER2 Overflow Interrupt */
	CLR_BIT( TIMSK , TOIE2 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_OVF_InterruptEnable( void )
{
	/* Enable the TIMER2 Overflow Interrupt */
	SET_BIT( TIMSK , TOIE2 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_COMP_InterruptDisable( void )
{
	/* Disable the TIMER2 Compare Match Interrupt */
	CLR_BIT( TIMSK , OCIE2 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_COMP_InterruptEnable( void )
{
	/* Enable the TIMER2 Compare Match Interrupt */
	SET_BIT( TIMSK , OCIE2 );
}
/*___________________________________________________________________________________________________*/



#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE || TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE
/*___________________________________________________________________________________________________*/
void TIMER2_SetPWMDutyCycle( uint8 DutyCycle )
{
	/* Set the Duty Cycle of the PWM [0:255] */
	OCR2 = DutyCycle;
}
/*___________________________________________________________________________________________________*/
#else

#if TIMER2_COUNT_MODE == TIMER2_COUNT_ENABLE
/*___________________________________________________________________________________________________*/
uint32 TIMER2_GetTime_ms( void )
{
	/* Return Total Time for When Timer Start Count (if no thing change the timer TCNT2 and TIMER2_TCNT2_PRELOAD = 0) */

	#if	  TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE
		return (uint32)((TCNT2 + (((uint32)TIMER2_Counter) << 8))*(presc_T2*1000.0/F_CPU));
	#else
		return (uint32)((TCNT2 + TIMER2_Counter*OCR2)*(presc_T2*1000.0/F_CPU));
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_RESET( void )
{
	/* Set TCNT2 and TIMER2_Counter to 0 */

	TCNT2 = 0;
	TIMER2_Counter = 0;
}
/*___________________________________________________________________________________________________*/
#endif


/*___________________________________________________________________________________________________*/
uint16 TIMER2_Set_INT_Time_ms( uint16 milliseconds )
{
	/* Return Number of Counting for the Given Time (in milliseconds) */


	#if   TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE

		float32 CountsNumber = ((float32)milliseconds*F_CPU)/(FREQ_DIVIDER_T2) ;

		uint8 TCNT2_value = (1 - (CountsNumber - (uint32)CountsNumber))*256;

		TCNT2 = TCNT2_value;

		if (CountsNumber > (uint32)CountsNumber)
		{
			CountsNumber = (uint32)CountsNumber + 1;
		}

		return CountsNumber;

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE

		float32 CountsNumber = ((float32)milliseconds*F_CPU)/(OCR2*presc_T2*1000.0) ;

		uint8 TCNT2_value = (1 - (CountsNumber - (uint16)CountsNumber))*OCR2;

		if (TCNT2_value == OCR2)
		{
			TCNT2_value = 0;
		}

		TCNT2 = TCNT2_value;

		if (CountsNumber > (int)CountsNumber)
		{
			CountsNumber = (int)CountsNumber + 1;
		}
		return CountsNumber;

	#endif

}
/*___________________________________________________________________________________________________*/
#endif


/*___________________________________________________________________________________________________*/
void TIMER2_Set_OVF_Callback( void (*CopyFuncPtr)(void) )
{
	/* Set Call Back Function for the Overflow (OVF) Interrupt */

	/* Check that the Pointer is Valid */
	if( CopyFuncPtr != NULL ){

		/* Copy the Function Pointer */
		TIMER2_OVF_CallBack = CopyFuncPtr ;
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER2_Set_COMP_Callback( void (*CopyFuncPtr)(void) )
{
	/* Set Call Back Function for the Compare Match (COMP) Interrupt */

	/* Check that the Pointer is Valid */
	if( CopyFuncPtr != NULL ){

		/* Copy the Function Pointer */
		TIMER2_COMP_CallBack = CopyFuncPtr ;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_4 (void)		__attribute__ ((signal)) ;
void __vector_4 (void)
{
	/* ISR for TIMER2 Compare Match (COMP) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER2_COMP_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER2_COMP_CallBack();
	}

	#if	  TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE		&&	\
		TIMER2_COUNT_MODE == TIMER2_COUNT_ENABLE

		TIMER2_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_5 (void)		__attribute__ ((signal)) ;
void __vector_5 (void)
{
	/* ISR for TIMER2 Overflow (OVF) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER2_OVF_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER2_OVF_CallBack();
	}

	#if		TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE		&&	\
			TIMER2_COUNT_MODE == TIMER2_COUNT_ENABLE

		TIMER2_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/


