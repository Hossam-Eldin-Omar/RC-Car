#include "PORT.h"

/*___________________________________________________________________________________________________*/
void PORT_Init( uint8 port_ID , DIO_Port_DirectionType direction )
{
	/* Initialization the Port Send Direction */
	DIO_setup_Port_Direction( port_ID , direction );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void PORT_Set_Value( uint8 port_ID , uint8 PORT_Value )
{
	/* Set the Send Port Value */
	DIO_write_Port( port_ID , PORT_Value );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
uint8 PORT_Get_Value( uint8 port_ID )
{
	/* Get the Send Port Value */
	return DIO_read_Port( port_ID );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void PORT_Toggle( uint8 port_ID )
{
	/* Toggle the Send Port */
	DIO_Toggle_Port( port_ID );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void PORT_Init_All( DIO_Port_DirectionType portA_direction , DIO_Port_DirectionType portB_direction , DIO_Port_DirectionType portC_direction , DIO_Port_DirectionType portD_direction )
{
	/* Initialization All Ports Direction */
	DIO_setup_Port_Direction( PORTA_ID , portA_direction );
	DIO_setup_Port_Direction( PORTB_ID , portB_direction );
	DIO_setup_Port_Direction( PORTC_ID , portC_direction );
	DIO_setup_Port_Direction( PORTD_ID , portD_direction );
}
/*___________________________________________________________________________________________________*/



/*___________________________________________________________________________________________________*/
void PORT_Set_Value_All( uint8 portA_Value , uint8 portB_Value , uint8 portC_Value , uint8 portD_Value )
{
	/*Set All Ports Value*/
	DIO_write_Port( PORTA_ID , portA_Value );
	DIO_write_Port( PORTB_ID , portB_Value );
	DIO_write_Port( PORTC_ID , portC_Value );
	DIO_write_Port( PORTD_ID , portD_Value );
}
/*___________________________________________________________________________________________________*/







