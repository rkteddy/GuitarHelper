#include<adc.h>    //ѹ���մ�pzt

__IO uint16_t ADCVal[2048];//adc���ݴ���

void RCC_Conf()//ʱ�ӳ�ʼ��
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|
																		RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
	
