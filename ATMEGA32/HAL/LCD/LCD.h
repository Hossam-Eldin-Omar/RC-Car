#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/DIO/DIO.h"
#include<util/delay.h>
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*Set number of data bits mode
 * choose between
 * 1. 4
 * 2. 8
 */
#define LCD_BIT_MODE					4
/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN0_ID

#if(LCD_BIT_MODE==4)
#define LCD_DATA_PORT_ID               PORTC_ID
#define LCD_DATA_PIN0_ID			   PIN4_ID
#define LCD_DATA_PIN1_ID			   PIN5_ID
#define LCD_DATA_PIN2_ID			   PIN6_ID
#define LCD_DATA_PIN3_ID			   PIN7_ID

#elif(LCD_BIT_MODE==8)
#define LCD_DATA_PORT_ID               PORTC_ID
#endif

/* LCD Commands */
#define LCD_CLEAR_SCREEN               		 0x01
#define LCD_GO_TO_HOME                 		 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  		 0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   		 0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                 		 0x0C
#define LCD_CURSOR_ON                  		 0x0E
#define LCD_SET_CURSOR_LOCATION        		 0x80
#define LCD_SAVE_IN_CGRAM					 0X40

/*******************************************************************************
 *                                FUNCTIONS                                  *
 *******************************************************************************/

void LCD_init(void);

void LCD_displayCharacter(uint8 data);

void LCD_displayString(const char *str);

void LCD_setCursor(uint8 row,uint8 column);

void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *str);

void LCD_clearScreen(void);

void LCD_integerToString(int data);

void LCD_Save_Custom_char(char * custum_char, uint8 location);

void LCD_sendCommand(uint8 command);

void LCD_CursorOFF();

void LCD_CursorON();
#endif
