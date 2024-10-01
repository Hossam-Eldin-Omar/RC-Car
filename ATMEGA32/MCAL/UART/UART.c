#include "UART.h"
/*___________________________________________________________________________________________________*/
#if UART_TRANSMITTER_ENABLE == ENABLE && UART_TX_COMPLETE_INTERRUPT == ENABLE

/* Pointer  => Carry the Address of TX String From the main Function */
uint8 * UART_TXString_pointer = NULL;

/* variable to indicate for the current Character index of the TX String */
uint8 UART_TX_Index;

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (* UART_TXCallBack)(void)= NULL;

#endif
/*___________________________________________________________________________________________________*/


/*___________________________________________________________________________________________________*/
#if UART_RECEIVER_ENABLE == ENABLE && UART_RX_COMPLETE_INTERRUPT == ENABLE

/* Pointer  => Carry the Address of RX String From the main Function */
uint8 * UART_RXString_pointer = NULL;

/* variable to carry the RX String size */
uint8 UART_StringSize;

/* variable to indicate for the current Character index of the RX String */
uint8 UART_RX_Index;

/* variable to indicate for the current Character index of the RX String */
uint8 UART_RX_Index;

/* variable to Stop Character of the RX String */
uint8 UART_Stop_Character;

/* Pointer to Function => Carry the Address of ISR Function From the main Function */
void (* UART_RXCallBack)(void)= NULL;

#endif
/*___________________________________________________________________________________________________*/



static uint16 Round(float64 num)
{
	return (uint16)(num + 0.5);
}


