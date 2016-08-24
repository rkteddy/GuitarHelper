#include "stm32f10x.h"
#include "adc.h"
#include "picture.h"
#include "LCD_driver.h"
#include "touch.h"
#include "math.h"
#include "FFT.h"

#define NPT 256
#define Fs 256
#define PI 3.141592653589793

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

void USART_Conf(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);
void delay_ms(int count);
extern void GUI(void);
void GUI_Init(void);
extern void FFT(struct compx *xin);

extern __IO uint16_t ADCVal[2048];

unsigned char keycheck(uint lx,uint ly,uint x1,uint y1,uint x,uint y);
unsigned int lx,ly;
unsigned char flag;
unsigned char change=0;
unsigned char page=0;
unsigned long i,j;

u16   X_Addata,Y_Addata;
u16 TP_X,TP_Y;

// 触摸屏返回电压值范围
int TchScr_Xmax=3880,TchScr_Xmin=10,
		TchScr_Ymax=3880,TchScr_Ymin=10;

struct compx {float real,imag;};
struct compx s[NPT];

int main(void)
{
		RCC_Conf();
		USART_Conf();
		printf("boot\r\n");
		GUI_Init();
		adc_init();
		printf("init done\r\n");
		while (1)
		{
				GUI();
		}
}


void GUI_Init()
{
			// 系统时钟配置函数
			RCC_Configuration(); 
     // NVIC配置函数  
			NVIC_Configuration();
			// 启动GPIO模块时钟
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
			// 把调试设置普通IO口
			// GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
			// 所有GPIO为同一类型端口
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			// 推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			// 输出的最大频率为50HZ
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			// 初始化GPIOB端口
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
	
			// 初始化GPIOA端口
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);  
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	 
			GPIO_Init(GPIOA, &GPIO_InitStructure);		
			// 选择PB3
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
			// 开漏输入
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			// 输出的最大频率为50HZ
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			// 初始化GPIOB端口
			GPIO_Init(GPIOB, &GPIO_InitStructure); 

			// 将GPIOA 16个端口全部置为高电平
		  GPIO_Write(GPIOA,0xffff);
		  // 将GPIOB 16个端口全部置为高电平
		  GPIO_Write(GPIOB,0xffff);

		  LCD_Init();
		  delayms(150); 
		
		  AD7843(CMD_RDX);
		  AD7843(CMD_RDY);
		  
			// 涂黑
		  Piant(color[1]);
			// 第一幅图，电池电量检测
		  LCD_ShowString(16,107,color[0],color[1],"Guitar Helper");
		  LCD_ShowString(64,133,color[0],color[1],"Battery");
		  LCD_ShowString(32,161,color[0],color[1],"Checking");
			// 图标
		  Drawsingle(96,200,48,48,288,color[2],color[1],test);
		  LCD_ShowString(160,161,color[0],color[1],".");
		  delayms(500);
		  LCD_ShowString(176,161,color[0],color[1],".");
		  delayms(500);
		  LCD_ShowString(192,161,color[0],color[1],".");
		  delayms(500);
		  Rechangle(160,161,208,184,color[1]);
		 
		 // 涂黑后显示page0
		  Piant(color[1]);
		  Rechangle(4,4,232,154,color[5]);
		  Rechangle(4,162,232,154,color[5]);
		  Drawsingle(60,4,120,120,1800,color[0],color[5],tune);
		  Drawsingle(60,162,120,120,1800,color[0],color[5],chord);
		  LCD_ShowString(24,122,color[0],color[5],"Guitar Tuner");
		  LCD_ShowString(8,280,color[0],color[5],"Chord Analysis");
}

void RCC_Configuration(void)
{   
	  // 复位RCC外部设备寄存器到默认值
		RCC_DeInit();

		// 打开外部高速晶振
		RCC_HSEConfig(RCC_HSE_ON);

		// 等待外部高速时钟准备好
		HSEStartUpStatus = RCC_WaitForHSEStartUp();

		if (HSEStartUpStatus == SUCCESS)
		{								    
				// 开启FLASH的预取功能
				FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

				// FLASH延迟2个周期
				FLASH_SetLatency(FLASH_Latency_2);
			
				// 配置AHB(HCLK)时钟=SYSCLK
				RCC_HCLKConfig(RCC_SYSCLK_Div1);  
			
				// 配置APB2(PCLK2)钟=AHB时钟
				RCC_PCLK2Config(RCC_HCLK_Div1); 

				// 配置APB1(PCLK1)钟=AHB 1/2时钟
				RCC_PCLK1Config(RCC_HCLK_Div2);

				 // 配置PLL时钟 == 外部高速晶体时钟*9  PLLCLK = 8MHz * 9 = 72 MHz 
				RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

				// 使能PLL时钟
				RCC_PLLCmd(ENABLE);

			 // 等待PLL时钟就绪
				while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
				
				// 配置系统时钟 = PLL时钟
				RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

				// 检查PLL时钟是否作为系统时钟
				while(RCC_GetSYSCLKSource() != 0x08);
		}
}
