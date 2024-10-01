/*File Guard*/
#ifndef TIMER0_DEF_H_
#define TIMER0_DEF_H_

#include "../../LIB/std_types.h"


/*---------------------------------------    Registers    ---------------------------------------*/

#define TCNT0			*((volatile uint8 *)0x52)	/*Timer/Counter Register*/
#define OCR0			*((volatile uint8 *)0x5C)	/*Output Compare Register*/
#define TCCR0			*((volatile uint8 *)0x53)	/*Timer/Counter Control Register*/
#define TIMSK			*((volatile uint8 *)0x59)	/*Timer/Counter Interrupt Mask Register*/
#define TIFR			*((volatile uint8 *)0x58)	/*Timer/Counter Interrupt Flag Register*/
#define SREG			*((volatile uint8 *)0x5F)	/*status register*/
#define DDRB 			*((volatile uint8 *)0x37)	/*Port B Data Direction Register (OC0 pin Register)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*TCCR0 Register*/
#define CS00		0	/*Clock Select Bit 0*/ /*unused definition (bit in Register used)*/
#define CS01		1	/*Clock Select Bit 1*/ /*unused definition (bit in Register used)*/
#define CS02		2	/*Clock Select Bit 2*/ /*unused definition (bit in Register used)*/
#define WGM01		3	/*Waveform Generation Mode Bit 1 (CTC0)*/
#define COM00		4	/*Compare Match Output Mode Bit 0*/
#define COM01		5	/*Compare Match Output Mode Bit 1*/
#define WGM00		6	/*Waveform Generation Mode Bit 0 (PWM0)*/
#define FOC0		7	/*Force Output Compare*/ /*unused*/

/*TIMSK Register*/
#define TOIE0		0	/*Timer/Counter0 Overflow Interrupt Enable*/
#define OCIE0		1	/*Timer/Counter0 Output Compare Match Interrupt Enable*/

/*TIFR Register*/
#define TOV0		0	/*Timer/Counter0 Overflow Flag*/
#define OCF0		1	/*Timer/Counter0 Output Compare Match Flag*/

/*SREG Register*/
#define	I			7	/*Global Interrupt Enable*/

/*DDRB Register*/
#define OC0_PIN		3	/*Compare Match Output 0 pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define NULL			((void*)0)	/*define NULL value*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*TIMER0 Clock Source*/
#define TIMER0_NO_CLOCK_SOURCE				0	/*No clock source (Timer/Counter stopped)*/
#define TIMER0_NO_PRESCALER					1	/*TIMER0 Frequency = F_CPU (No prescaling)*/
#define TIMER0_PRESCALER_8					2	/*TIMER0 Frequency = F_CPU / 8	  (CLK/8)*/
#define TIMER0_PRESCALER_64					3	/*TIMER0 Frequency = F_CPU / 64	  (CLK/64)*/
#define TIMER0_PRESCALER_256				4	/*TIMER0 Frequency = F_CPU / 256  (CLK/256)*/
#define TIMER0_PRESCALER_1024				5	/*TIMER0 Frequency = F_CPU / 1024 (CLK/1024)*/
#define TIMER0_EXT_CLOCK_FALLING			6	/*External clock source on T0 pin. Clock on falling edge*/
#define TIMER0_EXT_CLOCK_RISING				7	/*External clock source on T0 pin. Clock on rising  edge*/

/*TIMER0 Waveform Generation Mode (Timer mode)*/
#define TIMER0_NORMAL_MODE					0	/*Normal mode*/
#define TIMER0_PWM_MODE						1	/*PWM, Phase Correct mode*/
#define TIMER0_CTC_MODE						2	/*CTC mode*/
#define TIMER0_FAST_PWM_MODE				3	/*Fast PWM mode*/

/*Compare Match Output Mode, non-PWM Mode*/
#define TIMER0_COM_DISCONNECT_OC0			0	/*Normal port operation, OC0 disconnected*/
#define TIMER0_COM_TOGGLE_OC0				1	/*Toggle OC0 on compare match*/
#define TIMER0_COM_CLEAR_OC0				2	/*Clear OC0 on compare match*/
#define TIMER0_COM_SET_OC0					3	/*Set OC0 on compare match*/

/*Compare Match Output Mode, Phase Correct PWM Mode*/
#define TIMER0_COM_DISCONNECT_OC0			0	/*Normal port operation, OC0 disconnected*/
#define TIMER0_COM_NON_INVERTING_OC0		2	/*Clear OC0 on compare match when up-counting. Set OC0 on compare match when down-Counting*/
#define TIMER0_COM_INVERTING_OC0			3	/*Set OC0 on compare match when up-counting. Clear OC0 on compare match when down-Counting*/

/*Compare Match Output Mode, Fast PWM Mode*/
#define TIMER0_COM_DISCONNECT_OC0			0	/*Normal port operation, OC0 disconnected*/
#define TIMER0_COM_NON_INVERTING_OC0		2	/*Clear OC0 on compare match, set OC0 at TOP (most popular)*/
#define TIMER0_COM_INVERTING_OC0			3	/*Set OC0 on compare match, clear OC0 at TOP*/

/*the Timer0 Overflow Interrupt Status*/
#define TIMER0_OVF_INT_DISABLE				0	/*Timer0 Overflow Interrupt Disable*/
#define TIMER0_OVF_INT_ENABLE				1	/*Timer0 Overflow Interrupt Enable*/

/*the Timer0 Compare Match Interrupt Status*/
#define TIMER0_COMP_INT_DISABLE				0	/*Timer0 Compare Match Interrupt Disable*/
#define TIMER0_COMP_INT_ENABLE				1	/*Timer0 Compare Match Interrupt Enable*/

/*the Count mode (for TIMER0_GetTime_ms function)*/
#define TIMER0_COUNT_DISABLE				0	/*do not use TIMER0_Counter in ISR (TIMER0_GetTime_ms function will not work and TIMER0_Counter variable will be unused)*/
#define TIMER0_COUNT_ENABLE					1	/*use TIMER0_Counter in ISR (TIMER0_GetTime_ms function will work and TIMER0_Counter variable will be used)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define TIMER0_PRESCALER_clr_msk 		0xF8	/*TIMER0 PRESCALER Clear mask (0B11111000)*/
/*_______________________________________________________________________________________________*/


#endif /* TIMER0_DEF_H_ */
