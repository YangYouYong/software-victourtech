#include "lib_gpio_lpc213x.h"
#include "lib_e2prom_lpc213x.h"
#include "lib_watchdog_lpc213x.h"
#include "lib_spi_lpc213x.h"
#include "lib_scb_lpc213x.h" 
#include "PeripProtocol.h"
#include "HostProtocol.h"
#include "Led.h"
#include "Wd.h"
//ϵͳʱ��
#define configCPU_CLOCK_HZ			        ( ( unsigned long ) 60000000 )
//�ڲ�����
void delay(uint32 t);
//����һ���������͵Ĳ���
typedef  void (*iapfun)(void);
iapfun jump2app; 

int main(void)
{
	static uint8 DelayTime = 0;
	uint8 buf;
	
	SCB_SetClockFrequency(configCPU_CLOCK_HZ);
	SCB_SetAPBClock(SCB_APBDIV_1);
	
	LED_Init();
	HostProtocol_Init();
	PeripProtocol_Init();
	//��ʼ�����Ź���ʱ��5�룩
	WDInit(75000000);

	while(1)
	{
		DataControl();
		
		eepromRead(0xFF00, &buf, 1);
		
		if((DelayTime > 7) &&(buf == 1))
		{
			DelayTime = 0;
			__disable_irq();		
			jump2app = (iapfun)0x4000;
			(*jump2app)();	
		}
	
		DelayTime++;
		if(DelayTime > 200)
		{
			DelayTime = 0;
		}
		
		LED_Set(LED[5]);
		delay(5000000);	
		
		LED_Clear(LED[5]);
		delay(5000000);
		
		//ι��
		WD_Feed();
	}
}
//��ʱ
void delay(uint32 t)
{
	while(t--);
}
