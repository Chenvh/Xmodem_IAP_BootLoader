#include "xmodem.h"

// 当前数据包号
extern unsigned int CurrentPackNum = 0;

int CalCRC(char *ptr, int count)
{
	int crc;
	char i;
 
	crc = 0;
	while (--count >= 0)
	{
		crc = crc ^ (int) *ptr++ << 8;
		i = 8;
		do
		{
			if (crc & 0x8000)
				crc = crc << 1 ^ 0x1021;
			else
				crc = crc << 1;
		} while (--i);
	}
 
	return (crc);
}

unsigned char xmodemReceive(unsigned char checkType)
{



}


/**
 * @brief   Xmodem数据包校验
 * @param   packet      接收到的数据包
 * @param   pLen        数据包长度
 * @param   checkType   校验类型：NAK 校验 或 CHECK_CRC CRC校验
 * @return  -1为帧头检测失败，-2帧号检测失败，-3 CRC校验失败， 0为校验成功
*/
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType)
{
    // 不是帧头
    if ( SOH != packet[0]) return -1;
    if ( (packet[1] != CurrentPackNum + 1) && (packet[1] == ~(packet[2]))) {
        return -2;
    }
}



