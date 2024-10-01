/*File Guard*/
#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

#include "TIMER2_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif

/*value that set in TCNT2 Register in Initialization function in normal mode*/
#define TIMER2_TCNT2_PRELOAD	0

/*value that set in OCR2 Register in Initialization function in CTC mode*/
#define TIMER2_OCR2_PRELOAD		0


/*Set TIMER2 Clock Source
 * choose between
 * 1. TIMER2_NO_CLOCK_SOURCE
 * 2. TIMER2_NO_PRESCALER
 * 3. TIMER2_PRESCALER_8
 * 4. TIMER2_PRESCALER_32
 * 5. TIMER2_PRESCALER_64
 * 6. TIMER2_PRESCALER_128
 * 7. TIMER2_PRESCALER_256
 * 8. TIMER2_PRESCALER_1024
 */
#define TIMER2_CLOCK_SOURCE_msk		TIMER2_PRESCALER_256


/*Set TIMER2 Waveform Generation Mode
 * choose between
 * 1. TIMER2_NORMAL_MODE
 * 2. TIMER2_PWM_MODE
 * 3. TIMER2_CTC_MODE
 * 4. TIMER2_FAST_PWM_MODE
 */
#define TIMER2_WAVEFORM_GENERATION_MODE		TIMER2_FAST_PWM_MODE



#if   TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_TOGGLE_OC2			//HINT: DIO will not be able to control this pin
	 * 3. TIMER2_COM_CLEAR_OC2			//HINT: DIO will not be able to control this pin
	 * 4. TIMER2_COM_SET_OC2			//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE	TIMER2_COM_DISCONNECT_OC2	//<--the most popular is "TIMER2_COM_DISCONNECT_OC2"


	/*Set TIMER2 Overflow Interrupt Status
	 * choose between
	 * 1. TIMER2_OVF_INT_DISABLE
	 * 2. TIMER2_OVF_INT_ENABLE
	 */
	#define  TIMER2_OVF_INT_STATUS	TIMER2_OVF_INT_ENABLE	//<--the most popular is "TIMER2_OVF_INT_ENABLE"


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between
	 * 1. TIMER2_COMP_INT_DISABLE
	 * 2. TIMER2_COMP_INT_ENABLE
	 */
	#define  TIMER2_COMP_INT_STATUS	TIMER2_COMP_INT_DISABLE	//<--the most popular is "TIMER2_COMP_INT_DISABLE"


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_NON_INVERTING_OC2	//HINT: DIO will not be able to control this pin
	 * 3. TIMER2_COM_INVERTING_OC2		//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE	TIMER2_COM_NON_INVERTING_OC2	//<--the most popular is "TIMER2_COM_NON_INVERTING_OC2"


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_TOGGLE_OC2			//HINT: DIO will not be able to control this pin
	 * 3. TIMER2_COM_CLEAR_OC2			//HINT: DIO will not be able to control this pin
	 * 4. TIMER2_COM_SET_OC2			//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE	TIMER2_COM_DISCONNECT_OC2	//<--the most popular is "TIMER2_COM_DISCONNECT_OC2"


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between
	 * 1. TIMER2_COMP_INT_DISABLE
	 * 2. TIMER2_COMP_INT_ENABLE
	 */
	#define  TIMER2_COMP_INT_STATUS	TIMER2_COMP_INT_ENABLE	//<--the most popular is "TIMER2_COMP_INT_ENABLE"


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE

	/*Set Compare Output Mode
	 * choose between
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_NON_INVERTING_OC2	//HINT: DIO will not be able to control this pin
	 * 3. TIMER2_COM_INVERTING_OC2		//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE	TIMER2_COM_NON_INVERTING_OC2	//<--the most popular is "TIMER2_COM_NON_INVERTING_OC2"


#endif


/*Set the Count mode (for TIMER2_GetTime_ms function)
 * choose between
 * 1. TIMER2_COUNT_DISABLE
 * 2. TIMER2_COUNT_ENABLE
 */
#define TIMER2_COUNT_MODE	TIMER2_COUNT_DISABLE



/* FREQ_DIVIDER_T2 = prescaler * 256(timer cup)*1000 */
#if   TIMER2_CLOCK_SOURCE_msk == TIMER2_NO_PRESCALER
	#define FREQ_DIVIDER_T2			0x3E800UL		/* 1*256*1000   = 256000 */
	#define presc_T2				1
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_8
	#define FREQ_DIVIDER_T2			0x1F4000UL		/* 8*256*1000   = 2048000 */
	#define presc_T2				8
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_64
	#define FREQ_DIVIDER_T2			0xFA0000UL		//* 64*256*1000   = 16384000 */
	#define presc_T2				64
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_256
	#define FREQ_DIVIDER_T2			0x3E80000UL		/* 256*256*1000  = 65536000 */
	#define presc_T2				256
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_1024
	#define FREQ_DIVIDER_T2			0xFA00000UL		/* 1024*256*1000 = 26214400 */
	#define presc_T2				1024
#endif


#endif /* TIMER2_CONFIG_H_ */
