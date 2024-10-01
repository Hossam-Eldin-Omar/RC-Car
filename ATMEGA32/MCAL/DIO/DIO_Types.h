#ifndef DIO_TYPES_H
#define DIO_TYPES_H

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

typedef enum{
	INPUT,
	OUTPUT,
	INPUT_PULLUP
}DIO_Pin_DirectionType;

typedef enum
{
	PORT_INPUT,
	PORT_OUTPUT=0xFF
}DIO_Port_DirectionType;

typedef enum{
	LOW,
	HIGH
}Value;

#endif
