#include "ATMEGA32/HAL/DC_MOTOR/DC_MOTOR.h"
#include "ATMEGA32/MCAL/UART/UART.h"
#include "ATMEGA32/MCAL/TIMER2/TIMER2.h"
#include "ATMEGA32/MCAL/TIMER0/TIMER0.h"
#include "ATMEGA32/MCAL/TIMER1/TIMER1.h"
#include "ATMEGA32/HAL/SERVO_MOTOR/servo_motor.h"
#include "ATMEGA32/HAL/KEYPAD/keypad.h"
#include "ATMEGA32/HAL/LCD/LCD.h"
#include "ATMEGA32/MCAL/EEPROM/EEPROM_driver.h"
#include <util/delay.h>
#include <avr/io.h>

#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define NOTPRESSED 0xff

#define MOTOR_1_PORT		PORTC_ID
#define MOTOR_2_PORT		PORTC_ID

#define MOTOR_1_PIN1		0
#define MOTOR_1_PIN2		1

#define MOTOR_2_PIN1		2
#define MOTOR_2_PIN2		3

#define MOTOR_1				0
#define MOTOR_2				1



#define MAX_GEAR 			6
#define MIN_GEAR 			3



#define NOTHING				0 + 48
#define FORWARD				1 + 48
#define BACKWARD			2 + 48
#define STOP				3 + 48
#define STEER_RIGHT			4 + 48
#define STEER_LEFT			5 + 48
#define GEARUP				6 + 48
#define GEARDOWN			7 + 48
#define CLR_SCREEN		    8 + 48
#define SEND_LCD			9 + 48
#define UART_STOPCHAR		10 + 48
#define REVERSE				11 + 48
#define SKIP				12 + 48
#define PASSWORD             1234
#define EQUAL_KEY            '='
#define BUZZER_ON            'o'
#define BUZZER_OFF           'f'
uint16_t entered_password = 0;
uint16_t pass = 0;
uint8_t key;
struct rev
{
	uint32 mode : 3;
	uint32 gear : 3;
	uint32 time : 26;
};

struct rev arr[200] = {};

uint8 MODE = SKIP;
uint8 INDEX = 0;
uint8 gear = MIN_GEAR;
uint8 command = '0';
uint8 str[34] = {'0'};
volatile uint16 countsNumber = 0;

volatile uint16 counter = 0;

uint8 CAR_STATUS = 0;

uint8 flag = 0;

void UARt_func()
{
	command = str[0];
	CAR_STATUS = 1;

}

void UART_LCD_func()
{
	LCD_displayString(str);
	UART_Set_RX_Callback(&UARt_func,str,1,UART_STOPCHAR);
	CAR_STATUS = 1;
}

void save_data()
{
	if(MODE != SKIP)
	{
		arr[INDEX].time = TIMER0_GetTime_ms()/10;
		TIMER0_RESET();
		arr[INDEX].mode = MODE;
		arr[INDEX].gear = gear;

		INDEX++;
	}
	else
	{
		TIMER0_RESET();
	}


}


void TIMER0_fun()
{
	counter++;
	if(counter >= countsNumber)
	{
		counter = 0;
		receive_data();
	}
}


void TIMER0_OVF_fun()
{
	counter++;
	if(counter >= countsNumber)
	{
		counter = 0;

		if(CAR_STATUS == 0 && MODE != SKIP)
		{
			flag = 1;
			arr[INDEX].time = TIMER0_GetTime_ms()/10;
			TIMER0_RESET();
			DC_MOTOR_STOP(MOTOR_1,MOTOR_2);
			arr[INDEX].mode = MODE;
			arr[INDEX].gear = gear;

			INDEX++;

			TIMER0_Set_OVF_Callback(&TIMER0_fun);
			TIMER0_SetTimerValue(255);
		}
		else if(MODE == SKIP)
		{
			CAR_STATUS = 1;
		}
		else
		{
			CAR_STATUS = 0;
		}


	}
}

