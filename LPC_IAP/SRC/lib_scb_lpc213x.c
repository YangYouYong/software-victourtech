/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: lib_scb_lpc213x.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: lpc213x ϵͳ����ģ������
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "lib_scb_lpc213x.h"
#include "lib_map_lpc213x.h"


/***********************************************************
*
************************************************************/
#define OSC_FREQUENCY 12000000
#define MAX_FREQUENCY 60000000
#define MIN_FREQUENCY 10000000

/******************************************************/

typedef struct 
{
	volatile uint32 MEMMAP;
	volatile uint32 Reserved0[15];
	volatile uint32 PLLCON;
	volatile uint32 PLLCFG;
	volatile uint32 PLLSTAT;
	volatile uint32 PLLFEED;
	volatile uint32 Reserved1[12];
	volatile uint32 PCON;
	volatile uint32 PCONP;
	volatile uint32 Reserved2[14];
	volatile uint32 APBDIV;
	volatile uint32 Reserved3[15];
	volatile uint32 EXTINT;
	volatile uint32 INTWAKE;
	volatile uint32 EXTMODE;
	volatile uint32 EXTPOLAR;
	volatile uint32 Reserved4[12];
	volatile uint32 RSID;
	volatile uint32 CSPR;
	volatile uint32 Reserved[6];
	volatile uint32 SCS;
	
}SCB_TypeDef;

/* CRC�ṹ���ַ��ʼ�� */
SCB_TypeDef *SCB = (SCB_TypeDef *)SCB_BASE;

//SCB�Ĵ���
#define EXTINT_MASK 0x0f
#define EXTWAKE_MASK 0xc00f
#define EXTMODE_MASK 0x0f
#define EXTPOLAR_MASK 0x0f
#define SCS_MASK 0x03
#define MEMMAP_MASK 0x03

//PLL�Ĵ���
#define PLL_ENABLE (0x01)
#define PLL_CONNECT (0x02)

#define PLL_STS_ENABLE (1 << 8)
#define PLL_STS_CONNECT (1 << 9)
#define PLL_STS_LOCK (1 << 10)
#define PLL_M_MASK (0x1f)
#define FCCO_LOW 156000000
#define FCCO_HIGH 320000000

//power
#define PCON_MASK (0x1f) 
#define PCONP_MASK (0x1817be)
#define RSID_MASK (0x0f)
#define APBDIV_MASK (0x03)

