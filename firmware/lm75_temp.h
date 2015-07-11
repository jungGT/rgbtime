#ifndef LM75_TEMP_H
#define LM75_TEMP_H

#define TEMP_ADDR	0x00
#define CONFIG_ADDR	0x01
#define THYST_ADDR	0x02
#define TOS_ADDR	0x03

uint8_t lm75_init(uint8_t i2cAddr);
int8_t lm75_getTemp(uint8_t i2cAddr);
uint8_t lm75_setHyst(uint8_t i2cAddr, int8_t temperature);
uint8_t lm75_setOS(uint8_t i2cAddr, int8_t temperature);

#endif
