#include "TIMER1.h"

/*
	Pointer to Function => Carry the Address of ISR Function From the main Function
	Hint : EXTI_SetCallback( & External_Interrupt_0_Function , 0 );
*/
void (*TIMER1_CallBack[4])(void) = {NULL};

volatile uint16 TIMER1_Counter = 0;


/*___________________________________________________________________________________________________*/
void TIMER1_Init( void )
{
	/* Initialization the TIMER1 Based on TIMER0_config.h File Choices */

	/* Clear the Waveform Generation Mode Bits */
	TCCR1A &= TIMER1_WGM1_10_clr_msk;
	TCCR1B &= TIMER1_WGM1_32_clr_msk;

	/* Set the Waveform Generation Mode Bits */
	TCCR1A |= ( TIMER1_WAVEFORM_GENERATION_MODE & 0x03 );
	TCCR1B |= ( TIMER1_WAVEFORM_GENERATION_MODE & 0x0C ) << 1;

	// '\'  means that the macro will be completed on another line
	#if 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE	 || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE


			/* Check on Compare Output Mode (OC1A Pin Mode) */
			#if   TIMER1_0C1A_MODE == TIMER1_COM_DISCONNECT_0C1A

				/* Normal Port Operation, 0C1A Disconnected */
				CLR_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

			#elif TIMER1_0C1A_MODE == TIMER1_COM_TOGGLE_0C1A

				/* Toggle 0C1A PIN on Compare Match */
				CLR_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction 0C1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_0C1A_MODE == TIMER1_COM_CLEAR_0C1A

				/* Clear 0C1A PIN on Compare Match */
				SET_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

				/* Direction 0C1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_0C1A_MODE == TIMER1_COM_SET0_0C1A

				/* Set 0C1A PIN on Compare Match */
				SET_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction 0C1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_0C1A_MODE\" configuration option"
			#endif


			/* Check on Compare Output Mode (OC1B Pin Mode) */
			#if   TIMER1_0C1B_MODE == TIMER1_COM_DISCONNECT_0C1B

				/* Normal Port Operation, OC1B Disconnected */
				CLR_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

			#elif TIMER1_0C1B_MODE == TIMER1_COM_TOGGLE_0C1B

				/* Toggle OC1B PIN on Compare Match */
				CLR_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_0C1B_MODE == TIMER1_COM_CLEAR_0C1B

				/* Clear OC1B PIN on Compare Match */
				SET_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_0C1B_MODE == TIMER1_COM_SET0_0C1B

				/* Set OC1B PIN on Compare Match */
				SET_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_0C1B_MODE\" configuration option"
			#endif


	#elif	TIMER1_WAVEFORM_GENERATION_MODE != 13 && TIMER1_WAVEFORM_GENERATION_MODE <16


			/* Check on Compare Output Mode (0C1A Pin Mode) */
			#if   TIMER1_0C1A_MODE == TIMER1_COM_DISCONNECT_0C1A

				/* Normal Port Operation, 0C1A Disconnected */
				CLR_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

			#elif TIMER1_0C1A_MODE == TIMER1_COM_NON_INVERTING_0C1A

				/* OC1A in Non Inverting Mode */
				SET_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_0C1A_MODE == TIMER1_COM_INVERTING_0C1A

				/* OC1A in Inverting Mode */
				SET_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_0C1A_MODE\" configuration option"
			#endif

			/* Check on Compare Output Mode (OC1B Pin Mode) */
			#if   TIMER1_0C1B_MODE == TIMER1_COM_DISCONNECT_0C1B

				/* Normal Port Operation, OC1B Disconnected */
				CLR_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

			#elif TIMER1_0C1B_MODE == TIMER1_COM_NON_INVERTING_0C1B

				/* 0C1B in Non Inverting Mode */
				SET_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_0C1B_MODE == TIMER1_COM_INVERTING_0C1B

				/* 0C1B in Inverting Mode */
				SET_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_0C1B_MODE\" configuration option"
			#endif


	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif


	/* Set TCNT1 PREload Value From Configuration File */
	TCNT1 = TIMER1_TCNT1_PRELOAD;

	/* Set OCR1A PREload Value From Configuration File */
	OCR1A = TIMER1_OCR1A_PRELOAD;

	/* Set OCR1B PREload Value From Configuration File */
	OCR1B = TIMER1_OCR1B_PRELOAD;

	// '\'  means that the macro will be completed on another line
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE ||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE		||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE		||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		/* Set ICR1 PREload Value From Configuration File */
		ICR1 = TIMER1_ICR1_PRELOAD;

	#endif


	#if   TIMER1_OVF_INT_STATUS == TIMER1_OVF_INT_ENABLE

			/* Clear the Overflow Interrupt Flag */
			SET_BIT( TIFR , TOV1 );

			/* Enable the Overflow Interrupt */
			SET_BIT( TIMSK , TOIE1 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_OVF_INT_STATUS == TIMER1_OVF_INT_DISABLE

			/* Disable the Overflow Interrupt */
			CLR_BIT( TIMSK , TOIE1 );

	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_OVF_INT_STATUS\" configuration option"
	#endif


	#if TIMER1_COMPA_INT_STATUS == TIMER1_COMPA_INT_ENABLE

			/* Clear the Compare Match A Interrupt Flag */
			SET_BIT( TIFR , OCF1A );

			/* Enable the Compare Match A Interrupt */
			SET_BIT( TIMSK , OCIE1A );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_COMPA_INT_STATUS == TIMER1_COMPA_INT_DISABLE

			/* Disable the Compare Match A Interrupt */
			CLR_BIT( TIMSK , OCIE1A );

	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_COMPA_INT_STATUS\" configuration option"
	#endif


	#if TIMER1_COMPB_INT_STATUS == TIMER1_COMPB_INT_ENABLE

			/* Clear the Compare Match B Interrupt Flag */
			SET_BIT( TIFR , OCF1B );

			/* Enable the Compare Match B Interrupt */
			SET_BIT( TIMSK , OCIE1B );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_COMPB_INT_STATUS == TIMER1_COMPB_INT_DISABLE

			/* Disable the Compare Match B Interrupt */
			CLR_BIT( TIMSK , OCIE1B );
	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_COMPB_INT_STATUS\" configuration option"
	#endif


	/* Clear the Clock Source Select Bits */
	TCCR1B &= TIMER1_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR1B |= TIMER1_CLOCK_SOURCE_msk;

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ICU_Init( void )
{
	/* (You must Initialization TIMER1 First) Initialization the Input Capture Unit Based on TIMER0_config.h File Choices */

	/* Check on Input Capture Noise Canceler Status */
	#if   ICU_NOISE_CANCELER_STATUS == ICU_NOISE_CANCELER_DISABLE

		/* Disable Input Capture Noise Canceler */
		CLR_BIT( TCCR1B , ICNC1 );

	#elif ICU_NOISE_CANCELER_STATUS == ICU_NOISE_CANCELER_ENABLE

		/* Enable Input Capture Noise Canceler */
		SET_BIT( TCCR1B , ICNC1 );

	#else
		/* Make an Error */
		#error "Wrong \"ICU_NOISE_CANCELER_STATUS\" configuration option"
	#endif


	/* Check on Input Capture Signal Start Edge Status */
	#if   ICU_START_EDGE_STATUS == ICU_FALLING_EDGE

		/* the Input Capture Signal Start Edge is Falling Edge */
		CLR_BIT( TCCR1B , ICES1 );

	#elif ICU_START_EDGE_STATUS == ICU_RISING_EDGE

		/* the Input Capture Signal Start Edge is Rising Edge */
		SET_BIT( TCCR1B , ICES1 );

	#else
		/* Make an Error */
		#error "Wrong \"ICU_START_EDGE_STATUS\" configuration option"
	#endif

	/* Direction ICP1 PIN as Input */
	CLR_BIT( DDRD  , ICP1_PIN );

	#if   TIMER1_CAPT_INT_STATUS == TIMER1_CAPT_INT_ENABLE

		/* Clear Input Capture Unit Interrupt Flag */
		SET_BIT( TIFR , ICF1 );

		/* Enable Input Capture Unit Interrupt */
		SET_BIT( TIMSK , TICIE1 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ICU_FallingTriggerEdge( void )
{
	/* Set the Trigger Edge as Falling Edge */
	CLR_BIT( TCCR1B , ICES1 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ICU_RisingTriggerEdge( void )
{
	/* Set the Trigger Edge as Rising Edge */
	SET_BIT( TCCR1B , ICES1 );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_SetCompare_A_Value( uint16 CompareAValue )
{
	/* Take the Compare A Value to Set it in OCR1A Register */
	OCR1A = CompareAValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_SetCompare_B_Value( uint16 CompareBValue )
{
	/* Take the Compare B Value to Set it in OCR1B Register */
	OCR1B = CompareBValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_SetTimerValue( uint16 TimerValue )
{
	/* Take the Timer Value to Set it in TCNT1 Register (do not use it when you use ICU) */
	TCNT1 = TimerValue;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint16 TIMER1_GetTimerValue( void )
{
	/* Return the Value of the TCNT1 Register */
	return TCNT1;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_InterruptDisable( uint8 TIMER1_interrupt_label )
{
	/* Disable the Specified TIMER1 Interrupt */
	switch (TIMER1_interrupt_label)
	{
		/* Disable Overflow Interrupt */
		case TIMER1_OVF_LABEL:   CLR_BIT( TIMSK , TOIE1 );  break;

		/* Disable Compare Match A Interrupt */
		case TIMER1_COMPA_LABEL: CLR_BIT( TIMSK , OCIE1A ); break;

		/* Disable Compare Match B Interrupt */
		case TIMER1_COMPB_LABEL: CLR_BIT( TIMSK , OCIE1B ); break;

		/* Disable Capture Event Interrupt */
		case TIMER1_CAPT_LABEL:  CLR_BIT( TIMSK , TICIE1 ); break;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_InterruptEnable( uint8 TIMER1_interrupt_label )
{
	/* Enable the Specified TIMER1 Interrupt */
	switch (TIMER1_interrupt_label)
	{
		/* Enable Overflow Interrupt */
		case TIMER1_OVF_LABEL:   SET_BIT( TIMSK , TOIE1 );  break;

		/* Enable Compare Match A Interrupt */
		case TIMER1_COMPA_LABEL: SET_BIT( TIMSK , OCIE1A ); break;

		/* Enable Compare Match B Interrupt */
		case TIMER1_COMPB_LABEL: SET_BIT( TIMSK , OCIE1B ); break;

		/* Enable Capture Event Interrupt */
		case TIMER1_CAPT_LABEL:  SET_BIT( TIMSK , TICIE1 ); break;
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_SetPWM_OC1A_DutyCycle( uint8 DutyCycle )
{
	/* Set the Duty Cycle of the OC1A Pin PWM [0:255] */

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8BIT_MODE

		OCR1A = DutyCycle;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9BIT_MODE

		OCR1A = DutyCycle << 1;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10BIT_MODE

		OCR1A = DutyCycle << 2;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE ||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE		||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		OCR1A = (((uint32)DutyCycle)*ICR1) / 255;

	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_SetPWM_OC1B_DutyCycle( uint8 DutyCycle )
{
	/* Set the Duty Cycle of the OC1A Pin PWM [0:255] */

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8BIT_MODE

		OCR1B = DutyCycle;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9BIT_MODE

		OCR1B = DutyCycle << 1;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10BIT_MODE 	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10BIT_MODE

		OCR1B = DutyCycle << 2;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE ||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE		||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		OCR1B = (((uint32)DutyCycle)*ICR1) / 255;

	#elif 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_OCR1A_MODE ||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_OCR1A_MODE		||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE

		OCR1B = (((uint32)DutyCycle)*OCR1A) / 255;


	#endif

}
/*___________________________________________________________________________________________________*/



#if TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE
/*___________________________________________________________________________________________________*/
uint32 TIMER1_GetTime_ms( void )
{
	/* Return Total Time for When Timer Start Count */
	/* should no thing change the timer TCNT1 and TIMER1_TCNT1_PRELOAD = 0 */
	/* if else you can use TIMER1_RESET function if you can */

	#if	  TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE
		return (uint32)((TCNT1 + (((uint32)TIMER1_Counter) << 16))*(presc_T1*1000.0/F_CPU));
	#else
		return (uint32)((TCNT1 + ((uint32)TIMER1_Counter)*OCR1A)*(presc_T1*1000.0/F_CPU));
	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void TIMER1_RESET( void )
{
	/* Set TCNT1 and TIMER1_Counter to 0 */

	TCNT1 = 0;
	TIMER1_Counter = 0;
}
/*___________________________________________________________________________________________________*/
#endif


uint16 TIMER1_Set_INT_Time_ms( uint16 milliseconds )
{
	/* Return Number of Counting for the Given Time (in milliseconds) */

	#if   TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

			float32 CountsNumber = ((float32)milliseconds*F_CPU)/(FREQ_DIVIDER_T1) ;

			uint16 TCNT1_value = (1 - (CountsNumber - (uint32)CountsNumber))*65536;

			TCNT1 = TCNT1_value;

			if (CountsNumber > (uint32)CountsNumber)
			{
				CountsNumber = (uint32)CountsNumber + 1;
			}

			return CountsNumber;

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE		||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE

			float32 CountsNumber = ((float32)milliseconds*F_CPU)/(OCR1A*presc_T1*1000.0) ;

			uint16 TCNT1_value = (1 - (CountsNumber - (uint16)CountsNumber))*OCR1A;

			if (TCNT1_value == OCR1A)
			{
				TCNT1_value = 0;
			}

			TCNT1 = TCNT1_value;

			if (CountsNumber > (int)CountsNumber)
			{
				CountsNumber = (int)CountsNumber + 1;
			}
			return CountsNumber;

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_OCR1A_MODE	||	\
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_OCR1A_MODE

			float32 CountsNumber = ((float32)milliseconds*F_CPU)/(OCR1A*presc_T1*1000.0) ;

			uint16 TCNT1_value = (uint16)((1 - (CountsNumber - (uint16)CountsNumber))*OCR1A) >> 1;

			if (TCNT1_value == OCR1A)
			{
				TCNT1_value = 0;
			}

			TCNT1 = TCNT1_value;

			if (CountsNumber > (int)CountsNumber)
			{
				CountsNumber = (int)CountsNumber + 1;
			}
			return CountsNumber;

	#elif TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE

			float32 CountsNumber = ((float32)milliseconds*F_CPU)/(ICR1*presc_T1*1000.0) ;

			uint16 TCNT1_value = (1 - (CountsNumber - (uint16)CountsNumber))*ICR1;

			if (TCNT1_value == OCR1A)
			{
				TCNT1_value = 0;
			}

			TCNT1 = TCNT1_value;

			if (CountsNumber > (int)CountsNumber)
			{
				CountsNumber = (int)CountsNumber + 1;
			}
			return CountsNumber;

	#endif

}


/*___________________________________________________________________________________________________*/
void TIMER1_SetCallback( void (*CopyFuncPtr)(void) , uint8 TIMER1_interrupt_label )
{
	/* Set Call Back Function for the Specified TIMER1 Interrupt */

	/* Check that the Pointer is Valid */
	if( CopyFuncPtr != NULL && TIMER1_interrupt_label < 4)
	{
		/* Copy the Function Pointer */
		TIMER1_CallBack[TIMER1_interrupt_label] = CopyFuncPtr;
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint16 ICU_GetICUvalue( void )
{
	/* Return the Value of the ICR1 Register */
	return ICR1;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ICU_ClearFlag( void )
{
	/* Clear Input Capture Unit Flag */
	TIFR = (1 << ICF1);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 ICU_GetFlag( void )
{
	/* Return Input Capture Unit Flag Value */
	return (TIFR & (1 << ICF1));
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{
	/* ISR for Timer1 Overflow (OVF) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER1_CallBack[0] != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER1_CallBack[0]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		TIMER1_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{
	/* ISR for Timer1 Compare Match A (COMPA) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER1_CallBack[1] != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER1_CallBack[1]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		TIMER1_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	/* ISR for Timer1 Compare Match B (COMPB) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER1_CallBack[2] != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER1_CallBack[2]();
	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_6 (void)		__attribute__ ((signal)) ;
void __vector_6 (void)
{

	/* ISR for Timer1 Capture Event (CAPT) Interrupt */

	/* Check that the Pointer is Valid */
	if(TIMER1_CallBack[3] != NULL )
	{
		/* Call The Global Pointer to Function */
		TIMER1_CallBack[3]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		TIMER1_Counter++;
	#endif
}
/*___________________________________________________________________________________________________*/


