
#include "stm32f10x.h"
#include "touch.h"

extern GPIO_InitTypeDef GPIO_InitStructure;

//**********************************************************
void SPI_Start()                                     //SPI开始
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
void WriteCharTo7843(unsigned char num)          //SPI写数据
{
		unsigned char count=0;
		DCLK(0);
		for(count=0;count<8;count++)
		{
				if((num<<count)&0x80)
						DIN(1);   /*判断发送位*/
				else
						DIN(0);   
				DCLK(0); Delay(150);                //上升沿有效
				DCLK(1); Delay(150);
		}
}
//**********************************************************
unsigned int ReadFromCharFrom7843()             //SPI 读数据
{
	unsigned char count=0;
	unsigned int Num=0;
	
	for(count=0;count<12;count++)
	{
			Num<<=1;
			DCLK(1);
			Delay(150);                //下降沿有效
			DCLK(0);
			Delay(150);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; // 选择所有脚
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出的最大频率为50HZ
			GPIO_Init(GPIOB, &GPIO_InitStructure); 
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
					Num++;
	}
	return(Num);
}

/*void inttostr(int dd,  char *str)
{
		str[0]=dd/10000+48;	    // 个位
		str[1]=(dd/1000)-((dd/10000)*10)+48;   // 十位
		str[2]=(dd/100)-((dd/1000)*10)+48;	  // 百位
		str[3]=(dd/10)-((dd/100)*10)+48;    // 千位
		str[4]=dd-((dd/10)*10)+48;    // 万位
		str[5]=0;
}*/

u16 AD7843(u8 CMD)    // 外部中断0 用来接受键盘发来的数据
{
		u16 AD_Data;
		//delayms(1);    // 中断后延时以消除抖动，使得采样数据更准确
		SPI_Start();    // 启动SPI
		//delayms(1);
		WriteCharTo7843(CMD);    // 送控制字 10010000 即用差分方式读X坐标
		//delayms(1);
		DCLK(1); Delay(200);
		DCLK(0); Delay(200);
		AD_Data =ReadFromCharFrom7843();
		//WriteCharTo7843(0xD0);    // 送控制字 11010000 即用差分方式读Y坐标
		//DCLK=1; _nop_();_nop_();_nop_();_nop_();
		//DCLK=0; _nop_();_nop_();_nop_();_nop_();
		//TP_X=ReadFromCharFrom7843();
		Delay(150); 
		Delay(150); 
		CS(1);

		return  AD_Data	;
}

unsigned int ADS_Read_XY(u8 xy)
{
		u16  i, j;
		u16  buf[READ_TIMES];
		u16 sum=0;
		u16 temp;
		for(i=0;i<READ_TIMES;i++)
		{				 
				buf[i]=AD7843(xy);	    
		}				    
		for(i=0;i<READ_TIMES-1; i++)    // 排序
		{
				for(j=i+1;j<READ_TIMES;j++)
				{
						if(buf[i]>buf[j])    // 升序排列
						{
								temp=buf[i];
								buf[i]=buf[j];
								buf[j]=temp;
						}
				}
		}	  
		sum=0;
		for (i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)
				sum+=buf[i];
		temp=sum/(READ_TIMES-2*LOST_VAL);
		return temp;   
}

unsigned char Read_ADS2(u16 *x,u16 *y) 
{
    u16  x1,y1;
    u16  x2,y2;
    u8  flag;    
    flag=Read_ADS(&x1,&y1);   
    if (flag==0)
				return(0);//如果读数失败
		flag=Read_ADS(&x2,&y2);	   
    if (flag==0)
				return(0);//如果读数失败   
		if (((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
				&&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
		{
				*x=(x1+x2)/2;
				*y=(y1+y2)/2;
				return 1;
		}
		else return 0;	  
} 
