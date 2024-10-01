#include "GIE.h"


/*___________________________________________________________________________________*/
void GIE_Enable( void )
{
	/* Function to enable global interrupt */

	/* Enable Global Interrupt */
	SET_BIT( SREG , I );
}
/*___________________________________________________________________________________*/



/*___________________________________________________________________________________*/
void GIE_Disable( void )
{
	/* Function to disable global interrupt */

	/* Disable Global Interrupt */
	CLR_BIT( SREG , I );
}
/*___________________________________________________________________________________*/
