
//--------------------------------------
#include "include\mcu_type.h"
//
#include "include\intgnd.h"
#include "include\app.h"
//
#include "..\interface\GPIO\GPIO.h"
#include "..\interface\Uart\Uart.h"
#include "..\interface\ADC\ADC.h"
#include "..\interface\WDT\WDT.h"
#include "..\interface\Systick\SysTick.h"
//
#include "..\Utility\Utility.h"
//--------------------------------------

void PreMain(void);

/*****************************************************************************
* Function		: 
* Description	: 
* Input			: None
* Output		: None
* Return		: 
* Note			: None
*****************************************************************************/
int main(void)
{		
	SystemInit();
	SystemCoreClockUpdate();
	UT_DelayNms(20);
	GPIO_Init();															//Initial GPIO
	ADC_Init();																//Initial ADC
	PreMain();																//Pre Main
	UART0_Init();															//Initial Uart0
	SysTick_Init();															//Initial Systick
	WDT_Init();																//Initial Watch Dog
	
	while(1)
	{	
		SN_WDT->FEED = 0x5AFA55AA;
		Mn_Intgnd();
		Mn_App();
	}
}

/*****************************************************************************
* Function		: 
* Description	: 
* Input			: None
* Output		: None
* Return		: 
* Note			: None
*****************************************************************************/
void PreMain(void)
{
	AppFifoWrite(APP_POWER_ON);
}



