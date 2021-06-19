#include "package_data.h"
void package_infor(){
	printf("5. infor sent \n");
	package_header( INFO, buffer_tx_uart, START_HEADER_INFO);	
	package_data_infor(voltage_module1,SIZE_MODULE_1,voltage_module2,SIZE_MODULE_2, buffer_tx_uart,SIZE_BUFFER_TX,START_DATA_INFO);	
	package_status_infor(Flag_battery, SIZE_BATTERY, Flag_temp,SIZE_TEMPERATURE,buffer_tx_uart,SIZE_BUFFER_TX,START_STATUS_INFO);
	package_crc(buffer_tx_uart,SIZE_BUFFER_TX,START_CRC_INFO);
	package_end (buffer_tx_uart,SIZE_BUFFER_TX,START_END_INFOR);
	UART_PutString(buffer_tx_uart);
	reset_buffer_tx(buffer_tx_uart,SIZE_BUFFER_TX);
	printf("5. end infor sent \n");
}
void package_human(){
	printf("6. infor human \n");
	package_header( HUMAN_TOUCH, buffer_tx_uart, START_HEADER_HUMAN);
	package_data_human(Flag_pheripheral,SIZE_PHERIPHERAL,buffer_tx_uart, SIZE_BUFFER_TX,START_DATA_HUMAN);
	package_crc(buffer_tx_uart,SIZE_BUFFER_TX,START_CRC_HUMAN);
	package_end(buffer_tx_uart,SIZE_BUFFER_TX,START_END_HUMAN);
	UART_PutString(buffer_tx_uart);
	reset_buffer_tx(buffer_tx_uart,SIZE_BUFFER_TX);
	printf("6. infor human \n");
}
void package_emer(){
	package_header( EMER, buffer_tx_uart, START_HEADER_EMER);
	package_data_emer(Flag_emer,SIZE_EMER,buffer_tx_uart, SIZE_BUFFER_TX,START_DATA_EMER);
	package_crc(buffer_tx_uart,SIZE_BUFFER_TX,START_CRC_EMER);
	package_end(buffer_tx_uart,SIZE_BUFFER_TX,START_END_EMER);
	UART_PutString(buffer_tx_uart);
	reset_buffer_tx(buffer_tx_uart,SIZE_BUFFER_TX);
}
void package_infor_spi(){
	package_header( INFO, buffer_tx_spi, START_HEADER_INFO);	
	package_data_infor(voltage_module1,SIZE_MODULE_1,voltage_module2,SIZE_MODULE_2, buffer_tx_spi,SIZE_BUFFER_TX,START_DATA_INFO);	
	package_status_infor(Flag_battery, SIZE_BATTERY, Flag_temp,SIZE_TEMPERATURE,buffer_tx_spi,SIZE_BUFFER_TX,START_STATUS_INFO);
	package_crc(buffer_tx_spi,SIZE_BUFFER_TX,START_CRC_INFO);
	package_end (buffer_tx_spi,SIZE_BUFFER_TX,START_END_INFOR);
	UART_PutString_stm32f103(buffer_tx_spi);
}
void package_human_spi(){
	package_header( HUMAN_TOUCH, buffer_tx_spi, START_HEADER_HUMAN);
	package_data_human(Flag_pheripheral,SIZE_PHERIPHERAL,buffer_tx_spi, SIZE_BUFFER_TX,START_DATA_HUMAN);
	package_crc(buffer_tx_spi,SIZE_BUFFER_TX,START_CRC_HUMAN);
	package_end(buffer_tx_spi,SIZE_BUFFER_TX,START_END_HUMAN);
	GPIO_ResetBits(GPIOA,NSS);
	SPI_send_data(buffer_tx_spi);
	GPIO_SetBits(GPIOA,NSS);
}
void package_emer_spi(){
	package_header( EMER, buffer_tx_spi, START_HEADER_EMER);
	package_data_emer(Flag_emer,SIZE_EMER,buffer_tx_spi, SIZE_BUFFER_TX,START_DATA_EMER);
	package_crc(buffer_tx_spi,SIZE_BUFFER_TX,START_CRC_EMER);
	package_end(buffer_tx_spi,SIZE_BUFFER_TX,START_END_EMER);
  GPIO_ResetBits(GPIOA,NSS);
	SPI_send_data(buffer_tx_spi);
	GPIO_SetBits(GPIOA,NSS);
}
void reset_buffer_tx(BYTE buffer_tx[],int size_buffer_tx)
{
	for(int i =0 ;i<size_buffer_tx; i++){
	buffer_tx[i] = 0x00;
	}
}

