#include<adc.h>    //压电陶瓷pzt

__IO uint16_t ADCVal[2048];//adc数据储存


void adc_init(void)//开机调用它初始化adc相关外设
{
	
	GPIO_Conf();
	TIM3_Conf();
	DMA_Conf();
	NVIC_Conf();
	ADC1_Conf();
}

void adc_start(u8 mode) //mode ：PZT压电 MIC麦克
{
	switch(mode)
	{
		case PZT:
		{
			ADC_Cmd(ADC1,DISABLE);
			ADC_RegularChannelConfig(ADC1,ADC_Channel_15,1,ADC_SampleTime_239Cycles5);
			ADC_Cmd(ADC1,ENABLE);
			break;
		}
		/*case MIC:
		{
			ADC_Cmd(ADC1,DISABLE);
			ADC_RegularChannelConfig(ADC1,ADC_Channel_9,1,ADC_SampleTime_239Cycles5);
			ADC_Cmd(ADC1,ENABLE);
			break;
		}*/
	}		
	TIM_Cmd(TIM3,ENABLE);	
}

void RCC_Conf()//时钟初始化
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|
																		RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
	
void GPIO_Conf()//GPIO:调试时根据需要开关io防止ad口悬空
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

void TIM3_Conf()//定时器配置，1s中断2048次
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period=35155;//36m/2048=17578.125 72m/2048=35156.25
	TIM_TimeBaseStructure.TIM_Prescaler=0; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
}

void NVIC_Conf()   //tim中断，组1优先级0副优先级1
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel=DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void DMA_Conf()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADCVal;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize=2048;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_ClearFlag(DMA1_FLAG_TC1);
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void ADC1_Conf()//规则组：pzt&mic  注入组：电池
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T3_TRGO;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);
	
	/*
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_InjectedSequencerLengthConfig(ADC1, 2);
	ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);
  ADC_InjectedChannelConfig(ADC1,ADC_Channel_Vrefint, 1, ADC_SampleTime_55Cycles5);
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);*/
	ADC_DMACmd(ADC1,ENABLE);
	ADC_ExternalTrigConvCmd(ADC1,ENABLE);
	//ADC_ExternalTrigInjectedConvCmd(ADC1, DISABLE);   
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}
