#ifndef  _UART_H
#define _UART_H
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "type.h"
extern int counter_tx;
void UART_init_config(void);
void UART_pin_config(void);

void UART_init_config_esp(void);
void UART_pin_config_esp(void);

void UART_PutChar(BYTE c);
void UART_PutString(BYTE* str);

void UART_PutChar_esp(BYTE c);
void UART_PutString_esp(BYTE* str);

uint16_t UART_GetChar(void);
void UART_config_stm32f103(void);
void UART_pin_stm32f103(void);
void UART_PutChar_stm32f13(BYTE c);
void UART_PutString_stm32f103(BYTE* str);
#endif