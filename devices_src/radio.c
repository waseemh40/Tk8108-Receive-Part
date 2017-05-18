/*
 * radio.c
 *
 *  Created on: Apr 11, 2017
 *      Author: waseemh
 */

#include "radio.h"

/*
 * private variables
 */
/*
 * public variables
 */

/*
 * private functions
 */

/*
 * public functions
 */

void radio_init(void){
	spi_init();
	GPIO_PinModeSet(PWR_EN_PORT,RADIO_PWR_EN,gpioModePushPull,0);
	radio_on();
	spi_cs_set(radio);
	radio_write_cmd(OP_MODE_W,0x80);		//sleep mode and write configurations
	delay_ms(0);
	radio_write_cmd(PA_RAMP_W,0x08);
	delay_ms(0);
	radio_write_cmd(MODEM_CONFIG1_W,0x06);
	delay_ms(0);
	radio_write_cmd(MODEM_CONFIG2_W,0x70);
	delay_ms(0);
	radio_write_cmd(TEST_W,0x34);
	delay_ms(0);
	radio_write_cmd(OP_MODE_W,0x83);		//finally in TX mode
	delay_ms(0);
	return;
}

void radio_on(void){
	GPIO_PinOutSet(PWR_EN_PORT,RADIO_PWR_EN);
	return;
}

void radio_off(void){
	GPIO_PinOutClear(PWR_EN_PORT,RADIO_PWR_EN);
	return;
}
 void radio_write_cmd(uint8_t addr,uint8_t cmd){
	 spi_cs_clear(radio);
	 spi_write_byte((uint8_t)addr);
	 spi_write_byte((uint8_t)cmd);
	 spi_cs_set(radio);
	 return;
 }
 uint8_t radio_read_cmd(uint8_t addr){
	 uint8_t rx_data=0;
	 spi_cs_clear(radio);
	 spi_write_byte((uint8_t)addr);
	 rx_data=spi_read_byte();
	 spi_cs_set(radio);
	 return rx_data;
 }
