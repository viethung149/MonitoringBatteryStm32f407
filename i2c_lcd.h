#ifndef __I2C_LCD_H
#define __I2C_LCD_H
#include "stm32f4xx.h" 

#define PCF8574A_Address    0x4E
#define I2C_Chanel      		I2C2
extern void delay_ms(uint16_t delay);
void lcd_Write_byte(char data);
void lcd_init (void);
void lcd_Data_Write(char data);
void lcd_Control_Write(char data);
void lcd_send_string (char *str);
void Delete_LCD(void)            ;

#endif
