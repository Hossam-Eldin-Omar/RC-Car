/*File Guard*/
#ifndef TIMER2_DEF_H_
#define TIMER2_DEF_H_

#include "../../LIB/std_types.h"


/*---------------------------------------    Registers    ---------------------------------------*/

#define TCNT2			*((volatile uint8 *)0x44)	/*Timer/Counter Register*/
#define OCR2			*((volatile uint8 *)0x43)	/*Output Compare Register*/
#define TCCR2			*((volatile uint8 *)0x45)	/*Timer/Counter Control Register*/
#define TIMSK			*((volatile uint8 *)0x59)	/*Timer/Counter Interrupt Mask Register*/
#define TIFR			*((volatile uint8 *)0x58)	/*Timer/Counter Interrupt Flag Register*/
#define ASSR			*((volatile uint8 *)0x42)	/*Timer/Counter Asynchronous Status Register*/
#define SREG			*((volatile uint8 *)0x5F)	/*status register*/
#define DDRD 			*((volatile uint8 *)0x31)	/*Port D Data Direction Register (OC2 pin Register)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*TCCR2 Register*/
#define CS20		0	/*Clock Select Bit 0*/ /*unused definition (bit in Register used)*/
#define CS21		1	/*Clock Select Bit 1*/ /*unused definition (bit in Register used)*/
#define CS22		2	/*Clock Select Bit 2*/ /*unused definition (bit in Register used)*/
#define WGM21		3	/*Waveform Generation Mode Bit 1 (CTC2)*/
#define COM20		4	/*Compare Match Output Mode Bit 0*/
#define COM21		5	/*Compare Match Output Mode Bit 1*/
#define WGM20		6	/*Waveform Generation Mode Bit 0 (PWM2)*/
#define FOC2		7	/*Force Output Compare*/ /*unused*/

/*TIMSK Register*/
#define TOIE2		6	/*Timer/Counter2 Overflow Interrupt Enable*/
#define OCIE2		7	/*Timer/Counter2 Output Compare Match Interrupt Enable*/

/*TIFR Register*/
#define TOV2		6	/*Timer/Counter2 Overflow Flag*/
#define OCF2		7	/*Timer/Counter2 Output Compare Match Flag*/

/*ASSR Register*/
#define TCR2UB		0	/*Timer/Counter Control Register2 Update Busy*/
#define OCR2UB		1	/*Output Compare Register2 Update Busy*/
#define TCN2UB		2	/*Timer/Counter2 Update Busy*/
#define AS2			3	/*Asynchronous Timer/Counter2*/

/*SREG Register*/
#define	I			7	/*Global Interrupt Enable*/

/*DDRD Register*/
#define OC2_PIN		7	/*Compare Match Output 2 pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define NULL			((void*)0)	/*define NULL value*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*TIMER2 Clock Mode*/
#define TIMER2_SYNCHRONOUS_MODE				0	/*The Timer/Counter2 clocked by an internal synchronous  clock source (F_CPU / prescaler)*/
#define TIMER2_ASYNCHRONOUS_MODE			1	/*The Timer/Counter2 clocked by an external asynchronous clock source (Oscillator connected to TOSC1 and TOSC2 Pins)*/

/*TIMER2 Clock Source*/
#define TIMER2_NO_CLOCK_SOURCE				0	/*No clock source (Timer/Counter stopped)*/
#define TIMER2_NO_PRESCALER					1	/*TIMER2 Frequency = F_CPU (No prescaling)*/
#define TIMER2_PRESCALER_8					2	/*TIMER2 Frequency = F_CPU / 8	  (CLK/8)*/
#define TIMER2_PRESCALER_32					3	/*TIMER2 Frequency = F_CPU / 32	  (CLK/32)*/
#define TIMER2_PRESCALER_64					4	/*TIMER2 Frequency = F_CPU / 64   (CLK/64)*/
#define TIMER2_PRESCALER_128				5	/*TIMER2 Frequency = F_CPU / 128  (CLK/128)*/
#define TIMER2_PRESCALER_256				6	/*TIMER2 Frequency = F_CPU / 256  (CLK/256)*/
#define TIMER2_PRESCALER_1024				7	/*TIMER2 Frequency = F_CPU / 1024 (CLK/1024)*/

/*TIMER2 Waveform Generation Mode (Timer mode)*/
#define TIMER2_NORMAL_MODE					0	/*Normal mode*/
#define TIMER2_PWM_MODE						1	/*PWM, Phase Correct mode*/
#define TIMER2_CTC_MODE						2	/*CTC mode*/
#define TIMER2_FAST_PWM_MODE				3	/*Fast PWM mode*/

/*Compare Match Output Mode, non-PWM Mode*/
#define TIMER2_COM_DISCONNECT_OC2			0	/*Normal port operation, OC2 disconnected*/
#define TIMER2_COM_TOGGLE_OC2				1	/*Toggle OC2 on compare match*/
#define TIMER2_COM_CLEAR_OC2				2	/*Clear OC2 on compare match*/
#define TIMER2_COM_SET_OC2					3	/*Set OC2 on compare match*/

/*Compare Match Output Mode, Phase Correct PWM Mode*/
#define TIMER2_COM_DISCONNECT_OC2			0	/*Normal port operation, OC2 disconnected*/
#define TIMER2_COM_NON_INVERTING_OC2		2	/*Clear OC2 on compare match when up-counting. Set OC2 on compare match when down-Counting*/
#define TIMER2_COM_INVERTING_OC2			3	/*Set OC2 on compare match when up-counting. Clear OC2 on compare match when down-Counting*/

/*Compare Match Output Mode, Fast PWM Mode*/
#define TIMER2_COM_DISCONNECT_OC2			0	/*Normal port operation, OC2 disconnected*/
#define TIMER2_COM_NON_INVERTING_OC2		2	/*Clear OC2 on compare match, set OC2 at TOP (most popular)*/
#define TIMER2_COM_INVERTING_OC2			3	/*Set OC2 on compare match, clear OC2 at TOP*/

/*the TIMER2 Overflow Interrupt Status*/
#define TIMER2_OVF_INT_DISABLE				0	/*TIMER2 Overflow Interrupt Disable*/
#define TIMER2_OVF_INT_ENABLE				1	/*TIMER2 Overflow Interrupt Enable*/

/*the TIMER2 Compare Match Interrupt Status*/
#define TIMER2_COMP_INT_DISABLE				0	/*TIMER2 Compare Match Interrupt Disable*/
#define TIMER2_COMP_INT_ENABLE				1	/*TIMER2 Compare Match Interrupt Enable*/

/*the Count mode (for TIMER2_GetTime_ms function)*/
#define TIMER2_COUNT_DISABLE				0	/*do not use TIMER2_Counter in ISR (TIMER2_GetTime_ms function will not work and TIMER2_Counter variable will be unused)*/
#define TIMER2_COUNT_ENABLE					1	/*use TIMER2_Counter in ISR (TIMER2_GetTime_ms function will work and TIMER2_Counter variable will be used)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define TIMER2_PRESCALER_clr_msk 		0xF8	/*TIMER2 PRESCALER Clear mask (0B11111000)*/
/*_______________________________________________________________________________________________*/


#endif /* TIMER2_DEF_H_ */
