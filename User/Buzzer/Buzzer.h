#ifndef Buzzer_H
#define Buzzer_H


#include "stm32f10x.h"


/*B12�˿�*/
#define Buz_GPIO_PIN		GPIO_Pin_12
#define Buz_GPIO_PORT		GPIOB
#define Buz_GPIO_CLK		RCC_APB2Periph_GPIOB

/*����ߵ�ƽ-��*/
#define Buz_ON			GPIO_SetBits(Buz_GPIO_PORT,Buz_GPIO_PIN)
/*����͵�ƽ-����*/
#define Buz_OFF			GPIO_ResetBits(Buz_GPIO_PORT,Buz_GPIO_PIN)


void Buz_GPIO_Config(void);
void BEEP(int x);
#endif

