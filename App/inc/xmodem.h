#ifndef __XMODEM_H_
#define __XMODEM_H_


/* Xmodem ����֡��ʽ
---------------------------------------------------------------------------
|     Byte1     |    Byte2    |     Byte3      |Byte4~Byte131|  Byte132   |
|-------------------------------------------------------------------------|
|Start Of Header|Packet Number|~(Packet Number)| Packet Data |  Check Sum |
---------------------------------------------------------------------------

Xmodem-CRC16 ����֡��ʽ
------------------------------------------------------------------------------
|     Byte1     |    Byte2    |     Byte3      |Byte4~Byte131|Byte132~Byte133|
|----------------------------------------------------------------------------|
|Start Of Header|Packet Number|~(Packet Number)| Packet Data |   16Bit CRC   |
------------------------------------------------------------------------------

Xmode ��������
------------------------------------------------------------------------------
|               SENDER                |          |          RECIEVER         |
|                                     |  <---    |  NAK                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  NAK                      |
| SOH|0x01|0xFE|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
|                                     |  <---    |  ACK                      |
| EOT                                 |  --->    |                           |
|                                     |  <---    |  ACK                      |
------------------------------------------------------------------------------

Xmodem-CRC16 ��������
---------------------------------------------------------------------------
|               SENDER             |          |           RECIEVER        |
|                                  |  <---    |  'C'                      |
|                                  |          |  Time out after 3 second  |
|                                  |  <---    |  'C'                      |
| SOH|0x01|0xFE|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| .                                |          |  .                        |
| .                                |          |  .                        |
| .                                |          |  .                        |
|                                  |  <---    |  ACK                      |
| EOT                              |  --->    |                           |
|                                  |  <---    |  ACK                      |
---------------------------------------------------------------------------

˫֧�ִ�������
------------------------------------------------------------------------------
|               SENDER                |          |           RECIEVER        |
|                                     |  <---    |  'C'                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  NAK                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  'C'                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  NAK                      |
| SOH|0x01|0xFE|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
|                                     |  <---    |  ACK                      |
| EOT                                 |  --->    |                           |
|                                     |  <---    |  ACK                      |
------------------------------------------------------------------------------

*/


#define SOH     0x01    // Start Of Header modem 128����֡ͷ
#define STX     0x02    // 1k-XModem ����֡ͷ
#define EOT     0x04    // ���ͽ�����־
#define ACK     0x06    // Ӧ���־
#define NAK     0x15    // ��Ӧ���־/�ط���־
#define CAN     0x18    // ȡ�����ͱ�־
#define CTRLZ   0x1A    // ֡�հ�����ַ�
#define CRC16   0x43    // ʹ�� CRC16 У���־


#define CHECK_CRC 'C'
#define CHECK_NUM NAK

// Xmodem ����֡У��
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType);

unsigned char XmodemReceive(unsigned char checkType);

void SendXmodemCtrlChar(unsigned char Ctrltype);

//
unsigned char SaveXmodemData(void);

// CRC����
int CalCRC(char *ptr, int count);

#endif /* __XMODEM_H_ */

