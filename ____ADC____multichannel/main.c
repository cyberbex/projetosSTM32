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
float tensaoPlaca =0.0, tensaoPot;


uint16_t samples[2] = {0,0};  

int main(void)
{
	UART_init(2,9600);
	systick_init();
	
	//-------------------------| ADC CONFIG CODE |-------------------------------------------
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // pre scaler de 6 no clock do conversor ad
	RCC->APB2ENR |= 0x205;  // Alternate function I/O clock enable / I/O port A clock enable/ ADC1 EN
	RCC->AHBENR |= RCC_AHBENR_DMA1EN; //Habilita DMA1
	
	GPIOA->CRL &= 0x0F0FFFFF; // reseta os bits(mode5/cnf5) do registrador CRL
	GPIOA->CRL |= 0x80800000;   // configura o PA5,PA7 como input, com pull-up/pull-down.
	
	//Set the sample rate
	ADC1->SMPR2 |= ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP5_0 | ADC_SMPR2_SMP5_1;
	ADC1->SMPR2 |= ADC_SMPR2_SMP7_2 | ADC_SMPR2_SMP7_0 | ADC_SMPR2_SMP7_1;
	
	
	ADC1->SQR3 |= 0x5; //canal 5 primeiro da sequencia a ser lido.
	ADC1->SQR3 |= 7<<5; //canal 7 segundo da sequencia a ser lido.
	ADC1->SQR1 |= 1<<20; //configura dois canais a ser lido.
	
	//ADC DMA Enable and scan mode.
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_DMA;
	
	//DMA settings
	DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
	DMA1_Channel1->CMAR = (uint32_t)samples;
	DMA1_Channel1->CNDTR = 2;
	DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_PSIZE_0 | DMA_CCR1_MSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
	
	
	
	
	
	ADC1->CR2 |= ADC_CR2_ADON |ADC_CR2_CONT; // turn ON  + Continuos Conversion
	
	DelayMs(1); // T(stab) , não precisa ser um milisegundo.
	
	ADC1->CR2 |= ADC_CR2_ADON; // turn ON pela segunda vez para realmente ligar!
	DelayMs(1);
	ADC1->CR2 |= ADC_CR2_CAL;
	DelayMs(2);
	
	while(1)
	{
	
		tensaoPlaca = samples[0] * 3.3/4096;
		tensaoPlaca = tensaoPlaca * fator;
		unidade = tensaoPlaca;
		decimal = (tensaoPlaca * 100);
		decimal = decimal%100;
		
		UART_SEND(2,"tensao placa= ");
		int2char(unidade,num);
		UART_SEND(2,num);
		UART_SEND(2,",");
		int2char(decimal,num);
		UART_SEND(2,num);
		str_empty(num);
		//UART_SEND(2,"\n");
		
		tensaoPot = samples[1] * 3.3/4096;
		tensaoPot = tensaoPot * fator;
		unidade = tensaoPot;
		decimal = (tensaoPot * 100);
		decimal = decimal%100;
		
		UART_SEND(2,"tensao Pot = ");
		int2char(unidade,num);
		UART_SEND(2,num);
		UART_SEND(2,",");
		int2char(decimal,num);
		UART_SEND(2,num);
		str_empty(num);
		
		
		
		
		DelayMs(1000);
		
	}

}


