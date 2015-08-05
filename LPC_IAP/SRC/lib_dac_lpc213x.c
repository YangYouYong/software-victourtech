/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x DACģ������
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_dac_lpc213x.h"
#include "lib_map_lpc213x.h"
#include "lib_def_lpc213x.h"


/******************************************************/

typedef struct 
{
    volatile uint32 DACR;
}DAC_TypeDef;

/* VIC�ṹ���ַ��ʼ�� */
DAC_TypeDef *DAC = (DAC_TypeDef *)DAC_BASE;

/************************************************************************
Function: void DAC_SetOutputVal(uint16 val)
Description: ���DAֵ
Input: val��DAֵ��0-1203
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void DAC_SetOutputVal(uint16 val)
{
    uint16 DACR_temp = DAC->DACR;
	DACR_temp &= ~(0x3ff << 6);//0xffff003f;
	DACR_temp |= val << 6;
	DAC->DACR = DACR_temp;    
}

/************************************************************************
Function: void DAC_OutputVoltage(uint16 val)
Description: �����ѹֵ
Input: val:��ѹֵ����λΪmv
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void DAC_OutputVoltage(uint16 val)
{
    uint16 dacVal = 0;
    uint16 DACR_temp = DAC->DACR;
    dacVal = val * 1023 / AD_REF;
    dacVal &= 0x3ff;
    
  	DACR_temp &= ~(0x3ff << 6);//0xffff003f;
	DACR_temp |= val << 6;
	DAC->DACR = DACR_temp;  
}

/************************************************************************
Function: void DAC_SetBIAS(void)
Description: ����DAC���bias
Input: val:��ѹֵ����λΪmv
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL DAC_SetBIAS(__in uint8 bias)
{
    if(bias == DAC_BIAS_700)
    {
        DAC->DACR &= ~(1 << 16);
    }
    else if(bias == DAC_BIAS_350)
    {
        DAC->DACR &= ~(1 << 16);
        DAC->DACR |= (1 << 16);
    }
    else
        return FALSE;
    
    return TRUE;
}







