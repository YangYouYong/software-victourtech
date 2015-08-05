/*****************************************************************
**  Copyright (C), 2013-2014, ZCJ.
**  FileName: Flash.c
**  Author: 
**  Version: V1.0.0 +
**  Date: 2014-5-20
**  Description: flash��д����
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_e2prom_lpc213x.h"
/*
 *  ���庯��ָ��  
 */
void (*IAP_Entry) (unsigned long ulParam_tab[], unsigned long ulPesult_tab[]) = (void(*)())IAP_ENTER_ADR;

unsigned long   GulParamin[8];                                           /* IAP��ڲ��������� */
unsigned long   GulParamout[8];

/*  IAP���ڲ��������� */
/*********************************************************************************************************
** Function name:       sectorPrepare
** Descriptions:        IAP��������ѡ���������50
** input parameters:    ucSec1:           ��ʼ����
**                      ucSec2:           ��ֹ����
** output parameters:   GulParamout[0]:   IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:   IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  sectorPrepare (unsigned char  ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_Prepare;                                        /* ���������� */
    GulParamin[1] = ucSec1;                                             /* ���ò��� */
    GulParamin[2] = ucSec2;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */
   
    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       ramCopy
** Descriptions:        ����RAM�����ݵ�FLASH���������51
** input parameters:    ulDst:             Ŀ���ַ����FLASH��ʼ��ַ����512�ֽ�Ϊ�ֽ�
**                      ulSrc:             Դ��ַ����RAM��ַ����ַ�����ֶ���
**                      ulNo:              �����ֽڸ�����Ϊ512/1024/4096/8192
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  ramCopy (unsigned long  ulDst, unsigned long  ulSrc, unsigned long  ulNo)
{  
    GulParamin[0] = IAP_RAMTOFLASH;                                     /* ���������� */
    GulParamin[1] = ulDst;                                              /* ���ò��� */
    GulParamin[2] = ulSrc;
    GulParamin[3] = ulNo;
    GulParamin[4] = IAP_FCCLK;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */
    
    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       sectorErase
** Descriptions:        �����������������52
** input parameters:    ucSec1             ��ʼ����
**                      ucSec2             ��ֹ����92
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  sectorErase (unsigned char ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_ERASESECTOR;                                    /* ���������� */
    GulParamin[1] = ucSec1;                                             /* ���ò��� */
    GulParamin[2] = ucSec2;
    GulParamin[3] = IAP_FCCLK;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */

    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       blankChk
** Descriptions:        ������գ��������53
** input parameters:    ucSec1:              ��ʼ����
**                      ucSec2:              ��ֹ����92
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  blankChk (unsigned char  ucSec1, unsigned char  ucSec2)
{  
    GulParamin[0] = IAP_BLANKCHK;                                       /* ���������� */
    GulParamin[1] = ucSec1;                                             /* ���ò��� */
    GulParamin[2] = ucSec2;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */

    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       parIdRead
** Descriptions:        ��������ʶ�ţ��������54
** input parameters:    ��
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  parIdRead (void)
{
    GulParamin[0] = IAP_READPARTID;                                     /* ���������� */
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */

    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       codeIdBoot
** Descriptions:        ��Boot����汾�ţ��������55
** input parameters:    ��
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  codeIdBoot (void)
{
    GulParamin[0] = IAP_BOOTCODEID;                                     /* ���������� */
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */

    return (GulParamout[0]);                                            /* ����״̬�� */
}

/*********************************************************************************************************
** Function name:       dataCompare
** Descriptions:        У�����ݣ��������56
** input parameters:    ulDst:             Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
**                      ulSrc:             Դ��ַ����FLASH/RAM��ַ����ַ�����ֶ���
**                      ulNo:              ���Ƚϵ��ֽ���������ֵӦ��Ϊ4�ı�����
** output parameters:   GulParamout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      GulParamout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
unsigned long  dataCompare (unsigned long  ulDst, unsigned long  ulSrc, unsigned long  ulNo)
{  
    GulParamin[0] = IAP_COMPARE;                                        /* ���������� */
    GulParamin[1] = ulDst;                                              /* ���ò��� */
    GulParamin[2] = ulSrc;
    GulParamin[3] = ulNo;
    (*IAP_Entry)(GulParamin, GulParamout);                              /* ����IAP������� */

    return (GulParamout[0]);                                            /* ����״̬�� */
}

/********************************************************************************************************
** �û��ӿڲ�
********************************************************************************************************/
/*********************************************************************************************************
** Function name:       eepromWrite
** Descriptions:        ���øú�������ģ��дEEPROM���������д����256�ֽ�
** input parameters:    bank:��EEPROM�ռ俪ʼ�Ĵ洢��bank���,һ��bank 256�ֽ�
**                      src_addr:�洢���ݵ�Դ��ַ
** output parameters:   ״̬��Ϣ
** Returned value:      ��
**                      һ��д�������Ϊ256�ֽ�
ע�⣺���øú�������ʹ����ΪEEPROM��Flashȫ������������ʹǰ��д���������ݶ�ʧ
*********************************************************************************************************/
uint8 eepromWrite(uint32 WriteAddr, uint8 *pBuffer, IAPWRITEMODE mode)
{
    uint8 ucErr = 0;
	
	__disable_irq();

    if (WriteAddr >  64 * 1024)
    { 
		__enable_irq();
        return PARA_BANK_ERROR;
    }  
    
    if ((((unsigned long)pBuffer) % 4) != 0 ) 
    {
		__enable_irq();
       return PARA_SRCADDR_ERROR;  
    }
	
	ucErr = sectorPrepare(EEPROM_STARTSEC, EEPROM_ENDSEC);
	ucErr = ramCopy(WriteAddr, (unsigned long)pBuffer, mode);
	ucErr = dataCompare(WriteAddr, (unsigned long)pBuffer, mode);		
	  
	if (ucErr != CMD_SUCCESS) 
	{                       /*  IAP�������ó��� */
		__enable_irq();  
		return IAP_ERROR;
    }
	
	__enable_irq();
    return EE_SUUCEESS;
}
/*********************************************************************************************************
** Function name:       eepromWrite
** Descriptions:        ���øú�������ģ��дEEPROM���������д����256�ֽ�
** input parameters:    bank:��EEPROM�ռ俪ʼ�Ĵ洢��bank���,һ��bank 256�ֽ�
**                      src_addr:�洢���ݵ�Դ��ַ
** output parameters:   ״̬��Ϣ
** Returned value:      ��
**                      һ��д�������Ϊ256�ֽ�
ע�⣺���øú�������ʹ����ΪEEPROM��Flashȫ������������ʹǰ��д���������ݶ�ʧ
*********************************************************************************************************/
uint8 eepromErase(IAPCHANNEL StartSec, IAPCHANNEL EndSec)
{
    uint8 ucErr = 0;
	
	__disable_irq();
 
	ucErr = sectorPrepare(StartSec, EndSec);
	ucErr = sectorErase(StartSec, EndSec);
	ucErr = blankChk(StartSec, EndSec);
	  
	if(ucErr != CMD_SUCCESS)
	{                       /*  IAP�������ó��� */
		__enable_irq();  
		return IAP_ERROR;
    }
	
	__enable_irq();
    return EE_SUUCEESS;
}
/*********************************************************************************************************
** Function name:       eepromRead
** Descriptions:        ���øú������Զ���EEPROM_STARTSEC(EEPROM��ʼ������ʼ������)
** input parameters:    src_addr:����EEPROM�洢�ռ��ƫ������ַ
**                      dst_addr:���ն�ȡ���ݵ�Դ��ַ
**                      num:��ȡ���ֽ���
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
/*void eepromRead(uint32 src_addr, uint8 *dst_addr, uint32 num)
{
    uint32 i;
  
    for (i = 0; num != 0; num--, i++) 
    {    
        *(dst_addr + i) = *(((uint8 * )(EEPROM_STARTSEC * 1024 * 4 + src_addr)) + i);
    }
}*/
void eepromRead(uint32 ReadAddr, uint8 *pBuffer, uint16 NumToRead)
{
    uint16 i;
  
    for (i = 0; i < NumToRead; i++)
    {    
        pBuffer[i] = *(uint8 * )ReadAddr;
        ReadAddr += 1;
    }
}

