#include "stm32f10x.h"
#include"LCD_driver.h"
#include"char.h"

void LCD_Init(void)
{
    LCD_RST(1);
	  delayms(5);	
		LCD_RST(0);
		delayms(5);
		LCD_RST(1);
		delayms(5);

		// ��Ƭѡʹ��	
		LCD_CS(0);
		                                                                                                                                                                                                                                                       
    delayms(10);
	
		// TESTM=1
		LCD_Write_COM(0x00,0x83);           
		LCD_Write_DATA(0x00,0x02); 
				 
    // VDC_SEL=011
		LCD_Write_COM(0x00,0x85);  
		LCD_Write_DATA(0x00,0x03);
		LCD_Write_COM(0x00,0x8B);  
		LCD_Write_DATA(0x00,0x01);

    // STBA[7]=1, STBA[5:4]=01, STBA[1:0]=11		
		LCD_Write_COM(0x00,0x8C); 
		LCD_Write_DATA(0x00,0x93);
		
    // DCDC_SYNC=1
		LCD_Write_COM(0x00,0x91); 
		LCD_Write_DATA(0x00,0x01);

    // TESTM=0
		LCD_Write_COM(0x00,0x83);  
		LCD_Write_DATA(0x00,0x00);
		
		// Gamma Setting
		LCD_Write_COM(0x00,0x3E);  
		LCD_Write_DATA(0x00,0xB0);
		LCD_Write_COM(0x00,0x3F);  
		LCD_Write_DATA(0x00,0x03); 
		LCD_Write_COM(0x00,0x40);  
		LCD_Write_DATA(0x00,0x10); 
		LCD_Write_COM(0x00,0x41);  
		LCD_Write_DATA(0x00,0x56); 
		LCD_Write_COM(0x00,0x42);  
		LCD_Write_DATA(0x00,0x13); 
		LCD_Write_COM(0x00,0x43);  
		LCD_Write_DATA(0x00,0x46); 
		LCD_Write_COM(0x00,0x44);  
		LCD_Write_DATA(0x00,0x23);
		LCD_Write_COM(0x00,0x45);  
		LCD_Write_DATA(0x00,0x76); 
		LCD_Write_COM(0x00,0x46);  
		LCD_Write_DATA(0x00,0x00); 
		LCD_Write_COM(0x00,0x47);  
		LCD_Write_DATA(0x00,0x5E); 
		LCD_Write_COM(0x00,0x48);  
		LCD_Write_DATA(0x00,0x4F);
		LCD_Write_COM(0x00,0x49);  
		LCD_Write_DATA(0x00,0x40);	
		
		// Power On sequence
		
		LCD_Write_COM(0x00,0x17);  
		LCD_Write_DATA(0x00,0x91); 
	 
		LCD_Write_COM(0x00,0x2B);  
		LCD_Write_DATA(0x00,0xF9); 
		delayms(10);
		
		LCD_Write_COM(0x00,0x1B);  
		LCD_Write_DATA(0x00,0x14); 
		
		LCD_Write_COM(0x00,0x1A);  
		LCD_Write_DATA(0x00,0x11); 
					
		LCD_Write_COM(0x00,0x1C);  
		LCD_Write_DATA(0x00,0x06);
		
		LCD_Write_COM(0x00,0x1F);  
		LCD_Write_DATA(0x00,0x42);
		delayms(20);
		
		LCD_Write_COM(0x00,0x19);  
		LCD_Write_DATA(0x00,0x0A); 
 
		LCD_Write_COM(0x00,0x19);  
		LCD_Write_DATA(0x00,0x1A); 
		delayms(40);
		
		
		LCD_Write_COM(0x00,0x19);  
		LCD_Write_DATA(0x00,0x12); 
		delayms(40);
		
		LCD_Write_COM(0x00,0x1E);  
		LCD_Write_DATA(0x00,0x27);
		delayms(100);	   
		
		// Display on setting
        
		LCD_Write_COM(0x00,0x24);  
		LCD_Write_DATA(0x00,0x60);	
		
		LCD_Write_COM(0x00,0x3D);  
		LCD_Write_DATA(0x00,0x40); 
		
		LCD_Write_COM(0x00,0x34);  
		LCD_Write_DATA(0x00,0x38);
		
		LCD_Write_COM(0x00,0x35);  
		LCD_Write_DATA(0x00,0x38);
		
		LCD_Write_COM(0x00,0x24);  
		LCD_Write_DATA(0x00,0x38);
		delayms(40);
		
		LCD_Write_COM(0x00,0x24);  
		LCD_Write_DATA(0x00,0x3C); 
		
		LCD_Write_COM(0x00,0x16);  
		LCD_Write_DATA(0x00,0x1C); 
		
		LCD_Write_COM(0x00,0x01);  
		LCD_Write_DATA(0x00,0x06);	
		
		LCD_Write_COM(0x00,0x55);  
		LCD_Write_DATA(0x00,0x00);

		LCD_Write_COM(0x00,0x02);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x03);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x04);           
		LCD_Write_DATA(0x00,0x00);
		LCD_Write_COM(0x00,0x05);           
		LCD_Write_DATA(0x00,0xef); 
		
		LCD_Write_COM(0x00,0x06);           
		LCD_Write_DATA(0x00,0x00);	
		LCD_Write_COM(0x00,0x07);           
		LCD_Write_DATA(0x00,0x00);	
		LCD_Write_COM(0x00,0x08);           
		LCD_Write_DATA(0x00,0x01);	
		LCD_Write_COM(0x00,0x09);           
		LCD_Write_DATA(0x00,0x8f); 

		LCD_Write_COM(0x00,0x22);  


		LCD_CS(1); 
}  

