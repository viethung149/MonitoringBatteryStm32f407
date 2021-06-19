#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
void TIMER_interupt_config(void);
void TIMER_read_button(int period);
#endif