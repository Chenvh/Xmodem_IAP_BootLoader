#include "xmodem.h"

// 当前数据包号
unsigned int CurrentPackNum = 0;

int CalCRC(unsigned char *ptr, int count)
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
	
	return 0;


}
void SendXmodemCtrlChar(unsigned char Ctrltype)
{

}


/**
 * @brief   Xmodem数据包校验
 * @param   packet      接收到的数据包
 * @param   pLen        数据包长度
 * @param   checkType   校验类型：NAK 校验 或 CHECK_CRC CRC校验
 * @return  -1为帧头检测失败，-2帧号检测失败，-3 CRC校验失败， 0为校验成功, 1接收结束
*/
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType)
{
	int packetCRC = 0;
	int CalpacketCRC = 0;
	unsigned short packcheckStat = 0;

	if (EOT == packet[0]) packcheckStat = 1;

    // 不是帧头
    if ( SOH != packet[0]) packcheckStat = -1;
    if ( (packet[1] != CurrentPackNum) && (packet[1] == ~(packet[2]))) {
        packcheckStat = -2;
    }

	// 获取CRC值 
	if (CHECK_CRC == checkType) {
		packetCRC = (packet[PACKETDATALEN-2] << 8) + packet[PACKETDATALEN-1];

		CalpacketCRC = CalCRC(&packet[4], PACKETDATALEN-2);

		if (packetCRC != CalpacketCRC) {
			packcheckStat = -3;
		} else {
			CurrentPackNum++;
			packcheckStat = 0;
		}
	}

	if (0 < packcheckStat) {
		SendXmodemCtrlChar((unsigned char )NAK);
	} else {
		SendXmodemCtrlChar((unsigned char )ACK);
	}

	return packcheckStat;
}



