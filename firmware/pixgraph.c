#include <avr/io.h>
#include "pixgraph.h"

// draws a bitmap monochrome (color[3]) image onto a canvas
void pg_drawBitmap(uint8_t n, uint8_t cdata[5][5][3], uint8_t color[3])
{
  uint8_t zeros[3] = {0,0,0};

  for(uint8_t line = 0; line < 5; line++)
  {
    for(uint8_t col = 0; col < 5; col++)
    {
      if ( ((pg_digLUT[n][line]<<col) & 0x10) == 0x10)
      {
        pg_cpRGB(color,cdata[col][line]);
      } else {
        pg_cpRGB(zeros,cdata[col][line]);
      }
    }
  }
}

// maps the 5x5 images (0,0 at top left corner) on canvas
// to the actual hardware LED arrangement
void pg_canvas2hw(uint8_t cdata[5][5][3], uint8_t buf[25][3])
{
  pg_cpRGB(cdata[0][0],buf[4]);
  pg_cpRGB(cdata[0][1],buf[3]);
  pg_cpRGB(cdata[0][2],buf[2]);
  pg_cpRGB(cdata[0][3],buf[1]);
  pg_cpRGB(cdata[0][4],buf[0]);

  pg_cpRGB(cdata[1][0],buf[5]);
  pg_cpRGB(cdata[1][1],buf[6]);
  pg_cpRGB(cdata[1][2],buf[7]);
  pg_cpRGB(cdata[1][3],buf[8]);
  pg_cpRGB(cdata[1][4],buf[9]);

  pg_cpRGB(cdata[2][0],buf[14]);
  pg_cpRGB(cdata[2][1],buf[13]);
  pg_cpRGB(cdata[2][2],buf[12]);
  pg_cpRGB(cdata[2][3],buf[11]);
  pg_cpRGB(cdata[2][4],buf[10]);

  pg_cpRGB(cdata[3][0],buf[15]);
  pg_cpRGB(cdata[3][1],buf[16]);
  pg_cpRGB(cdata[3][2],buf[17]);
  pg_cpRGB(cdata[3][3],buf[18]);
  pg_cpRGB(cdata[3][4],buf[19]);

  pg_cpRGB(cdata[4][0],buf[24]);
  pg_cpRGB(cdata[4][1],buf[23]);
  pg_cpRGB(cdata[4][2],buf[22]);
  pg_cpRGB(cdata[4][3],buf[21]);
  pg_cpRGB(cdata[4][4],buf[20]);
}

// helper function for copying RGB triplets to
// locations in other arrays
void pg_cpRGB(uint8_t src[3], uint8_t dst[3])
{
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}

// bitmap representation of digits 0 to 9
const uint8_t pg_digLUT[10][5] = {
  {0x1F,0x13,0x15,0x19,0x1F},
  {0x04,0x04,0x04,0x04,0x04},
  {0x1F,0x01,0x1F,0x10,0x1F},
  {0x1F,0x01,0x0F,0x01,0x1F},
  {0x11,0x11,0x1F,0x01,0x01},
  {0x1F,0x10,0x1F,0x01,0x1F},
  {0x1F,0x10,0x1F,0x11,0x1F},
  {0x1F,0x01,0x01,0x01,0x01},
  {0x1F,0x11,0x1F,0x11,0x1F},
  {0x1F,0x11,0x1F,0x01,0x1F}
};
