#include <avr/io.h>
#include "ws2812.h"

void ws_init(void)
{
  // initialize I/O
	WSDATA_DDR |= WSDATA_PIN;
}

/* Send a single data byte out to the WS2812 using somewhat correct
 * timing (it isn't as critical as the datasheet makes it seem).
 */
void ws_sendByte(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		if((data & 0x80) == 0x80)
		{
      WSDATA_PORT |= WSDATA_PIN;
			WSDATA_PORT |= WSDATA_PIN;
			WSDATA_PORT |= WSDATA_PIN;
			WSDATA_PORT |= WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
		} else {
			WSDATA_PORT |= WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
			WSDATA_PORT &= ~WSDATA_PIN;
		}
		data = (data<<1);
	}
}

/* Update a whole series of LEDs by sending out the RGB triplets as
 * fast as possible.
 * This function corrects for the byte order used by the LEDs.
 * The byte order for the input array is R-G-B
 */
void ws_updatePix(uint8_t rgb[][3], uint16_t len)
{
	for(uint16_t i = 0; i < len; i++)
	{
		ws_sendByte(rgb[i][1]);
		ws_sendByte(rgb[i][0]);
		ws_sendByte(rgb[i][2]);
	}
}

void ws_updateSingle(uint8_t rgb[])
{
	ws_sendByte(rgb[1]);
	ws_sendByte(rgb[0]);
	ws_sendByte(rgb[2]);
}
