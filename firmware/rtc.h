#ifndef RTC_H
#define RTC_H

struct rtc_time {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t weekday;
  uint8_t date;
  uint8_t month;
  uint8_t year;
};

void rtc_init(void);
void rtc_setTime(struct rtc_time *t);
void rtc_getTime(struct rtc_time *t);
uint8_t rtc_randRead(uint8_t addr);
void rtc_seqRead(uint8_t addr, uint8_t *buf, uint8_t length);
void rtc_randWrite(uint8_t addr, uint8_t data);
void rtc_seqWrite(uint8_t addr, uint8_t *buf, uint8_t length);

// MCP79410 memory map
#define RTCC_ADDR   0xDE // device address for SRAM/RTCC access
#define EEPROM_ADDR 0xAE // device address for EEPROM access
// Timekeeping registers
#define RTCSEC    0x00
#define RTCMIN    0x01
#define RTCHOUR   0x02
#define RTCWKDAY  0x03
#define RTCDATE   0x04
#define RTCMTH    0x05
#define RTCYEAR   0x06
#define CONTROL   0x07
#define OSCTRIM   0x08
#define EEUNLOCK  0x09

// Alarm registers
/* Add alarm offset to register address
 * to access respective alarm registers
 */
#define AL0OFFS   0x00
#define AL1OFFS   0x07

#define ALMSEC    0x0A
#define ALMMIN    0x0B
#define ALMHOUR   0x0C
#define ALMWKDAY  0x0D
#define ALMDATE   0x0E
#define ALMMTH    0x0F

// Power fail timestamp registers
#define PWRDNMIN  0x18
#define PWRDNHOUR 0x19
#define PWRDNDATE 0x1A
#define PWRDNMTH  0x1B
#define PWRUPMIN  0x1C
#define PWRUPHOUR 0x1D
#define PWRUPDATE 0x1E
#define PWRUPMTH  0x1F

#endif /* RTC_H */
