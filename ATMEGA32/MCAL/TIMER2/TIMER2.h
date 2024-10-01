/*File Guard*/
#ifndef TIMER2_H_
#define TIMER2_H_

#include "../../LIB/common_macros.h"
#include "TIMER2_config.h"

/*Initialization the TIMER2 based on TIMER2_config.h file choices*/
void TIMER2_Init( void );

/*Take the Compare Value to Set it in OCR2 Register*/
void TIMER2_SetCompareValue( uint8 CompareValue );

/*Take the Timer Value to Set it in TCNT2 Register*/
void TIMER2_SetTimerValue( uint8 TimerValue );

/*Return the Value of the TCNT2 Register*/
uint8 TIMER2_GetTimerValue( void );

/*Disable the TIMER2 Overflow Interrupt*/
void TIMER2_OVF_InterruptDisable( void );

/*Enable the TIMER2 Overflow Interrupt*/
void TIMER2_OVF_InterruptEnable( void );

/*Disable the TIMER2 Compare Match Interrupt*/
void TIMER2_COMP_InterruptDisable( void );

/*Enable the TIMER2 Compare Match Interrupt*/
void TIMER2_COMP_InterruptEnable( void );


// '\'  means that the macro will be completed on another line
#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE || \
	TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

/*Set the Duty Cycle of the PWM [0:255]*/
void TIMER2_SetPWMDutyCycle( uint8 DutyCycle );

#else


#if TIMER2_COUNT_MODE == TIMER2_COUNT_ENABLE

/*Return Total Time for When Timer Start Count (if no thing change the timer TCNT2 and TIMER2_TCNT2_PRELOAD = 0)*/
uint32 TIMER2_GetTime_ms( void );

/*Set TCNT2 and TIMER2_Counter to 0*/
void TIMER2_RESET( void );

#endif


/*Return Number of Counting for the Given Time (in milliseconds)*/
uint16 TIMER2_Set_INT_Time_ms( uint16 milliseconds );


#endif


/*Set Call Back Function for the Overflow (OVF) Interrupt*/
void TIMER2_Set_OVF_Callback( void (*CopyFuncPtr)(void) );

/*Set Call Back Function for the Compare Match (COMP) Interrupt*/
void TIMER2_Set_COMP_Callback( void (*CopyFuncPtr)(void) );


#endif /* TIMER2_H_ */
