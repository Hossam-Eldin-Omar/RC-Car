/*
 * keypad_driver.c
 *
 * Created: 7/11/2024 10:32:36 PM
 *  Author: Ahmed shaban
 */
 #include "keypad.h"

 void keypad_vInit()
 {
	 
	 DIO_setup_Pin_Direction(PORTA_ID,0,1);
	 DIO_setup_Pin_Direction(PORTA_ID,1,1);
	 DIO_setup_Pin_Direction(PORTA_ID,2,1);
     DIO_setup_Pin_Direction(PORTA_ID,3,1);
	 DIO_setup_Pin_Direction(PORTA_ID,4,0);
	 DIO_setup_Pin_Direction(PORTA_ID,5,0);
	 DIO_setup_Pin_Direction(PORTA_ID,6,0);
	 DIO_setup_Pin_Direction(PORTA_ID,7,0);
	 DIO_setup_Pin_Direction( PORTA_ID, 4, INPUT_PULLUP);
	 DIO_setup_Pin_Direction( PORTA_ID, 5, INPUT_PULLUP);
	 DIO_setup_Pin_Direction( PORTA_ID, 6, INPUT_PULLUP);
	 DIO_setup_Pin_Direction( PORTA_ID, 7, INPUT_PULLUP);
	  
 }
 char keypad_u8check_press()
 {
	 char arr[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','=','D'}};
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 for(row=0;row<4;row++)
	 {
		DIO_write_Pin(PORTA_ID,0,1);
		DIO_write_Pin(PORTA_ID,1,1);
		DIO_write_Pin(PORTA_ID,2,1);
		DIO_write_Pin(PORTA_ID,3,1);
		DIO_write_Pin(PORTA_ID,row,0);
	
		for(coloumn=0;coloumn<4;coloumn++)
		{
		
			x=DIO_read_Pin(PORTA_ID,(coloumn+4));
			if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }  
		}	
		if(x==0)
		{
			break;
		}
	}	 
	 return returnval ;	 
 }