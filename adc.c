#include "adc.h"
#include "delay.h"
#include "type.h"

void ADC_pin_select_config(void)
{
		//Pin PD12, PD13, PD14, PD15 select channel
		//Pin 11 enable modedule adc 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
		GPIO_InitTypeDef GPIO_config;
		GPIO_config.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_config.GPIO_OType=GPIO_OType_PP;
		GPIO_config.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_11;
		GPIO_config.GPIO_PuPd=GPIO_PuPd_NOPULL;
		GPIO_config.GPIO_Speed=GPIO_Speed_100MHz;
		GPIO_Init(GPIOD,&GPIO_config);
		//Pin PE1, PE2, PE3, PE4 select channel
		//Pin PE0 enable modedule adc 
		GPIO_config.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
		GPIO_Init(GPIOE,&GPIO_config);
}
//-------------------------------------------------------------------------------------
void ADC_pin_config(void)
{
	  RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,ENABLE);
		// config pin using for ADC
		GPIO_InitTypeDef GPIO_config;
		GPIO_config.GPIO_Mode=GPIO_Mode_AN;
		GPIO_config.GPIO_OType=GPIO_OType_PP;
		GPIO_config.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
		GPIO_config.GPIO_PuPd=GPIO_PuPd_NOPULL;
		GPIO_config.GPIO_Speed=GPIO_Speed_100MHz;
		GPIO_Init(GPIOA,&GPIO_config);
	  // config overview ADC
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  					       // enable APB2
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);  					       // enable APB2
		ADC_DeInit();
		ADC_InitTypeDef ADC_config;
	  ADC_config.ADC_ContinuousConvMode=DISABLE;                            // read continuous
		ADC_config.ADC_DataAlign=ADC_DataAlign_Right;                         // data align left
	  ADC_config.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;
		ADC_config.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;    
		ADC_config.ADC_NbrOfConversion=1;                                    //Read one channel
	  ADC_config.ADC_Resolution=ADC_Resolution_12b;                          // Resolution: 12b
		ADC_config.ADC_ScanConvMode=DISABLE;		//conversion one channel
		
		ADC_Init(ADC1,&ADC_config);
		ADC_Init(ADC2,&ADC_config);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_84Cycles); /* choose channel and time sampling */
		ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_84Cycles); 
}
//----------------------------------------------------------------------------------------------------
int ADC_select_channel(int module, int channel)
{
	if(module == 1 && channel <= 15){
			for(int i =0 ;i< 4;i++)
			{
				BitAction Action;
				int remain = channel%2;
				channel/= 2;
				Action = remain == 1? Bit_SET:Bit_RESET;
				GPIO_WriteBit(PORT_MODULE1,PIN_SELECT_MODULE1[i+1],Action);
			}
			return channel;
	}
	else if(module == 2 && channel <=15){
			for(int i =0 ;i< 4;i++)
			{
				BitAction Action;
				int remain = channel%2;
				channel/= 2;
				Action = remain == 1? Bit_SET:Bit_RESET;
				GPIO_WriteBit(PORT_MODULE2,PIN_SELECT_MODULE2[i+1],Action);
			}
			return channel;
	}
	else{
	return -1;
	}
}
//----------------------------------------------------------------------------------------------------
float ADC_get_digital(ADC_TypeDef* ADCx, int numberRead)
{
	float sum_digital =0;

	for(int i=0; i<numberRead; i++)
	{	
		ADC_Cmd(ADCx,ENABLE);
		ADC_SoftwareStartConv(ADCx);
		while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));//Processing the conversion
		uint16_t value_digital = ADC_GetConversionValue(ADCx);
		sum_digital += (float)value_digital;
		Dellay_us(10);
	}
	return sum_digital/numberRead;
}
//----------------------------------------------------------------------------------------------------
float ADC_get_value_voltage(ADC_TypeDef* ADCx, int numberRead, float voltage_ref)
{
	float sum_voltage =0;
	
	for(int i=0; i<numberRead; i++)
	{
		ADC_Cmd(ADCx,ENABLE);
		ADC_SoftwareStartConv(ADCx);
		while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));//Processing the conversion
		uint16_t value_digital = ADC_GetConversionValue(ADCx);
		float Voltage = (float)value_digital*(voltage_ref/4095);
		sum_voltage += Voltage;
		Dellay_us(100);
	}
	return sum_voltage/numberRead;
}
//----------------------------------------------------------------------------
float ADC_get_value_voltage_mv(ADC_TypeDef* ADCx, int numberRead, float voltage_ref)
{
	float sum_voltage =0;
	for(int i=0; i<numberRead; i++)
	{
		ADC_Cmd(ADCx,ENABLE);
		ADC_SoftwareStartConv(ADCx);
		while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));//Processing the conversion
		uint16_t value_digital = ADC_GetConversionValue(ADCx);
		float Voltage = value_digital*(voltage_ref*1000/4095);
		sum_voltage += Voltage;
		Dellay_us(100);
	}
	return sum_voltage/numberRead;
}
//----------------------------------------------------------------------------------------------------
float ADC_get_voltage_from_channel(ADC_TypeDef* ADCx, int numberRead, int channel,int module, float voltage_ref)
{
	
	ADC_select_channel(module,channel);
	module == 1 ? GPIO_ResetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_ResetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]); 
	Dellay_us(1000);
	float voltage = ADC_get_value_voltage(ADCx,numberRead,voltage_ref);
	module == 1 ? GPIO_SetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_SetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]); 
	return voltage;
}
//----------------------------------------------------------------------------------------------------
float ADC_get_digital_from_channel(ADC_TypeDef* ADCx, int numberRead,int module, int channel)
{
	ADC_select_channel(module,channel);
	module == 1 ? GPIO_ResetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_ResetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]); 
	float digital = ADC_get_digital(ADCx,numberRead);
	module == 1 ? GPIO_SetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_SetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]);
  return digital;	
}
//-------------------------------------------------------------------------------------------
float ADC_get_voltage_from_channel_mv(ADC_TypeDef* ADCx, int numberRead, int channel,int module,  float voltage_ref)
{
	ADC_select_channel(module,channel);
	module == 1 ? GPIO_ResetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_ResetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]); 
	float voltage = ADC_get_value_voltage_mv(ADCx,numberRead,voltage_ref);
	module == 1 ? GPIO_SetBits(PORT_MODULE1,PIN_SELECT_MODULE1[0]):GPIO_SetBits(PORT_MODULE2,PIN_SELECT_MODULE2[0]); 
	return voltage;
}
//--convert voltage to current
float voltage_to_current(float sensitive, float voltage, int offset, Status channel_current_IO){
	int voltage_mv =voltage*1000;
	int denta = voltage_mv - offset;
	float current_a =0;
	// current out
	if(denta > 0 && denta > 15){
		channel_current_IO = ON;
		current_a = (float)denta/(float)sensitive;
		return current_a;
	}
	// current in 
	else if(denta <0 && denta < -15){
		channel_current_IO = OFF;
		current_a = ((float)denta/sensitive);
		return current_a;
	}
	else{
		return 0;
	}
}