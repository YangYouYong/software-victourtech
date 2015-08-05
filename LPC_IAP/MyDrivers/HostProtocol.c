/*****************************************************************
**  Copyright (C), 2013-2014, ZCJ Co.,Ltd.
**  FileName: LEC.c
**  Author: 
**  Version: V1.0.0 
**  Date: 2013-11-28
**  Description: ����ͨѶЭ��
**  Function List: 
**  1. -------
**  History: 
******************************************************************/
#include "HostProtocol.h"
#include "lib_spi_lpc213x.h"
#include "lib_gpio_lpc213x.h"
#include "lib_vic_lpc213x.h"
#include "lib_e2prom_lpc213x.h"
/****************************************
* ȫ�ֱ���
*****************************************/
static uint8 RecvData[8];
static uint8 RecvDataLen = 0;

static uint8 SendData[8];
static uint8 SendDataLen = 0;
static uint8 CurSendDataLen = 0;

static BOOL bWriteOrRead = FALSE;
static uint8 DataState = 0;

void HostDataISR(void) __irq;
/****************************************
* �ⲿ����
*****************************************/
extern BOOL Header;
/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
BOOL HostProtocol_Init(void)
{
    //ʹ��֪ͨ������GPIO�˿�
    GPIODef IOGPIO = {PORT_0, NUM19, FUC_GPIO, DIR_OUT};
	GPIO_SetFunction(&IOGPIO);
    
    
    //ʹ��SPI0����
    //SPI0������������ͨѶ
	{
		GPIODef SPIGPIO = {PORT_0, NUM4, FUC_FIRST, DIR_IN};
		GPIO_SetFunction(&SPIGPIO);
		SPIGPIO.num = NUM5;
		SPIGPIO.dir = DIR_OUT;
		GPIO_SetFunction(&SPIGPIO);
		SPIGPIO.num = NUM6;
		SPIGPIO.dir = DIR_IN;
		GPIO_SetFunction(&SPIGPIO);
		SPIGPIO.num = NUM7;
		SPIGPIO.dir = DIR_IN;
		GPIO_SetFunction(&SPIGPIO);
	}
    
    //���ô�SPI0(SPI����ʱ��1MHz)
	{
		SPIINFO nSPIInfo = {SPI_DATABITS_8, SPI_CPHA_FIRST, SPI_CPOL_HIGH, SPI_SLAVE, SPI_MSB};
		SPI_Open(&nSPIInfo);
		SPI_EnableInt();  //ʹ���ж�
		//��һ�ζ�ȡ����0x00
		SPI_GetStatus();
		SPI_GetData();
		SPI_WriteData(0x00);
	}
    
    //����SPI�ж�ΪIRQ
    VIC_IntSelect(VIC_INTBIT_SPI0, IRQ);
	//��SPI�ж�Ϊ�����ж�
    VIC_VectIRQBind(HOSTDATA_IRQ, VIC_INTNUM_SPI0, (uint32)HostDataISR);
    //ʹ���ⲿ�ж�
    VIC_EnableInt(VIC_INTBIT_SPI0);
	
	RecvDataLen = 0;
     
    return TRUE;
}
/************************************************************************
Function: 
Description: 
Input:  none
Output: none
Return: none
Author: 
Version: V1.0
Others: none
*************************************************************************/
void HostDataISR(void) __irq
{
    //����жϱ�־������λ
    SPI_GetStatus();
    RecvData[RecvDataLen] = SPI_GetData();

    if(RecvData[RecvDataLen] == 0 && bWriteOrRead == FALSE)  //����������
    {
        //д����һ�ζ�ȡ����Ҫ������
        if(CurSendDataLen < SendDataLen)
        {
            SPI_WriteData(SendData[CurSendDataLen]);
            CurSendDataLen++; 
        }
        else
        {
            RecvDataLen = 0;
            SPI_WriteData(0x00);
            bWriteOrRead = TRUE;
        }
    }
    else //����д����
    {   
        switch(RecvData[RecvDataLen])
        {
            case 0X6E:
			    Header = FALSE;
                DataState = 1;
                break; 
            case 0XFF:
                SendData[0] = DataState;
                SendDataLen = 1;
                CurSendDataLen = 1;
                //д���һ��Ҫ��ȡ������
                SPI_WriteData(SendData[0]);
                bWriteOrRead = FALSE;
                DataState = 0;
                break;                 
            default:
                SendDataLen = 1;
                CurSendDataLen = 1;
                //д���һ��Ҫ��ȡ������
                SPI_WriteData(0x00);
                bWriteOrRead = FALSE;
                break;
        }
    }
    
    
    RecvDataLen++;
    if(RecvDataLen > 7)
        RecvDataLen = 0;
   
    SPI_ClearIntFlag();
    VIC_ClearCurVectAddr();
}
