#include "AT24C256.h"
#include "I2C.h"

void AT24C256WriteByte(unsigned short addr, unsigned char data) {
    // 开始i2c通信
    I2CStart();
    // 写入当前at24c256设置地址，A2,A1,A0都默认接地000，1010 000 0，1010为固定前缀，000为A0-A1信号，最后一位为读写标识位1为读0为写
    I2CWrite(0xA0);
    // 写入数据高地址位
    I2CWrite(addr >> 8);
    // 写入数据低地址位
    I2CWrite(addr);
    // 写入数据
    I2CWrite(data);
    // 停止i2c通信
    I2CStop();
}

// 读取数据分两步，先向设备写入准备读取数据的相关信息，再向设置发起读取数据
unsigned char AT24C256ReadByte(unsigned short addr) {
    unsigned char data = 0x00;
    unsigned char ack = 0x01;// 读取完1个字节就结束读取，0x00为不结束读取
    // 开始i2c通信
    I2CStart();
    // 写入设置地址，告诉设备开始写入数据
    I2CWrite(0xA0);
    // 告诉设备即将要读取数据的地址
    I2CWrite(addr >> 8);
    I2CWrite(addr);
    // 开始准备继续下一步通信
    I2CStart();
    // 告诉设备即将进行读操作
    I2CWrite(0xA1);
    data = I2CAckRead(ack);
    // 停止i2c通信
    I2CStop();
    return data;
}

void AT24C256WritePage(unsigned short addr,const unsigned char* data, unsigned char len) {
    while (len > 0)
    {
        // 检测写入应答信号是否为0，0表示可以进行写入操作了
        while (1)
        {
            I2CStart();
            if (0 == I2CWrite(0xA0))
            {
                // 可以进行写入数据操作了
                break;
            }
            // 如果0xA0写入不成功，则结束本次写启动
            I2CStop();
        }
        // 高位写地址
        I2CWrite(addr >> 8);
        // 低位写地址
        I2CWrite(addr);
        // 开始写操作
        while (len > 0)
        {
            // *data++，*操作符比后缀++优先级低，所以指针先移动再取值，与*(data++)是一样的，指针会改变
            // (*data)++，先取data指针的值，再对取出的值自加，指针不会变
            // 这个data指针是一个拷贝，即使发生了改变也不会影响到实参的地址值
            I2CWrite(*data++);
            len--;
            addr++;// 设备数据存储地址往后移一位
            // 判断当前页是否已经用完
            if (addr % 64 == 0)
            {
                // 当前页用完则跳出当前循环，进行新一页初始化写入操作
                break;
            }
        }
        // 所有数据都写完，结束通信
        I2CStop();
    }
}

// 连续读取字节数据时，使用ack信号控制即可
void AT24C256ReadPage(unsigned short addr, unsigned char* data, unsigned char len) {
    // 先拿到写控制权
    while (1)
    {
        I2CStart();
        if (0 == I2CWrite(0xA0))
        {
            // 拿到写控制权后跳出开始准备写入操作
            break;
        }
        I2CStop();
    }
    // 读数据高地址
    I2CWrite(addr >> 8);
    // 读数据低地址
    I2CWrite(addr);
    // 开启准备读取数据
    I2CStart();
    // 读取0xA1设备数据
    I2CWrite(0xA1);
    // 连续读len长度的字节数据
    while (len > 0)
    {
        *data++ = I2CAckRead(0x00);
        len--;
    }
    // 读取数据完成后，发送不继续读取应答信号，这次读取只是为了发一个不继续读的信号，不会真正去读数据
    I2CAckRead(0x01);
    // 结束本次读取
    I2CStop();
}
