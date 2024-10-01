/*File Guard*/
#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

#include "TIMER1_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif

/*value that set in TCNT1 Register in Initialization function in normal mode*/
#define TIMER1_TCNT1_PRELOAD	0

/*value that set in OCR1A Register in Initialization function*/
#define TIMER1_OCR1A_PRELOAD	20000

/*value that set in OCR1B Register in Initialization function*/
#define TIMER1_OCR1B_PRELOAD	1500

/*value that set in ICR1 Register in Initialization function*/
#define TIMER1_ICR1_PRELOAD	200


/*Set TIMER0 Clock Source
 * choose between
 * 1. TIMER1_NO_CLOCK_SOURCE
 * 2. TIMER1_NO_PRESCALER
 * 3. TIMER1_PRESCALER_8
 * 4. TIMER1_PRESCALER_64
 * 5. TIMER1_PRESCALER_256
 * 6. TIMER1_PRESCALER_1024
 * 7. TIMER1_EXT_CLOCK_FALLING
 * 8. TIMER1_EXT_CLOCK_RISING
 */
#define TIMER1_CLOCK_SOURCE_msk		TIMER1_PRESCALER_8


/*Set TIMER1 Waveform Generation Mode
 * choose between
 * 1.  TIMER1_NORMAL_MODE
 * 2.  TIMER1_PWM_8BIT_MODE
 * 3.  TIMER1_PWM_9BIT_MODE
 * 4.  TIMER1_PWM_10BIT_MODE
 * 5.  TIMER1_CTC_OCR1A_MODE
 * 6.  TIMER1_FAST_PWM_8BIT_MODE
 * 7.  TIMER1_FAST_PWM_9BIT_MODE
 * 8.  TIMER1_FAST_PWM_10BIT_MODE
 * 9.  TIMER1_PFC_PWM_ICR1_MODE
 * 10. TIMER1_PFC_PWM_OCR1A_MODE
 * 11. TIMER1_PWM_ICR1_MODE
 * 12. TIMER1_PWM_OCR1A_MODE
 * 13. TIMER1_CTC_ICR1_MODE
 * 14. TIMER1_FAST_PWM_ICR1_MODE
 * 15. TIMER1_FAST_PWM_OCR1A_MODE
 */
#define TIMER1_WAVEFORM_GENERATION_MODE		TIMER1_FAST_PWM_OCR1A_MODE

// '\'  means that the macro will be completed on another line
#if 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE	 || \
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE || \
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE

	/*Set Compare Output Mode (OC1A Pin)
	 * choose between
	 * 1. TIMER1_COM_DISCONNECT_0C1A
	 * 2. TIMER1_COM_TOGGLE_0C1A			//HINT: DIO will not be able to control this pin
	 * 3. TIMER1_COM_CLEAR_0C1A				//HINT: DIO will not be able to control this pin
	 * 4. TIMER1_COM_SET0_0C1A				//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER1_0C1A_MODE	TIMER1_COM_DISCONNECT_0C1A	//<--the most popular is "TIMER1_COM_DISCONNECT_0C1A"


	/*Set Compare Output Mode (OC1B Pin)
	 * choose between
	 * 1. TIMER1_COM_DISCONNECT_0C1B
	 * 2. TIMER1_COM_TOGGLE_0C1B			//HINT: DIO will not be able to control this pin
	 * 3. TIMER1_COM_CLEAR_0C1B				//HINT: DIO will not be able to control this pin
	 * 4. TIMER1_COM_SET0_0C1B				//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER1_0C1B_MODE	TIMER1_COM_DISCONNECT_0C1B	//<--the most popular is "TIMER1_COM_DISCONNECT_0C1B"


#elif TIMER1_WAVEFORM_GENERATION_MODE != 13 && TIMER1_WAVEFORM_GENERATION_MODE <16

	/*Set Compare Output Mode (OC1A Pin)
	 * choose between
	 * 1. TIMER1_COM_DISCONNECT_0C1A
	 * 2. TIMER1_COM_NON_INVERTING_0C1A			//HINT: DIO will not be able to control this pin
	 * 3. TIMER1_COM_INVERTING_0C1A				//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER1_0C1A_MODE	TIMER1_COM_DISCONNECT_0C1A	//<--the most popular is "TIMER1_COM_NON_INVERTING_0C1A"


	/*Set Compare Output Mode (OC1B Pin)
	 * choose between
	 * 1. TIMER1_COM_DISCONNECT_0C1B
	 * 2. TIMER1_COM_NON_INVERTING_0C1B			//HINT: DIO will not be able to control this pin
	 * 3. TIMER1_COM_INVERTING_0C1B				//HINT: DIO will not be able to control this pin
	 */
	#define  TIMER1_0C1B_MODE	TIMER1_COM_NON_INVERTING_0C1B	//<--the most popular is "TIMER1_COM_NON_INVERTING_0C1B"

