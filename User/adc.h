/*
˵����
�������ʼ������void adc_init(void)
��ʼת������void adc_start(u8 mode)  ������PZT ѹ���մ� MIC��˷�
��dma�ж�DMA1_Channel1_IRQHandler()�����fft


*/

#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include <stdio.h>

#define ADC1_DR_Address ((uint32_t)0x4001244c)
#define PZT 0X01
#define MIC 0X02




void adc_init(void);
void RCC_Conf(void);
void TIM3_Conf(void);
void GPIO_Conf(void);
void NVIC_Conf(void);
void ADC1_Conf(void);
void DMA_Conf(void);
void adc_start(u8 mode);


#endif
