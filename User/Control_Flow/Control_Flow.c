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


/*
����ϸ�ڣ����ܵ������պÿ���ʶ�𵽰׹����ֵ
ѹ�ߣ���ƣ�Ϊ1��
��ѹ�ߣ�Ϊ0��

��47��50��Ϊֱ��

||��
&&��

�漰��־λ��ֵ�ģ��ж�������Ҫ������һ����־λ�����
*/


void Plan_A(void)
{
	
	int left,mid_l,mid_r,right;

	static int flag,states;

	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	#if 1
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))//����ѹ��
	{
		states=3;//ֱ��
	}
	if((flag==0)&(left==1)|(mid_l==1)|(mid_r==1)|(right==1))//��һ��ѹ����
	{
		flag=1;
	}
	if((flag==1)&(mid_l==1)&(right==0))//��ƫ
	{
		states=1;//�����ҿ�
		if(states==1)
		{
			flag=3;
		}
	}
	if((flag==1)&(mid_r==1)&(left==0))//��ƫ
	{
		states=2;//�������

	}
	if((flag==1)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//ȫѹ���߹�A��
	{
		states=3;
		//delay_ms(1000);
		SysTick_Delay_Ms(1000);
		flag=2;
	}
	if((flag==2)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//�ڶ���ȫѹ����
	{
		states=4;
	}
	#endif

	printf("flag=%d\n",flag);

	switch(states)
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;
		case 3: PWMA_UP(47),PWMB_UP(50);break;
		case 4: PWMB_STOP(),PWMA_STOP();break;
	}
/*=================================================================================================================================================================================*/			
	#if 0	//���Ժ��⴫������ֵ
	int left,mid_l,mid_r,right;
	
	left=LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	
	printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);
	#endif
	
	#if 0
	PWMA_UP(47);
	PWMB_UP(50);
	#endif
	
	#if 0	//�Ƕ�
	Read_DMP();
	printf ("Pitch=%f \n",Pitch)��
	#endif
}

