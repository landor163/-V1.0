#include "Balance.h"
#include "System.h"
#include "stm32f10x.h"
#include "MPU6050.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "stm32f10x.h"


double PID_Position (PID *pid , int TarVal , int StaVal)
{
	int ParErr,//�ֲ���ǰ���
		Out;//ʵ�����
	
	ParErr = TarVal - StaVal;
	pid->Error += pid->Int * ParErr;//�����ʵ��޷���������û��
	Out = pid->Pro * ParErr
		+ pid->Error
		+ pid->Der * (ParErr - pid->LastErr);

	return Out;
}