void delayms(int count)
{
		int i,j;
		for(i=0;i<count;i++)
			for(j=0;j<5000;j++);
}

/*
 ��������д�뺯��
*/
void LCD_Writ_Bus(char VH,char VL)
{
  	 // ��λP1��
    GPIOA->BSRR = VH & 0x00ff;
    GPIOA->BRR  = (~VH) & 0x00ff;
	
   	// ��λP0��
    GPIOB->BSRR = (VL<<8) & 0xff00;
    GPIOB->BRR  = (~(VL)<<8) & 0xff00;
		LCD_WR(0);
		LCD_WR(1); 
}

/*
 ��������
*/
void LCD_Write_COM(char VH,char VL)
{	
    LCD_RS(0);
		LCD_Writ_Bus(VH,VL);
}

/*
 ��������
*/
void LCD_Write_DATA(char VH,char VL)
{
    LCD_RS(1);
		LCD_Writ_Bus(VH,VL);
}

/*
 ��������
*/
 void LCD_Write_COLOR(char V1,char V2,char V3)
{
		LCD_RS(1);  
		LCD_DB17((V1 >> 5) & 0x01);   
		LCD_DB16((V1 >> 4) & 0X01);
	
 	  // rgb 666 ת 288	
		LCD_Writ_Bus(((V2 >> 2) & 0x0f)+((V1 << 4)& 0xf0),((V2 << 6)& 0xc0) + (V3 & 0x3f));
}	   

void Piant(const char *c)
{
		int i,j;
	
    // ��Ƭѡʹ��
		LCD_CS(0);
	
		Address_set(0,0,239,319);
		for (i=0;i<320;i++)
		{
				for (j=0;j<240;j++)
				{
						LCD_Write_COLOR(*c,*(c+1),*(c+2));
				}
		}
		
    // �ر�Ƭѡʹ��
		LCD_CS(1);
}

/*
 ָ�����򻭾���
*/
void Rechangle(int x1,int y1,int x,int y,const char *c)
{
		int i,j;
	
    // ��Ƭѡʹ��
		LCD_CS(0);
	
		Address_set(x1,y1,x1+x-1,y1+y-1);
    for(i=0;i<y;i++)
		{
				for (j=0;j<x;j++)
				{
						LCD_Write_COLOR(*c,*(c+1),*(c+2));
				}
	  }
		
    // �ر�Ƭѡʹ��
    LCD_CS(1);
}

