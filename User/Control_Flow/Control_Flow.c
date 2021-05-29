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
��47��50��Ϊֱ��

||��
&&��

�漰��־λ��ֵ�ģ��ж�������Ҫ������һ����־λ�����

�������뻷��Ҫ���Ե����룬��Ҫ�Լ�ƭ�Լ�

ѹ��Ϊ1����ѹΪ0
ѹ����ƣ���ѹ����
*/


int left,mid_l,mid_r,right,states;
static int flag=0;


void Follow_line()
{
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	if((flag!=1)&(mid_l==1)&(right==0))//��ƫ
	{
		states=1;//�����ҿ�
	}
	if((flag!=1)&(mid_r==1)&(left==0))//��ƫ
	{
		states=2;//�������
	}
}

void Plan_A(void)
{
	#if 1
	printf("flag=%d\n",flag);
	
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))//����ѹ�� �� flagΪ0
	{
		Car_Fore(50);//ֱ�� ��ѭ�ߵ�
		flag=1;
	}

	if((flag==1)&(left==1)|(mid_l==1)|(mid_r==1)|(right==1))//flagΪ0 �� ��һ��ѹ����
	{
		flag=2;//��ʼѲ��ģʽ
	}
	if((flag==1)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//ȫѹ���߹�A��
	{
		//��һ��ʶ�𵽺��ߣ�Ҳ����A��
		Car_Fore(50);		
		SysTick_Delay_Ms(1000);
		Car_Stop();
		flag=2;
	}

	switch(states)//�������״̬
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;//��ת
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;//��ת
		case 3: PWMA_UP(47),PWMB_UP(50);break;//ֱ��
		case 4: PWMB_STOP(),PWMA_STOP();break;//ͣ��
	}
	#endif
/*==========================================================================================================================================================================*/			
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
	printf ("Pitch=%f \n",(Pitch-3.5));
	#endif
}

