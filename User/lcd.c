#include "stm32f10x.h"
#include"LCD_driver.h"
#include"char.h"

void LCD_Writ_Bus(char VH,char VL)    // ��������д�뺯��
{
    GPIOA->BSRR = VH & 0x00ff;  	 // ��λP1��
    GPIOA->BRR  = (~VH) & 0x00ff;
    GPIOB->BSRR = (VL<<8) & 0xff00;   	// ��λP0��
    GPIOB->BRR  = (~(VL)<<8) & 0xff00;
		LCD_WR(0);
		LCD_WR(1); 
}

void LCD_Write_COM(char VH,char VL)  	 // ��������
{	
    LCD_RS(0);
		LCD_Writ_Bus(VH,VL);
}

void LCD_Write_DATA(char VH,char VL)  	// ��������
{
    LCD_RS(1);
		LCD_Writ_Bus(VH,VL);
}

 void LCD_Write_COLOR(char V1,char V2,char V3)	  // ��������
{
		LCD_RS(1);  
		LCD_DB17((V1 >> 5) & 0x01);   
		LCD_DB16((V1 >> 4) & 0X01);
		LCD_Writ_Bus(((V2 >> 2) & 0x0f)+((V1 << 4)& 0xf0),((V2 << 6)& 0xc0) + (V3 & 0x3f)); 	  // rgb 666 ת 288	
}	   


void Address_set(uint x1,uint y1,uint x2,uint y2)
{  
		LCD_Write_COM(0x00,0x02);LCD_Write_DATA(x1,x1>>8);    // ��ʼX
		LCD_Write_COM(0x00,0x03);LCD_Write_DATA(x1>>8,x1);

		LCD_Write_COM(0x00,0x06);LCD_Write_DATA(y1,y1>>8);    // ��ʼY
		LCD_Write_COM(0x00,0x07);LCD_Write_DATA(y1>>8,y1);

		LCD_Write_COM(0x00,0x04);LCD_Write_DATA(x2,x2>>8);    // ����X
		LCD_Write_COM(0x00,0x05);LCD_Write_DATA(x2>>8,x2);

		LCD_Write_COM(0x00,0x08);LCD_Write_DATA(y2,y2>>8);    // ����Y
		LCD_Write_COM(0x00,0x09);LCD_Write_DATA(y2>>8,y2);

		LCD_Write_COM(0x00,0x22);							 
}

void LCD_ShowChar(uint x,uint y,const char *f,const char *b,char ch)
{       
		unsigned char temp , Bytes;
		unsigned char pos,t;
		unsigned int  CHAR_W,CHAR_H;

		 
		// CHAR_W = 8;         // 8*16
		// CHAR_H = 16;

		CHAR_W = 16;         // 16*24
		CHAR_H = 24;
		LCD_CS(0);    // Ƭѡ��
		if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
				return;
		 
		Address_set(x, y, x+CHAR_W-1, y+CHAR_H-1);
		ch = ch-32;    // ����ASCII����˳��ĵ���Ӧ��ĸ�ı���
		Bytes = (CHAR_W*CHAR_H)/8;
		for(pos=0;pos<Bytes;pos++)    // CHAR_H 	(CHAR_W*CHAR_H)/8
		{
				//temp= Font8x16[ch][pos];
				//temp= Font16x24[ch][pos];
				temp= Font16x24[ch][pos];
				for(t=0;t<8;t++) //CHAR_W
				{                 
						if(temp&0x80)
								LCD_Write_COLOR(*f,*(f+1),*(f+2));
						else
								LCD_Write_COLOR(*b,*(b+1),*(b+2));
						temp<<=1; 
				}
		 }
		 LCD_CS(1);//�ر�Ƭѡ
}  

void LCD_ShowString(uint x,uint y,const char *f,const char *b,char *p)
{         
		while(*p!='\0')
		{       
				LCD_ShowChar(x,y,f,b,*p);
				// x+=8;
				x+=16;
				p++;
		} 
}
