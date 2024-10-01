/*File Guard*/
#ifndef UART_DEF_H_
#define UART_DEF_H_
#include "../../LIB/std_types.h"

/*---------------------------------------    Registers    ---------------------------------------*/

#define UCSRA		*((volatile uint8 *)0x2B)	/*USART Control and Status Register A*/
#define UCSRB		*((volatile uint8 *)0x2A)	/*USART Control and Status Register B*/
#define UCSRC		*((volatile uint8 *)0x40)	/*USART Control and Status Register C*/
#define UBRRL		*((volatile uint8 *)0x29)	/*USART Baud Rate LOW Register*/
#define UBRRH		*((volatile uint8 *)0x40)	/*USART Baud Rate HIGH Register*/
#define SREG		*((volatile uint8 *)0x5F)	/*status register*/
#define UDR			*((volatile uint8 *)0x2C)	/*USART I/O Data Register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*UCSRA Register*/
#define MPCM			0	/*Multi-processor Communication Mode*/
#define U2X				1	/*Double the USART Transmission Speed*/
#define PE				2	/*Parity Error*/
#define DOR				3	/*Data OverRun*/
#define FE				4	/*Frame Error*/
#define UDRE			5	/*USART Data Register Empty*/
#define TXC				6	/*USART Transmit Complete*/
#define RXC				7	/*USART Receive Complete*/
/*UCSRB Register*/
#define TXB8			0	/*Transmit Data Bit 8*/
#define RXB8			1	/*Receive Data Bit 8*/
#define UCSZ2			2	/*Character Size*/
#define TXEN			3	/*Transmitter Enable*/
#define RXEN			4	/*Receiver Enable*/
#define UDRIE			5	/*USART Data Register Empty Interrupt Enable*/
#define TXCIE			6	/*TX Complete Interrupt Enable*/
#define RXCIE			7	/*RX Complete Interrupt Enable*/
/*UCSRC Register*/
#define UCPOL			0	/*Clock Polarity*/
#define UCSZ0			1	/*Character Size Bit 0*/
#define UCSZ1			2	/*Character Size Bit 1*/
#define USBS			3	/*Stop Bit Select*/
#define UPM0			4	/*Parity Mode Bit 0*/
#define UPM1			5	/*Parity Mode Bit 1*/
#define UMSEL			6	/*USART Mode Select*/
#define URSEL			7	/*Register Select*/
/*SREG Register*/
#define	I				7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define NULL				((void*)0)	/*define NULL value*/

#define DISABLE					0		/*define DISABLE value*/
#define ENABLE					1		/*define ENABLE value*/

#define UART_COUNTOUT			10000	/*Set it by "INFINITE" to end its function OR Set it by any number (e.g. 100) to wait until counter equal it to end waiting*/

#define UART_MAX_INT_LENGTH		10		/*max number of digits in the integer send to function*/

/*UART Interrupt labels*/
#define UART_INT_TX_LABEL		0		/*TX  interrupt label for functions parameters*/
#define UART_INT_RX_LABEL		1		/*RX  interrupt label for functions parameters*/
#define UART_INT_UDR_LABEL		2		/*UDR interrupt label for functions parameters*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*Baud Rate Speed*/
#define Baud_Rate_2400				2400UL		/*BaudRate = 2400   bps*/
#define Baud_Rate_4800				4800UL		/*BaudRate = 4800   bps*/
#define Baud_Rate_9600				9600UL		/*BaudRate = 9600   bps*/
#define Baud_Rate_14400				14400UL		/*BaudRate = 14400  bps*/
#define Baud_Rate_19200				19200UL		/*BaudRate = 19200  bps*/
#define Baud_Rate_28800				28800UL		/*BaudRate = 28800  bps*/
#define Baud_Rate_38400				38400UL		/*BaudRate = 38400  bps*/
#define Baud_Rate_57600				57600UL		/*BaudRate = 57600  bps*/
#define Baud_Rate_76800				76800UL		/*BaudRate = 76800  bps*/
#define Baud_Rate_115200			115200UL	/*BaudRate = 115200 bps*/
#define Baud_Rate_230400			230400UL	/*BaudRate = 230400 bps*/

/*UART Multi-Processor Communication Mode*/
#define UART_MPCM_DISABLE			0	/*Multi-Processor Communication mode Disable*/
#define UART_MPCM_ENABLE			1	/*Multi-Processor Communication mode Enable*/

/*UART Double the UART Transmission Speed*/
#define UART_U2X_DISABLE			0	/*U2X mode Disable*/
#define UART_U2X_ENABLE				1	/*U2X mode Enable*/

/*UART Parity Mode*/
#define UART_Parity_Disabled		0	/*Parity mode Disabled*/
#define UART_Parity_Even			2	/*Parity mode Enabled, Even Parity*/
#define UART_Parity_Odd				3	/*Parity mode Enabled, Odd Parity*/

/*UART Stop Bit Mode*/
#define UART_1_Stop_Bit				0	/*1-bit Stop in the frame*/
#define UART_2_Stop_Bit				1	/*2-bit Stop in the frame*/

/*UART Character Size*/
#define UART_DATA_5_BIT_SIZE		0	/*5-bit Data in the frame*/
#define UART_DATA_6_BIT_SIZE		1	/*6-bit Data in the frame*/
#define UART_DATA_7_BIT_SIZE		2	/*7-bit Data in the frame*/
#define UART_DATA_8_BIT_SIZE		3	/*8-bit Data in the frame*/
#define UART_DATA_9_BIT_SIZE		7	/*9-bit Data in the frame*/
/*_______________________________________________________________________________________________*/


#endif /* UART_DEF_H_ */