/************************************************************************
Function: BOOL SCB_ClearEXTINT(uint32 bit)
Description:  �����ⲿ�ж�״̬�Ĵ���
Input:  bit: SCB_EXTINT_EINT0  �ⲿ�ж�0λ
			 SCB_EXTINT_EINT1  �ⲿ�ж�1λ
			 SCB_EXTINT_EINT2  �ⲿ�ж�2λ
			 SCB_EXTINT_EINT3  �ⲿ�ж�3λ
			 SCB_EXTINT_ALL   �ⲿ�ж�0-3λ
Output: none
Return: TRUE������ɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearEXTINT(__in uint32 bit)
{	
	
	bit &= EXTINT_MASK;
	SCB->EXTINT |= bit;
	
	return TRUE;
}


/************************************************************************
Function: uint32 SCB_GetEXTINT(uint32 bit)
Description:  ȡ���ⲿ�ж�״̬�Ĵ���
Input:  bit: SCB_EXTINT_EINT0  �ⲿ�ж�0λ
			 SCB_EXTINT_EINT1  �ⲿ�ж�1λ
			 SCB_EXTINT_EINT2  �ⲿ�ж�2λ
			 SCB_EXTINT_EINT3  �ⲿ�ж�3λ
			 SCB_EXTINT_ALL   �ⲿ�ж�0-3λ
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXTINT(__in uint32 bit)
{
	bit &= EXTINT_MASK;
	
	return (SCB->EXTINT & bit);
}

/************************************************************************
Function: BOOL SCB_IsEXTINTSet(bit)
Description:  ȡ���ⲿ�ж�״̬�Ĵ����ض�һλ��״̬
Input:  bit: SCB_EXTINT_EINT0  �ⲿ�ж�0λ
			 SCB_EXTINT_EINT1  �ⲿ�ж�1λ
			 SCB_EXTINT_EINT2  �ⲿ�ж�2λ
			 SCB_EXTINT_EINT3  �ⲿ�ж�3λ
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_IsEXTINTSet(__in uint32 bit)
{
	bit &= EXTINT_MASK;
	if(SCB->EXTINT & bit)
	{
		return TRUE;
	}
	
	return FALSE;
}

/************************************************************************
Function: BOOL SCB_ClearWakeUpInt(uint32 intFlag)
Description: �����жϻ���
Input:  intFlag:  SCB_EXTWAKE_EINT0 �ⲿ�ж�0����
				  SCB_EXTWAKE_EINT1 �ⲿ�ж�1����
				  SCB_EXTWAKE_EINT2 �ⲿ�ж�2����
				  SCB_EXTWAKE_EINT3 �ⲿ�ж�3����
				  SCB_EXTWAKE_BOD BOD�жϻ���
				  SCB_EXTWAKE_RTC RTC�жϻ���
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearWakeUpInt(__in uint32 intFlag)
{
	intFlag &= EXTWAKE_MASK;
	SCB->INTWAKE &= ~intFlag;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: �����жϻ���
Input:  intFlag:  SCB_EXTWAKE_EINT0 �ⲿ�ж�0����
				  SCB_EXTWAKE_EINT1 �ⲿ�ж�1����
				  SCB_EXTWAKE_EINT2 �ⲿ�ж�2����
				  SCB_EXTWAKE_EINT3 �ⲿ�ж�3����
				  SCB_EXTWAKE_BOD BOD�жϻ���
				  SCB_EXTWAKE_RTC RTC�жϻ���
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetWakeUpInt(__in uint32 intFlag)
{
	intFlag &= EXTWAKE_MASK;
	SCB->INTWAKE |= intFlag;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: ȡ���жϻ��ѱ�־
Input:  none
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetWakeUpInt(void)
{
	return (SCB->INTWAKE & EXTWAKE_MASK);
}

/************************************************************************
Function: BOOL SCB_SetEXINTMode_Level(uint32 channel)
Description: �����жϻ���,��ƽ
Input: channel���ж�ͨ������
       SCB_EXTMODE_EINT0���ⲿ�ж�0
	   SCB_EXTMODE_EINT1���ⲿ�ж�1
	   SCB_EXTMODE_EINT2���ⲿ�ж�2
	   SCB_EXTMODE_EINT3���ⲿ�ж�3
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTMode_Level(__in uint32 channel)
{
	channel &= EXTMODE_MASK;
	SCB->EXTMODE &= ~channel;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetEXINTMode_Edge(uint32 channel)
Description: �����жϻ��ѣ�����
Input:  channel���ж�ͨ������
       SCB_EXTMODE_EINT0���ⲿ�ж�0
	   SCB_EXTMODE_EINT1���ⲿ�ж�1
	   SCB_EXTMODE_EINT2���ⲿ�ж�2
	   SCB_EXTMODE_EINT3���ⲿ�ж�3
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTMode_Edge(__in uint32 channel)
{
	channel &= EXTMODE_MASK;
	SCB->EXTMODE |= channel;
	
	return TRUE;
}


/************************************************************************
Function: uint32 SCB_GetEXINTMode(uint32 channel)
Description: �����жϻ���
Input:  channel���ж�ͨ������
       SCB_EXTMODE_EINT0���ⲿ�ж�0
	   SCB_EXTMODE_EINT1���ⲿ�ж�1
	   SCB_EXTMODE_EINT2���ⲿ�ж�2
	   SCB_EXTMODE_EINT3���ⲿ�ж�3
Output: none
Return: ״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXINTMode(__in uint32 channel)
{
	channel &= EXTMODE_MASK; 
	return (SCB->EXTMODE & channel);
}


/************************************************************************
Function: BOOL SCB_SetEXINTPolarity_LowOrFall(uint32 channel)
Description: �����жϼ���,�͵�ƽ���½���
Input:  channel���ж�ͨ������
       SCB_EXTPOLAR_EINT0���ⲿ�ж�0
	   SCB_EXTPOLAR_EINT1���ⲿ�ж�1
	   SCB_EXTPOLAR_EINT2���ⲿ�ж�2
	   SCB_EXTPOLAR_EINT3���ⲿ�ж�3
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTPolarity_LowOrFall(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	SCB->EXTPOLAR &= ~channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: �����жϼ���,�ߵ�ƽ��������
Input:  channel���ж�ͨ������
       SCB_EXTPOLAR_EINT0���ⲿ�ж�0
	   SCB_EXTPOLAR_EINT1���ⲿ�ж�1
	   SCB_EXTPOLAR_EINT2���ⲿ�ж�2
	   SCB_EXTPOLAR_EINT3���ⲿ�ж�3
Output: none
Return: TRUE�����óɹ�
        FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetEXINTPolarity_HighOrRise(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	SCB->EXTPOLAR |= channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetWakeUpInt(uint32 intFlag)
Description: �����жϻ���
Input:  channel���ж�ͨ������
       SCB_EXTPOLAR_EINT0���ⲿ�ж�0
	   SCB_EXTPOLAR_EINT1���ⲿ�ж�1
	   SCB_EXTPOLAR_EINT2���ⲿ�ж�2
	   SCB_EXTPOLAR_EINT3���ⲿ�ж�3
Output: none
Return: �жϼ���״̬��־
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetEXINTPolarity(__in uint32 channel)
{
	channel &= EXTPOLAR_MASK;
	
	return (SCB->EXTPOLAR & channel);
}


/************************************************************************
Function: BOOL SCB_SetPortMode_APB(uint32 channel)
Description: ���ö˿�ģʽ
Input: channel�� 
      SCB_SCS_GPIO0:GPIO0�˿�
      SCB_SCS_GPIO1:GPIO1�˿�
Output: none
Return: TRUE�����óɹ�
        FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetPortMode_APB(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	SCB->SCS &= ~channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL SCB_SetPortMode_GPIO(uint32 channel)
Description: ���ö˿�ģʽ
Input: channel�� 
      SCB_SCS_GPIO0:GPIO0�˿�
      SCB_SCS_GPIO1:GPIO1�˿�
Output: none
Return: TRUE�����óɹ�
        FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetPortMode_GPIO(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	SCB->SCS |= channel;
	
	return TRUE;
}


/************************************************************************
Function: BOOL uint32 SCB_GetPortMode(uint32 channel)
Description: ȡ�ö˿����õ�ģʽ
Input: channel�� 
      SCB_SCS_GPIO0:GPIO0�˿�
      SCB_SCS_GPIO1:GPIO1�˿�
Output: none
Return: �˿�����ģʽ
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_GetPortMode(__in uint32 channel)
{
	channel &= SCS_MASK;
	
	return (SCB->SCS & channel);
}

/************************************************************************
Function: BOOL SCB_SetIntVecMap(uint32 mode)
Description: �����ڴ�ӳ��ģʽ
Input: mode:
	   SCB_MEMMAP_BOOTLOADER: boot loaderģʽ
	   SCB_MEMMAP_FLASH: �ڲ�flashģʽ
	   SCB_MEMMAP_RAM: �ڲ�ramģʽ
Output: none
Return: TRUE�����óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetIntVecMap(__in uint8 mode)
{
	mode &= MEMMAP_MASK;
	
	SCB->MEMMAP &= ~MEMMAP_MASK;
	SCB->MEMMAP |= mode;
	
	return TRUE;
}

/************************************************************************
Function: uint8 SCB_GetIntVecMap(void)
Description: ȡ���ڴ�ӳ��ģʽ
Input: none
Output: none
Return: �ڴ�ӳ��ģʽ
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetIntVecMap(void)
{	
	return (SCB->MEMMAP & MEMMAP_MASK);
}

/************************************************************************
Function: inline void SCB_FeedPLL(void)
Description: ���޸�PLLCFG��PLLCON֮ǰ������ô˺���
Input: none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void SCB_FeedPLL(void)
{
	SCB->PLLFEED = 0xAA;
	SCB->PLLFEED = 0x55;
}

/************************************************************************
Function: uint32 SCB_GetCurFrequence(void)
Description: ȡ�õ�ǰϵͳƵ��
Input: none
Output: none
Return: ���ص�ǰϵͳƵ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetCurFrequency(void)
{
	uint8 M_VAL = 0;
	uint32 curFreq = OSC_FREQUENCY;
	//PLL�Ѿ�����
	if(((SCB->PLLSTAT & PLL_STS_ENABLE) == PLL_STS_ENABLE) && ((SCB->PLLSTAT & PLL_STS_CONNECT) == PLL_STS_CONNECT))
	{
		M_VAL = (SCB->PLLCFG & PLL_M_MASK);
		curFreq *= (M_VAL + 1);
	}
	
	
	return curFreq;
}


/************************************************************************
Function: uint32 SCB_SetClockFreequence(uint32 frequence)
Description: ����ϵͳƵ��
Input: ϵͳƵ��
Output: none
Return: �ɹ�����֮ǰ��Ƶ�ʣ�ʧ�ܷ��أ�-1��
Author: 
Version: V1.0
Others: none
*************************************************************************/
int32 SCB_SetClockFrequency(uint32 frequency)
{
	uint8 M_VAL = 0;
	uint8 P_VAL = 0;
	uint32 Fcco= 0;
	uint32 Old_Freq = 0;
	BOOL bFlag = FALSE;
	
	//ȡ�õ�ǰ��Ƶ��
	Old_Freq = SCB_GetCurFrequency();
	
	if(frequency > MAX_FREQUENCY)  //Ƶ�����ù���
	{
		frequency = MAX_FREQUENCY;
	}
	
	if(frequency < MIN_FREQUENCY)  //Ƶ�����ù�С
	{
		frequency = MIN_FREQUENCY;  
	}
	
	//���жϵ�ǰPLL��û������������
	if(((SCB->PLLSTAT & PLL_ENABLE) == PLL_ENABLE) || ((SCB->PLLSTAT & PLL_CONNECT) == PLL_CONNECT))
	{
		SCB->PLLCON = 0x00;
		SCB_FeedPLL();
	}
	
	//���ñ�Ƶ���ͷ�Ƶ��
	//��Ƶϵ��  Mֵ������1-32֮��
	M_VAL = frequency / OSC_FREQUENCY;
	if(M_VAL < 1)
	{
		M_VAL = 1;  //����Ƶ
	}
	else if(M_VAL > 32)
	{
		M_VAL = 32;  //���Ƶ
	}
		
	//���÷�Ƶϵ�� Fcco��156MHz��320MHz֮��
	//PֵΪ1��2��4��8
	P_VAL = 1;
	Fcco = P_VAL * 2 * M_VAL * OSC_FREQUENCY;
	while(Fcco < FCCO_HIGH)
	{
		if(Fcco > FCCO_LOW)
		{
			bFlag = TRUE;
			break;
		}
		
		P_VAL *= 2;
		Fcco = P_VAL * 2 * M_VAL * OSC_FREQUENCY;
		
		if(P_VAL > 8)
			break;
	}
	
	if(bFlag)  //���óɹ�
	{
		SCB->PLLCFG = 0x00;
		SCB->PLLCFG |= (((P_VAL - 1) << 5) | (M_VAL - 1));
		SCB_FeedPLL();
		SCB->PLLCON |= PLL_ENABLE;
		SCB_FeedPLL();
		//�ȴ�PLL����
		while(!(SCB->PLLSTAT & PLL_STS_LOCK));
		SCB->PLLCON |= PLL_CONNECT;  //PLL����
		SCB_FeedPLL();
		
		return Old_Freq;
	}
	else
	{
		/*
		  ���Լ���ظ�֮ǰƵ�ʵĴ���
		*/
		return (-1);
	}
}


