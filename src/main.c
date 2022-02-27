
#include <STC89xx.h>
#include <mcs51/lint.h>
#include "Delay.h"
#include "AT24C256.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Timer1.h"
#include "Nixie.h"
#include "Key.h"
#include "E2PROM.h"
#include "UART.h"

void main() {

    // 初始化定时器
    // Timer0Init();
    Timer1Init();

    // 初始化串口通信
    UARTInit();

    // 初始化LCD
    LCD1602Init();

    // unsigned short addr = 0x2000;
    // unsigned char msg = 0xA6;
    // unsigned char rev = 0x4F;
    
    // unsigned short addr2 = 0x2200;
    // const unsigned char* msg2 = "write at24c256";
    // unsigned char len = 15;
    // unsigned char rev2[15];

    // 测试E2PROM
    // E2PROMErase(addr);
    // E2PROMErase(addr2);
    // E2PROMWriteByte(addr, msg);
    // rev = E2PROMReadByte(addr);
    // E2PROMWrite(addr2, msg2, len);
    // E2PROMRead(addr2, rev2, len);

    // 测试串口通信
    for (int i = 0; i < 255; i++)
    {
        Delay();
        UARTSendByte('H');
    }

    // 测试写入单字节数据，向设备中地址0x0000-0x7FFF处写入数据msg
    // AT24C256WriteByte(addr, msg);
    // at24c256写入时需要延时一段时间才能正确写入，写入比较消耗性能
    // Delay();
    // 读取设备存入的数据，让led灯按存储的数据显示亮灭
    // rev = AT24C256ReadByte(addr);
    // 测试写入多字节数据，向设备地址0x0000-0x7FFF处写入数据msg
    // AT24C256WritePage(addr2, msg2, len);
    // 读取多字节数据
    // AT24C256ReadPage(addr2, rev2, len);

    // LCD1602PrintChar(1, 1, rev);
    // LCD1602PrintString(1, 2, rev2);
    // LCD1602PrintBinNum(1, 1, 65535);
    // LCD1602PrintHexNum(2, 1, 65535);
    // LCD1602PrintUnsignedNum(2, 8, 65535);
    // LCD1602PrintSignedNum(2, 7, -123);

    while (1)
    {
        // if (rev == 255)
        // {
        //     rev = 15;
        // }
        // if (rev > 15)
        // {
        //     rev = 0;
        // }
        // unsigned char kd = KeyDown();
        // if (kd == 1)
        // {
        //     NexiePrint(1, rev);
        //     rev++;
        // } else if (kd == 2)
        // {
        //     NexiePrint(2, rev);
        //     rev--;
        // } else if (kd == 3)
        // {
        //     NexiePrint(1, 0);
        //     NexiePrint(2, 0);
        //     NexiePrint(3, 0);
        //     NexiePrint(4, 0);
        // }
        
        // unsigned char ku = KeyUp();
        // if (ku == 1)
        // {
        //     NexiePrint(4, 1);
        // } else if (ku == 2)
        // {
        //     NexiePrint(4, 2);
        // } else if (ku == 3)
        // {
        //     NexiePrint(4, 3);
        // }
    }
}

// void Timer0Inter() __interrupt(1) {
//     Timer0Loop();

//     static unsigned char timer_nexie = 0;
//     if (timer_nexie == 2)
//     {
//         timer_nexie = 0;
//         NexieLoop();
//     }
//     timer_nexie++;

//     static unsigned char timer_key = 0;
//     if (timer_key == 20)
//     {
//         timer_key = 0;
//         KeyLoop();
//     }
//     timer_key++;
// }

// 串口中断函数
void UARTInter() __interrupt(4) {
    UARTLoop();
}