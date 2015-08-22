#ifndef PIXGRAPH_H
#define PIXGRAPH_H

#include <avr/io.h>

const uint8_t pg_digLUT[10][5];

void pg_drawBitmap(uint8_t n, uint8_t cdata[5][5][3], uint8_t color[3]);
void pg_canvas2hw(uint8_t cdata[5][5][3], uint8_t buf[25][3]);
void pg_cpRGB(uint8_t src[3], uint8_t dst[3]);


#endif
