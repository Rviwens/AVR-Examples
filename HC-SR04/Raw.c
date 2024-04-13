#define F_CPU 20000000UL
#define USARTTX
//#define USARTRX


#include <avr/io.h>
#include <avr/interrupt.h>
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_Timer_Functions.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\USART_AM16.c"
#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_CharFunctions.c"
//#include "C:\Users\Operator\Documents\Atmel Studio\AVR-InterFace-Files-main\atmega-16Library\AM16_HC-SR04.c"


uint8_t DataBuff[511];




#define F_CPU 20000000UL
#define  Trigger_pin	PA2	/* Trigger pin */

volatile int TimerOverflow = 0;



ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}



void Error(uint8_t ErrorCode){
	switch (ErrorCode)
	{
		case 0: USART_Send("\r\n Error At -> \"Waiting for Raising Edge \" \r\n"); break;
		case 1: USART_Send("\r\nError At -> \"Waiting for Falling Edge \"\r\n ");break;
		case 2: USART_Send("\r\nError At -> \"UnKnown Error \" ");break;
	}
	
}

short ErrorFlag =0;
long count;
long double distance;
long long ErrorCount = 0;



int main(void)
{
	long count;
	double distance;
	char string [10];
	
	USART_init(0,8,57600);
	USART_Send("\r\n Hello World ");
	sei();
	
	DDRA = (1<<Trigger_pin);/* Make trigger pin as output */
	PORTD = 0xFF;

	TIMSK = (1 << TOIE1);
	TCCR1A = 0;

	/* Give 10us trigger pulse on trig. pin to HC-SR04 */

	
	while(1){
		
		
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));


		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
		/*Calculate width of Echo by Input Capture (ICP) */
		
		while ((TIFR & (1 << ICF1)) == 0)
		{
			ErrorCount++;
			if(ErrorCount>10000000){
				Error(0);
				ErrorFlag=1;
				break;
			}
		}
		
		
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TCCR1B |=(1<<CS10)|(1<<CS11);
		
		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
		TimerOverflow = 0;/* Clear Timer overflow count */


		while ((TIFR & (1 << ICF1)) == 0)
		{
			ErrorCount++;
			if(ErrorCount>10000000){
				Error(1);
				ErrorFlag=1;
				break;
			}
		}
		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)(17150*(count)*0.0000032);

		dtoa(distance,string);/* distance to string */
		strcat(string, " cm   ");	/* Concat unit i.e.cm */
		USART_Send("\r\n");
		USART_Send(string);
		_delay_ms(200);
	}

}
