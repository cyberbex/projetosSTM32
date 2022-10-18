#include "timer_drive.h"
//#include "help_func.h"
//#include "lcd_1602_drive.h"


char num[10];
int unidade=0;
int decimal=0;

int readValue;
float sensitivity = 0.06; //para modelo 30A, 0.1 para modelo 20A
float rawVoltage;
float current;
//TENSAO Vout do sensor corrente 2.351, com corrente = 0, e usando uma fonte de 4,6v.
//Ajustar conforme a fonte.

float Vout = 2.351;


int analog_rx = 0;
float fator= 11.4;
float tensaoPlaca =0.0;
float tensaoMaxCarregamento = 14.6;
char pwm=6;
void tensaoSaida(void);
void correnteSaida(void);

uint16_t samples[2] = {0,0};

int main(void)
{

	//systick_init();

	RCC->APB2ENR |= 0x0800;
	
	init_GP(PA,3,OUT50,O_AF_PP);

	
	TIM1->PSC = (24-1);
	TIM1->ARR = 100;
	TIM1->CNT = 0;
	TIM1->CCMR1 |= 0x30;
	TIM1->CCER |= 1;

	
	TIM1->BDTR |= 0x8000;
	
	TIM1->CCR1 = 50; // duty cycle

	
	TIM1->CR1 |= 1;

	
	
	 
while(1)
	{	
	 //correnteSaida();
	 //tensaoSaida();
		
	 /*if(tensaoPlaca > tensaoMaxCarregamento){
		    pwm++;
		    if(pwm > 99) pwm =99;
		    TIM1->CCR1 = pwm;
	   }
		if(tensaoPlaca+ 0.2 < tensaoMaxCarregamento){
				pwm--;
				if(pwm < 1) pwm =1;
				TIM1->CCR1 = pwm;
		}*/
	//lcd_msg(1,3,"gam222222222");
	//elayMs(1000);
	}
}


