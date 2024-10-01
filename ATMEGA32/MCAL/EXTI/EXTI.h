/*File Guard*/
#ifndef EXTI_INTERRUPT_H_
#define EXTI_INTERRUPT_H_

#include "../../LIB/common_macros.h"
#include "EXTI_config.h"

/*Initialization the External Interrupt based on EXIT_config.h file choices*/
void EXTI_Init( void );

/*Disable the Specified External Interrupt*/
void EXTI_DisableInterrupt( uint8 EXIT_interrupt_label );

/*Enable the Specified External Interrupt*/
void EXTI_EnableInterrupt( uint8 EXIT_interrupt_label );

/*Change the Sense Control in Run Time Exists in EXIT_Init function already (not necessary to use)*/
void EXTI_ChangeSenseControl( uint8 mode , uint8 EXIT_interrupt_label );

/*Set Call Back Function for the Specified External Interrupt*/
void EXTI_SetCallback( void (*CopyFuncPtr)(void) , uint8 EXIT_interrupt_label);

#endif /* EXTI_INTERRUPT_H_ */