#endif


/*Set Timer1 Overflow Interrupt Status
 * choose between
 * 1. TIMER1_OVF_INT_DISABLE
 * 2. TIMER1_OVF_INT_ENABLE
 */
#define  TIMER1_OVF_INT_STATUS	TIMER1_OVF_INT_ENABLE


/*Set Timer1 Compare Match A Interrupt Status
 * choose between
 * 1. TIMER1_COMPA_INT_DISABLE
 * 2. TIMER1_COMPA_INT_ENABLE
 */
#define  TIMER1_COMPA_INT_STATUS	TIMER1_COMPA_INT_DISABLE


/*Set Timer1 Compare Match B Interrupt Status
 * choose between
 * 1. TIMER1_COMPB_INT_DISABLE
 * 2. TIMER1_COMPB_INT_ENABLE
 */
#define  TIMER1_COMPB_INT_STATUS	TIMER1_COMPB_INT_DISABLE


/*Set Timer1 Overflow Interrupt Status
 * choose between
 * 1. TIMER1_CAPT_INT_DISABLE
 * 2. TIMER1_CAPT_INT_ENABLE
 */
#define  TIMER1_CAPT_INT_STATUS	TIMER1_CAPT_INT_DISABLE


/*Set the Input Capture Noise Canceler Status
 * choose between
 * 1. ICU_NOISE_CANCELER_DISABLE
 * 2. ICU_NOISE_CANCELER_ENABLE
 */
#define  ICU_NOISE_CANCELER_STATUS		ICU_NOISE_CANCELER_DISABLE


/*Set the Input Capture Signal Start Edge Status
 * choose between
 * 1. ICU_FALLING_EDGE
 * 2. ICU_RISING_EDGE
 */
#define  ICU_START_EDGE_STATUS		ICU_RISING_EDGE


/*Set the Count mode (for TIMER1_GetTime_ms function)
 * choose between
 * 1. TIMER1_COUNT_DISABLE
 * 2. TIMER1_COUNT_ENABLE
 */
#define TIMER1_COUNT_MODE	TIMER1_COUNT_ENABLE


/* FREQ_DIVIDER_T1 = prescaler * 65536(timer cup)*1000 */
#if   TIMER1_CLOCK_SOURCE_msk == TIMER1_NO_PRESCALER
	#define FREQ_DIVIDER_T1			0x3E80000UL		/* 1*65536*1000   = 65536000 */
	#define presc_T1				1
#elif TIMER1_CLOCK_SOURCE_msk == TIMER1_PRESCALER_8
	#define FREQ_DIVIDER_T1			0x1F400000UL		/* 8*65536*1000   = 524288000 */
	#define presc_T1				8
#elif TIMER1_CLOCK_SOURCE_msk == TIMER1_PRESCALER_64
	#define FREQ_DIVIDER_T1			0xFA000000ULL		//* 64*65536*1000   = 4194304000 */
	#define presc_T1				64
#elif TIMER1_CLOCK_SOURCE_msk == TIMER1_PRESCALER_256
	#define FREQ_DIVIDER_T1			0x3E8000000UL		/* 256*65536*1000  = 16777216000 */
	#define presc_T1				256
#elif TIMER1_CLOCK_SOURCE_msk == TIMER1_PRESCALER_1024
	#define FREQ_DIVIDER_T1			0xFA0000000UL		/* 1024*65536*1000 = 67108864000 */
	#define presc_T1				1024
#endif



#endif /* TIMER1_CONFIG_H_ */
