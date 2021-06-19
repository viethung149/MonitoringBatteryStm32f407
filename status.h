#ifndef _STATUS_H
#define _STATUS_H
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
void STATUS_pin_peripheral_config(void);
void STATUS_off_all_peripheral(void);
#endif