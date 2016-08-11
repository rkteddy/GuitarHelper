#include <picture.h>
#include <LCD_driver.h>
unsigned char keycheck(uint lx,uint ly,uint x1,uint y1,uint x,uint y);
unsigned int TP_X,TP_Y;
unsigned int lx,ly;
unsigned char flag;
unsigned char change=0;
unsigned char page=0;
unsigned long i,j;
unsigned int  X_Addata,Y_Addata;
int TchScr_Xmax=3880,TchScr_Xmin=10,
   TchScr_Ymax=3880,TchScr_Ymin=10;



void GUI()
{
		LCD_CS (0);  //打开片选使能
		
		if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))//触摸信号检测
		{		
				flag=Read_ADS2(&X_Addata,&Y_Addata);
				j = X_Addata;
				j = j*250;
				i = TchScr_Xmax-TchScr_Xmin;
				lx= j/i;
				j = Y_Addata;
				j = j*400;
				i = TchScr_Ymax-TchScr_Ymin;
				ly=j/i;
			
				if (flag)//检测到处触摸
				{
						switch (page)//当前页面触摸检测，更改page值
						{	
								case 0:
										if (keycheck(lx,ly,4,4,232,154))//选择调音功能
										{
												Rechangle(4,4,232,154,color[2]);
												Drawsingle(60,4,120,120,1800,color[0],color[2],tune);
												LCD_ShowString(24,122,color[0],color[2],"Guitar Tuner");
												page++;
												change=1;
												break;
										}
										if (keycheck(lx,ly,4,162,232,154))//选择和弦分析功能
										{
												Rechangle(4,162,232,154,color[2]);
												Drawsingle(60,162,120,120,1800,color[0],color[2],chord);
												LCD_ShowString(8,280,color[0],color[2],"Chord Analysis");
												break;
										}
										
								case 1:
										if (keycheck(lx,ly,4,2,232,83))//选吉他
										{
												Rechangle(4,2,232,83,color[2]);
												Drawsingle(30,2,120,80,1200,color[0],color[2],guitar);
												LCD_ShowString(120,52,color[0],color[2],"Guitar");
												page++; 
												change=1;
												break;
										}
										if (keycheck(lx,ly,4,87,232,83))//选贝司
										{
												Rechangle(4,87,232,83,color[2]);
												Drawsingle(30,87,120,80,1200,color[0],color[2],bass);
												LCD_ShowString(136,137,color[0],color[2],"Bass");
												page++; 
												change=1;
												break;
										}
										if (keycheck(lx,ly,4,172,232,83))//选尤克里里
										{
												Rechangle(4,172,232,83,color[2]);
												Drawsingle(20,172,120,80,1200,color[0],color[2],ukulele);
												LCD_ShowString(112,222,color[0],color[2],"Ukulele");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,4,257,114,62))//返回
										{
												Rechangle(4,257,114,62,color[2]);
												Drawsingle(35,270,48,36,216,color[0],color[2],arrowleft);
												page--;
												change=1;
												break;
										}
								
								case 2:
										if (keycheck(lx,ly,4,4,114,80))    // 一弦
										{	 
												Rechangle(4,4,114,80,color[2]);
												LCD_ShowString(5,46,color[0],color[2],"String1");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,122,4,114,80))    // 二弦
										{	 
												Rechangle(122,4,114,80,color[2]);
												LCD_ShowString(123,46,color[0],color[2],"String2");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,4,88,114,80))    // 三弦
										{
												Rechangle(4,88,114,80,color[2]);
												LCD_ShowString(5,130,color[0],color[2],"String3");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,122,88,114,80))    // 四弦
										{	 
												Rechangle(122,88,114,80,color[2]);
												LCD_ShowString(123,130,color[0],color[2],"String4");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,4,172,114,80))    // 五弦
										{	 
												Rechangle(4,172,114,80,color[2]);
												LCD_ShowString(5,214,color[0],color[2],"String5");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,122,172,114,80))    // 六弦
										{
												Rechangle(122,172,114,80,color[2]);
												LCD_ShowString(123,214,color[0],color[2],"String6");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,4,257,114,62))    // 返回
										{
											  Rechangle(4,257,114,62,color[2]);
												Drawsingle(35,270,48,36,216,color[0],color[2],arrowleft);
												page--;
												change=1;
												break;
										}
										
								case 3:
										if(keycheck(lx,ly,3,4,76,59))    // A
										{
												Rechangle(3,4,76,59,color[2]);
												LCD_ShowString(33,22,color[0],color[2],"A");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,82,4,76,59))    // #A
										{
												Rechangle(82,4,76,59,color[2]);
												LCD_ShowString(104,22,color[0],color[2],"#A");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,161,4,76,59))    // B
										{	
												Rechangle(161,4,76,59,color[2]);
												LCD_ShowString(191,22,color[0],color[2],"B");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,3,67,76,59))    // C
										{	
												Rechangle(3,67,76,59,color[2]);
												LCD_ShowString(33,85,color[0],color[2],"C");
												page++; 
												change=1; 
												break;
										}
										if(keycheck(lx,ly,82,67,76,59))    // #C
										{
												Rechangle(82,67,76,59,color[2]);
												LCD_ShowString(104,85,color[0],color[2],"#C");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,161,67,76,59))    // D
										{
												Rechangle(161,67,76,59,color[2]);
												LCD_ShowString(191,85,color[0],color[2],"D");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,3,130,76,59))    // #D
										{
												Rechangle(3,130,76,59,color[2]);
												LCD_ShowString(25,148,color[0],color[2],"#D");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,82,130,76,59))    // E
										{
												Rechangle(82,130,76,59,color[2]);
												LCD_ShowString(112,148,color[0],color[2],"E");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,161,130,76,59))    // F
										{
												Rechangle(161,130,76,59,color[2]);
												LCD_ShowString(191,148,color[0],color[2],"F");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,3,193,76,59))    // #F
										{
												Rechangle(3,193,76,59,color[2]);
												LCD_ShowString(25,211,color[0],color[2],"#F");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,82,193,76,59))    // G
										{	
												Rechangle(82,193,76,59,color[2]);
												LCD_ShowString(112,211,color[0],color[2],"G");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,161,193,76,59))    // #G
										{
												Rechangle(161,193,76,59,color[2]);
												LCD_ShowString(183,211,color[0],color[2],"#G");
												page++; 
												change=1; 
												break;
										}
										if (keycheck(lx,ly,4,257,114,62))    // 返回
										{
												Rechangle(4,257,114,62,color[2]);
												Drawsingle(35,270,48,36,216,color[0],color[2],arrowleft);
												page--;
												change=1;
												break;
										}
										
						case 4:
								if(keycheck(lx,ly,4,257,114,62))    // 返回
								{
										Rechangle(4,257,114,62,color[2]);
										Drawsingle(35,270,48,36,216,color[0],color[2],arrowleft);
										page--;
										change=1;
										break;
								} 		 
						}			
						flag=0;	
				}
		}
		 
		LCD_CS (1);    // 关闭片选使能	
   }
 }
 
unsigned char keycheck(uint lx,uint ly,uint x1,uint y1,uint x,uint y)    // 检测触摸位置是否在某区域中
{  
		if((lx<x1+x-1)&&(ly<y1+y-1)&&(lx>x1)&&(ly>y1))
		{ 
			return 1;
		}
		else return 0;
}