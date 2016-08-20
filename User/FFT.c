#include "math.h"
#include "FFT.h"

struct compx EE(struct compx a,struct compx b)      
{
		struct compx c;
		c.real=a.real*b.real-a.imag*b.imag;
		c.imag=a.real*b.imag+a.imag*b.real;
		return(c);
}

void FFT(struct compx *xin)
{
		int f,m,nv2,nm1,i,k,l,j=0;
		struct compx u,w,t;
   
		// 变址运算，即把自然顺序变成倒位序，采用雷德算法
    nv2=NPT/2;
    nm1=NPT-1; 

    // 如果i<j,即进行变址
    for (i=0;i<nm1;i++)        
    {	
        if (i<j)
        {
            t=xin[j];           
            xin[j]=xin[i];
            xin[i]=t;
        }
				
		    // 求j的下一个倒位序
        k=nv2;
				
		    // 如果k<=j,表示j的最高位为1
        while (k<=j)   
        {          
						// 把最高位变成0
            j=j-k;
					  // k/2，比较次高位，依次类推，逐个比较，直到某个位为0
            k=k/2;
        }
        j=j+k;    // 把0改为1
  }

    // FFT运算核，使用蝶形运算完成FFT运算	
		int le,lei,ip;
		f=NPT;
	
    // 计算l的值，即计算蝶形级数
		for (l=1;(f=f/2)!=1;l++);
	
	  // 控制蝶形结级数
		for (m=1;m<=l;m++)
		{
				// m表示第m级蝶形，l为蝶形级总数l=log（2）N
		    // le蝶形结距离，即第m级蝶形的蝶形结相距le点
				le=2<<(m-1);
			
		    // 同一蝶形结中参加运算的两点的距离
				lei=le/2;
			
		    // u为蝶形结运算系数，初始值为1
				u.real=1.0;
				u.imag=0.0;
			
		    // w为系数商，即当前系数与前一个系数的商
				w.real=cos(PI/lei);
				w.imag=-sin(PI/lei);
			
		    // 控制计算不同种蝶形结，即计算系数不同的蝶形结
				for(j=0;j<=lei-1;j++)
				{
					
				    // 控制同一蝶形结运算，即计算系数相同蝶形结
						for(i=j;i<=NPT-1;i=i+le)
						{
							
						    // i，ip分别表示参加蝶形运算的两个节点
								ip=i+lei;
							
						    // 蝶形运算
								t=EE(xin[ip],u);
								xin[ip].real=xin[i].real-t.real;
								xin[ip].imag=xin[i].imag-t.imag;
								xin[i].real=xin[i].real+t.real;
								xin[i].imag=xin[i].imag+t.imag;
						}
						
						//改变系数，进行下一个蝶形运算
						u=EE(u,w);
				}
		}
  
}
