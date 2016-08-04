#include "stm32f10x.h"
#include"LCD_driver.h"
#include"char.h"

void LCD_Writ_Bus(char VH,char VL)    // 并行数据写入函数
{
    GPIOA->BSRR = VH & 0x00ff;  	 // 高位P1口
    GPIOA->BRR  = (~VH) & 0x00ff;
    GPIOB->BSRR = (VL<<8) & 0xff00;   	// 低位P0口
    GPIOB->BRR  = (~(VL)<<8) & 0xff00;
		LCD_WR(0);
		LCD_WR(1); 
}

void LCD_Write_COM(char VH,char VL)  	 // 发送命令
{	
    LCD_RS(0);
		LCD_Writ_Bus(VH,VL);
}

void LCD_Write_DATA(char VH,char VL)  	// 发送数据
{
    LCD_RS(1);
		LCD_Writ_Bus(VH,VL);
}

 void LCD_Write_COLOR(char V1,char V2,char V3)	  // 发送数据
{
		LCD_RS(1);  
		LCD_DB17((V1 >> 5) & 0x01);   
		LCD_DB16((V1 >> 4) & 0X01);
		LCD_Writ_Bus(((V2 >> 2) & 0x0f)+((V1 << 4)& 0xf0),((V2 << 6)& 0xc0) + (V3 & 0x3f)); 	  // rgb 666 转 288	
}	   

