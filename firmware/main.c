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
	uint8_t color[3] = {0,0,0};
	uint8_t d[25][3] = {{0}};

	struct lm75 tempSensor;
	tempSensor.i2cAddr = 0x90;

	struct rtc_time rtcTime;
	rtcTime.second = 0;
	rtcTime.minute = 0;
	rtcTime.hour = 0;

	uint16_t colorIndex = 0;

	// initialize peripherals
	i2c_init();
	// initialize board
	rtc_init();
	lm75_init(&tempSensor);

	ws_init();

	while(1)
	{
			rtc_getTime(&rtcTime);
			//lm75_getTemp(&tempSensor);
			colorIndex = (uint16_t)(rtcTime.hour*60 + rtcTime.minute)>>2;
			color[0] = pgm_read_byte(&(rgb_lookup[colorIndex][0]));
			color[1] = pgm_read_byte(&(rgb_lookup[colorIndex][1]));
			color[2] = pgm_read_byte(&(rgb_lookup[colorIndex][2]));
			pg_drawDigit((rtcTime.second%10),img,color);
			pg_canvas2hw(img,d);
			ws_updatePix(d,25);

			_delay_ms(500);


	}
	return 0;
}
