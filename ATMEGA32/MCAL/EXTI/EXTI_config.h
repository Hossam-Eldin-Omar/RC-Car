/*File Guard*/
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#include "EXTI_def.h"


/*-----------------------------------   External Interrupt 0   ----------------------------------*/
/*Set Interrupt Status
 * choose between
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define INTERRUPT_0_STATUS			EXTI_ENABLE

/*Set Interrupt Sense Control
 * choose between
 * 1. EXTI_THE_LOW_LEVEL
 * 2. EXTI_ANY_LOGIC_CHANGE
 * 3. EXTI_THE_FALLING_EDGE
 * 4. EXTI_THE_RISING_EDGE
 */
#define INTERRUPT_0_SENSE_CONTROL		EXTI_ANY_LOGIC_CHANGE

/*Set the External Interrupt PIN mode
 * choose between
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define INTERRUPT_0_PIN_MODE			EXTI_INPUT_PULLUP
/*_______________________________________________________________________________________________*/



/*-----------------------------------   External Interrupt 1   ----------------------------------*/
/*Set Interrupt Status
 * choose between
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define INTERRUPT_1_STATUS			EXTI_DISABLE

/*Set Interrupt Sense Control
 * choose between
 * 1. EXTI_THE_LOW_LEVEL
 * 2. EXTI_ANY_LOGIC_CHANGE
 * 3. EXTI_THE_FALLING_EDGE
 * 4. EXTI_THE_RISING_EDGE
 */
#define INTERRUPT_1_SENSE_CONTROL		EXTI_ANY_LOGIC_CHANGE

/*Set the External Interrupt PIN mode
 * choose between
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define INTERRUPT_1_PIN_MODE			EXTI_INPUT
/*_______________________________________________________________________________________________*/



/*-----------------------------------   External Interrupt 2   ----------------------------------*/
/*Set Interrupt Status
 * choose between
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define INTERRUPT_2_STATUS			EXTI_DISABLE

/*Set Interrupt Sense Control
 * choose between
 * 1. EXTI_THE_FALLING_EDGE
 * 2. EXTI_THE_RISING_EDGE
 */
#define INTERRUPT_2_SENSE_CONTROL		EXTI_THE_RISING_EDGE

/*Set the External Interrupt PIN mode
 * choose between
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define INTERRUPT_2_PIN_MODE			EXTI_INPUT_PULLUP
/*_______________________________________________________________________________________________*/


#endif /* EXTI_CONFIG_H_ */
