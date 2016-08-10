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
   
    nv2=NPT/2;    // ��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
    nm1=NPT-1; 
    for (i=0;i<nm1;i++)        
    {	
        if (i<j)    // ���i<j,�����б�ַ
        {
            t=xin[j];           
            xin[j]=xin[i];
            xin[i]=t;
        }
        k=nv2;    // ��j����һ����λ��
        while (k<=j)    // ���k<=j,��ʾj�����λΪ1   
        {           
             j=j-k;    // �����λ���0
             k=k/2;    // k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
        }
        j=j+k;    // ��0��Ϊ1
  }
                         
		int le,lei,ip;    // FFT����ˣ�ʹ�õ����������FFT����
		f=NPT;
		for (l=1;(f=f/2)!=1;l++);    // ����l��ֵ����������μ���
		for (m=1;m<=l;m++)    // ���Ƶ��νἶ��
		{
		// m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
				le=2<<(m-1);    // le���ν���룬����m�����εĵ��ν����le��
				lei=le/2;    // ͬһ���ν��вμ����������ľ���
				u.real=1.0;    // uΪ���ν�����ϵ������ʼֵΪ1
				u.imag=0.0;
				w.real=cos(PI/lei);    // wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
				w.imag=-sin(PI/lei);
				for(j=0;j<=lei-1;j++)    // ���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
				{
						for(i=j;i<=NPT-1;i=i+le)    // ����ͬһ���ν����㣬������ϵ����ͬ���ν�
						{
								ip=i+lei;    // i��ip�ֱ��ʾ�μӵ�������������ڵ�
								t=EE(xin[ip],u);    // �������㣬�����ʽ
								xin[ip].real=xin[i].real-t.real;
								xin[ip].imag=xin[i].imag-t.imag;
								xin[i].real=xin[i].real+t.real;
								xin[i].imag=xin[i].imag+t.imag;
						}
						u=EE(u,w);//�ı�ϵ����������һ����������
				}
		}
  
}