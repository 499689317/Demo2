
#include <STC89xx.h>
#include "Delay.h"
#include "AT24C256.h"
#include "LCD1602.h"

void main() {
    P1 = 0x00;
    unsigned short addr = 0x0001;
    unsigned char data = 0xA6;
    unsigned char rev = 0x00;
    
    unsigned short addr2 = 0x0007;
    const unsigned char* data2 = "write at24c256";
    unsigned char len = 1;
    // unsigned char rev2[1];

    // 测试写入单字节数据，向设备中地址0x0001处写入数据data
    // AT24C256WriteByte(addr, data);
    // at24c256写入时需要延时一段时间才能正确写入，写入比较消耗性能
    // Delay();
    // 读取设备存入的数据，让led灯按存储的数据显示亮灭
    // rev = AT24C256ReadByte(addr);
    // P1 = rev;

    // 测试写入多字节数据，向设备地址0x0002处写入数据data
    // AT24C256WritePage(addr2, &data, len);
    // 读取多字节数据
    // AT24C256ReadPage(addr2, rev2, len);
    // P1 = *rev2;

    LCD1602Init();
    // LCD1602PrintChar(1, 1, 'H');
    // LCD1602PrintString(1, 2, data2);

    LCD1602PrintBinNum(1, 1, 65535);
    LCD1602PrintHexNum(2, 1, 65535);
    LCD1602PrintUnsignedNum(2, 8, 65535);
    // LCD1602PrintSignedNum(2, 7, -123);
    while (1)
    {

    }
}