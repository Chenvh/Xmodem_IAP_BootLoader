#include "xmodem.h"

// ��ǰ���ݰ���
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
 * @brief   Xmodem���ݰ�У��
 * @param   packet      ���յ������ݰ�
 * @param   pLen        ���ݰ�����
 * @param   checkType   У�����ͣ�NAK У�� �� CHECK_CRC CRCУ��
 * @return  -1Ϊ֡ͷ���ʧ�ܣ�-2֡�ż��ʧ�ܣ�-3 CRCУ��ʧ�ܣ� 0ΪУ��ɹ�
*/
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType)
{
    // ����֡ͷ
    if ( SOH != packet[0]) return -1;
    if ( (packet[1] != CurrentPackNum + 1) && (packet[1] == ~(packet[2]))) {
        return -2;
    }
}



