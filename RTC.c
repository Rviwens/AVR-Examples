/*
 * Maintance.c
 *
 * Created: 12/6/2023 2:55:26 PM
 * Author : Operator
 */ 

#define USARTTX 
#define F_CPU 20000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "AM16_Timer_Functions.c"
#include "I2C_AM16.c"
#include "AM16_RTC_.c"
#include "USART_AM16.c"



int main(void)
{

int str [10];
USART_init(0,8,57600);
USART_Send("\r\nHello world");

I2C_Init();
USART_Send("\r\n I2C, Started");
/* Replace with your application code */

// Change clock Time if Needed -> RTC_Clock_Write(6,,0,0);
USART_Send("\r\n Updated");

while(1){

RTC_Read_Clock(str);
RTC_Read_Calendar(str);


USART_Send("\r\n Day =");
USART_Int_Str(str[4],0);	
USART_Send("\r\n Date =");
USART_Int_Str(str[5],0);
USART_Send("/");
USART_Int_Str(str[6],0);
USART_Send("/");
USART_Int_Str(str[7],0);
USART_Send("\r\n Time =");
USART_Int_Str(str[2],0);
USART_Send(":");
USART_Int_Str(str[1],0);
USART_Send(":");
USART_Int_Str(str[0],0);
	
_delay_ms(1000);
}
	USART_Send("\r\nSigning Off");
		
    }

