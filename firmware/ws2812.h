#ifndef WS2812_H
#define WS2812_H

#define WSDATA_PIN 0x08
#define WSDATA_DDR DDRD
#define WSDATA_PORT PORTD

void ws_init(void);
void ws_sendByte(uint8_t data);
void ws_updatePix(uint8_t rgb[][3], uint16_t len);
void ws_updateSingle(uint8_t rgb[]);

#endif /* WS2812_H */
