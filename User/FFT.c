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
   
		// ��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
    nv2=NPT/2;
    nm1=NPT-1; 

    // ���i<j,�����б�ַ
    for (i=0;i<nm1;i++)        
    {	
        if (i<j)
        {
            t=xin[j];           
            xin[j]=xin[i];
            xin[i]=t;
        }
				
		    // ��j����һ����λ��
        k=nv2;
				
		    // ���k<=j,��ʾj�����λΪ1
        while (k<=j)   
        {          
						// �����λ���0
            j=j-k;
					  // k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
            k=k/2;
        }
        j=j+k;    // ��0��Ϊ1
  }

    // FFT����ˣ�ʹ�õ����������FFT����	
		int le,lei,ip;
		f=NPT;
	
    // ����l��ֵ����������μ���
		for (l=1;(f=f/2)!=1;l++);
	
	  // ���Ƶ��νἶ��
		for (m=1;m<=l;m++)
		{
				// m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
		    // le���ν���룬����m�����εĵ��ν����le��
				le=2<<(m-1);
			
		    // ͬһ���ν��вμ����������ľ���
				lei=le/2;
			
		    // uΪ���ν�����ϵ������ʼֵΪ1
				u.real=1.0;
				u.imag=0.0;
			
		    // wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
				w.real=cos(PI/lei);
				w.imag=-sin(PI/lei);
			
		    // ���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
				for(j=0;j<=lei-1;j++)
				{
					
				    // ����ͬһ���ν����㣬������ϵ����ͬ���ν�
						for(i=j;i<=NPT-1;i=i+le)
						{
							
						    // i��ip�ֱ��ʾ�μӵ�������������ڵ�
								ip=i+lei;
							
						    // ��������
								t=EE(xin[ip],u);
								xin[ip].real=xin[i].real-t.real;
								xin[ip].imag=xin[i].imag-t.imag;
								xin[i].real=xin[i].real+t.real;
								xin[i].imag=xin[i].imag+t.imag;
						}
						
						//�ı�ϵ����������һ����������
						u=EE(u,w);
				}
		}
  
}
