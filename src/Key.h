/**
 * 按键驱动
 */

#ifndef KEY_H
#define KEY_H

// 按键按下
extern unsigned char KeyDown();
// 按键松开
extern unsigned char KeyUp();
// 定时器20ms循环一次
extern void KeyLoop();

#endif
