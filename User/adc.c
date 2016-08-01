#include<adc.h>    //压电陶瓷pzt

__IO uint16_t ADCVal[2048];//adc数据储存

void RCC_Conf()//时钟初始化
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|
																		RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
	
