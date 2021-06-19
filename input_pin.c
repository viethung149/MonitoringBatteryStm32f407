#include "input_pin.h"
void INPUT_Pin_config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitTypeDef GPIO_config;
  //set pin for external interrup Pin PD2 -> 5 button package1, package2, fan1, fan2
	GPIO_config.GPIO_Mode=GPIO_Mode_IN;
	GPIO_config.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7;
	GPIO_config.GPIO_OType=GPIO_OType_PP;
	GPIO_config.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_config.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_config);
}