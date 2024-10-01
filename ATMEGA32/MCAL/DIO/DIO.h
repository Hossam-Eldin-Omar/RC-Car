#include "DIO_Types.h"
#include"../../LIB/common_macros.h"
#include "DIO_REGS.h"
#ifndef DIO_H_
#define DIO_H_


void DIO_setup_Pin_Direction(uint8 port_ID, uint8 pin_ID, DIO_Pin_DirectionType direction);

void DIO_setup_Port_Direction(uint8 port_ID, DIO_Port_DirectionType direction);

void DIO_write_Pin(uint8 port_ID,uint8 pin_ID,Value value);

void DIO_write_Port(uint8 port_ID,uint8 value);

uint8 DIO_read_Pin(uint8 port_ID,uint8 pin_ID);

uint8 DIO_read_Port(uint8 port_ID);

void DIO_Toggle_Pin(uint8 port_ID,uint8 pin_ID);

void DIO_Toggle_Port(uint8 port_ID);

#endif
