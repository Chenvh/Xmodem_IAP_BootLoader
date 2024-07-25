#ifndef __XMODEM_H_
#define __XMODEM_H_


/* Xmodem 数据帧格式
---------------------------------------------------------------------------
|     Byte1     |    Byte2    |     Byte3      |Byte4~Byte131|  Byte132   |
|-------------------------------------------------------------------------|
|Start Of Header|Packet Number|~(Packet Number)| Packet Data |  Check Sum |
---------------------------------------------------------------------------

Xmodem-CRC16 数据帧格式
------------------------------------------------------------------------------
|     Byte1     |    Byte2    |     Byte3      |Byte4~Byte131|Byte132~Byte133|
|----------------------------------------------------------------------------|
|Start Of Header|Packet Number|~(Packet Number)| Packet Data |   16Bit CRC   |
------------------------------------------------------------------------------

Xmode 传输流程
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

Xmodem-CRC16 传输流程
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

双支持传输流程
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


#define SOH     0x01    // Start Of Header modem 128数据帧头
#define STX     0x02    // 1k-XModem 数据帧头
#define EOT     0x04    // 发送结束标志
#define ACK     0x06    // 应答标志
#define NAK     0x15    // 非应答标志/重发标志
#define CAN     0x18    // 取消发送标志
#define CTRLZ   0x1A    // 帧空白填充字符
#define CRC16   0x43    // 使用 CRC16 校验标志


#define CHECK_CRC 'C'
#define CHECK_NUM NAK

// 当前数据包号
extern unsigned int CurrentPackNum;

/**
 * @brief   Xmodem数据包校验
 * @param   packet      接收到的数据包
 * @param   pLen        数据包长度
 * @param   checkType   校验类型：NAK 校验 或 CHECK_CRC CRC校验
 * @return  -1为帧头检测失败，-2帧号检测失败，-3 CRC校验失败， 0为校验成功
*/
unsigned char XmodemPacketCheck(unsigned char *packet, unsigned int pLen, unsigned checkType);

unsigned char XmodemReceive(unsigned char checkType);

void SendXmodemCtrlChar(unsigned char Ctrltype);

//
unsigned char SaveXmodemData(void);

// CRC计算
int CalCRC(char *ptr, int count);

#endif /* __XMODEM_H_ */

