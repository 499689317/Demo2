/**
 * i2c通信驱动声明
 */

#ifndef I2C_H
#define I2C_H

// i2c驱动延时函数
extern void I2CDelay();
// i2c开始工作信号
extern void I2CStart();
// i2c停止工作信号
extern void I2CStop();
// i2c写数据
extern unsigned char I2CWrite(unsigned char data);
// i2c读数据
unsigned char I2CAckRead(unsigned char ack);

#endif