void init_data_test(float voltage_module1[],int size_module1,float voltage_module2[],int size_module2,Status Flag_battery[],int size_battery,Status Flag_temp[],int size_temp){
	for(int i =0 ;i< size_module1;i++)
	{
		voltage_module1[i]=3.2;
	}
	for(int i =0 ;i< size_module2;i++)
	{
		voltage_module2[i]=1.1;
	}
	for(int i =0 ;i< size_battery;i++)
	{
		Flag_battery[i]=OFF;
	}
	for(int i =0 ;i< size_temp;i++)
	{
		Flag_temp[i]=ON;
	}
}
void package_header( TX_types types, BYTE buffer_tx[], int startIndex ){
if(types == INFO){
	buffer_tx[startIndex] = 'I';
}
else if (types ==  HUMAN_TOUCH){
	buffer_tx[startIndex] = 'H';
}
else if (types ==  EMER){
	buffer_tx[startIndex] = 'E';
}
else if (types ==  UPLOAD){
	buffer_tx[startIndex] = 'U';
}
else{

}
}

void package_data_infor(float voltage_module1[],int size_module1,float voltage_module2[],int size_module2,BYTE buffer_tx[],int size_buffer_tx,int startIndex){
	union floatToByte temp;		
	for(int i =0 ;i<size_module1;i++){
		temp.variableFloat = voltage_module1[i];
		for(int index = 0 ; index < 4; index ++){
			buffer_tx[startIndex++] = temp.varialbeByte[index];
		}
	}
	for(int i =0 ;i<size_module2;i++){
		temp.variableFloat = voltage_module2[i];
		for(int index = 0 ; index < 4; index ++){
			buffer_tx[startIndex++] = temp.varialbeByte[index];
		}
	}
}
												
void package_status_infor(B_Voltage_status Flag_battery[],int size_battery,B_Voltage_status Flag_temp[],int size_temp,BYTE buffer_tx[],int size_buffer_tx,int startIndex){
	//size temp is 8 so run loop in one time
		for(int i =0 ;i < (size_temp / 8);i++){
				BYTE temp_byte = 0x00;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = (Flag_temp[j] == MIN || Flag_temp[j] == MAX )? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx[startIndex++]=temp_byte;
		}		
	//size battery is 8 so run loop in one time
	for(int i =0 ;i < (size_battery / 8);i++){
				BYTE temp_byte = 0x00 ;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = (Flag_battery[j] == MIN || Flag_battery[j] == MAX) ? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx[startIndex++]=temp_byte;
		}
	  
}
													
void package_crc(BYTE buffer_tx[],int size_buffer_tx,int startIndex){
		BYTE crc = 0x00;
		for(int i = 0; i< startIndex;i++)
		{
			crc += buffer_tx[i];
		}
		buffer_tx[startIndex]=crc;
}
void package_end (BYTE buffer_tx[],int size_buffer,int startIndex){
	buffer_tx[startIndex++] = '\r';
	buffer_tx[startIndex++] = '\n';
}


