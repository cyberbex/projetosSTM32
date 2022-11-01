/*
Welcome to the WeeW - Electronics
follow us on our Channel : https://www.youtube.com/channel/UCnTWd_4LwCEcAw19Jds0Vjg

The topic of this program is to:

- Set up an efficient UART communication 
- Using UART Interrupt


Related explanatory video : https://youtu.be/mb7G1-1RnZ8

*/

#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"
#include "uart_drive.h"


char USART_1_msg[250];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;

char USART_2_msg[250];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;

char USART_3_msg[250];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;




char c = 'C';

char msg[30] = "";
int i=0;

int main(void)
{
systick_init();
UART_init(2,115200);
UART_init(3,115200);

DelayMs(100);

//UART_SEND(2,msg);
	

while(1)
	{	
			
				DelayMs(100);
			  if(USART_2_sig)
				{
					UART_SEND(3,USART_2_msg);
					USART_2_sig=0;
				}
						
	}

}


void USART3_IRQHandler()
{
//	while((USART3->SR & 0x20) == 0x00)
//	{};
//	c = USART3->DR;
//	msg[i] += c;
//	i++;
//	UART_SEND(2,msg);
		
		
	UART_ISR(3,2,&USART_3_sig, &USART_3_cnt, USART_3_msg);
}

void USART2_IRQHandler()
{
	UART_ISR(2,0,&USART_2_sig, &USART_2_cnt, USART_2_msg);
}

