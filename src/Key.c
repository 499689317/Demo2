#include <STC89xx.h>
#include "Key.h"

SBIT(KEY_K1, _P1, 0);
SBIT(KEY_K2, _P1, 1);
SBIT(KEY_K3, _P1, 2);

unsigned char KEY_DOWN = 0;
unsigned char KEY_UP = 0;

// 按键按下
unsigned char KeyDown() {
    unsigned char status = 0;
    status = KEY_DOWN;
    // 按键按下时，保持按键激活状态???不好使
    KEY_DOWN = 0;
    return status;
}

// 按键松开
unsigned char KeyUp() {
    unsigned char status = 0;
    status = KEY_UP;
    // 按钮在松开时，清除掉所有状态缓存
    KEY_UP = 0;
    // KEY_DOWN = 0;
    return status;
}

// 按键状态，低电平时返回相应按键状态码
unsigned char KeyStatus() {
    unsigned char status = 0;
    // 这里如果是矩阵键盘的话，情况会更复杂
    if (KEY_K1 == 0x00)
    {
        status = 1;
    }
    if (KEY_K2 == 0x00)
    {
        status = 2;
    }
    if (KEY_K3 == 0x00)
    {
        status = 3;
    }
    return status;
}

// 扫描按键按下状态，只有在按键有机械动作的情况下才会改变当前缓存的状态值，否则视为状态不变
void KeyScanDown(unsigned char now, unsigned char last) {
    if (last == 0 && now == 1)
    {
        KEY_DOWN = 1;
    }
    if (last == 0 && now == 2)
    {
        KEY_DOWN = 2;
    }
    if (last == 0 && now == 3)
    {
        KEY_DOWN = 3;
    }
}

// 扫描按建松开状态
void KeyScanUp(unsigned char now, unsigned char last) {
    if (last == 1 && now == 0)
    {
        KEY_UP = 1;
    }
    if (last == 2 && now == 0)
    {
        KEY_UP = 2;
    }
    if (last == 3 && now == 0)
    {
        KEY_UP = 3;
    }
}

// 定时器循环，消抖
void KeyLoop() {
    // 两个定时器周期确认一次状态, s1当前周期状态，s2上一周期状态
    static unsigned char status_now = 0, status_last = 0;
    // 暂存上一周期（相对于当前周期来说算上一周期）状态
    status_last = status_now;
    // 更新当前周期铵键状态
    status_now = KeyStatus();
    // 扫描按下
    KeyScanDown(status_now, status_last);
    // 扫描松开
    KeyScanUp(status_now, status_last);
}
