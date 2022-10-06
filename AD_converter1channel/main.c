#include "systick_time.h"
#include "help_func.h"
#include "gp_drive.h"
#include "stm32f10x.h"  
#include "uart_drive.h"



int val = 0;
int val2;
char num[10];
int unidade=0;
int decimal=0;
float fator= 11.4;
float tensaoPlaca =0.0;

int main(void)
{
	UART_init(2,9600);
	systick_init();
	
	RCC->CFGR |= 0x8000; // pre scaler de 6 no clock do conversor ad
	RCC->APB2ENR |= 0x205;  // Alternate function I/O clock enable / I/O port A clock enable/ ADC1 EN
	GPIOA->CRL &= 0xFF0FFFFF; // reseta os bits(mode5/cnf5) do registrador CRL
	GPIOA->CRL |= 0x800000;   // configura o PA5 como input, com pull-up/pull-down.
	
	
	ADC1->CR1 |= 0x20; //Enable End of Conversion interrupt
	NVIC_EnableIRQ(ADC1_2_IRQn);// Enable the interrupt in the NVIC
	
	ADC1->SMPR2 |= 0x38000; //quantidade de samples do conversor ad.
	ADC1->SQR3 |= 0x5; // primeiro da sequencia de canais a ser lido, no caso apenas 1 canal.
	
	ADC1->CR2 |= ADC_CR2_ADON |ADC_CR2_CONT; // turn ON  + Continuos Conversion
	
	DelayMs(1); // T(stab) , não precisa ser um milisegundo.
	
	ADC1->CR2 |= ADC_CR2_ADON; // turn ON pela segunda vez para realmente ligar!
	DelayMs(1);
	ADC1->CR2 |= ADC_CR2_CAL;
	DelayMs(2);
	
	while(1)
	{
		/*UART_SEND(2,"tensao placa: ");
		tensaoPlaca = val * 3.3/4096;
		tensaoPlaca = tensaoPlaca * fator;
		unidade = tensaoPlaca;
		decimal = (tensaoPlaca * 100);
		decimal = decimal%100;
		
		UART_SEND(2,"tensao placa: ");
		int2char(unidade,num);
		UART_SEND(2,num);
		UART_SEND(2,",");
		int2char(decimal,num);
		UART_SEND(2,num);
		str_empty(num);*/
		DelayMs(100);
		val2 = val;
	}

}

void ADC1_2_IRQHandler(){
//check if we are here because end of conversion flag is set.
//the end of conversion flag is cleared by reading the data register
if(ADC1->SR & ADC_SR_EOC){
	val = ADC1->DR;
} 	
}
