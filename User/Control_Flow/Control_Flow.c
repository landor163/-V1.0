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
�������뻷��Ҫ���Ե����룬��Ҫ�Լ�ƭ�Լ�

ѹ��Ϊ1����ѹΪ0
ѹ����ƣ���ѹ����
*/


int left,mid_l,mid_r,right,states;
static int flag=0;


//void delay_us(int time)//���뼶��ʱ
//{    
//   u16 i=0;  
//   while(time--)
//   {
//      i=10;  //�Լ�����
//      while(i--) ;    
//   }
//}

void Follow_line()
{
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	//printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);

	Read_DMP();
	printf ("Pitch=%f \n",(Pitch-3.5));

	if((mid_l==1)&(right==0))//��ƫ
	{
		states=1;//��ת
	}
	if((mid_r==1)&(left==0))//��ƫ
	{
		states=2;//��ת
	}
	switch(states)//�������״̬
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;//��ת
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;//��ת
		case 3: PWMA_UP(47),PWMB_UP(50);break;//ֱ��
		case 4: PWMB_STOP(),PWMA_STOP();break;//ͣ��
	}
}

void Plan_A(void)
{
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))//����ѹ�� �� flagΪ0
	{
		Car_Fore(50);//ֱ�� ��ѭ�ߵ�
	}

	if((flag==0)&(left==1)|(mid_l==1)|(mid_r==1)|(right==1))//flagΪ0 �� ��һ��ѹ����
	{
		flag=1;//��ʼѲ��ģʽ��ֻʵ����״̬�л�
	}
	if((flag==1)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//ȫѹ���߹�A��
	{
		//��һ��ʶ�𵽺��ߣ�Ҳ����A��
		Car_Fore(50);		
		delay_us(1000);
		Car_Stop();
		flag=2;
	}
	if(flag==2)
	{
		BEEP(500);
	}
}

