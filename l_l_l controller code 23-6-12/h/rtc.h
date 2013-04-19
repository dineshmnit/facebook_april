
#ifndef _rtc_H
#define _rtc_H

#define SDA        PORTDbits.RD6	// RTC (DS1307)
#define SCL        PORTAbits.RA5


void d4();
void I2CInit();
void I2CStart();
void I2CRestart();
void I2CStop();
void I2CAck();
void I2CNak();
void I2CSend(unsigned char Data);
unsigned char I2CRead();
void i2cinit();
unsigned char read_mem(unsigned char d);
void write_mem(unsigned char addr,unsigned char data);
void i2ctime(int *pe,int *te);

#endif