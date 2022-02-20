
/**
 * at24c256通信驱动声明
 */

#ifndef AT24C256_H
#define AT24C256_H

// 写字节
extern void AT24C256WriteByte(unsigned short addr, unsigned char data);
// 读字节
extern unsigned char AT24C256ReadByte(unsigned short addr);

// 分页读写相当于批量读写字节，at24c256可以分成512页，每页64字节
// at24c256写时序中，写入数据时需要延时5-10ms才能正常写入成功，所以单字节写入是非常耗时的操作
// 页写，len为data写入字节数据的长度，每写一个字节，长度len减1直到为0说明写完了
// 注：连续写入多个字节必需要在同一页中，不能进行跨页连续写操作，因此一次通信周期（i2c start-stop区间）内只能写一页（64字节）数据。
extern void AT24C256WritePage(unsigned short addr, const unsigned char* data, unsigned char len);
// 页读，len为需要读取多少个字节，每读取一个字节，长度len减1直到为0说明读完了
// 注：读取完一个字节，发送应答信号为0表示继续读取，直到读完数据发送ack=1表示不继续读了
extern void AT24C256ReadPage(unsigned short addr, unsigned char* data, unsigned char len);

#endif
