#include "Delay.h"

// 单片机晶振频率为11.0592MHz，机器周期为12个时钟周期，12/11059200=1.09us
// 延时5ms大概为5000us/1.09=4587
void Delay() {
    unsigned short n = 4587;
    while (n > 0)
    {
        n--;
    }
}