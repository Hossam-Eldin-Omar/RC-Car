#include "ADC.h"

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (*ADC_CallBack)(void) = {NULL};

/* Pointer => Carry the Address of ADC Result Variable From the main Function */
uint16 * ADC_copy_result_pointer = NULL;

/* Hint : ADC_SetCallback( & ADC_Interrupt_Function , & ADC_Result_Variable ); */


/*___________________________________________________________________________________________________*/
void ADC_Init( void )
{
	/* Initialization the ADC based on ADC_config.h file Choices */

	/* Check the ADC Voltage Reference */
	#if	  ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AREF

		/* ADC Voltage Reference is AREF PIN */
		CLR_BIT( ADMUX , REFS1 ); CLR_BIT( ADMUX , REFS0 );

	#elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AVCC

		/* ADC Voltage Reference is AVCC pin */
		CLR_BIT( ADMUX , REFS1 ); SET_BIT( ADMUX , REFS0 );

	#elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_2_56v

		/* ADC Voltage Reference is Internal 2.56V */
		SET_BIT( ADMUX , REFS1 ); SET_BIT( ADMUX , REFS0 );

	#else
		/* Make an Error */
		#error "Wrong \"ADC_VOLTAGE_REF\" configuration option"
	#endif


	/* Check the Adjust mode */
	#if	  ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

		/* ADC in Right ADJUST mode */
		CLR_BIT( ADMUX , ADLAR );

	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* ADC in Left ADJUST mode */
		SET_BIT( ADMUX , ADLAR );

	#else
		/* Make an Error */
		#error "Wrong \"ADC_ADJUSTMENT\" configuration option"
	#endif


	/* Clear the Prescaler Bits */
	ADCSRA &= ADC_PRESCALER_clr_msk;

	/* Set the Prescaler Value */
	ADCSRA |= ADC_PRESCALER;


	/* Check the ADC mode */
	#if	 ADC_MODE == ADC_MODE_AUTO_TRIGGER

		/* Disable ADC Auto Trigger */
		CLR_BIT( ADCSRA , ADATE );

		/* Clear the ADC AUTO TRIGGER Source Bits */
		SFIOR &= ADC_AUTO_TRIGGER_SRC_clr_msk;

		/* Set the ADC AUTO TRIGGER Source Bits */
		SFIOR |= ADC_AUTO_TRIG_SRCE;

		/* Enable ADC Auto Trigger */
		SET_BIT( ADCSRA , ADATE );

	#elif ADC_MODE == ADC_MODE_SINGLE_CONVERSION

		/* Disable ADC Auto Trigger */
		CLR_BIT( ADCSRA , ADATE );

	#else
		/* Make an Error */
		#error "Wrong \"ADC_MODE\" configuration option"
	#endif


	/* Enable the ADC */
	SET_BIT( ADCSRA , ADEN );


	/* Check if the ADC Interrupt is Enable*/
	#if   ADC_INT_STATUS == ADC_INT_ENABLE

		/* Clear the ADC Interrupt Flag */
		SET_BIT( ADCSRA , ADIF );

		/* Enable the ADC Interrupt */
		SET_BIT( ADCSRA , ADIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#elif ADC_INT_STATUS == ADC_INT_DISABLE

		/* Disable the ADC Interrupt */
		CLR_BIT( ADCSRA , ADIE );

	#else
		/* Make an Error */
		#error "Wrong \"ADC_INT_STATUS\" configuration option"
	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint16 ADC_Get_10BIT_Result( uint8 ADC_channel )
{
	/* Start Conversion And Get the Value of the ADC Registers */

	/* Clear the Channel Bits */
	ADMUX &= ADC_CHANNEL_clr_msk;

	/* Set the Channel Bits */
	ADMUX |= ADC_channel;

	/* Start Conversion */
	SET_BIT( ADCSRA , ADSC );

	/* Counter that Count until it Equals ADC_COUNTOUT */
	/* to end the Waiting if Conversion does not End */
	uint8 ADC_counter = 0;

	/* Waiting until the Conversion is Complete or until Waiting Time is End */
	while(GET_BIT( ADCSRA , ADSC ) && ADC_counter < ADC_COUNTOUT)
	{
		/* Counter UP */
		ADC_counter++;
	}


	/* Return the 10 BITS in any mode */
	#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 10 BITS */
			return ADC;
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 10 BITS */
			return (ADC >> 6);
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 ADC_Get_8BIT_Result( uint8 ADC_channel )
{
	/* Start Conversion And Get the Value of the ADCH Register */

	/* Clear the Channel Bits */
	ADMUX &= ADC_CHANNEL_clr_msk;

	/* Set the Channel Bits */
	ADMUX |= ADC_channel;

	/* Start Conversion */
	SET_BIT( ADCSRA , ADSC );

	/* Counter that Count until it Equals ADC_COUNTOUT */
	/* to end the Waiting if Conversion does not End */
	uint8 ADC_counter = 0;

	/* Waiting until the Conversion is Complete or until Waiting Time is End */
	while(GET_BIT( ADCSRA , ADSC ) && ADC_counter < ADC_COUNTOUT)
	{
		/* Counter UP */
		ADC_counter++;
	}


	/* if ADC in Right ADJUST mode */
	#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 8 MSB */
			return (ADC >> 2);
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	/* if ADC in Left ADJUST mode */
	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 8 MSB */
			return ADCH;
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ADC_Only_Start_Conversion( uint8 ADC_channel )
{
	/* Start Conversion Without Read ADC Register */

	/* Clear the Channel Bits */
	ADMUX &= ADC_CHANNEL_clr_msk;

	/* Set the Channel Bits */
	ADMUX |= ADC_channel;

	/* Start Conversion */
	SET_BIT( ADCSRA , ADSC );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint16 ADC_Only_Get_10BIT_Result( void )
{
	/* Get the Value of the ADC Without Conversion (Read ADC Register only) */

	/* Counter that Count until it Equals ADC_COUNTOUT */
	/* to end the Waiting if Conversion does not End */
	uint8 ADC_counter = 0;

	/* Waiting until the Conversion is Complete or until Waiting Time is End */
	while(GET_BIT( ADCSRA , ADSC ) && ADC_counter < ADC_COUNTOUT)
	{
		/* Counter UP */
		ADC_counter++;
	}

	/* Return the 10 BITS in any mode */
	#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 10 BITS */
			return ADC;
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* Check that the Conversion is End Correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* Return the 10 BITS */
			return (ADC >> 6);
		}
		else
		{
			/* Return 0 */
			return 0;
		}

	#endif
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ADC_Enable ( void )
{
	/* Enable the ADC */

	SET_BIT(ADCSRA , ADEN) ;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ADC_Disable ( void )
{
	/* Disable the ADC */

	CLR_BIT(ADCSRA , ADEN) ;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ADC_InterruptEnable ( void )
{
	/* Enable the ADC Interrupt */

	SET_BIT(ADCSRA , ADIE) ;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void ADC_InterruptDisable ( void )
{
	/* Disable the ADC Interrupt */

	CLR_BIT(ADCSRA , ADIE) ;
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/

void ADC_SetCallback( void (*CopyFuncPtr)(void) , uint16 * ADC_10BIT_result_pointer )
{
	/* Set Call Back Function for the ADC */


	/* Check that the Function Pointer And Variable Pointer are Valid */
	if((CopyFuncPtr != NULL) && (ADC_10BIT_result_pointer != NULL))
	{
		/* Copy the Function Pointer */
		ADC_CallBack = CopyFuncPtr;

		/* Copy the Result Variable Pointer */
		ADC_copy_result_pointer = ADC_10BIT_result_pointer;

		/* Check if the ADC Interrupt is Disable*/
		#if ADC_INT_STATUS == ADC_INT_DISABLE

			/* Clear the ADC Interrupt Flag */
			SET_BIT( ADCSRA , ADIF );

			/* Enable the ADC Interrupt */
			SET_BIT( ADCSRA , ADIE );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );
		#endif

	}
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	/* ISR for ADC Interrupt */

	/* Check that the Pointer is Valid */
	if(ADC_copy_result_pointer != NULL)
	{
		#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

			* ADC_copy_result_pointer = ADC;

		#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

			*ADC_copy_result_pointer = (ADC >> 6);

		#endif
	}

	/* Check that the Pointer is Valid */
	if(ADC_CallBack != NULL)
	{
		/* Call The Pointer to Function */
		ADC_CallBack();
	}
}
/*___________________________________________________________________________________________________*/

