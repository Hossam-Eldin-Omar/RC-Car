#include "DIO.h"



void DIO_setup_Pin_Direction(uint8 port_ID,uint8 pin_ID,DIO_Pin_DirectionType direction){

	if(direction == OUTPUT)
	{
		switch(port_ID)
		{
		case PORTA_ID:
			SET_BIT(DDRA,pin_ID);
			break;
		case PORTB_ID:
			SET_BIT(DDRB,pin_ID);
			break;
		case PORTC_ID:
			SET_BIT(DDRC,pin_ID);
			break;
		default:
			SET_BIT(DDRD,pin_ID);
			break;
		}
	}
	else if(direction == INPUT_PULLUP)
		{
			switch(port_ID)
			{
			case PORTA_ID:
				CLR_BIT(DDRA,pin_ID);
				SET_BIT(PORTA,pin_ID);
				break;
			case PORTB_ID:
				CLR_BIT(DDRB,pin_ID);
				SET_BIT(PORTB,pin_ID);
				break;
			case PORTC_ID:
				CLR_BIT(DDRC,pin_ID);
				SET_BIT(PORTC,pin_ID);
				break;
			default:
				CLR_BIT(DDRD,pin_ID);
				SET_BIT(PORTD,pin_ID);
				break;

			}
		}
	else if(direction == INPUT)
	{
		switch(port_ID)
		{
		case PORTA_ID:
			CLR_BIT(DDRA,pin_ID);
			break;
		case PORTB_ID:
			CLR_BIT(DDRB,pin_ID);
			break;
		case PORTC_ID:
			CLR_BIT(DDRC,pin_ID);
			break;
		default:
			CLR_BIT(DDRD,pin_ID);
			break;

		}
	}
}


void DIO_setup_Port_Direction(uint8 port_ID,DIO_Port_DirectionType direction){

	switch(port_ID)
	{
	case PORTA_ID:
		DDRA=direction;
		break;
	case PORTB_ID:
		DDRB=direction;
		break;
	case PORTC_ID:
		DDRC=direction;
		break;
	default:
		DDRD=direction;
		break;
	}
}


void DIO_write_Pin(uint8 port_ID,uint8 pin_ID,Value value){

	if(value == HIGH)
		{
			switch(port_ID)
			{
			case PORTA_ID:
				SET_BIT(PORTA,pin_ID);
				break;
			case PORTB_ID:
				SET_BIT(PORTB,pin_ID);
				break;
			case PORTC_ID:
				SET_BIT(PORTC,pin_ID);
				break;
			default:
				SET_BIT(PORTD,pin_ID);
				break;
			}
		}
		else if(value == LOW)
		{
			switch(port_ID)
			{
			case PORTA_ID:
				CLR_BIT(PORTA,pin_ID);
				break;
			case PORTB_ID:
				CLR_BIT(PORTB,pin_ID);
				break;
			case PORTC_ID:
				CLR_BIT(PORTC,pin_ID);
				break;
			default:
				CLR_BIT(PORTD,pin_ID);
				break;

			}
		}
}


void DIO_write_Port(uint8 port_ID,uint8 value){

	switch(port_ID)
	{
	case PORTA_ID:
		PORTA = value;
		break;
	case PORTB_ID:
		PORTB = value;
		break;
	case PORTC_ID:
		PORTC = value;
		break;
	default:
		PORTD = value;
		break;
	}
}


uint8 DIO_read_Pin(uint8 port_ID,uint8 pin_ID){

	switch(port_ID)
	{
	case PORTA_ID:
		return GET_BIT(PINA,pin_ID);
	case PORTB_ID:
		return GET_BIT(PINB,pin_ID);
	case PORTC_ID:
		return GET_BIT(PINC,pin_ID);
	default:
		return GET_BIT(PIND,pin_ID);
	}
}


uint8 DIO_read_Port(uint8 port_ID){

	switch(port_ID)
	{
	case PORTA_ID:
		return PINA;
	case PORTB_ID:
		return PINB;
	case PORTC_ID:
		return PINC;
	default:
		return PINC;
	}
}


void DIO_Toggle_Pin(uint8 port_ID,uint8 pin_ID){

	switch(port_ID)
	{
	case PORTA_ID:
		TOGGLE_BIT(PORTA,pin_ID);
		break;
	case PORTB_ID:
		TOGGLE_BIT(PORTB,pin_ID);
		break;
	case PORTC_ID:
		TOGGLE_BIT(PORTC,pin_ID);
		break;
	default:
		TOGGLE_BIT(PORTD,pin_ID);
		break;
	}
}

void DIO_Toggle_Port(uint8 port_ID)
{
	switch(port_ID)
		{
		case PORTA_ID:
			PORTA ^= 0xFF;
			break;
		case PORTB_ID:
			PORTB ^= 0xFF;
			break;
		case PORTC_ID:
			PORTC ^= 0xFF;
			break;
		default:
			PORTD ^= 0xFF;
			break;
		}
}