/*
 ָ����������ɫͼ
*/
void Draw(uint x1,uint y1,uint x,uint y,uint m,const unsigned char*p)
{   
		int n;
    // �������������
		unsigned char k=0;
    // �������������
	  int l=0;
    // �Ƿ���Ҫ����д��ַ
		char i=1;
	  LCD_CS(0);
		for (n=0;n<m/3;n++)	   
	  {
				// ��ɫ������
				if (*p==0x3f&&*(p+1)==0x00&&*(p+2)==0x3f){i=1;}
			  else
			  { 
						if(i)
						{	 
								Address_set(x1+k,y1+l,x1+x-1,y1+l);
								i=0;
						} 
				    LCD_Write_COLOR(*p,*(p+1),*(p+2));
				}
				
		    // ����������
				p=p+3;
				k++;
				
				// x�����غ�k���¹���
				if(k==x)
				{
					 i=1;
					 k=0;
					 l++; 
				}		 
	  }
    LCD_CS(1);		
}

/*
 ָ����������,��ɫ
*/
void Drawsingle(uint x1,uint y1,uint x,uint y,uint m,const char *f,const char *b,const unsigned char*p)
{   
		int n;
	  char k=0;
	  char i;
		unsigned char j;
	  LCD_CS(0);
	
	   // ���õ�ַ��Χ
	  Address_set(x1,y1,x1+x-1,y1+y-1);
		for (n=0;n<m;n++)
		{	
				j=*p;
				for(k=0;k<8;k++) 
				{
				    // ȡ���ֽ����λ
						i=j&0x80;
						j=j<<1;
						i=i>>7;
						if(i)
						{
								LCD_Write_COLOR(*f,*(f+1),*(f+2));
						}
						else
						{ 
								LCD_Write_COLOR(*b,*(b+1),*(b+2));
						} 
				}
				
    // ����ָ���Լ�
		p++;
		}
		
    LCD_CS(1);		
}

/*
 ���õ�ַ��Χ
*/
void Address_set(uint x1,uint y1,uint x2,uint y2)
{  
    // ��ʼX
		LCD_Write_COM(0x00,0x02);LCD_Write_DATA(x1,x1>>8);
		LCD_Write_COM(0x00,0x03);LCD_Write_DATA(x1>>8,x1);

    // ��ʼY
		LCD_Write_COM(0x00,0x06);LCD_Write_DATA(y1,y1>>8);
		LCD_Write_COM(0x00,0x07);LCD_Write_DATA(y1>>8,y1);

    // ����X
		LCD_Write_COM(0x00,0x04);LCD_Write_DATA(x2,x2>>8);
		LCD_Write_COM(0x00,0x05);LCD_Write_DATA(x2>>8,x2);

    // ����Y
		LCD_Write_COM(0x00,0x08);LCD_Write_DATA(y2,y2>>8);
		LCD_Write_COM(0x00,0x09);LCD_Write_DATA(y2>>8,y2);

		LCD_Write_COM(0x00,0x22);							 
}

void LCD_ShowChar(uint x,uint y,const char *f,const char *b,char ch)
{       
		unsigned char temp , Bytes;
		unsigned char pos,t;
		unsigned int  CHAR_W,CHAR_H;
	  
		// 8*16
		// CHAR_W = 8;
		// CHAR_H = 16;

    // 16*24
		CHAR_W = 16;
		CHAR_H = 24;

    // Ƭѡ��
		LCD_CS(0);
		if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
				return;
		 
		Address_set(x, y, x+CHAR_W-1, y+CHAR_H-1);
		
    // ����ASCII����˳��ĵ���Ӧ��ĸ�ı���
		ch = ch-32;
		Bytes = (CHAR_W*CHAR_H)/8;
		
    // CHAR_H 	(CHAR_W*CHAR_H)/8
		for(pos=0;pos<Bytes;pos++)
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
		
		// �ر�Ƭѡ
		LCD_CS(1);
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
