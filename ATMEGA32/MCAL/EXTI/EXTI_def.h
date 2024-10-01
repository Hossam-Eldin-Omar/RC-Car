/*File Guard*/
#ifndef EXTI_DEF_H_
#define EXTI_DEF_H_

#include "../DIO/DIO.h"


/*---------------------------------------    Registers    ---------------------------------------*/

#define SREG			*((volatile uint8 *)0x5F)	/*status register*/
#define MCUCR			*((volatile uint8 *)0x55)	/*MCU Control Register*/
#define MCUCSR			*((volatile uint8 *)0x54)	/*MCU Control and Status Register*/
#define GICR			*((volatile uint8 *)0x5B)	/*General Interrupt Control Register*/
#define GIFR			*((volatile uint8 *)0x5A)	/*General Interrupt Flag Register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*SREG Register*/
#define	I				7	/*Global Interrupt Enable*/

/*MCUCR Register*/
#define ISC00			0	/*Interrupt Sense Control 0 Bit 0*/
#define ISC01			1	/*Interrupt Sense Control 0 Bit 1*/
#define ISC10			2	/*Interrupt Sense Control 1 Bit 0*/
#define ISC11			3	/*Interrupt Sense Control 1 Bit 1*/

/*MCUCSR Register*/
#define ISC2			6	/*Interrupt Sense Control 2*/

/*GICR Register*/
#define INT0			6	/*External Interrupt Request 0 Enable*/
#define	INT1			7	/*External Interrupt Request 1 Enable*/
#define INT2			5	/*External Interrupt Request 2 Enable*/

/*GIFR Register*/
#define	INTF0			6	/*External Interrupt Flag 0*/
#define	INTF1			7	/*External Interrupt Flag 1*/
#define	INTF2			5	/*External Interrupt Flag 2*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define NULL				((void*)0)	/*define NULL value*/

/*External Interrupt labels*/
#define EXTI_INT0_LABEL		0			/*External Interrupt 0 label for functions parameters*/
#define EXTI_INT1_LABEL		1			/*External Interrupt 1 label for functions parameters */
#define EXTI_INT2_LABEL		2			/*External Interrupt 2 label for functions parameters */

/*External Interrupt PORTs*/
#define INT0_PORT			PORTD_ID	/*External Interrupt 0 port from pinout*/
#define INT1_PORT			PORTD_ID	/*External Interrupt 1 port from pinout*/
#define INT2_PORT			PORTB_ID	/*External Interrupt 2 port from pinout*/

/*External Interrupt Pins*/
#define INT0_PIN			2			/*External Interrupt 0 pin from pinout*/
#define INT1_PIN			3			/*External Interrupt 1 pin from pinout*/
#define INT2_PIN			2			/*External Interrupt 2 pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*the External Interrupt Status*/
#define EXTI_DISABLE			0		/*Disable the External Interrupt*/
#define EXTI_ENABLE				1		/*Enable  the External Interrupt*/

/*Interrupt Sense Control*/
#define EXTI_THE_LOW_LEVEL		0		/*The Low Level of		INTx generates an interrupt request*/
#define EXTI_ANY_LOGIC_CHANGE	1		/*Any Logical Change on INTx generates an interrupt request*/
#define EXTI_THE_FALLING_EDGE	2		/*The Falling Edge of 	INTx generates an interrupt request*/
#define EXTI_THE_RISING_EDGE	3		/*The Rising Edge of 	INTx generates an interrupt request*/

/*the External Interrupt PIN Mode*/
#define EXTI_INPUT				0		/*the External Interrupt PIN in normal  input mode(value same as in DIO_Types.h file)*/
#define EXTI_INPUT_PULLUP		2		/*the External Interrupt PIN in pull up input mode(value same as in DIO_Types.h file)*/
/*_______________________________________________________________________________________________*/


#endif /* EXTI_DEF_H_ */
