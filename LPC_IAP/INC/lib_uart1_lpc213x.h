#ifndef _LIB_UART1_LPC213X_H_
  #define _LIB_UART1_LPC213X_H_


#include "SystemDef.h"


//������
#define BAUD_075          ((uint32)0x4B)
#define BAUD_110          ((uint32)0x6E)
//#define BAUD_134_5        ((uint32)0x00000004)
#define BAUD_150          ((uint32)0x96)
#define BAUD_300          ((uint32)0x12c)
#define BAUD_600          ((uint32)0x258)
#define BAUD_1200         ((uint32)0x4B0)
#define BAUD_1800         ((uint32)0x708)
#define BAUD_2400         ((uint32)0x960)
#define BAUD_4800         ((uint32)0x12c0)
#define BAUD_7200         ((uint32)0x1c20)
#define BAUD_9600         ((uint32)0x2580)
#define BAUD_14400        ((uint32)0x3840)
#define BAUD_19200        ((uint32)0x4B00)
#define BAUD_38400        ((uint32)0x9600)
#define BAUD_56K          ((uint32)0xDAC0)
#define BAUD_128K         ((uint32)0x1F400)
#define BAUD_115200       ((uint32)0x1C200)
#define BAUD_57600        ((uint32)0xE100)
//#define BAUD_USER         ((uint32)0x10000000)

//�ֽڳ���
#define DATABITS_5        ((uint32)0x00)
#define DATABITS_6        ((uint32)0x01)
#define DATABITS_7        ((uint32)0x02)
#define DATABITS_8        ((uint32)0x03)

//ֹͣλ
#define STOPBITS_10       ((uint32)0x00)
#define STOPBITS_15       ((uint32)0x00)
#define STOPBITS_20       ((uint32)(0x01 << 2))

//��żУ��
#define PARITY_NONE       ((uint32)0xff)
#define PARITY_ODD        ((uint32)0x00)
#define PARITY_EVEN       ((uint32)(0x01 << 4))
#define PARITY_MARK       ((uint32)(0x02 << 4))
#define PARITY_SPACE      ((uint32)(0x03 << 4))


//������FIFO�жϴ����ֽ�
#define TRIGGER_1        (0x00)
#define TRIGGER_4        (0x01 << 6)
#define TRIGGER_8        (0x02 << 6)
#define TRIGGER_14       (0x03 << 6)

typedef struct
{
    uint32 baud;
    uint32 wordlen;
    uint32 stopbit;
    uint32 patity;
    uint32 trigger;
}COMINFO, *PCOMINFO;

//�ж�λ
#define UART1_INT_RDA      0x01
#define UART1_INT_THRE     0x02
#define UART1_INT_RXLS     0x04
#define UART1_INT_ABE      (1 << 8)
#define UART1_INT_ABT      (1 << 9)

//�ж�״̬
#define UART1_INTFLAG_RLS            (3 << 1)
#define UART1_INTFLAG_RDA            (2 << 1)
#define UART1_INTFLAG_CTI            (6 << 1)
#define UART1_INTFLAG_THRE           (1 << 1)
#define UART1_INTFLAG_ABE            (1 << 8)
#define UART1_IINTFLAG_ABT           (1 << 9)
#define UART1_INTFLAG_ALL            (255)
#define UART1_INTFLAG_MASK           (0x07 << 1)

//��״̬��־λ
#define UART1_LSR_RDR               (0x01)
#define UART1_LSR_OE                (0x02)
#define UART1_LSR_PE                (0x04)
#define UART1_LSR_FE                (0x08)
#define UART1_LSR_BI                (0x10)
#define UART1_LSR_THRE              (0x20)
#define UART1_LSR_TEMT              (0x40)
#define UART1_LSR_RXFE              (0x80)



//�ӿں���
void UART1_RecvPacket(__out puint8 buf,  __in uint8 readLen, __out puint8 readedLen);
uint8 UART1_RecvByte(void);
void UART1_SendData(__in puint8 buf, __in uint8 len);
uint32 UART1_GetBaud(void);
uint32 UART1_SetBaud(uint32 baud);
void UART1_EnableInt(uint32 intFlag);
void UART1_DisableInt(uint32 intFlag);
BOOL UART1_IsIntPending(void);
uint32 UART1_GetIntFlag(void);
void UART1_EnableFIFO(void);
void UART1_DisableFIFO(void);
void UART1_ResetRXFIFO(void);
void UART1_ResetTXFIFO(void);
void UART1_SetRXTrigger(uint8 trigger);
void UART1_SetLineControl(uint8 len, uint8 stopbit, uint8 parity);
void UART1_EnableBreakTransmission(void);
void UART1_DisableBreakTransmission(void);
uint32 UART1_GetLineStatus(void);
void UART1_EnableSendData(void);
void UART1_DisableSendData(void);
void UART1_Open(PCOMINFO pComInfo);










#endif

