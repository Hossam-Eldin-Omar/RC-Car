/*File Guard*/
#ifndef TIMER0_H_
#define TIMER0_H_

#include "TIMER0_config.h"
#include "../../LIB/common_macros.h"

/*Initialization the TIMER0 based on TIMER0_config.h file choices*/
void TIMER0_Init( void );

/*Take the Compare Value to Set it in OCR0 Register*/
void TIMER0_SetCompareValue( uint8 CompareValue );

/*Take the Timer Value to Set it in TCNT0 Register*/
void TIMER0_SetTimerValue( uint8 TimerValue );

/*Return the Value of the TCNT0 Register*/
uint8 TIMER0_GetTimerValue( void );

/*Disable the TIMER0 Overflow Interrupt*/
void TIMER0_OVF_InterruptDisable( void );

/*Enable the TIMER0 Overflow Interrupt*/
void TIMER0_OVF_InterruptEnable( void );

/*Disable the TIMER0 Compare Match Interrupt*/
void TIMER0_COMP_InterruptDisable( void );

/*Enable the TIMER0 Compare Match Interrupt*/
void TIMER0_COMP_InterruptEnable( void );


// '\'  means that the macro will be completed on another line
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE || \
	TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

/*Set the Duty Cycle of the PWM [0:255]*/
void TIMER0_SetPWMDutyCycle( uint8 DutyCycle );

#else


#if TIMER0_COUNT_MODE == TIMER0_COUNT_ENABLE

/*Return Total Time for When Timer Start Count (if no thing change the timer TCNT0 and TIMER0_TCNT0_PRELOAD = 0)*/
uint32 TIMER0_GetTime_ms( void );

/*Set TCNT0 and TIMER0_Counter to 0*/
void TIMER0_RESET( void );

#endif


// '\'  means that the macro will be completed on another line
#if TIMER0_CLOCK_SOURCE_msk >= TIMER0_NO_PRESCALER && \
	TIMER0_CLOCK_SOURCE_msk <= TIMER0_PRESCALER_1024

/*Return Number of Counting for the Given Time (in milliseconds)*/
uint16 TIMER0_Set_INT_Time_ms( uint32 milliseconds );

#endif

#endif


/*Set Call Back Function for the Overflow (OVF) Interrupt*/
void TIMER0_Set_OVF_Callback( void (*CopyFuncPtr)(void) );

/*Set Call Back Function for the Compare Match (COMP) Interrupt*/
void TIMER0_Set_COMP_Callback( void (*CopyFuncPtr)(void) );


#endif /* TIMER0_H_ */
