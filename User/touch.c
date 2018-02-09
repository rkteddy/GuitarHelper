
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
//**********************************************************
unsigned int ReadFromCharFrom7843()             //SPI ������
{
	unsigned char count=0;
	unsigned int Num=0;
	
	for(count=0;count<12;count++)
	{
			Num<<=1;
			DCLK(1);
			Delay(150);                //�½�����Ч
			DCLK(0);
			Delay(150);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; // ѡ�����н�
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
			GPIO_Init(GPIOB, &GPIO_InitStructure); 
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
					Num++;
	}
	return(Num);
}

/*void itostr(int dd, char *str)
{
		str[0]=dd/10000+48;	    // ��λ
		str[1]=(dd/1000)-((dd/10000)*10)+48;   // ʮλ
		str[2]=(dd/100)-((dd/1000)*10)+48;	  // ��λ
		str[3]=(dd/10)-((dd/100)*10)+48;    // ǧλ
		str[4]=dd-((dd/10)*10)+48;    // ��λ
		str[5]=0;
}*/
