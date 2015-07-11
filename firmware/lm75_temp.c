#include <avr/io.h>
#include "lm75_temp.h"
#include "i2c_master.h"

uint8_t lm75_init(uint8_t i2cAddr)
{
	uint8_t data;
	
	data = (uint8_t)CONFIG_ADDR;
	i2c_transmit(i2cAddr, &data, 1);
	
	data = 0x01; 
	i2c_transmit(i2cAddr, &data, 1);
	
	return 0;
}

int8_t lm75_getTemp(uint8_t i2cAddr)
{
	int8_t temperature;
	uint8_t data[2];
	
	// retrieve temp data from LM75
	data[0] = (uint8_t)TEMP_ADDR;
	i2c_transmit(i2cAddr, data, 1);
	i2c_receive(i2cAddr, data, 2);
	
	// discard lower 0.5°C bit
	temperature = data[0];
	
	return temperature;
}	

uint8_t lm75_setHyst(uint8_t i2cAddr, int8_t temperature)
{
	uint8_t data[2];
	
	data[0] = (uint8_t)THYST_ADDR;
	i2c_transmit(i2cAddr, data, 1);
	
	data[0] = (uint8_t)temperature;
	data[1] = 0;
	i2c_transmit(i2cAddr, data, 2);
	
	return 0;
}

uint8_t lm75_setOS(uint8_t i2cAddr, int8_t temperature)
{
	uint8_t data[2];
	
	data[0] = (uint8_t)TOS_ADDR;
	i2c_transmit(i2cAddr, data, 1);
	
	data[0] = (uint8_t)temperature;
	data[1] = 0;
	i2c_transmit(i2cAddr, data, 2);
	
	return 0;
}