// data human
void package_data_human(Status Flag_pheripheral[],int size_flag_pheripheral,BYTE buffer_tx[],int size_buffer_tx,int startIndex){
	for(int i =0 ;i < (size_flag_pheripheral / 8);i++){
				BYTE temp_byte = 0x00 ;
		//byte 1: bit 8 package, bit 7 package 2, bit 6 3 fan1, bit 5 fan2
				for(int j = i*8;j< i*8+8;j++){
					BYTE temp_status = Flag_pheripheral[j] == ON ? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx[startIndex++]=temp_byte;
		}
}
// data_emer
void package_data_emer(B_Voltage_status Flag_emer[], int size_flag_emer,BYTE buffer_tx[],int size_buffer_tx,int startIndex){
		for(int i =0 ;i < (size_flag_emer / 8);i++){
				BYTE temp_byte = 0x00 ;
				for(int j = i*8;j< i*8+8;j++){
					BYTE temp_status = (Flag_emer[j] == MAX || Flag_emer[j] == MIN) ? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx[startIndex++]=temp_byte;
		}
}

// set flag emer in battery voltage and temperature
void set_emer_flag(float* battery_voltage,int size_battery,float* temp_voltage,int size_temp,B_Voltage_status* Flag_emer,int size_emer_flag){
	printf("4. set flag \n");
			for(int i = 0 ;i< size_battery ;i++)
			{
				Flag_emer[i] = battery_voltage[i]> 4.2 ? MAX:((battery_voltage[i]<3.2)? MIN : NORMAL); 
			}
			for(int i = 0 ;i< size_temp ;i++)
			{
				Flag_emer[i+8] = temp_voltage[i]> 100 ? MAX:((temp_voltage[i])<0 ? MIN: NORMAL); 
			}
			printf("4. end set flag \n");
}
void set_flag(B_Voltage_status Flag[], int index , Style what,float value){
	if(what == VOLTAGE){
		if(value> 4.2 ){
			// over voltage need to turn of package 1
			Flag[index] = MAX;
		}
		else if(value < 3.2){
			// over discharge need to turn off package 1
			Flag[index] = MIN;
		}
		else
			Flag[index] = NORMAL;
	}
	else if(what == TEMPERATURE){
		// set flag battery temperature
		if(value > 100 ){
			// over voltage need to turn of package 1
			Flag[index] = MAX;
		}
		else if(value < 0){
			// over discharge need to turn off package 1
			Flag[index] = MIN;
		}
		else
			Flag[index] = NORMAL;
	Dellay_us(10);
	}
}

void get_current(float current_voltage[],float current_a[]){
// get data from channel 	13 -14
   current_voltage[0] = ADC_get_voltage_from_channel(ADC_MODULE1,NUMBER_READ_CURRENT,CHANNEL_CURRENT_1,MODULE1,VOLTAGE_REF)*CHANNEL_13;
	 current_voltage[1] = ADC_get_voltage_from_channel(ADC_MODULE1,NUMBER_READ_CURRENT,CHANNEL_CURRENT_2,MODULE1,VOLTAGE_REF_CR1)*CHANNEL_14;
	 current_voltage[2] = ADC_get_voltage_from_channel(ADC_MODULE1,NUMBER_READ_CURRENT,CHANNEL_CURRENT_3,MODULE1,VOLTAGE_REF_CR2)*CHANNEL_15;
	// convert voltage to current 13 -14
	 current_a[0] = voltage_to_current(SENSITIVE_13,current_voltage[0],VOLTAGE_CURRENT_OFFSET,CHANNEL_13_IO);
	 current_a[1] = voltage_to_current(SENSITIVE_14,current_voltage[1],VOLTAGE_CURRENT_OFFSET,CHANNEL_14_IO);
	 current_a[2] = voltage_to_current(SENSITIVE_15,current_voltage[2],VOLTAGE_CURRENT_OFFSET,CHANNEL_15_IO);
}
// set the package to send to esp32
void package_infor_spi_esp(){
	package_header( UPLOAD,buffer_tx_spi_esp, SPI_ESP_HEADER);	
	// add voltage 4*8 bytes
	package_voltage(buffer_tx_spi_esp,voltage_module2,8,SPI_ESP_VOLTAGE);
	// add temperature 4*8 bytes
	package_temperature(buffer_tx_spi_esp,voltage_module1,8,SPI_ESP_TEMPERATURE);
	// add curent 3*8 bytes
	package_current(buffer_tx_spi_esp,current_a,3,SPI_ESP_CURRENT);
	// add status
	package_status_voltage(buffer_tx_spi_esp, Flag_battery,1,SPI_ESP_STATUS_VOLTAGE);
	package_status_temperature(buffer_tx_spi_esp, Flag_temp,1 , SPI_ESP_STATUS_TEMPERATURE);
	package_status_current(buffer_tx_spi_esp,SPI_ESP_STATUS_CURRENT);
	package_status_pheripheral(buffer_tx_spi_esp, Flag_pheripheral, 1, SPI_ESP_STATUS_PHERIPHERAL);
	package_status_balancing(buffer_tx_spi_esp,Flag_blancing, 1, SPI_ESP_STATUS_BLANCE);
	package_crc(buffer_tx_spi_esp,SIZE_BUFFER_ESP_TX,SPI_ESP_CRC);
	package_end (buffer_tx_spi_esp,SIZE_BUFFER_ESP_TX,SPI_ESP_END);
	GPIO_ResetBits(GPIOA,NSS_ESP);
	//Dellay_ms_timer4(10);
	SPI_send_data(buffer_tx_spi_esp);
	Dellay_ms_timer4(1);
	GPIO_SetBits(GPIOA,NSS_ESP);
}
// set voltage spi esp
void package_voltage(BYTE buffer_tx_spi_esp[],float voltage_module2[], int size,int startIndex){
	union floatToByte temp;		
	for(int i =0 ;i<size;i++){
		temp.variableFloat = voltage_module2[i];
		for(int index = 0 ; index < 4; index ++){
			buffer_tx_spi_esp[startIndex++] = temp.varialbeByte[index];
		}
	}
} 
// set temperature spi esp
void package_temperature(BYTE buffer_tx_spi_esp[],float voltage_module1[], int size,int startIndex){
	union floatToByte temp;		
	for(int i =0 ;i<size;i++){
		temp.variableFloat = voltage_module1[i];
		for(int index = 0 ; index < 4; index ++){
			buffer_tx_spi_esp[startIndex++] = temp.varialbeByte[index];
		}
	}
}
// set current spi esp
void package_current(BYTE buffer_tx_spi_esp[],float current_a[], int size,int startIndex){
	union floatToByte temp;		
	for(int i =0 ;i<size;i++){
		temp.variableFloat = current_a[i];
		for(int index = 0 ; index < 4; index ++){
			buffer_tx_spi_esp[startIndex++] = temp.varialbeByte[index];
		}
	}
}
// set status voltage
void package_status_voltage(BYTE buffer_tx_spi_esp[], B_Voltage_status Voltage_status[],int size, int startIndex){
	
		for(int i =0 ;i < size;i++){
				BYTE temp_byte = 0x00;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = (Voltage_status[j] == MIN || Voltage_status[j] == MAX )? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx_spi_esp[startIndex++]=temp_byte;
		}		
}
// set status temperature
void package_status_temperature (BYTE buffer_tx_spi_esp[], B_Voltage_status Temp_status[],int size, int startIndex){
	
		for(int i =0 ;i < size;i++){
				BYTE temp_byte = 0x00;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = (Temp_status[j] == MIN || Temp_status[j] == MAX )? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx_spi_esp[startIndex++]=temp_byte;
		}		
}
// set status pheripheral
void package_status_pheripheral (BYTE buffer_tx_spi_esp[], Status Flag_pheripheral[],int size, int startIndex){
	
		for(int i =0 ;i < size;i++){
				BYTE temp_byte = 0x00;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = Flag_pheripheral[j] == ON? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx_spi_esp[startIndex++]=temp_byte;
		}		
}
//set status current
void package_status_current(BYTE buffer_tx_spi_esp[],int startIndex){
	BYTE temp_byte = 0x00;
	temp_byte |= ((FAIL_CURRENT_P1 == ON)? 0x01: 0x00);
	temp_byte |= ((FAIL_CURRENT_P2 == ON)? 0x02: 0x00);
	temp_byte |= ((FAIL_CURRENT_ALL == ON)? 0x04: 0x00);
	buffer_tx_spi_esp[startIndex++] = temp_byte;
}
//set status balance
void package_status_balancing(BYTE buffer_tx_spi_esp[],Status Flag_blancing[], int size, int startIndex){
	for(int i =0 ;i < size;i++){
				BYTE temp_byte = 0x00;
				for(int j = i*8; j< i*8+8 ;j++){
					BYTE temp_status = Flag_blancing[j] == ON? 0x01 : 0x00;
					temp_byte |= (temp_status<<(j%8));
				}
				buffer_tx_spi_esp[startIndex++]=temp_byte;
				
		}		
}
		