/************************************************************************
Function: BOOL SCB_EnterPowerDownMode(uint32 mode)
Description: ����͹���ģʽ
Input: mode
Output: none
Return: TRUE:���óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_EnterPowerDownMode(uint32 mode)
{
	mode &= PCON_MASK;
	SCB->PCON |= PCON_MASK;
	
	return FALSE;
}

/************************************************************************
Function: BOOL SCB_EnablePerpPower(uint32 perp)
Description: ʹ������ģ��ĵ�Դ
Input: perp
Output: none
Return: TRUE:���óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_EnablePerpPower(uint32 perp)
{
	perp &= PCONP_MASK;
	
	SCB->PCONP |= perp;
	
	return TRUE;
	
}


/************************************************************************
Function: BOOL SCB_DisablePerpPower(uint32 perp)
Description: �Ͽ������Դ
Input: perp
Output: none
Return: TRUE:���óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_DisablePerpPower(uint32 perp)
{
	perp &= PCONP_MASK;
	
	SCB->PCONP &= ~perp;
	
	return TRUE;
}

/************************************************************************
Function: uint32 SCB_GetPerpPower(void)
Description: ȡ�������Դ
Input: perp
Output: none
Return: TRUE:���óɹ�
		FALSE������ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint32 SCB_GetPerpPower(void)
{
	return (SCB->PCONP & PCONP_MASK);
}

/************************************************************************
Function: uint8 SCB_GetResetSource(void)
Description: ȡ�ø�λԴ
Input: none
Output: none
Return: ��λԴ
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetResetSource(void)
{
	return (SCB->RSID & RSID_MASK);
}

/************************************************************************
Function: BOOL SCB_ClearResetSource(uint8 src)
Description: ��λ��λԴ
Input: src:��λԴ
Output: none
Return: TRUE:��λ�ɹ�
		FALSE����λʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_ClearResetSource(uint8 src)
{
	src &= RSID_MASK;
	
	SCB->RSID |= src;
	
	return TRUE;
}

/************************************************************************
Function: BOOL SCB_SetAPBClock(uint8 src)
Description: ����APB����ʱ�ӷ�Ƶ
Input: src:��λԴ
Output: none
Return: TRUE:��λ�ɹ�
		FALSE����λʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL SCB_SetAPBClock(uint8 divd)
{
	divd &= APBDIV_MASK;
	
	SCB->APBDIV |= divd;
	
	return TRUE;
}

/************************************************************************
Function: uint8 SCB_GetAPBClock(void)
Description: ȡ��APB����ʱ�ӷ�Ƶ
Input: none
Output: none
Return: APB���߷�Ƶϵ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
uint8 SCB_GetAPBClock(void)
{
	return (SCB->APBDIV & APBDIV_MASK);
}
