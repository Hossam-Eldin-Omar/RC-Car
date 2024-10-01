#include "INPUT.h"

/*___________________________________________________________________________________________________*/
void INPUT_Init( uint8 port_ID , uint8 pin_ID )
{
	/* Initialization the Pin Send Direction as Floating Input */
	DIO_setup_Pin_Direction(port_ID, pin_ID, INPUT);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void INPUT_PULLUP_Init( uint8 port_ID , uint8 pin_ID )
{
	/* Initialization the Pin Send Direction as Pull Up Input */
	DIO_setup_Pin_Direction(port_ID, pin_ID, INPUT_PULLUP);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 INPUT_Read( uint8 port_ID , uint8 pin_ID )
{
	/* Read the Send Pin as One if it High */
	return DIO_read_Pin(port_ID, pin_ID);
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 INPUT_PULLUP_Read( uint8 port_ID , uint8 pin_ID )
{
	/* Read the Send Pin as One if it Low */
	return !DIO_read_Pin(port_ID, pin_ID);
}
/*___________________________________________________________________________________________________*/
