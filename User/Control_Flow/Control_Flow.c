#include "Control_Flow.h"
#include "stm32f10x.h"
#include "bsp_Find_Num.h"
#include "bsp_usart.h"
#include "MPU6050.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "Buzzer.h"
#include "Delay.h"
#include "bsp_SysTick.h"
#include "Filter.h"


/*
�������뻷��Ҫ���Ե����룬��Ҫ�Լ�ƭ�Լ�
*/


int left,mid_l,mid_r,right,states;
int flag=0;
float a[10]={0};
int temp=0;
float filPitch=0.00;
int OUT;
int KP=10,KI=0,KD=0;

int Position_PID(int Encoder , int Target);

void Plan_A(void)
{
#if 1
/*
����Ϊ���ݲɼ����������ڵ�����ˮƽΪ 2.7 ����ͷ̧�߶�����󣬳�β̧�߶�����С��20��������ȶ�������������û�� 5����ͷ��Ϊ 2.9����ͷ��Ϊ 3.2��
�ڰ������ݷ�Χ�� 11.2�� -4.3 ֮�䣻����ƽ��ʱ��ֵΪ 0��
*/
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	//printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);

	Read_DMP();
	//printf ("Pitch=%f \n",Pitch);

	for (int i = 0; i < 10; i++)
	{
		a[i]=Pitch;
	}
	for(int i=0;i<10;i++)
	{
		if(a[i]>a[i+1])
		{
			temp=a[i];
            a[i]=a[i+1];
            a[i+1]=temp;
		}
	}
	filPitch = (a[4]+a[5])/2;
	//printf ("filPitch=%f \n",filPitch);
	OUT=Position_PID(filPitch , 0);
	printf("OUT=%d,filPitch=%f \n",OUT,filPitch);
#endif


#if 1
/*
����Ϊһ���򵥵�Ѳ�߳���ѹ��Ϊ1����ѹΪ0��ѹ����ƣ���ѹ���ƣ�һ��ʼû���ҵ������е�ȫ����δѹ�ߡ�
*/
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))
	{
		states=3;//ֱ��
	}
	if((mid_l==1)&(right==0))//��ƫ
	{
		states=1;//��ת
		flag=1;
	}
	if((mid_r==1)&(left==0))//��ƫ
	{
		states=2;//��ת
		flag=2;
	}
	
	switch(states)//�������״̬
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;//��ת
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;//��ת
		case 3: PWMA_UP(47),PWMB_UP(50);break;//ֱ��
		case 4: PWMB_STOP(),PWMA_STOP();break;//ͣ��
		case 5: PWMA_BACK(50);PWMB_BACK(50);break;//����
	}
	//printf("flag=%d \n",flag);
#endif


#if 1
/*
����Ϊ�����ΰ�����ƽ�����
����������㣬������ 7.72V ʱ
A UP 45�Լ��ܶ� 40�Լ��Ͷ�������    BACK 45�ջ� 40һ�㶼����
B UP 50���ܴ� 40�����Ĳ��� 45Ҳ���� BACK 40Ҳ���� 45�ܺ�
*/
	if(filPitch>10)
	{
		flag=3;//�ϰ��־
	}
	if((flag==3)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//ȫѹ���߹�A��
	{
		flag=4;//����һ�����߱�־
	}
	if(flag==4)
	{
		if(filPitch> 1 )
		{
			PWMA_UP(OUT);
			PWMB_UP(OUT);
		}
		if(filPitch< -1 )
		{
			OUT=-OUT;
			PWMA_BACK(OUT);
			PWMB_BACK(OUT);
		}
	}
#endif
}

int Position_PID(int Encoder , int Target)
{
	static float Bias,Pwm,Intergral_Bias,Last_Bias;

	Bias=Encoder-Target;
	Intergral_Bias+=Bias;
	Pwm=KP*Bias+KI*Intergral_Bias+KD*(Bias-Last_Bias);
	Last_Bias=Bias;
	return Pwm;
}

