#define u16   unsigned int
#define u8    unsigned char



#define CS_PIN      GPIO_Pin_4	 //CS ��Ӧ��Ƭ�����Ŷ��� P2^3 / ��ӦSTM32�� PB4
#define DIN_PIN     GPIO_Pin_5	 //RD  ��Ӧ��Ƭ�����Ŷ��� P2^2 / ��ӦSTM32�� PB5
#define DCLK_PIN    GPIO_Pin_6	 //WR  ��Ӧ��Ƭ�����Ŷ��� P2^1 / ��ӦSTM32�� PB6
#define DOUT_PIN    GPIO_Pin_7  //RS  ��Ӧ��Ƭ�����Ŷ��� P2^0 / ��ӦSTM32�� PB7
#define IRQ_PIN     GPIO_Pin_3	 //CS  ��Ӧ��Ƭ�����Ŷ��� P2^4 / ��ӦSTM32�� PB3

#define    CS(x)     x ? GPIO_SetBits(GPIOB,   CS_PIN) :   GPIO_ResetBits(GPIOB, CS_PIN) //�Լ�����λ��������
#define    DIN(x)    x ? GPIO_SetBits(GPIOB,  DIN_PIN) :   GPIO_ResetBits(GPIOB, DIN_PIN)
#define    DCLK(x)   x ? GPIO_SetBits(GPIOB, DCLK_PIN) :   GPIO_ResetBits(GPIOB, DCLK_PIN)
#define    DOUT(x)   x ? GPIO_SetBits(GPIOB, DOUT_PIN) :   GPIO_ResetBits(GPIOB, DOUT_PIN)
#define    IRQ(x)    x ? GPIO_SetBits(GPIOB,  IRQ_PIN) :   GPIO_ResetBits(GPIOB, IRQ_PIN)


// A/D ͨ��ѡ�������ֺ͹����Ĵ���
#define	CMD_RDX 	0xD0
#define	CMD_RDY 	0x90
#define READ_TIMES 12 //��ȡ����
#define LOST_VAL    2    //����ֵ
#define ERR_RANGE 50 //��Χ 

#define LCDWIDTH		240
#define LCDHEIGHT		400




 void Delay(vu32 nCount);
 extern u16 AD7843(u8 CMD) ;
// void inttostr(int dd,  char *str);
 unsigned int ReadFromCharFrom7843(void);
 void WriteCharTo7843(unsigned char num) ;
 void spistar(void);



//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//unsigned int ADS_Read_AD(u8 CMD);
unsigned int ADS_Read_XY(u8 xy);//
unsigned char Read_ADS(u16 *x,u16 *y);////��Сֵ��������100.
unsigned char Read_ADS2(u16 *x,u16 *y);//2�ζ�ȡADS7846,������ȡ2����Ч��ADֵ,�������ε�ƫ��ܳ���ERR_RANGE







