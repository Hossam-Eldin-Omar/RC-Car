/*File Guard*/
#ifndef ADC_H_
#define ADC_H_

#include "ADC_config.h"
#include "../../LIB/common_macros.h"

/*Initialization the ADC based on ADC_config.h file choices*/
void ADC_Init( void );

/*Start Conversion And Get the Value of the ADC Registers*/
uint16 ADC_Get_10BIT_Result( uint8 ADC_channel );

/*Start Conversion And Get the Value of the ADCH Register*/
uint8 ADC_Get_8BIT_Result( uint8 ADC_channel );

/*Start Conversion Without Read ADC Register*/
void ADC_Only_Start_Conversion( uint8 ADC_channel );

/*Get the Value of the ADC Without Conversion (Read ADC Register only)*/
uint16 ADC_Only_Get_10BIT_Result( void );

/*Enable the ADC*/
void ADC_Enable( void );

/*Disable the ADC*/
void ADC_Disable( void );

/*Enable the ADC Interrupt*/
void ADC_InterruptEnable( void );

/*Disable the ADC Interrupt*/
void ADC_InterruptDisable( void );

/*Set Call Back Function for the ADC*/
void ADC_SetCallback( void (*CopyFuncPtr)(void) , uint16 * ADC_result_pointer );

#endif /* ADC_H_ */
