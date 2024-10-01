/*File Guard*/
#ifndef PORT_PORT_H_
#define PORT_PORT_H_

#include "../../MCAL/DIO/DIO.h"

/*Initialization the Port send Direction*/
void PORT_Init( uint8 port_ID , DIO_Port_DirectionType direction );

/*Set the send Port Value*/
void PORT_Set_Value( uint8 port_ID , uint8 PORT_Value );

/*Get the send Port Value*/
uint8 PORT_Get_Value( uint8 port_ID );

/*Toggle the send Port*/
void PORT_Toggle( uint8 port_ID );

/*Initialization All Ports Direction*/
void PORT_Init_All( DIO_Port_DirectionType portA_direction , DIO_Port_DirectionType portB_direction , DIO_Port_DirectionType portC_direction , DIO_Port_DirectionType portD_direction );

/*Set All Ports Value*/
void PORT_Set_Value_All( uint8 portA_Value , uint8 portB_Value , uint8 portC_Value , uint8 portD_Value );

#endif /* PORT_PORT_H_ */
