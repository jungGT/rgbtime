#include <avr/io.h>
#include "rtc.h"
#include "i2c_master.h"

void rtc_init(void)
{
  uint8_t temp[4];
  rtc_stopOsc();
  rtc_seqRead((uint8_t)RTCSEC,temp,4);

  // check PWRFAIL bit
  if ((temp[3] & 0x10) != 0x10)
  {
    temp[2] &= ~0x40;   // 24 hour format
    temp[3] |= 0x08;    // enable battery backup
    rtc_seqWrite((uint8_t)RTCSEC,temp,4);
  } else {
    temp[3] |= 0x08;
    rtc_randWrite((uint8_t)RTCWKDAY,temp[3]);
  }

  rtc_startOsc();
}

void rtc_setTime(struct rtc_time *t)
{
  uint8_t temp[7];

  rtc_stopOsc();
  rtc_seqRead((uint8_t)RTCSEC,temp,7);

  temp[0] = (temp[0] & 0x80) | ((t->second/10)<<4) | (t->second%10);
  temp[1] = ((t->minute/10)<<4) | (t->minute%10);
  temp[2] = (temp[2] & 0xC0) | ((t->hour/10)<<4) | (t->hour%10);
  temp[3] = (temp[3] & 0x38) | (t->weekday & 0x07);
  temp[4] = ((t->date / 10)<<4) | (t->date%10);
  temp[5] = (temp[5] & 0x20) | ((t->month/10)<<4) | (t->month%10);
  temp[6] = ((t->year/10)<<4) | (t->year%10);

  rtc_seqWrite((uint8_t)RTCSEC,temp,7);
  rtc_startOsc();
}

void rtc_getTime(struct rtc_time *t)
{
  uint8_t temp[7];
  rtc_seqRead((uint8_t)RTCSEC,temp,7);

  // format the received data and store it in a nice struct
  t->second = (uint8_t)(((temp[0] & 0x70)>>4)*10 + (temp[0] & 0x0F));
  t->minute = (uint8_t)(((temp[1] & 0x70)>>4)*10 + (temp[1] & 0x0F));
  t->hour = (uint8_t)(((temp[2] & 0x30)>>4)*10 + (temp[2] & 0x0F));
  t->weekday = (uint8_t)(temp[3] & 0x07);
  t->date = (uint8_t)(((temp[4] & 0x30)>>4)*10 + (temp[4] & 0x0F));
  t->month = (uint8_t)(((temp[5] & 0x10)>>4)*10 + (temp[5] & 0x0F));
  t->year = (uint8_t)(((temp[6] & 0xF0)>>4)*10 + (temp[6] & 0x0F));
}

void rtc_startOsc(void)
{
  uint8_t temp;
  temp = rtc_randRead((uint8_t)RTCSEC);
  temp |= 0x80;
  rtc_randWrite((uint8_t)RTCSEC,temp);
}

void rtc_stopOsc(void)
{
  uint8_t temp;
  temp = rtc_randRead((uint8_t)RTCSEC);
  temp &= ~0x80;
  rtc_randWrite((uint8_t)RTCSEC,temp);
}

uint8_t rtc_randRead(uint8_t addr)
{
  uint8_t temp;
  i2c_readReg((uint8_t)RTCC_ADDR,addr,&temp,1);
  return temp;
}

void rtc_seqRead(uint8_t addr, uint8_t *buf, uint8_t length)
{
  i2c_readReg((uint8_t)RTCC_ADDR,addr,buf,length);
}

void rtc_randWrite(uint8_t addr, uint8_t data)
{
  i2c_writeReg((uint8_t)RTCC_ADDR,addr,&data,1);
}

void rtc_seqWrite(uint8_t addr, uint8_t *buf, uint8_t length)
{
  i2c_writeReg((uint8_t)RTCC_ADDR,addr,buf,length);
}
