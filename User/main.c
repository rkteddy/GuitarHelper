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

// ´¥ÃþÆÁ·µ»ØµçÑ¹Öµ·¶Î§
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

