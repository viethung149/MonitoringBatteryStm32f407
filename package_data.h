#ifndef _PACKAGE_DATA_H
#define _PACKAGE_DATA_H
#include "stm32f4xx.h"
#include "type.h"
#include "spi.h"
#include "uart.h"
#include "delay.h"
#include "adc.h"
extern BYTE buffer_tx_uart[];
extern BYTE buffer_tx_spi[];
extern BYTE buffer_tx_spi_esp[];

extern float voltage_module1[];
extern float voltage_module2[];
extern float current_voltage[];
extern float current_a[];

extern Status CHANNEL_15_IO;
extern Status CHANNEL_14_IO;
extern Status CHANNEL_13_IO;

extern B_Voltage_status Flag_battery[];
extern B_Voltage_status Flag_temp[];
extern Status Flag_pheripheral[];
extern Status Flag_blancing[];
extern B_Voltage_status Flag_emer[];

extern Status FAIL_CURRENT_P1;
extern Status FAIL_CURRENT_P2;
extern Status FAIL_CURRENT_ALL;

#define START_HEADER_INFO  0
#define START_DATA_INFO    1
#define START_STATUS_INFO  129
#define START_CRC_INFO     133
#define START_END_INFOR    134

#define START_HEADER_HUMAN 0
#define START_DATA_HUMAN 1
#define START_CRC_HUMAN 5
#define START_END_HUMAN 134

#define START_HEADER_EMER 0
#define START_DATA_EMER 1
#define START_CRC_EMER 5
#define START_END_EMER 134

#define SPI_ESP_HEADER             0
#define SPI_ESP_VOLTAGE            1
#define SPI_ESP_TEMPERATURE        33
#define SPI_ESP_CURRENT            65
#define SPI_ESP_STATUS_VOLTAGE     77
#define SPI_ESP_STATUS_TEMPERATURE 78
#define SPI_ESP_STATUS_CURRENT     79
#define SPI_ESP_STATUS_PHERIPHERAL 80
#define SPI_ESP_STATUS_BLANCE      81
#define SPI_ESP_ADDING             82
#define SPI_ESP_CRC                90
#define SPI_ESP_END                91
void reset_buffer_tx(BYTE buffer_tx[],int size_buffer_tx);
void init_data_test(float voltage_module1[],
										int size_module1,
										float voltage_module2[],
										int size_module2,
										Status Flag_battery[],
										int size_battery,
										Status Flag_temp[],
										int size_temp);
// human infor									
								
void package_header( TX_types types, BYTE buffer_tx[], int startIndex );

void package_data_infor(float voltage_module1[],
												int size_module1,
												float voltage_module2[],
												int size_module2,
												BYTE buffer_tx[],
												int size_buffer_tx,
												int startIndex);
												
void package_status_infor(B_Voltage_status Flag_battery[],
													int size_battery,
													B_Voltage_status Flag_temp[],
													int size_temp,
													BYTE buffer_tx[],
													int size_buffer_tx,
													int startIndex);
													
void package_crc(BYTE buffer_tx[],
									     int size_buffer_tx,
									     int startIndex);
void package_end (BYTE buffer_tx[],
									int size_buffer,
									int startIndex);

//-- human data

void package_data_human(Status Flag_pheripheral[],
												int size_flag_pheripheral,
												BYTE buffer_tx[],
												int size_buffer_tx,
												int startIndex);
// -- emer
void package_data_emer(B_Voltage_status Flag_emer[], 
											int size_flag_emer,
											BYTE buffer_tx[],
											int size_buffer_tx,
											int startIndex);												

//final 
void package_infor(void);
// human package have 5 byte
// HEADER, DATA, CRC, END 
void package_human(void);
// emer packet send flag that tell the status of the bin baterry
// V > 4.2 flag = MAX,  V< 0 flag = MIN , nothing wrong is NORMAL
// temp > 100 flag = MAX, temp< 0 flag = MIN, nothing wrong is NORMAL
void package_emer(void);											
void set_emer_flag(float* battery_voltage,
									 int size_battery,
									 float* temp_voltage,
									 int size_temp,
									 B_Voltage_status* Flag_emer,
									 int size_emer_flag);
void package_infor_spi();
void package_human_spi();
void package_emer_spi();
void set_flag(B_Voltage_status Flag[], int index , Style what,float value);
void get_current(float current_voltage[],float current_a[]);
									 
void package_infor_spi_esp();
void package_voltage(BYTE buffer_tx_spi_esp[],float voltage_module2[], int size,int startIndex);
void package_temperature(BYTE buffer_tx_spi_esp[],float voltage_module1[], int size,int startIndex);
void package_current(BYTE buffer_tx_spi_esp[],float current_a[], int size,int startIndex);
void package_status_voltage(BYTE buffer_tx_spi_esp[], B_Voltage_status Voltage_status[],int size, int startIndex);
void package_status_temperature (BYTE buffer_tx_spi_esp[], B_Voltage_status Temp_status[],int size, int startIndex);
void package_status_current (BYTE buffer_tx_spi_esp[], int startIndex);
void package_status_pheripheral (BYTE buffer_tx_spi_esp[], Status Flag_pheripheral[],int size, int startIndex);
void package_status_balancing(BYTE buffer_tx_spi_esp[],Status Flag_blancing[], int size, int startIndex); 
									 
#endif