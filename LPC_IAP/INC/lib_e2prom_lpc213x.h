#ifndef _LIB_E2PROM_LPC213X_H_
  #define _LIB_E2PROM_LPC213X_H_


#include "SystemDef.h"
#include "lib_def_lpc213x.h"

#define IAP_ENTER_ADR   0x7FFFFFF1  // IAP��ڵ�ַ����

/*
 *  ����IAP������
 */
#define IAP_Prepare             50                                      /*  ѡ������                    */
                                                                        /*  ����ʼ�����š����������š�  */
#define IAP_RAMTOFLASH          51                                      /*  �������� FLASHĿ���ַ      */
                                                                        /*  RAMԴ��ַ    ����д���ֽ��� */
                                                                        /*  ϵͳʱ��Ƶ�ʡ�              */
#define IAP_ERASESECTOR         52                                      /*  ��������    ����ʼ������    */
                                                                        /*  ���������š�ϵͳʱ��Ƶ�ʡ�  */
#define IAP_BLANKCHK            53                                      /*  �������    ����ʼ�����š�  */
                                                                        /*  ���������š�                */
#define IAP_READPARTID          54                                      /*  ������ID    ���ޡ�          */
#define IAP_BOOTCODEID          55                                      /*  ��Boot�汾�š��ޡ�          */
#define IAP_COMPARE             56                                      /*  �Ƚ�����    ��Flash��ʼ��ַ */
                                                                        /*  RAM��ʼ��ַ����Ҫ�Ƚϵ�     */
                                                                        /*  �ֽ�����                    */
/*
 *  ����IAP����״̬��
 */
#define CMD_SUCCESS                                0
#define INVALID_COMMAND                            1
#define SRC_ADDR_ERROR                             2
#define DST_ADDR_ERROR                             3
#define SRC_ADDR_NOT_MAPPED                        4
#define DST_ADDR_NOT_MAPPED                        5
#define COUNT_ERROR                                6
#define INVALID_SECTOR                             7
#define SECTOR_NOT_BLANK                           8
#define SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION    9
#define COMPARE_ERROR                              10
#define BUSY                                       11

/* 
 *  ����CCLKֵ��С����λΪKHz 
 */
#define IAP_FCCLK            (60000)                                    /* ��Ƶ��ֵ����ͬ��Ƶ��ͬ */

#define EEPROM_STARTSEC            4                                    /* ������ΪEEPROM��Falsh */                                                                    /* ��ʼ�����ͽ������� */
#define EEPROM_ENDSEC              8

#define EE_SUUCEESS                0                                    /* EEPROMд�����ɹ���� */
#define IAP_ERROR                  1                                    /* �ڲ�IAP�������ó��� */
#define PARA_BANK_ERROR            2                                    /* �����İ����� */
#define PARA_SRCADDR_ERROR         3                                    /* д����ʱ��Դ��ַ����(z�ֶ���) */
#define PARA_OVERFLOW_ERROR        4                                    /* д����� */


//IAPд���ֽ���
typedef enum
{
    MODE0 = 256,
    MODE1 = 512,
	MODE2 = 1024,
    MODE3 = 4096,
}IAPWRITEMODE;

//IAPд���ֽ���
typedef enum
{
    SECTOR0,
    SECTOR1,
	SECTOR2,
    SECTOR3,
	SECTOR4,
    SECTOR5,
	SECTOR6,
    SECTOR7,
	SECTOR8,
}IAPCHANNEL;
/*********************************************************************************************************
**   ע�⣺���øú�������ʹ����ΪEEPROM��Flashȫ���������Ȼ�ʹǰ��д���������ݶ�ʧ
*********************************************************************************************************/
uint8 eepromWrite(uint32 WriteAddr, uint8 *pBuffer, IAPWRITEMODE mode);
uint8 eepromErase(IAPCHANNEL StartSec, IAPCHANNEL EndSec);
/*********************************************************************************************************
** src_addr��ʾƫ����
*********************************************************************************************************/
void eepromRead(uint32 ReadAddr, uint8 *pBuffer, uint16 NumToRead);
#endif