void receive_data()
{
	if(INDEX != 0)
	{
		INDEX--;
		if(MODE != SKIP)
		{
			TIMER2_SetPWMDutyCycle(42.5*arr[INDEX].gear);
			DC_MOTOR_SET_Direction(MOTOR_1,MOTOR_2,arr[INDEX].mode);
			countsNumber = TIMER0_Set_INT_Time_ms(arr[INDEX].time*10);
		}

	}
	else
	{

		DC_MOTOR_STOP(MOTOR_1,MOTOR_2);
		command = NOTHING;
		MODE = SKIP;
		flag = 0;
		TIMER0_RESET();
		CAR_STATUS = 1;
		countsNumber = TIMER0_Set_INT_Time_ms(5000);
		TIMER0_Set_OVF_Callback(&TIMER0_OVF_fun);
		//counter = 0;
		//countsNumber = 0;

	}
}


int main()
{
	MCUCSR |=1<<JTD;
	MCUCSR |=1<<JTD;
	
	char value=NOTPRESSED;
	char i =0;
	
	DC_MOTOR_init( MOTOR_1 , MOTOR_1_PORT , MOTOR_1_PIN1 , MOTOR_1_PIN2 );

	DC_MOTOR_init( MOTOR_2 , MOTOR_1_PORT , MOTOR_2_PIN1 , MOTOR_2_PIN2 );

	DIO_setup_Pin_Direction(PORTD_ID,PIN6_ID,OUTPUT);


	UART_Init();

	TIMER2_Init();
    keypad_vInit();
	TIMER0_Init();

	LCD_init();
	LCD_CursorON();
	LCD_setCursor(0,5);
	LCD_displayString("HELLO!");
	_delay_ms(1000);
	LCD_clearScreen();

	TIMER1_Init();

	Servo_motor_degree(-90);
	_delay_ms(500);
	Servo_motor_degree(90);

	TIMER2_SetPWMDutyCycle(42.5*gear);

	UART_Set_RX_Callback(&UARt_func,str,1,UART_STOPCHAR);

	TIMER0_RESET();
	countsNumber = TIMER0_Set_INT_Time_ms(5000);
	TIMER0_Set_OVF_Callback(&TIMER0_OVF_fun);
	
	if (EEPROM_read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		LCD_displayString("set pass:");
		for (i=0;i<=3;i++)
		{
			do
			{
				value=keypad_u8check_press();
			}while (value==NOTPRESSED);
			LCD_displayCharacter(value);
			pass = pass * 10 + (value - '0');
			_delay_ms(300);
			LCD_setCursor(0,9+i);
			LCD_displayCharacter('*');
			_delay_ms(500);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
		}
		EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
		LCD_clearScreen();
		LCD_displayString("Password is set");
		_delay_ms(1000);
		LCD_clearScreen();
		i=0;
	}
	else
	{
		pass = ((int)(EEPROM_read(EEPROM_PASSWORD_LOCATION1)-'0')) * 1000 + ((int)(EEPROM_read(EEPROM_PASSWORD_LOCATION2)-'0'))* 100 + ((int)(EEPROM_read(EEPROM_PASSWORD_LOCATION3)-'0'))* 10 + ((int)(EEPROM_read(EEPROM_PASSWORD_LOCATION4)-'0'));
	}
	while(1)
	{
		

		if(flag == 0)
		{
			switch (command)
			{
				case NOTHING:

					break;

				case FORWARD:

					DC_MOTOR_FORWARD(MOTOR_1,MOTOR_2);
					save_data();
					MODE = BACKWARD;
					command = NOTHING;
					break;

				case BACKWARD:

					DC_MOTOR_BACKWARD(MOTOR_1,MOTOR_2);
					save_data();
					MODE = FORWARD;
					command = NOTHING;
					break;

				case STOP:

					DC_MOTOR_STOP(MOTOR_1,MOTOR_2);
					save_data();
					MODE = STOP;
					command = NOTHING;
					break;

				case STEER_RIGHT:

					DC_MOTOR_STEER_Right(MOTOR_1,MOTOR_2);
					save_data();
					MODE = STEER_LEFT;
					command = NOTHING;
					break;

				case STEER_LEFT:

					DC_MOTOR_STEER_Left(MOTOR_1,MOTOR_2);
					save_data();
					MODE = STEER_RIGHT;
					command = NOTHING;
					break;

				case GEARUP:

					if(gear < MAX_GEAR)
					{
						gear++;
						TIMER2_SetPWMDutyCycle(42.5*gear);
						save_data();
					}
					command = NOTHING;
					break;


				case GEARDOWN:

					if(gear > MIN_GEAR)
					{
						gear--;
						TIMER2_SetPWMDutyCycle(42.5*gear);
						save_data();
					}
					command = NOTHING;
					break;


				case CLR_SCREEN:

					LCD_clearScreen();
					break;

				case SEND_LCD:

					UART_Set_RX_Callback(&UART_LCD_func,str,34,UART_STOPCHAR);
					command = NOTHING;
					break;

                case REVERSE:

					flag = 1;
					arr[INDEX].time = TIMER0_GetTime_ms()/10;
					TIMER0_RESET();
					DC_MOTOR_STOP(MOTOR_1,MOTOR_2);
					arr[INDEX].mode = MODE;
					arr[INDEX].gear = gear;

					INDEX++;

					TIMER0_Set_OVF_Callback(&TIMER0_fun);
					TIMER0_SetTimerValue(255);
					break;

				case BUZZER_ON:
				DIO_write_Pin(PORTD_ID,PIN6_ID,HIGH);
				command = NOTHING;
				break;
				case BUZZER_OFF:
				DIO_write_Pin(PORTD_ID,PIN6_ID,LOW);
				command = NOTHING;
				break;

				default:
					//DIO_write_Pin(PORTB_ID,PIN7_ID,HIGH);
					break;
			}


		}
		key = keypad_u8check_press();
		if (key != 0xFF && key != '*')
		{
			if(entered_password == 0)
			{
				LCD_clearScreen();
				LCD_displayString("Enter pass:");
			}


			if (key == EQUAL_KEY)
			{
				if (entered_password == pass)
				{
					LCD_clearScreen();


					LCD_displayString("   VALID PIN");
					LCD_setCursor(1,3);
					LCD_displayString("BOX OPENED");
					_delay_ms(300);
					Servo_motor_degree(-90);
					i = 0;
				}
				else
				{
					LCD_clearScreen();
					LCD_displayString("  INVALID PIN");
					LCD_setCursor(1,0);
					i = 0;
				}
				entered_password = 0;
			}
			else
			{
				entered_password = entered_password * 10 + (key - '0');
				LCD_displayCharacter(key);
				_delay_ms(300);
				LCD_setCursor(0,11+i);
				LCD_displayCharacter('*');
				i++;
			}
			_delay_ms(50);
		}
		else if (key == '*')
		{
			LCD_clearScreen();
			LCD_displayString("Enter old pass");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("Old pass:");
			entered_password = 0;
			for (i=0;i<=3;i++)
			{
				do
				{
					value=keypad_u8check_press();
				}while (value==NOTPRESSED);
				LCD_setCursor(0,9+i);
				LCD_displayCharacter(value);
				_delay_ms(300);
				entered_password = entered_password * 10 + (value - '0');
			}
			if(entered_password != pass)
			{
				LCD_clearScreen();
				LCD_displayString("Wrong password");
				i=0;
			}
			else
			{
				pass = 0;
				LCD_clearScreen();
				LCD_displayString("change pass:");
				LCD_setCursor(0,12);
				_delay_ms(1000);
				for (i=0;i<=3;i++)
				{
					do
					{
						value=keypad_u8check_press();
					}while (value==NOTPRESSED);
					LCD_displayCharacter(value);
					pass = pass * 10 + (value - '0');
					_delay_ms(300);
					LCD_setCursor(0,12+i);
					LCD_displayCharacter('*');
					_delay_ms(500);
					EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
				}
				EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
				LCD_clearScreen();
				LCD_displayString("Password is set");
				_delay_ms(1000);
				LCD_clearScreen();
			}
			i = 0;
			entered_password = 0;			
		}
	}
}