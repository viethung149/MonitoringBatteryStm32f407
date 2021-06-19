#include "exti.h"
#include "type.h"
void EXTI_Pin_config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitTypeDef GPIO_config;
  //set pin for external interrup Pin PD2 -> 5 button 
	// pin 6 handshark stm32f103
	// pin 8 handshark esp32
	GPIO_config.GPIO_Mode=GPIO_Mode_IN;
	GPIO_config.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_6;
	GPIO_config.GPIO_OType=GPIO_OType_PP;
	GPIO_config.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_config.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_config);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource6);//handshark PD6 stm32f1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource8);//handshark PD8 esp32
}
void EXTI_line_config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitTypeDef   NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXTI_STM32F103;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXTI_ESP32;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	EXTI_Init(&EXTI_InitStructure);
}