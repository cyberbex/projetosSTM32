#include "timer_drive.h"
#include "adc_drive.h"
#include "uart_drive.h"
#include "help_func.h"

char num[10];
int analog_rx = 0;
int unidade=0;
int decimal=0;
float fator= 11.4;
float tensaoPlaca =0.0;
float tensaoMaxCarregamento = 14.6;
char pwm=1;


int main(void)
{
	//Initialize the ADC
	systick_init();
	//UART_init(2,9600);
	
	adc_init(adc1, PA, 1);
	RCC->APB2ENR |= 0x0800;
	
	init_GP(PA,8,OUT50,O_AF_PP);

	
	TIM1->PSC = (24-1);
	TIM1->ARR = 100;
	TIM1->CNT = 0;
	TIM1->CCMR1 |= 0x60;
	TIM1->CCER |= 1;

	
	TIM1->BDTR |= 0x8000;
	
	TIM1->CCR1 = pwm; // duty cycle

	
	TIM1->CR1 |= 1;

	
	
	 
while(1)
	{	
	if(adc_check(adc1, PA, 1))
	{
		analog_rx = adc_rx(adc1, PA, 1);
		//UART_SEND(2,"ADC1: ");
		tensaoPlaca = analog_rx * 3.3/4096;
		tensaoPlaca = tensaoPlaca * fator;
		
	
		
		//unidade = tensaoPlaca;
		//decimal = (tensaoPlaca * 100);
		//decimal = decimal%100;
		
		//UART_SEND(2,"tensao placa: ");
		//int2char(unidade,num);
		//UART_SEND(2,num);
		//UART_SEND(2,",");
		//int2char(decimal,num);
		//UART_SEND(2,num);
		//str_empty(num);
		
		
	}
	 if(tensaoPlaca > tensaoMaxCarregamento){
		    pwm++;
		    if(pwm > 99) pwm =99;
		    TIM1->CCR1 = pwm;
	   }
		if(tensaoPlaca+ 0.2 < tensaoMaxCarregamento){
				pwm--;
				if(pwm < 1) pwm =1;
				TIM1->CCR1 = pwm;
		}
	
	DelayMs(50);
	}
}