/*___________________________________________________________________________________________________*/
void UART_Init(void)
{
	/* Initialize UART based on UART_config file Choices */

	/*Calculate The UBRR Registers */
	#if UART_U2X_Mode == UART_U2X_DISABLE

		uint16 UBRR = (uint16)(Round(F_CPU/(UART_BAUD_RATE*16.0))-1);

	#elif UART_U2X_Mode == UART_U2X_ENABLE

		uint16 UBRR = (uint16)(Round(F_CPU/(UART_BAUD_RATE*8.0))-1);

	#else
		/* Make an Error */
		#error "Wrong \"UART_U2X_Mode\" configuration option"
	#endif


	/* Set The UBRR Register */
	UBRRH = (uint8)(UBRR >> 8);
	UBRRL = (uint8)(UBRR);


	/* Clear Error Flag Bits */
	UCSRA &= 0XE3;


	/* Check on Multi-Processor Communication mode */
	#if UART_MPCM_Mode == UART_MPCM_DISABLE

		/* Disable Multi-Processor Communication mode */
		CLR_BIT( UCSRA , MPCM );

	#elif UART_MPCM_Mode == UART_MPCM_ENABLE

		/* Enable Multi-Processor Communication mode */
		SET_BIT( UCSRA , MPCM );

	#else
		/* Make an Error */
		#error "Wrong \"UART_MPCM_Mode\" configuration option"
	#endif


	/* Check on Double the UART Transmission Speed mode */
	#if UART_U2X_Mode == UART_U2X_DISABLE

		/* Disable Double Speed mode */
		CLR_BIT( UCSRA , U2X );

	#elif UART_U2X_Mode == UART_U2X_ENABLE

		/* Enable Double Speed mode */
		SET_BIT( UCSRA , U2X );

	#else
		/* Make an Error */
		#error "Wrong \"UART_U2X_Mode\" configuration option"
	#endif


	/* Declaration Temporarily Variable UCSRC_REG */
	uint8 UCSRC_REG = 0X80;


	/* Set Asynchronous mode */
	CLR_BIT(UCSRC_REG , UMSEL) ;


	/* Check on Parity mode */
	#if UART_Parity_Mode == UART_Parity_Disabled

		/* Disabled Parity */
		CLR_BIT( UCSRC_REG , UPM1 ); CLR_BIT( UCSRC_REG , UPM0 );

	#elif UART_Parity_Mode == UART_Parity_Even

		/* Enabled, Even Parity */
		SET_BIT( UCSRC_REG , UPM1 ); CLR_BIT( UCSRC_REG , UPM0 );

	#elif UART_Parity_Mode == UART_Parity_Odd

		/* Enabled, Odd Parity */
		SET_BIT( UCSRC_REG , UPM1 ); SET_BIT( UCSRC_REG , UPM0 );

	#else
		/* Make an Error */
		#error "Wrong \"UART_Parity_Mode\" configuration option"
	#endif

	/* Check on Stop Bit Mode */
	#if UART_Stop_Bit_Mode == UART_1_Stop_Bit

		/* 1 Stop BIT */
		CLR_BIT( UCSRC_REG , USBS );

	#elif UART_Stop_Bit_Mode == UART_2_Stop_Bit

		/* 2 Stop BITs */
		SET_BIT( UCSRC_REG , USBS );

	#else
		/* Make an Error */
		#error "Wrong \"UART_Stop_Bit_Mode\" configuration option"
	#endif

	/* Check on Data Size */
	#if UART_Character_Size_Mode == UART_DATA_5_BIT_SIZE

		/* 5 BITs Data Size */
		CLR_BIT( UCSRC_REG , UCSZ0 );
		CLR_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_Character_Size_Mode == UART_DATA_6_BIT_SIZE

		/* 6 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		CLR_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_Character_Size_Mode == UART_DATA_7_BIT_SIZE

		/* 7 BITs Data Size */
		CLR_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_Character_Size_Mode == UART_DATA_8_BIT_SIZE

		/* 8 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_Character_Size_Mode == UART_DATA_9_BIT_SIZE

		/* 9 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		SET_BIT( UCSRB , UCSZ2 );

	#else
		/* Make an Error */
		#error "Wrong \"UART_Character_Size_Mode\" configuration option"
	#endif


	/*Set UCSRC*/
	UCSRC = UCSRC_REG;


	/*Check if the Receive is Enable*/
	#if UART_RECEIVER_ENABLE == DISABLE

		/* Disable the Receive */
		CLR_BIT( UCSRB , RXEN );

	#elif UART_RECEIVER_ENABLE == ENABLE

		/* Enable the Receive */
		SET_BIT( UCSRB , RXEN );

	#else
		/* Make an Error */
		#error "Wrong \"UART_RECEIVER_ENABLE\" configuration option"
	#endif

	/*Check if the Transmitter is Enable*/
	#if UART_TRANSMITTER_ENABLE == DISABLE

		/* Disable the Transmitter */
		CLR_BIT( UCSRB , TXEN );

	#elif UART_TRANSMITTER_ENABLE == ENABLE

		/* Enable the Transmitter */
		SET_BIT( UCSRB , TXEN );

	#else
		/* Make an Error */
		#error "Wrong \"UART_TRANSMITTER_ENABLE\" configuration option"
	#endif


	/* Check if RX Complete Interrupt is Enable */
	#if UART_RX_COMPLETE_INTERRUPT == DISABLE

		/* Disable RX Complete Interrupt */
		CLR_BIT( UCSRB , RXCIE );

	#elif UART_RX_COMPLETE_INTERRUPT == ENABLE

		/* Enable RX Complete Interrupt */
		SET_BIT( UCSRB , RXCIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_RX_COMPLETE_INTERRUPT\" configuration option"
	#endif


	/* Check if TX Complete Interrupt is Enable */
	#if UART_TX_COMPLETE_INTERRUPT == DISABLE

		/* Disable TX Complete Interrupt */
		CLR_BIT( UCSRB , TXCIE );

	#elif UART_TX_COMPLETE_INTERRUPT == ENABLE

		/* Enable TX Complete Interrupt */
		SET_BIT( UCSRB , TXCIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_TX_COMPLETE_INTERRUPT\" configuration option"
	#endif


	/* Check if UDR Empty Interrupt is Enable */
	#if UART_UDR_EMPTY_INTERRUPT == DISABLE

		/* Disable UDR Empty Interrupt */
		CLR_BIT( UCSRB , UDRIE );

	#elif UART_UDR_EMPTY_INTERRUPT == ENABLE



		/* Enable UDR Empty Interrupt */
		SET_BIT( UCSRB , UDRIE )

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_UDR_EMPTY_INTERRUPT\" configuration option"
	#endif


}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_InterruptDisable(uint8 UART_interrupt_label)
{
	switch (UART_interrupt_label)
	{
		/* Disable TX Complete Interrupt */
		case UART_INT_TX_LABEL:  CLR_BIT( UCSRB , TXCIE ); break;

		/* Disable RX Complete Interrupt */
		case UART_INT_RX_LABEL:  CLR_BIT( UCSRB , RXCIE ); break;

		/* Disable UDR Empty Interrupt */
		case UART_INT_UDR_LABEL: CLR_BIT( UCSRB , UDRIE ); break;
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_InterruptEnable(uint8 UART_interrupt_label)
{
	switch (UART_interrupt_label)
	{
		/* Enable TX Complete Interrupt */
		case UART_INT_TX_LABEL:  SET_BIT( UCSRB , TXCIE ); break;

		/* Enable RX Complete Interrupt */
		case UART_INT_RX_LABEL:  SET_BIT( UCSRB , RXCIE ); break;

		/* Enable UDR Empty Interrupt */
		case UART_INT_UDR_LABEL: SET_BIT( UCSRB , UDRIE ); break;
	}

}
/*___________________________________________________________________________________________________*/



/*===================================================================================================*/
#if UART_TRANSMITTER_ENABLE == ENABLE

/*___________________________________________________________________________________________________*/
void UART_SendCharacter( uint8 Character )
{
	/* Send One Character */


	#if UART_COUNTOUT != INFINITE

		/* Counter that Count until it Equals UART_COUNTOUT */
		/* to end the Waiting if Sending does not End */
		uint16 UART_counter = 0 ;

		/* Waiting until the Sending is Complete or until Waiting Time is End */
		while (((GET_BIT( UCSRA , UDRE )) == 0) && (UART_counter != UART_COUNTOUT))
		{
			/* Counter UP */
			UART_counter++ ;
		}

		/* Check that the Sending is Complete Correctly */
		if (UART_counter != UART_COUNTOUT)
		{
			/* Send the Character */
			UDR = Character ;
		}

	#else
		/* Waiting until the Sending is Complete */
		while (GET_BIT( UCSRA , UDRE ) == 0);
		/* Send the Character */
		UDR = Character ;
	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_SendString( const uint8 * String_pointer )
{
	/* Send String Until '\0' Character */

	/* Loop on the String Until it End */
	for(uint8 index = 0 ; String_pointer[index] != '\0' ; index++)
	{
		/* Send One Character */
		UART_SendCharacter(String_pointer[index]) ;
	}
	/* Send '\0' Character as End of the String */
	UART_SendCharacter('\0');

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_SendInteger( int number )
{
	/* Send Integer Number */

	uint8 arr[UART_MAX_INT_LENGTH];

   /* store the integer number to arr & 10 is for decimal numbering system*/
   itoa(number,arr,10);

   UART_SendString(arr);
}
/*___________________________________________________________________________________________________*/


#if UART_TX_COMPLETE_INTERRUPT == ENABLE

/*___________________________________________________________________________________________________*/
void UART_Set_TX_Callback ( void (*CopyFuncPtr)(void) , uint8 * TXString_pointer )
{
	/* Set Call Back Function for the TX */

	/* Check that the Function Pointer And Variable Pointer are Valid */
	if ((TXString_pointer != NULL) && (CopyFuncPtr != NULL))
	{
		/* Assign the UART */
		UART_TXString_pointer = TXString_pointer ;
		UART_TXCallBack = CopyFuncPtr ;

		/*Set Index to First Element*/
		UART_TX_Index = 0 ;

		/*Send First Character */
		UART_SendCharacter(UART_TXString_pointer[UART_TX_Index]);

	}
	else
	{
		/* Check if TX Interrupt Enable */
		#if UART_TX_COMPLETE_INTERRUPT == ENABLE

			/* Disable TX Complete Interrupt */
			CLR_BIT( UCSRB , TXCIE );

		#endif
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_15 (void)		__attribute__ ((signal)) ;
void __vector_15 (void)
{
	/* ISR for TX complete */

	/* Increment index of the TX String */
	UART_TX_Index++ ;

	if (UART_TXString_pointer[UART_TX_Index] == '\0')
	{
		/* Send the Last Character */
		UDR = UART_TXString_pointer[UART_TX_Index] ;

		/* Ready for New String */
		UART_TX_Index=0;

		/* Check that the Pointer is Valid */
		if(UART_TXCallBack != NULL )
		{
			/* Call The Pointer to Function */
			UART_TXCallBack() ;
		}

	}
	else
	{
		/* Send next Character */
		UDR = UART_TXString_pointer[UART_TX_Index] ;
	}
}
/*___________________________________________________________________________________________________*/

#endif

#endif
/*===================================================================================================*/






/*===================================================================================================*/
#if UART_RECEIVER_ENABLE == ENABLE

/*___________________________________________________________________________________________________*/
uint8 UART_readCharacter( void )
{
	/* Read 0ne Character */

	#if UART_COUNTOUT != INFINITE

		/* Counter that Count until it Equals UART_COUNTOUT */
		/* to end the Waiting if Sending does not End */
		uint16 UART_counter = 0 ;

		/* Waiting until the Reading is Complete or until Waiting Time is End */
		while (((GET_BIT( UCSRA , RXC )) == 0) && (UART_counter != UART_COUNTOUT))
		{
			/* Counter UP */
			UART_counter++ ;
		}

		/* Check that the Reading is Complete Correctly */
		if (UART_counter != UART_COUNTOUT)
		{
			/* Read the Character */
			return UDR;
		}
		else
		{
			/* Read '?' Character */
			return '?';
		}

	#else

		/* Waiting until the Reading is Complete */
		while (GET_BIT( UCSRA , RXC ) == 0);

		/* Send the Character */
		return UDR;

	#endif

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_readStringUntilSize( uint8 * String_pointer , uint16 String_Size )
{
	/* Read String Until Size Complete*/

	/* Loop on the String Until it End */
	for(uint16 index = 0 ; index < String_Size ; index++)
	{
		/* Read One Character */
		String_pointer[index] = UART_readCharacter();

		/* if that Character is '\0' End the Function */
		if(String_pointer[index] == '\0')
			break;
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_readString( uint8 * String_pointer )
{
	/* Read String Until Size Complete*/

	uint16 index;

	/* Loop on the String Until it End (Read '\0') */
	for(index = 0 ; String_pointer[index] != '\0' ; index++)
	{
		/* Read One Character */
		String_pointer[index] = UART_readCharacter();
	}

	/* Read '\0' Character as End of the String */
	String_pointer[index] = '\0';
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void UART_readStringUntil( uint8 * String_pointer , uint8 stop_Character )
{
	/* Read String Until Find stop_Character */

	uint8 index = 0;
	uint8 c;
	do
	{
		if(UART_available_To_Read())
		{
			c = UART_readCharacter();
			String_pointer[index] = c;
			if(c == '\0' || c == stop_Character)
			{
				if(c == stop_Character)
				{
					String_pointer[index] = '\0';
				}
				break;
			}
			index++;
		}
	}while(1);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 UART_available_To_Read( void )
{
	/* Check that there is Data Ready to Read */

	return GET_BIT( UCSRA,RXC );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 UART_CheckErrors( void )
{
	/* Return Flag Register */

	return UCSRA & 0x1C ;
}
/*___________________________________________________________________________________________________*/


#if UART_RX_COMPLETE_INTERRUPT == ENABLE

/*___________________________________________________________________________________________________*/
void UART_Set_RX_Callback ( void (*CopyFuncPtr)(void) , uint8 * RXString_pointer , uint8 StringSize, uint8 Stop_Character )
{
	/* Set Call Back Function for the RX */

	/* Check that the Function Pointer And Variable Pointer are Valid */
	if ((RXString_pointer != NULL) && (CopyFuncPtr != NULL))
	{
		/*Assign the UART */
		UART_RXCallBack	= CopyFuncPtr ;
		UART_RXString_pointer = RXString_pointer ;
		UART_StringSize	= StringSize;
		UART_Stop_Character = Stop_Character;

		/* Set Index to First Element */
		UART_RX_Index = 0 ;

	}
	else
	{
		/* Check if Receive Interrupt Enable */
		#if UART_RX_COMPLETE_INTERRUPT == ENABLE

			/* Disable RX Complete Interrupt */
			CLR_BIT( UCSRB , RXCIE );

		#endif
	}

}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void __vector_13 (void)		__attribute__ ((signal)) ;
void __vector_13 (void)
{
	/* ISR for RX complete */

	uint8 ch;

	/* Receive next Character */
	ch = UDR ;
	UART_RXString_pointer[UART_RX_Index] = ch;

	/* Increment index of the RX String */
	UART_RX_Index++ ;


	if ((UART_RX_Index >= UART_StringSize) || (ch == '\0') || (ch == UART_Stop_Character))
	{

		if(ch != '\0' && UART_RX_Index < UART_StringSize)
		{
			/* Read '\0' Character as End of the String */
			UART_RXString_pointer[UART_RX_Index - 1] = '\0';
		}


		/* Ready for New String */
		UART_RX_Index = 0;

		/* Check that the Pointer is Valid */
		if(UART_RXCallBack != NULL )
		{
			/* Call The Pointer to Function */
			UART_RXCallBack() ;
		}

	}

}
/*___________________________________________________________________________________________________*/

#endif

#endif
/*===================================================================================================*/


