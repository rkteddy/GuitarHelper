#include<adc.h>    //ѹ���մ�pzt

__IO uint16_t ADCVal[2048];//adc���ݴ���

void RCC_Conf()//ʱ�ӳ�ʼ��
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|
																		RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
	
void GPIO_Conf()//GPIO:����ʱ������Ҫ����io��ֹad������
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;      //Analog--PZT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;     //Analog--MIC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;      //Analog--BAT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	*/
	
}
