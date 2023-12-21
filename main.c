#include "Link.c"
#include <AM16_Timer_Functions.c>
#include <USART_AM16.c>
#include <SPI_ATM16.c>
#include <MicroSD_AM16.c>
#include <AM16_FAT32.c>

int main(void){
	USART_init(0,8,57600);
	DDRA=0x1;
	
		SPI_MAST_Init(0,128,0,0,0);
		char SDIS = SD_Init();
	
USART_Send("\r\nHello Void. I have awoken\r\n Response | ");
USART_Int_Str(SDIS,0);USART_Send("\r\n");
 if(SDIS==5){	FAT32_Init();

FAT32_Open_File("VOID");


FAT32_Read_File("VOID");



USART_Send("\r\n");	
USART_Send("\r\n Done");
}
}
