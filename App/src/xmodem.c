#include "xmodem.h"

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




