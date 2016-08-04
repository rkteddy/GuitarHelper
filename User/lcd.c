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
