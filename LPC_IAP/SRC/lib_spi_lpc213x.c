/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x SPIģ������
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_spi_lpc213x.h"
#include "lib_def_lpc213x.h"

/* VIC�ṹ���ַ��ʼ�� */
SPI_TypeDef *SPI = (SPI_TypeDef *)SPI_BASE;

/************************************************************************
Function: void SPI_Open(PSPIINFO info)
Description: ��SPI
Input: info��SPI��������
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SPI_Open(PSPIINFO info)
{
    SPI->S0SPCR &= ~(1 << 2);
    SPI->S0SPCR &= ~(0x0f << 8);
    //SPI->S0SPCR |= info->bits;
    
    SPI->S0SPCR &= ~(1 << 3);
    SPI->S0SPCR |= info->cpha;
    
    SPI->S0SPCR &= ~(1 << 4);
    SPI->S0SPCR |= info->cpol;
    
    SPI->S0SPCR &= ~(1 << 5);
    SPI->S0SPCR |= info->mstr;
    
    SPI->S0SPCR &= ~(1 << 6);
    SPI->S0SPCR |= info->lsbf;
}

/************************************************************************
Function: uint32 SPI_SetClock(uint32 clock)
Description: ����SPIʱ��
Input: clock:ʱ��ֵ
Output: none
Return: ������ɺ��ʱ��ֵ
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SPI_SetClock(uint32 clock)
{
    uint8 divVal = CPU_PCLK / clock;
    divVal &= 0xfe;
    
    if(divVal < 8)
        divVal = 8;
    
    SPI->S0SPCCR = divVal;
    
    return (CPU_PCLK / divVal);
}

/************************************************************************
Function: uint8 SPI_WaitTransDone(void)
Description: �ȴ�SPI���ݴ������
Input: none
Output: none
Return: 0���ɹ�
        -1����ʱ����ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SPI_WaitTransDone(void)
{
    while(!(SPI->S0SPSR & (1 << 7)));
    
    return 0;
}

#if 0
/************************************************************************
Function: uint32 SPI_SetClock(uint32 clock)
Description: ����SPIʱ��
Input: clock:ʱ��ֵ
Output: none
Return: ������ɺ��ʱ��ֵ
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SPI_GetClock(void)
{
   return (CPU_PCLK / (SPI->S0SPCCR));
}


/************************************************************************
Function: void SPI_EnableInt(void)
Description: ʹ��SPI�ж�
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SPI_EnableInt(void)
{
    SPI->S0SPCR |= (1 << 7);
}

/************************************************************************
Function: void SPI_DisableInt(void)
Description: ��ֹSPI�ж�
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SPI_DisableInt(void)
{
    SPI->S0SPCR &= ~(1 << 7);
}

/************************************************************************
Function: uint32 SPI_GetStatus(void)
Description: ȡ��SPI״̬
Input: none
Output: none
Return: SPI״̬
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SPI_GetStatus(void)
{
    return SPI->S0SPSR;
}


/************************************************************************
Function: void SPI_GetIntFlag(void)
Description: ȡ���жϱ�־λ
Input: none
Output: none
Return: 0x00:�ж�δ��λ
        0x01���ж���λ
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SPI_GetIntFlag(void)
{
    return (SPI->S0SPINT & 0x01);
}

/************************************************************************
Function: void SPI_ClearIntFlag(void)
Description: ����жϱ�־λ
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SPI_ClearIntFlag(void)
{
    SPI->S0SPINT = 0x01;
}


/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint16 SPI_GetData(void)
{
    return SPI->S0SPDR;
}


/************************************************************************
Function: 
Description: none
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SPI_WriteData(uint16 data)
{
    SPI->S0SPDR = data;
}

#endif
