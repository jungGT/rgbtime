#include <avr/io.h>
#include "lm75_temp.h"
#include "i2c_master.h"

void lm75_init(struct lm75 *s)
{
	uint8_t data;

	data = (uint8_t)CONFIG_ADDR;
	i2c_transmit(s->i2cAddr, &data, 1);

	data = 0x01;
	i2c_transmit(s->i2cAddr, &data, 1);
}

void lm75_getTemp(struct lm75 *s)
{
	uint8_t data[2];

	// retrieve temp data from LM75
	data[0] = (uint8_t)TEMP_ADDR;
	i2c_transmit(s->i2cAddr, data, 1);
	i2c_receive(s->i2cAddr, data, 2);

	// discard lower 0.5°C bit
	s->temperature = (int8_t)data[0];
}

void lm75_setHyst(struct lm75 *s)
{
	uint8_t data[2];

	data[0] = (uint8_t)THYST_ADDR;
	i2c_transmit(s->i2cAddr, data, 1);

	data[0] = s->temperature;
	data[1] = 0;
	i2c_transmit(s->i2cAddr, data, 2);
}

void lm75_setOS(struct lm75 *s)
{
	uint8_t data[2];

	data[0] = (uint8_t)TOS_ADDR;
	i2c_transmit(s->i2cAddr, data, 1);

	data[0] = s->temperature;
	data[1] = 0;
	i2c_transmit(s->i2cAddr, data, 2);
}
