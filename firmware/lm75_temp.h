#ifndef LM75_TEMP_H
#define LM75_TEMP_H

#define TEMP_ADDR	0x00
#define CONFIG_ADDR	0x01
#define THYST_ADDR	0x02
#define TOS_ADDR	0x03

struct lm75{
  uint8_t i2cAddr;
  uint8_t temperature;
  uint8_t tHyst;
  uint8_t tOS;
};

void lm75_init(struct lm75 *s);
void lm75_getTemp(struct lm75 *s);
void lm75_setHyst(struct lm75 *s);
void lm75_setOS(struct lm75 *s);

#endif
