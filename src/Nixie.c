#include <STC89xx.h>
#include "Nixie.h"

// 位选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE1, _P0, 6);
// 段选寄存器控制位，0x01为可输入状态，0x00为锁存状态
SBIT(NEXIE_LE2, _P0, 7);
// 寄存器I/O口，跟据LE控制位选择来输入输出位选还是段选寄存器
SFR(NEXIE_IO, _P2);

// 打印数码管显示
void NexiePrint(unsigned char local, unsigned char data) {
    
}
// 扫描刷新数据
void NexieScan(unsigned char local, unsigned char data) {
    
}
// 定时器2ms循环一次
void NexieLoop() {
    
}