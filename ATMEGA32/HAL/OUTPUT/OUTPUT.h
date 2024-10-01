/*File Guard*/
#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "../../MCAL/DIO/DIO.h"

/*Initialization the Pin send Direction as Output*/
void OUTPUT_Init_PIN( uint8 port_ID , uint8 pin_ID );

/*set the send Pin as High Value*/
void OUTPUT_Hith_PIN( uint8 port_ID , uint8 pin_ID );

/*set the send Pin as Low Value*/
void OUTPUT_Low_PIN( uint8 port_ID , uint8 pin_ID );

/*Toggle the send Pin*/
void OUTPUT_Toggle_PIN( uint8 port_ID , uint8 pin_ID );

#endif /* OUTPUT_H_ */
