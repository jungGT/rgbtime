#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "i2c_master.h"
#include "lm75_temp.h"
#include "rtc.h"
#include "ws2812.h"
#include "rgb_lookup.h"
#include "pixgraph.h"

uint8_t img[5][5][3] = {
	{{25,0,0},{0,0,0},{0,0,0},{0,0,0},{25,0,0}},
	{{25,0,0},{0,0,0},{25,0,0},{0,0,0},{25,0,0}},
	{{25,0,0},{0,0,0},{25,0,0},{0,0,0},{25,0,0}},
	{{25,0,0},{0,0,0},{25,0,0},{0,0,0},{25,0,0}},
	{{25,0,0},{25,0,0},{25,0,0},{25,0,0},{25,0,0}}
};

int main(void)
{
	uint8_t killer[3] = {25,25,25};

	uint8_t d[25][3] = {{0}};
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


	while(1)
	{
		for(uint8_t i = 0; i < 10; i++)
		{
			pg_drawBitmap(i,img,killer);
			pg_canvas2hw(img,d);
			ws_updatePix(d,25);
			_delay_ms(1000);
		}
		/*
		for (uint16_t i = 0; i < 360; i++)
		{
			killer[0] = pgm_read_byte(&(rgb_lookup[i][0]));
			killer[1] = pgm_read_byte(&(rgb_lookup[i][1]));
			killer[2] = pgm_read_byte(&(rgb_lookup[i][2]));

			for (uint8_t n = 0; n < 25; n++)
			{
				d[n][0] = killer[0];
				d[n][1] = killer[1];
				d[n][2] = killer[2];
			}
			ws_updatePix(d,25);
			_delay_ms(25);
		}*/
	}
	return 0;
}
