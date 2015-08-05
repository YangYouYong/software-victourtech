/*****************************************************************
**  Copyright (C), 2013-2014, HY Co.,Ltd.
**  FileName: LEC.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: ��ΧLED����
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "LED.h"
#include "lib_gpio_lpc213x.h"


//P1.20-P1.25

/********************************************
* ȫ�ֱ���
*********************************************/
PINNum LED[6] = {NUM20, NUM21, NUM22, NUM23, NUM24, NUM25};

/************************************************************************
Function: BOOL InitLED(void)
Description:  ��ʼ��LED����
Input:  none
Output: none
Return: TRUE����ʼ���ɹ�
		FALSE����ʼ��ʧ��
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Init(void)
{
	int i = 0;
	//��ʼ��LED�˿�
	GPIODef LedGPIO;
	LedGPIO.port = PORT_1;
	LedGPIO.num = LED[0];
	LedGPIO.fuc = FUC_GPIO;
	LedGPIO.dir = DIR_OUT;

	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[1];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[2];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[3];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[4];
	GPIO_SetFunction(&LedGPIO);
    LedGPIO.num = LED[5];
	GPIO_SetFunction(&LedGPIO);
    
    //����LED
    /*for(int i = 0; i < 6; i++)
    {
        LED_Set(LED[i]);
        for(volatile int j = 0; j < 200000; j++);
    }*/
        
    
    //�ر�LED
    for(i = 0; i < 6; i++)
        LED_Clear(LED[i]);

	return TRUE;
}

/************************************************************************
Function: void SetLED(PINNum led)
Description:  ����LED
Input:  led:LED���
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Set(PINNum led)
{
	return GPIO_SET(PORT_1, led);
}

/************************************************************************
Function: void ClrLED(PINNum led)
Description:  Ϩ��LED
Input:  led��LED���
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL LED_Clear(PINNum led)
{
	return GPIO_CLR(PORT_1, led);
}
