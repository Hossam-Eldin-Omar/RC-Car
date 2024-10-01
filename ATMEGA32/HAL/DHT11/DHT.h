/*
 * DTH.h
 *
 * Created: 7/5/2024 6:27:32 PM
 *  Author: Ahmed shaban
 */ 




#ifndef DHT_H_
#define DHT_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/DIO/DIO.h"  // Adjust this if your header file is named differently
#include <stdint.h>

#define DHT_port PORTD_ID
#define DHT_pin   6

void Request();
void Response();
uint8_t Receive_data();

#endif /* DHT_H_ */

