/*File Guard*/
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include  "UART_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*Hint : check table in 68 page 163 in data sheet*/
/*Set Baud Rate
 * choose between
 * 1. Baud_Rate_2400
 * 2. Baud_Rate_4800
 * 3. Baud_Rate_9600
 * 4. Baud_Rate_14400
 * 5. Baud_Rate_19200
 * 6. Baud_Rate_28800
 * 7. Baud_Rate_38400
 * 8. Baud_Rate_57600
 * 9. Baud_Rate_76800
 * 10.Baud_Rate_115200
 * 11.Baud_Rate_230400
 */
#define UART_BAUD_RATE					Baud_Rate_9600


/*Set Parity Mode
 *  choose between
 * 1. UART_Parity_Disabled
 * 2. UART_Parity_Even
 * 3. UART_Parity_Odd
 */
#define UART_Parity_Mode		UART_Parity_Disabled


/*Set Stop Bit Mode
 *  choose between
 * 1. UART_1_Stop_Bit
 * 2. UART_2_Stop_Bit
 */
#define UART_Stop_Bit_Mode			UART_1_Stop_Bit


/*Set Character Size
 *  choose between
 * 1. UART_DATA_5_BIT_SIZE
 * 2. UART_DATA_6_BIT_SIZE
 * 3. UART_DATA_7_BIT_SIZE
 * 4. UART_DATA_8_BIT_SIZE
 * 5. UART_DATA_9_BIT_SIZE
 */
#define UART_Character_Size_Mode	UART_DATA_8_BIT_SIZE


/*Set Receiver Enable
 * choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define UART_RECEIVER_ENABLE		ENABLE


/*Set Transmitter Enable
 * choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define UART_TRANSMITTER_ENABLE		DISABLE


/*Set Multi-Processor Communication mode
 * choose between
 * 1. UART_MPCM_DISABLE
 * 2. UART_MPCM_ENABLE
 */
#define UART_MPCM_Mode 		UART_MPCM_DISABLE


/*Set Double the UART Transmission Speed
 *  choose between
 * 1. UART_U2X_DISABLE
 * 2. UART_U2X_ENABLE
 */
#define UART_U2X_Mode			UART_U2X_DISABLE


/*Set TX Complete Interrupt Enable
 * choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define UART_TX_COMPLETE_INTERRUPT		DISABLE


/*Set RX Complete Interrupt Enable
 * choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define UART_RX_COMPLETE_INTERRUPT		ENABLE


/*Set UDR Empty Interrupt Enable
 * choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define UART_UDR_EMPTY_INTERRUPT		DISABLE


#endif /* UART_CONFIG_H_ */
