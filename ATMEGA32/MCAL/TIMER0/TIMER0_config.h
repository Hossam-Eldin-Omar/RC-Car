/*File Guard*/
#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#include "TIMER0_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif

/*value that set in TCNT0 Register in Initialization function in normal mode*/
#define TIMER0_TCNT0_PRELOAD	0

/*value that set in OCR0 Register in Initialization function in CTC mode*/
#define TIMER0_OCR0_PRELOAD		127


/*Set TIMER0 Clock Source
 * choose between
 * 1. TIMER0_NO_CLOCK_SOURCE
 * 2. TIMER0_NO_PRESCALER
 * 3. TIMER0_PRESCALER_8
 * 4. TIMER0_PRESCALER_64
 * 5. TIMER0_PRESCALER_256
 * 6. TIMER0_PRESCALER_1024
 * 7. TIMER0_EXT_CLOCK_FALLING
 * 8. TIMER0_EXT_CLOCK_RISING
 */
#define TIMER0_CLOCK_SOURCE_msk		TIMER0_PRESCALER_256


/*Set TIMER0 Waveform Generation Mode
 * choose between
 * 1. TIMER0_NORMAL_MODE
 * 2. TIMER0_PWM_MODE
 * 3. TIMER0_CTC_MODE
 * 4. TIMER0_FAST_PWM_MODE
 */
#define TIMER0_WAVEFORM_GENERATION_MODE		TIMER0_NORMAL_MODE



#if   TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_TOGGLE_OC0			//HINT: DIO will not be able to control this pin
	 * 3. TIMER0_COM_CLEAR_OC0			//HINT: DIO will not be able to control this pin
	 * 4. TIMER0_COM_SET_OC0			//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE	TIMER0_COM_DISCONNECT_OC0	//<--the most popular is "TIMER0_COM_DISCONNECT_OC0"


	/*Set Timer0 Overflow Interrupt Status
	 * choose between
	 * 1. TIMER0_OVF_INT_DISABLE
	 * 2. TIMER0_OVF_INT_ENABLE
	 */
	#define  TIMER0_OVF_INT_STATUS	TIMER0_OVF_INT_ENABLE	//<--the most popular is "TIMER0_OVF_INT_ENABLE"


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between
	 * 1. TIMER0_COMP_INT_DISABLE
	 * 2. TIMER0_COMP_INT_ENABLE
	 */
	#define  TIMER0_COMP_INT_STATUS	TIMER0_COMP_INT_DISABLE	//<--the most popular is "TIMER0_COMP_INT_DISABLE"


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_NON_INVERTING_OC0	//HINT: DIO will not be able to control this pin
	 * 3. TIMER0_COM_INVERTING_OC0		//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE	TIMER0_COM_NON_INVERTING_OC0	//<--the most popular is "TIMER0_COM_NON_INVERTING_OC0"


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_TOGGLE_OC0			//HINT: DIO will not be able to control this pin
	 * 3. TIMER0_COM_CLEAR_OC0			//HINT: DIO will not be able to control this pin
	 * 4. TIMER0_COM_SET_OC0			//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE	TIMER0_COM_DISCONNECT_OC0	//<--the most popular is "TIMER0_COM_DISCONNECT_OC0"


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between
	 * 1. TIMER0_COMP_INT_DISABLE
	 * 2. TIMER0_COMP_INT_ENABLE
	 */
	#define  TIMER0_COMP_INT_STATUS	TIMER0_COMP_INT_ENABLE	//<--the most popular is "TIMER0_COMP_INT_ENABLE"


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_NON_INVERTING_OC0	//HINT: DIO will not be able to control this pin
	 * 3. TIMER0_COM_INVERTING_OC0		//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE	TIMER0_COM_NON_INVERTING_OC0	//<--the most popular is "TIMER0_COM_NON_INVERTING_OC0"


#endif


/*Set the Count mode (for TIMER0_GetTime_ms function)
 * choose between
 * 1. TIMER0_COUNT_DISABLE
 * 2. TIMER0_COUNT_ENABLE
 */
#define TIMER0_COUNT_MODE	TIMER0_COUNT_ENABLE



/* FREQ_DIVIDER_T0 = prescaler * 256(timer cup)*1000 */
#if   TIMER0_CLOCK_SOURCE_msk == TIMER0_NO_PRESCALER
	#define FREQ_DIVIDER_T0			0x3E800UL		/* 1*256*1000   = 256000 */
	#define presc_T0				1
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_8
	#define FREQ_DIVIDER_T0			0x1F4000UL		/* 8*256*1000   = 2048000 */
	#define presc_T0				8
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_64
	#define FREQ_DIVIDER_T0			0xFA0000UL		//* 64*256*1000   = 16384000 */
	#define presc_T0				64
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_256
	#define FREQ_DIVIDER_T0			0x3E80000UL		/* 256*256*1000  = 65536000 */
	#define presc_T0				256
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_1024
	#define FREQ_DIVIDER_T0			0xFA00000UL		/* 1024*256*1000 = 26214400 */
	#define presc_T0				1024
#endif


#endif /* TIMER0_CONFIG_H_ */
