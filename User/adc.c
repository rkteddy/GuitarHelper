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

void TIM3_Conf()//��ʱ�����ã�1s�ж�2048��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period=35155;//36m/2048=17578.125 72m/2048=35156.25
	TIM_TimeBaseStructure.TIM_Prescaler=0; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
}

void NVIC_Conf()   //tim�жϣ���1���ȼ�0�����ȼ�1
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
