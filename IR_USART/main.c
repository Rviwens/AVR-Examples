/*
 * Maintance.c
 *
 * Created: 12/6/2023 2:55:26 PM
 * Author : Operator
 */ 
/*Notes */
//ORC May need to be adjusted, should work between (80-150) Adjust in "Timer_Functions" lib.
//  eep BAUD Rate Low. (1200) as a Standard



#define USARTTX 
#define F_CPU 20000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
 #include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_Timer_Functions.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_CharFunctions.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\USART_AM16.c"



int main(void)
{
USART_init(0,8,1200); 
sei();

IR_Init();

while(1){ 
USART_Send("\r\n Hello World");
USART_Send("\r\n Never-Ending");


_delay_ms(1000); 
}
}

