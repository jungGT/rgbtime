#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "i2c_master.h"
#include "lm75_temp.h"
#include "rtc.h"
#include "ws2812.h"

#define LM75_ADDR 0x90

const uint8_t digitLookup[10][5] =
{
	{0x00,0x00,0x1F,0x00,0x00},
	{0x1D,0x15,0x15,0x15,0x17},
	{0x15,0x15,0x15,0x15,0x1F},
	{0x07,0x04,0x04,0x04,0x1F},
	{0x17,0x15,0x15,0x15,0x17},
	{0x1F,0x15,0x15,0x15,0x1D},
	{0x01,0x10,0x01,0x10,0x1F},
	{0x1F,0x15,0x15,0x15,0x1F},
	{0x17,0x15,0x15,0x15,0x1F},
	{0x1F,0x13,0x15,0x19,0x1F}
};

int main(void)
{
	uint8_t killer[3] = {0,0,0};
	struct rtc_time rtcTime;
	struct lm75 tempSensor;
	tempSensor.i2cAddr = 0x90;

	rtcTime.second = 0;
	rtcTime.minute = 0;
	rtcTime.hour = 0;

	// initialize peripherals
	i2c_init();
	// initialize board
	rtc_init();
	lm75_init(&tempSensor);
	ws_init();

	ws_updateSingle(killer);

	while(1)
	{
		for(uint8_t i = 0; i < 255; i++)
		{
			killer[0] = i;
			killer[2] = 254-i;
			ws_updateSingle(killer);
			_delay_ms(25);
		}

		for(uint8_t i = 0; i < 255; i++)
		{
			killer[0] = 254-i;
			killer[1] = i;
			ws_updateSingle(killer);
			_delay_ms(25);
		}

		for(uint8_t i = 0; i < 255; i++)
		{
			killer[1] = 254-i;
			killer[2] = i;
			ws_updateSingle(killer);
			_delay_ms(25);
		}
	}
	return 0;
}
