#include "xmodem.h"

// ��ǰ���ݰ���
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
 * @brief   Xmodem���ݰ�У��
 * @param   packet      ���յ������ݰ�
 * @param   pLen        ���ݰ�����
 * @param   checkType   У�����ͣ�NAK У�� �� CHECK_CRC CRCУ��
 * @return  -1Ϊ֡ͷ���ʧ�ܣ�-2֡�ż��ʧ�ܣ�-3 CRCУ��ʧ�ܣ� 0ΪУ��ɹ�, 1���ս���
*/
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType)
{
	int packetCRC = 0;
	int CalpacketCRC = 0;
	unsigned short packcheckStat = 0;

	if (EOT == packet[0]) packcheckStat = 1;

    // ����֡ͷ
    if ( SOH != packet[0]) packcheckStat = -1;
    if ( (packet[1] != CurrentPackNum) && (packet[1] == ~(packet[2]))) {
        packcheckStat = -2;
    }

	// ��ȡCRCֵ 
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



