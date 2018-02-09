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

// ���������ص�ѹֵ��Χ
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
			// ϵͳʱ�����ú���
			RCC_Configuration(); 
     // NVIC���ú���  
			NVIC_Configuration();
			// ����GPIOģ��ʱ��
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
			// �ѵ���������ͨIO��
			// GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
			// ����GPIOΪͬһ���Ͷ˿�
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			// �������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			// ��������Ƶ��Ϊ50HZ
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			// ��ʼ��GPIOB�˿�
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
	
			// ��ʼ��GPIOA�˿�
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
			// ѡ��PB3
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
			// ��©����
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			// ��������Ƶ��Ϊ50HZ
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			// ��ʼ��GPIOB�˿�
			GPIO_Init(GPIOB, &GPIO_InitStructure); 

			// ��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
		  GPIO_Write(GPIOA,0xffff);
		  // ��GPIOB 16���˿�ȫ����Ϊ�ߵ�ƽ
		  GPIO_Write(GPIOB,0xffff);

		  LCD_Init();
		  delayms(150); 
		
		  AD7843(CMD_RDX);
		  AD7843(CMD_RDY);
		  
			// Ϳ��
		  Piant(color[1]);
			// ��һ��ͼ����ص������
		  LCD_ShowString(16,107,color[0],color[1],"Guitar Helper");
		  LCD_ShowString(64,133,color[0],color[1],"Battery");
		  LCD_ShowString(32,161,color[0],color[1],"Checking");
			// ͼ��
		  Drawsingle(96,200,48,48,288,color[2],color[1],test);
		  LCD_ShowString(160,161,color[0],color[1],".");
		  delayms(500);
		  LCD_ShowString(176,161,color[0],color[1],".");
		  delayms(500);
		  LCD_ShowString(192,161,color[0],color[1],".");
		  delayms(500);
		  Rechangle(160,161,208,184,color[1]);
		 
		 // Ϳ�ں���ʾpage0
		  Piant(color[1]);
		  Rechangle(4,4,232,154,color[5]);
		  Rechangle(4,162,232,154,color[5]);
		  Drawsingle(60,4,120,120,1800,color[0],color[5],tune);
		  Drawsingle(60,162,120,120,1800,color[0],color[5],chord);
		  LCD_ShowString(24,122,color[0],color[5],"Guitar Tuner");
		  LCD_ShowString(8,280,color[0],color[5],"Chord Analysis");
}
