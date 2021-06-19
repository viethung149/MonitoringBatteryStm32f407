#include "spi.h"
void SPI_pin_config(void){
	// config SPI 1
	// mosi : PA7
	// MISO : PA6
	// SCK : PA5
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio_spi1;
	gpio_spi1.GPIO_Mode=GPIO_Mode_AF;
	gpio_spi1.GPIO_OType=GPIO_OType_PP;
	gpio_spi1.GPIO_Pin=CLK|MISO|MOSI;
	gpio_spi1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_spi1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);	
}
void SPI_init(){
	SPI_pin_config();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	SPI_InitTypeDef spi_config;
	spi_config.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_256;
	spi_config.SPI_CPHA=SPI_CPHA_1Edge;
	spi_config.SPI_CPOL=SPI_CPOL_Low;
	spi_config.SPI_CRCPolynomial=0x0007;
	spi_config.SPI_DataSize=SPI_DataSize_8b;
	spi_config.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	spi_config.SPI_FirstBit=SPI_FirstBit_MSB;
	spi_config.SPI_Mode=SPI_Mode_Master;
	spi_config.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI1,&spi_config);
	SPI_Cmd(SPI1,ENABLE);
}
// NSS pin is PA10 for stm32f103
void SPI_pin_nss(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio_config;
	gpio_config.GPIO_Mode = GPIO_Mode_OUT;
	gpio_config.GPIO_OType = GPIO_OType_PP;
	gpio_config.GPIO_Pin = NSS;
	gpio_config.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_config);	
}
// NSS pin is PA15 for esp32
void SPI_pin_nss_esp(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio_config;
	gpio_config.GPIO_Mode = GPIO_Mode_OUT;
	gpio_config.GPIO_OType = GPIO_OType_PP;
	gpio_config.GPIO_Pin = NSS_ESP;
	gpio_config.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_config);
}

void SPI_send_data(BYTE* tx_buffer){
	int i =0;
	while(i<92){
			SPI_I2S_SendData(SPI1,*(tx_buffer));
		  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
		  tx_buffer++;
		  i++;
	}
 test_counter_send++;
}
