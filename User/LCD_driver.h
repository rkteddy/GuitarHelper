#define uint unsigned int
#define u8 unsigned char
#define uchar unsigned char	

#define LCD_RST_PIN    GPIO_Pin_8	 //RST 对应单片机引脚定义 P3^2 / 对应STM32的 PA8

#define LCD_WR_PIN     GPIO_Pin_3	 //WR  对应单片机引脚定义 P2^5 / 对应STM32的 PB3
#define LCD_RS_PIN     GPIO_Pin_1	 //RD  对应单片机引脚定义 P2^6 / 对应STM32的 PB1
#define LCD_CS_PIN     GPIO_Pin_0	 //CS  对应单片机引脚定义 P2^7 / 对应STM32的 PB0

#define LCD_DB17_PIN   GPIO_Pin_12   //DB17	 对应单片机引脚定义 P3^4 / 对应STM32的 PC12
#define LCD_DB16_PIN   GPIO_Pin_11   //DB16	 对应单片机引脚定义 P3^3 / 对应STM32的 PC11

#define    LCD_RST(x)  x ? GPIO_SetBits(GPIOA, LCD_RST_PIN):   GPIO_ResetBits(GPIOA, LCD_RST_PIN) //自己定义位操作函数

#define    LCD_WR(x)   x ? GPIO_SetBits(GPIOC, LCD_WR_PIN) :   GPIO_ResetBits(GPIOC, LCD_WR_PIN)
#define    LCD_RS(x)   x ? GPIO_SetBits(GPIOB, LCD_RS_PIN) :   GPIO_ResetBits(GPIOB, LCD_RS_PIN)
#define    LCD_CS(x)   x ? GPIO_SetBits(GPIOB, LCD_CS_PIN) :   GPIO_ResetBits(GPIOB, LCD_CS_PIN)

#define    LCD_DB17(x)   x ? GPIO_SetBits(GPIOA, LCD_DB17_PIN) :   GPIO_ResetBits(GPIOC, LCD_DB17_PIN)
#define    LCD_DB16(x)   x ? GPIO_SetBits(GPIOA, LCD_DB16_PIN) :   GPIO_ResetBits(GPIOC, LCD_DB16_PIN)
#define  LCD_SIZE_X		240
#define  LCD_SIZE_Y		320



void LCD_Init(void);
void LCD_ShowString(uint x,uint y,const char *f,const char *b,char *p);
void LCD_ShowChar(uint x,uint y,const char *f,const char *b,char ch);
void ChineseChar(uint x,uint y,int size,char V1,char V2,char V3,char c);
void delayms(int count) ;
void LCD_Write_DATA18(char x,char y ,char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(char VH,char VL);
void LCD_Write_COLOR(char V1,char V2,char V3);
void Piant(const char *c);
void Address_set(uint x1,uint y1,uint x2,uint y2);
void Draw(uint x1,uint y1,uint x,uint y,uint m,const unsigned char*p);
void Rechangle(int x1,int y1,int x,int y,const char *c);
void Drawsingle(uint x1,uint y1,uint x,uint y,uint m,const char *f,const char *b,const unsigned char*p);

