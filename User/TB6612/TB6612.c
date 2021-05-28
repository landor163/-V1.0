#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "stm32f10x.h"


void AIN1_GPIO_Config(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(AIN1_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = AIN1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(AIN1_GPIO_PORT,&GPIO_InitStruct);
}

void AIN2_GPIO_Config(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(AIN2_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = AIN2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(AIN2_GPIO_PORT,&GPIO_InitStruct);
}

void BIN1_GPIO_Config(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(BIN1_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = BIN1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BIN1_GPIO_PORT,&GPIO_InitStruct);
}

void BIN2_GPIO_Config(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(BIN2_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = BIN2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BIN2_GPIO_PORT,&GPIO_InitStruct);
}


/*
��L298N�ķ���Ϊǰ�������ذ�ķ���Ϊ��
AIN����ߵ�����
1 OFF  2 ON��ǰ��
1 ON   2OFF�Ǻ���
BIN���ұߵ�����
1 ON   2OFF��ǰ��
1 OFF  2 ON�Ǻ���
*/

void PWMA_UP(int a)
{
	GENERAL_ccr1_Mode_Config(a);//A6
	AIN1_OFF;//B0
	AIN2_ON;//B1
}

void PWMA_BACK(int a)
{
	GENERAL_ccr1_Mode_Config(a);//A6
	AIN1_ON;//B0
	AIN2_OFF;//B1
}

void PWMA_STOP(void)
{
	GENERAL_ccr1_Mode_Config(0);//A6
	AIN1_ON;//B0
	AIN2_ON;//B1
}

void PWMB_UP(int a)
{
	GENERAL_ccr2_Mode_Config(a);//A6
	BIN1_ON;//B0
	BIN2_OFF;//B1
}

void PWMB_BACK(int a)
{
	GENERAL_ccr2_Mode_Config(a);//A6
	BIN1_OFF;//B0
	BIN2_ON;//B1
}

void PWMB_STOP(void)
{
	GENERAL_ccr2_Mode_Config(0);//A6
	BIN1_ON;//B0
	BIN2_ON;//B1
}
