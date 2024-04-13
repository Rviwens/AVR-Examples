#define F_CPU 20000000UL
#define USARTTX
//#define USARTRX


#include <avr/interrupt.h>
//#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_Timer_Functions.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\USART_AM16.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_CharFunctions.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_HC-SR04.c"


uint8_t DataBuff[511];


int main(void){
	char string[10];
	USART_init(0,8,57600);
	USART_Send("\r\n Hello World ");
	sei();
while(1){
		dtoa(HC_SR04_Distance(),string);/* distance to string */
		strcat(string, " cm   ");	/* Concat unit i.e.cm */
		USART_Send("\r\n");
		USART_Send(string);
		_delay_ms(1);
		
	}
}






