/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x �ж�����ģ������
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_vic_lpc213x.h"
#include "lib_map_lpc213x.h"

/*****************************************************/
/* VIC�ṹ���ַ��ʼ�� */
VIC_TypeDef *VIC = (VIC_TypeDef *)VIC_BASE;


/************************************************************************
Function: void VIC_ProduceSoftInt(uint32 intNum)
Description: �����������������ж�
Input:  intNum:�жϺ�
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_ProduceSoftInt(uint32 intBit)
{
	VIC->VICSoftInt |= intBit;
}

/************************************************************************
Function: void VIC_ClearSoftInt(uint32 intNum)
Description: ����������������ж�λ
Input:  intNum:�жϺ�
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_ClearSoftInt(uint32 intBit)
{
	VIC->VICSoftIntClear |= intBit;
}

/************************************************************************
Function: uint32 VIC_GetIntStatus(void)
Description: ȡ���ж�ԭʼ״̬�������ж���û��ʹ��
Input:  none
Output: none
Return: �ж�״̬
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetRawIntStatus(void)
{
	return VIC->VICRawIntr;
}


/************************************************************************
Function: void VIC_EnableInt(uint32 intNum)
Description: �ж�ʹ��
Input:  intNum���жϺ�
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_EnableInt(uint32 intBit)
{
	VIC->VICIntEnable |= intBit;
}


/************************************************************************
Function: uint32 VIC_GetEnabledInt(void)
Description: ȡ��ʹ�ܵ��жϺ�
Input:  none
Output: none
Return: ʹ�ܵ��жϺ�
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetEnabledInt(void)
{
	return VIC->VICIntEnable;
}


/************************************************************************
Function: void VIC_DisableInt(uint32 intNum)
Description: �ر��ж�
Input:  intNum:�жϺ�
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_DisableInt(uint32 intBit)
{
	VIC->VICIntEnClr |= intBit;
}


/************************************************************************
Function: BOOL VIC_IntSelect(uint32 intBit, INTTYPE type)
Description: �ж�ͨ��ѡ��
Input:  intNum:ͨ����
        type��IRQ���󶨵�IRQ�ж�   FIQ���󶨵�FIQ�ж�
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL VIC_IntSelect(uint32 intBit, INTTYPE type)
{
	if(type == IRQ)
	{
		VIC->VICIntSelect &= ~(intBit);
	}
	else if(type == FIQ)
	{
		VIC->VICIntSelect |= intBit;
	}
	else
		return FALSE;
	
	return TRUE;
}


/************************************************************************
Function: uint32 VIC_GetIRQIntStatus(void)
Description: ȡ��ʹ�ܵ�IRQ�жϵ�״̬
Input:  none
Output: none
Return: �ж�״̬
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetIRQIntStatus(void)
{
	return VIC->VICIRQStatus;
}


/************************************************************************
Function: uint32 VIC_GetFIQIntStatus(void)
Description: ȡ��ʹ�ܵ�FIQ�жϵ�״̬
Input:  none
Output: none
Return: �ж�״̬
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 VIC_GetFIQIntStatus(void)
{
	return VIC->VICFIQStatus;
}


/************************************************************************
Function: void VIC_IRQBind(uint8 irqChannel, uint8 intNum, void *intAddr)
Description: ����IRQͨ���͵�ַ��
Input:  irqChannel:irqͨ����
		intNum:�жϺ�
        intAddr:�жϵ�ַ
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_VectIRQBind(uint8 irqChannel, uint32 intNum, uint32 intAddr)
{
	VIC->VICVectAddr[irqChannel] = intAddr;
    VIC->VICVectCntl[irqChannel] = 0x20 | intNum;
}

/************************************************************************
Function: void VIC_NonVectIRQBind(uint8 irqChannel, uint8 intNum, void *intAddr)
Description: ������IRQͨ���͵�ַ��
Input:  irqChannel:irqͨ����
		intNum:�жϺ�
        intAddr:�жϵ�ַ
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_NonVectIRQBind(uint32 intAddr)
{
	if(VIC->VICDefVectAddr == 0x00)  //��һ�����÷������ж�ISR��ַ
		VIC->VICDefVectAddr = intAddr;
}

/************************************************************************
Function: uint32 VIC_GetCurVectAddr(void)
Description: ȡ�õ�ǰ���ȼ���ߵ�����IRQ���߷�����IRQ��ISR�ĵ�ַ
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
//uint32 VIC_GetCurVectAddr(void)
//{
//	return VIC->VICCurVectAddr;
//}

/************************************************************************
Function: void VIC_ClearCurVectAddr(void)
Description: �����ǰ�ж�ISR��ַ��Ϊ��һ���ж���׼��
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
//void VIC_ClearCurVectAddr(void)
//{
//	VIC->VICCurVectAddr = 0;
//}


/************************************************************************
Function: none
Description: none
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void VIC_SetVICAcceccMode(VICACCESSMODE mode)
{
	if(mode == USER)
	{
		VIC->VICProtection = 0x00;
	}
	else if(mode == PRIVILEGE)
	{
		VIC->VICProtection = 0x01;
	}
}
















