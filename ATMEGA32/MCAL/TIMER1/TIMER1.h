/*File Guard*/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "TIMER1_config.h"
#include "../../LIB/common_macros.h"

/*Initialization the TIMER1 based on TIMER0_config.h file choices*/
void TIMER1_Init( void );

/*Take the Compare A Value to Set it in OCR1A Register*/
void TIMER1_SetCompare_A_Value( uint16 CompareAValue );

/*Take the Compare B Value to Set it in OCR1B Register*/
void TIMER1_SetCompare_B_Value( uint16 CompareBValue );

/*Take the Timer Value to Set it in TCNT1 Register (do not use it when you use ICU)*/
void TIMER1_SetTimerValue( uint16 TimerValue );

/*Return the Value of the TCNT1 Register*/
uint16 TIMER1_GetTimerValue( void );

/* Disable the Specified TIMER1 Interrupt */
void TIMER1_InterruptDisable( uint8 TIMER1_interrupt_label );

/* Enable the Specified TIMER1 Interrupt */
void TIMER1_InterruptEnable( uint8 TIMER1_interrupt_label );

/*Set the Duty Cycle of the OC1A Pin PWM [0:255]*/
void TIMER1_SetPWM_OC1A_DutyCycle( uint8 DutyCycle );

/*Set the Duty Cycle of the OC1B Pin PWM [0:255]*/
void TIMER1_SetPWM_OC1B_DutyCycle( uint8 DutyCycle );

/*Set Call Back Function for the Specified TIMER1 Interrupt*/
void TIMER1_SetCallback( void (*CopyFuncPtr)(void) , uint8 TIMER1_interrupt_label );

/*(You must Initialization TIMER1 First) Initialization the Input Capture Unit based on TIMER0_config.h file choices*/
void ICU_Init( void );

/*Set the Trigger Edge as Falling Edge*/
void ICU_FallingTriggerEdge( void );

/*Set the Trigger Edge as Rising Edge*/
void ICU_RisingTriggerEdge( void );

/*Clear Input Capture Unit Flag*/
void ICU_ClearFlag( void );

/*Return Input Capture Unit Flag Value*/
uint8 ICU_GetFlag( void );

/*Return the Value of the ICR1 Register*/
uint16 ICU_GetICUvalue( void );


#if TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

/*Return Total Time for When Timer Start Count*/
/*should no thing change the timer TCNT1 and TIMER1_TCNT1_PRELOAD = 0*/
/*if else you can use TIMER1_RESET function if you can*/
uint32 TIMER1_GetTime_ms( void );

/*Set TCNT1 and TIMER1_Counter to 0*/
void TIMER1_RESET( void );

#endif

/*Return Number of Counting for the Given Time (in milliseconds)*/
uint16 TIMER1_Set_INT_Time_ms( uint16 milliseconds );

#endif /* TIMER1_H_ */
