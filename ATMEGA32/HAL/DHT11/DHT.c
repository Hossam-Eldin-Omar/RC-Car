
/*
 * DTH.c
 *
 * Created: 7/5/2024 6:27:20 PM
 *  Author: Ahmed shaban
 */
//#define F_CPU 8000000UL
#include <util/delay.h>
#include "DHT.h"


uint8_t I_RH, D_RH, I_Temp, D_Temp, CheckSum,value1,value0;
void Request() {
	DIO_setup_Pin_Direction(DHT_port, DHT_pin, 1);
   DIO_write_Pin(DHT_port, DHT_pin, 0); /*  low */
	_delay_ms(18);
	DIO_write_Pin(DHT_port, DHT_pin,1);   /* set pin high */
	_delay_us(20);
	DIO_setup_Pin_Direction(DHT_port, DHT_pin, 0);  /*  input */
}


void Response() {
	
	while (DIO_read_Pin(DHT_port, DHT_pin) != 0);  // Wait for low signal
	
	while (DIO_read_Pin(DHT_port, DHT_pin) == 0);  // Wait for high signal

	while (DIO_read_Pin(DHT_port, DHT_pin) != 0);  // Wait for low signal

}


uint8_t Receive_data() {
	Request();
	Response();

uint8_t data[5] = {0}; //hold the 8 bit for every decimal and intger Humidity ,temp and 8 bit for sum
for (int j = 0; j < 5; j++) {
	for (int q = 0; q < 8; q++) {
		while (DIO_read_Pin(DHT_port, DHT_pin) == 0);  /* wait for high */
		_delay_us(30);
		
		if ((DIO_read_Pin(DHT_port, DHT_pin) == 1))  // if is still high 
		data[j] = (data[j] << 1) | 0x01; /* set bit as 1 */
		else
		data[j] = (data[j] << 1);  /* set bit as 0 */
		while (DIO_read_Pin(DHT_port, DHT_pin) != 0);   /* wait to go low */
	}
}

I_RH = data[0];
D_RH = data[1];
I_Temp = data[2];
D_Temp = data[3];
CheckSum = data[4];

uint8_t sum = I_RH + D_RH + I_Temp + D_Temp;

if (sum != CheckSum) {
	return 0; // Error
}
return 1; // Success
}
