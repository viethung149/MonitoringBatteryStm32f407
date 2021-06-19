#include "timer.h"
#include "type.h"
void TIMER_interupt_config(void)
{
	TIM_TimeBaseInitTypeDef tim_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	tim_struct.TIM_Period = 5000000-1;
	tim_struct.TIM_Prescaler = (uint16_t)(SystemCoreClock/2/1000000)-1;
	tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &tim_struct);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  //configure interrup timer 2
	NVIC_InitTypeDef nvic_struct;
	nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = TIMER_ADC_READ;
	nvic_struct.NVIC_IRQChannelSubPriority =0;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_struct);
}

void TIMER_read_button(int period)
{
	TIM_TimeBaseInitTypeDef tim_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	tim_struct.TIM_Period = 4199;
	int presscaler = 20*period;
	tim_struct.TIM_Prescaler = presscaler;
	//tim_struct.TIM_ClockDivision = 0;
	tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &tim_struct);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, ENABLE	);
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);	
	NVIC_InitTypeDef nvic_struct;
	nvic_struct.NVIC_IRQChannel = TIM5_IRQn;
	nvic_struct.NVIC_IRQChannelPreemptionPriority =TIMER_READ_BUTTON;
	nvic_struct.NVIC_IRQChannelSubPriority =0;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_struct);
}