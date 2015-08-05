/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_mam_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x MAMģ������
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_mam_lpc213x.h"
#include "lib_map_lpc213x.h"

/******************************************************/


typedef struct 
{
	volatile uint32 MAMCR;
	volatile uint32 MAMTIM;
}MAM_TypeDef;

/* CRC�ṹ���ַ��ʼ�� */
MAM_TypeDef *MAM = (MAM_TypeDef *)MAM_BASE;

//MAM�Ĵ���
#define MAMCR_MASK  0x03
#define MAMTIM_MASK  0x07

/************************************************************************
Function: BOOL MAM_SetMode(uint32 mode)
Description:  ����MAMģ�����ģʽ
Input:  mode:  MAM_CONTROL_DISABLE:�ر�MAMģ��
               MAM_CONTROL_PARTICAL������ʹ��
               MAM_CONTROL_FULL��ȫ��ʹ��
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL MAM_SetMode(uint32 mode)
{

	MAM->MAMCR &= ~MAMCR_MASK;
	MAM->MAMCR |= mode;

	return TRUE;
}


/************************************************************************
Function: uint32 MAM_GetMode(void)
Description: ȡ��MAM����ģ��ģʽ
Input:  none
Output: MAM����ģ��ģʽ
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 MAM_GetMode(void)
{
	return (MAM->MAMCR & MAMCR_MASK);
}


/************************************************************************
Function: BOOL MAM_SetFetchCycle(uint32 cycle)
Description:  ����MAMģ�������ʱʱ��
Input:  cycle:  MAM_FETCH_1:��ʱ1��ʱ������
                MAM_FETCH_2:��ʱ2��ʱ������
                MAM_FETCH_3:��ʱ3��ʱ������
				MAM_FETCH_4:��ʱ4��ʱ������
				MAM_FETCH_5:��ʱ5��ʱ������
				MAM_FETCH_6:��ʱ6��ʱ������
				MAM_FETCH_7:��ʱ7��ʱ������
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL MAM_SetFetchCycle(uint32 cycle)
{

	MAM->MAMCR &= ~MAMTIM_MASK;
	MAM->MAMCR |= cycle;

	return TRUE;
}


/************************************************************************
Function: uint32 MAM_GetFetchCycle(void)
Description: ȡ��MAMģ�������ʱʱ��
Input:  none
Output: MAMģ�������ʱʱ��
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 MAM_GetFetchCycle(void)
{
	return (MAM->MAMTIM & MAMTIM_MASK);
}
