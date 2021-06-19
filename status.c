#include "status.h"

void STATUS_pin_peripheral_config(){
	  // PC0 start/stop
		// PC1 package 1
		// PC2 package 2
	  // PC3 Fan 1
		// PC4 Fan 2
		// PC5 timer interrupt read adc
		// PC6 RX uart
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		GPIO_InitTypeDef GPIO_config;
		GPIO_config.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_config.GPIO_OType=GPIO_OType_PP;
		GPIO_config.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_config.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_config.GPIO_Pin=GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init (GPIOC,&GPIO_config);
}

void STATUS_off_all_peripheral(){
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	GPIO_SetBits(GPIOC,GPIO_Pin_3);
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
}