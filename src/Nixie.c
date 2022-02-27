#include <STC89xx.h>
#include "Nixie.h"

// 位选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE1, _P0, 6);
// 段选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE2, _P0, 7);
// 寄存器I/O口，跟据LE控制位选择来输入输出位选还是段选寄存器
SFR(NEXIE_IO, _P2);

// 数码管初始值
unsigned char NEXIE_BUFF[] = {0x3F, 0x3F, 0x3F, 0x3F};
// 编码表
unsigned char NEXIE_CODE[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
// 位选表
unsigned char NEXIE_LOCAL[] = {0xFE, 0xFD, 0xFB, 0xF7};

// 打印数码管显示
void NexiePrint(unsigned char local, unsigned char data) {
    if (local < 1)
    {
        local = 1;
    }
    else if (local > 4)
    {
        local = 4;
    }
    NEXIE_BUFF[--local] = NEXIE_CODE[data];
}

// 选择数码管
void NexieLocal(unsigned char local) {
    NEXIE_IO = NEXIE_LOCAL[local];
    NEXIE_LE2 = 0x01;
    NEXIE_LE2 = 0x00;
}

// 显示数码管
void NexieByte(unsigned char data) {
    NEXIE_IO = data;
    NEXIE_LE1 = 0x01;
    NEXIE_LE1 = 0x00;
}

// 扫描刷新数据
void NexieScan(unsigned char local, unsigned char data) {
    NEXIE_IO = 0x00;
    NexieLocal(local);
    NexieByte(data);
}

// 定时器2ms循环一次
void NexieLoop() {
    static unsigned char index = 0;
    NexieScan(index, NEXIE_BUFF[index]);
    index++;
    if (index > 3)
    {
        index = 0;
    }
}