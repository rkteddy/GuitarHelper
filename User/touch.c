
#include "stm32f10x.h"
#include "touch.h"

extern GPIO_InitTypeDef GPIO_InitStructure;

//**********************************************************
void SPI_Start()                                     //SPI��ʼ
{
		DCLK(0);
		Delay(100);
		CS(1);
		Delay(150); 
		DIN(1);
		Delay(100);
		DCLK(1);
		Delay(200);
		CS(0);
		Delay(150); 
}
//**********************************************************
void WriteCharTo7843(unsigned char num)          //SPIд����
{
		unsigned char count=0;
		DCLK(0);
		for(count=0;count<8;count++)
		{
				if((num<<count)&0x80)
						DIN(1);   /*�жϷ���λ*/
				else
						DIN(0);   
				DCLK(0); Delay(150);                //��������Ч
				DCLK(1); Delay(150);
		}
}
