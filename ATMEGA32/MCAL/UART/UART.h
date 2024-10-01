/*File Guard*/
#ifndef UART_H_
#define UART_H_

#include "UART_config.h"
#include "../../LIB/common_macros.h"

/*Initialize UART based on UART_config file choices*/
void UART_Init( void );

/*Disable the Specified UART Interrupt*/
void UART_InterruptDisable( uint8 UART_interrupt_label );

/*Enable the Specified UART Interrupt*/
void UART_InterruptEnable( uint8 UART_interrupt_label );

/*___________________________________________________________________________________________________*/
#if UART_TRANSMITTER_ENABLE == ENABLE


/*Send one Character*/
void UART_SendCharacter( uint8 Character );

/*Send String until '\0' Character*/
void UART_SendString( const uint8 * String_pointer );

/*Send Integer Number*/
void UART_SendInteger( int number );

#if UART_TX_COMPLETE_INTERRUPT == ENABLE

/* Set Call Back Function for the TX */
void UART_Set_TX_Callback ( void (*CopyFuncPtr)(void) , uint8 * TXString_pointer );

#endif

#endif
/*___________________________________________________________________________________________________*/


/*___________________________________________________________________________________________________*/
#if UART_RECEIVER_ENABLE == ENABLE


/*Read one Character*/
uint8 UART_readCharacter( void );

/*Read String until size complete*/
void UART_readStringUntilSize( uint8 * String_pointer,uint16 String_Size );

/*Read String until '\0'*/
void UART_readString( uint8 * String_pointer );

/*Read String until find stop_Character*/
void UART_readStringUntil( uint8 * String_pointer,uint8 stop_Character );

/*Check that there is data ready to read*/
uint8 UART_available_To_Read( void );

/*Return flag register*/
uint8 UART_CheckErrors( void );

#if UART_RX_COMPLETE_INTERRUPT == ENABLE

/* Set Call Back Function for the RX */
void UART_Set_RX_Callback ( void (*CopyFuncPtr)(void) , uint8 * RXString_pointer , uint8 StringSize, uint8 Stop_Character );

#endif

#endif
/*___________________________________________________________________________________________________*/

#endif /* UART_H_ */
