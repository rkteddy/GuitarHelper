#define u16   unsigned int
#define u8    unsigned char



#define CS_PIN      GPIO_Pin_4	 //CS 对应单片机引脚定义 P2^3 / 对应STM32的 PB4
#define DIN_PIN     GPIO_Pin_5	 //RD  对应单片机引脚定义 P2^2 / 对应STM32的 PB5
#define DCLK_PIN    GPIO_Pin_6	 //WR  对应单片机引脚定义 P2^1 / 对应STM32的 PB6
#define DOUT_PIN    GPIO_Pin_7  //RS  对应单片机引脚定义 P2^0 / 对应STM32的 PB7
#define IRQ_PIN     GPIO_Pin_3	 //CS  对应单片机引脚定义 P2^4 / 对应STM32的 PB3

#define    CS(x)     x ? GPIO_SetBits(GPIOB,   CS_PIN) :   GPIO_ResetBits(GPIOB, CS_PIN) //自己定义位操作函数
#define    DIN(x)    x ? GPIO_SetBits(GPIOB,  DIN_PIN) :   GPIO_ResetBits(GPIOB, DIN_PIN)
#define    DCLK(x)   x ? GPIO_SetBits(GPIOB, DCLK_PIN) :   GPIO_ResetBits(GPIOB, DCLK_PIN)
#define    DOUT(x)   x ? GPIO_SetBits(GPIOB, DOUT_PIN) :   GPIO_ResetBits(GPIOB, DOUT_PIN)
#define    IRQ(x)    x ? GPIO_SetBits(GPIOB,  IRQ_PIN) :   GPIO_ResetBits(GPIOB, IRQ_PIN)


// A/D 通道选择命令字和工作寄存器
#define	CMD_RDX 	0xD0
#define	CMD_RDY 	0x90
#define READ_TIMES 12 //读取次数
#define LOST_VAL    2    //丢弃值
#define ERR_RANGE 50 //误差范围 

#define LCDWIDTH		240
#define LCDHEIGHT		400




 void Delay(vu32 nCount);
 extern u16 AD7843(u8 CMD) ;
// void inttostr(int dd,  char *str);
 unsigned int ReadFromCharFrom7843(void);
 void WriteCharTo7843(unsigned char num) ;
 void spistar(void);



//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//unsigned int ADS_Read_AD(u8 CMD);
unsigned int ADS_Read_XY(u8 xy);//
unsigned char Read_ADS(u16 *x,u16 *y);////最小值不能少于100.
unsigned char Read_ADS2(u16 *x,u16 *y);//2次读取ADS7846,连续读取2次有效的AD值,且这两次的偏差不能超过ERR_RANGE







