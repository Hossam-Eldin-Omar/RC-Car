/*File Guard*/
#ifndef INPUT_H_
#define INPUT_H_

#include "../../MCAL/DIO/DIO.h"

/*Initialization the Pin send Direction as Floating Input*/
void INPUT_Init( uint8 port_ID , uint8 pin_ID );

/*Initialization the Pin send Direction as Pull Up Input*/
void INPUT_PULLUP_Init( uint8 port_ID , uint8 pin_ID );

/*Read the send Pin as One if it High*/
uint8 INPUT_Read( uint8 port_ID , uint8 pin_ID );

/*Read the send Pin as One if it Low*/
uint8 INPUT_PULLUP_Read( uint8 port_ID , uint8 pin_ID );

#endif /* INPUT_H_ */
