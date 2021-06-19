#ifndef  _DELAY_H
#define _DELAY_H
#include "stm32f4xx.h"
#include "system_timetick.h"
static __IO uint32_t TimingDelay;// bien dem  cua ham sys tick
/* Private function prototypes -----------------------------------------------*/
void timetick_configure(void); //nho khoi tao ham nay trc
void Delay_ms(__IO uint32_t nTime);// ho?t d?ng t?t dã test
void Dellay_us(uint16_t period);
void Dellay_ms_timer4(int time);
#endif