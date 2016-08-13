#define u16   unsigned int
#define u8    unsigned char

#define CS_PIN      GPIO_Pin_4 
#define DIN_PIN     GPIO_Pin_5	
#define DCLK_PIN    GPIO_Pin_6
#define DOUT_PIN    GPIO_Pin_7
#define IRQ_PIN     GPIO_Pin_3

#define    CS(x)     x ? GPIO_SetBits(GPIOB,   CS_PIN) :   GPIO_ResetBits(GPIOB, CS_PIN)
#define    DIN(x)    x ? GPIO_SetBits(GPIOB,  DIN_PIN) :   GPIO_ResetBits(GPIOB, DIN_PIN)
#define    DCLK(x)   x ? GPIO_SetBits(GPIOB, DCLK_PIN) :   GPIO_ResetBits(GPIOB, DCLK_PIN)
#define    DOUT(x)   x ? GPIO_SetBits(GPIOB, DOUT_PIN) :   GPIO_ResetBits(GPIOB, DOUT_PIN)
#define    IRQ(x)    x ? GPIO_SetBits(GPIOB,  IRQ_PIN) :   GPIO_ResetBits(GPIOB, IRQ_PIN)

// A/D 通道选择命令字和工作寄存器
#define	CMD_RDX 	0xD0
#define	CMD_RDY 	0x90
#define READ_TIMES 12    // 读取次数
#define LOST_VAL 2    // 丢弃值
#define ERR_RANGE 50    // 误差范围 

#define LCDWIDTH		240
#define LCDHEIGHT		400

void Delay(vu32 nCount);
extern u16 AD7843(u8 CMD) ;
// void inttostr(int dd,  char *str);
unsigned int ReadFromCharFrom7843(void);
void WriteCharTo7843(unsigned char num) ;
void spistar(void);

unsigned int ADS_Read_XY(u8 xy);
unsigned char Read_ADS(u16 *x,u16 *y);
unsigned char Read_ADS2(u16 *x,u16 *y);
