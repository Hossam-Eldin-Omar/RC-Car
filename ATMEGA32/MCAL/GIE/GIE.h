/*File Guard*/
#ifndef GIE_H_
#define GIE_H_

#include "../../LIB/common_macros.h"
#include "GIE_REGS.h"

/* Function to enable global interrupt */
void GIE_Enable( void );

/* Function to disable global interrupt */
void GIE_Disable( void );

#endif /* GIE_H_ */
