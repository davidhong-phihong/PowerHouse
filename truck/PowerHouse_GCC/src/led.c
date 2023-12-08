/*------------------------------------------------------------
File name:		Led.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "include\led.h"
//------------------------------------------------------------

//----------------variable------------------------------------
uint8_t bR_LedMode[LED_PORT_NUM] = {0};
uint16_t dbR_LedFlashVal[LED_PORT_NUM] = {0};

uint8_t bF_LedFlashStatus = 0;
uint16_t dbT_LedFlashTime = LED_FLASH_TIME;
//------------------------------------------------------------

//-------------statement--------------------------------------
void Led_NoBat(uint8_t port);
void Led_Charge100(uint8_t port);
void Led_ChargeFull(uint8_t port);
void Led_DisCharge75(uint8_t port);
void Led_ChargeError(uint8_t port);
//------------------------------------------------------------

/*------------------------------------------------------------
Function:
Description:	10ms
Input:
Output:
--------------------------------------------------------------*/
void Led_TimeChk(void)
{
	if(dbT_LedFlashTime != 0)
	{
		dbT_LedFlashTime--;

		if(dbT_LedFlashTime == 0)
		{
			dbT_LedFlashTime = LED_FLASH_TIME;

			if(bF_LedFlashStatus == 0)
			{
				bF_LedFlashStatus = 1;
				LED_BAT_INTERNAL_PORT->BCLR = dbR_LedFlashVal[LED_BAT_INTERNAL];
				LED_BAT_CAMERA1_PORT->BCLR = dbR_LedFlashVal[LED_BAT_CAMERA1];
				LED_BAT_CAMERA2_PORT->BCLR = dbR_LedFlashVal[LED_BAT_CAMERA2];
			}else
			{
				bF_LedFlashStatus = 0;
				LED_BAT_INTERNAL_PORT->BSET = dbR_LedFlashVal[LED_BAT_INTERNAL];
				LED_BAT_CAMERA1_PORT->BSET = dbR_LedFlashVal[LED_BAT_CAMERA1];
				LED_BAT_CAMERA2_PORT->BSET = dbR_LedFlashVal[LED_BAT_CAMERA2];
			}
		}
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_SetDisplayMode(uint8_t port,uint8_t mode)
{
	if(bR_LedMode[port] == mode)
	{
		return;
	}

	bR_LedMode[port] = mode;
	switch(mode)
	{
		case LED_MODE_NO_BAT:
			Led_NoBat(port);
			break;
		case LED_MODE_CHARGE_25:
		case LED_MODE_CHARGE_50:
		case LED_MODE_CHARGE_75:
		case LED_MODE_CHARGE_100:
			Led_Charge100(port);
			break;
		case LED_MODE_CHARGE_FULL:
			Led_ChargeFull(port);
			break;
		case LED_MODE_DISCHARGE_25:
		case LED_MODE_DISCHARGE_50:
		case LED_MODE_DISCHARGE_75:
		case LED_MODE_DISCHARGE_100:
			Led_DisCharge75(port);
			break;
		case LED_MODE_CHARGE_ERROR:
		case LED_MODE_DISCHARGE_ERROR:
			Led_ChargeError(port);
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_NoBat(uint8_t port)
{
	switch(port)
	{
		case LED_BAT_INTERNAL:
			LED_BAT_INTERNAL_PORT->BSET |= (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3 | LED_BAT_INTERNAL_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA1:
			LED_BAT_CAMERA1_PORT->BSET |= (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3 | LED_BAT_CAMERA1_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA2:
			LED_BAT_CAMERA2_PORT->BSET |= (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3 | LED_BAT_CAMERA2_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_Charge100(uint8_t port)
{
	switch(port)
	{
		case LED_BAT_INTERNAL:
			LED_BAT_INTERNAL_PORT->BCLR |= (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3);
			dbR_LedFlashVal[port] = LED_BAT_INTERNAL_BIT4;
			break;
		case LED_BAT_CAMERA1:
			LED_BAT_CAMERA1_PORT->BCLR |= (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3);
			dbR_LedFlashVal[port] = LED_BAT_CAMERA1_BIT4;
			break;
		case LED_BAT_CAMERA2:
			LED_BAT_CAMERA2_PORT->BCLR |= (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3);
			dbR_LedFlashVal[port] = LED_BAT_CAMERA2_BIT4;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_ChargeFull(uint8_t port)
{
	switch(port)
	{
		case LED_BAT_INTERNAL:
			LED_BAT_INTERNAL_PORT->BCLR |= (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3 |	LED_BAT_INTERNAL_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA1:
			LED_BAT_CAMERA1_PORT->BCLR |= (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3 | LED_BAT_CAMERA1_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA2:
			LED_BAT_CAMERA2_PORT->BCLR |= (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3 | LED_BAT_CAMERA2_BIT4);
			dbR_LedFlashVal[port] = 0;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_DisCharge75(uint8_t port)
{
	switch(port)
	{
		case LED_BAT_INTERNAL:
			LED_BAT_INTERNAL_PORT->BCLR |= (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3);
			LED_BAT_INTERNAL_PORT->BSET |= LED_BAT_INTERNAL_BIT4;
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA1:
			LED_BAT_CAMERA1_PORT->BCLR |= (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3);
			LED_BAT_CAMERA1_PORT->BSET |= LED_BAT_CAMERA1_BIT4;
			dbR_LedFlashVal[port] = 0;
			break;
		case LED_BAT_CAMERA2:
			LED_BAT_CAMERA2_PORT->BCLR |= (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3);
			LED_BAT_CAMERA2_PORT->BSET |= LED_BAT_CAMERA2_BIT4;
			dbR_LedFlashVal[port] = 0;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Led_ChargeError(uint8_t port)
{
	switch(port)
	{
		case LED_BAT_INTERNAL:
			LED_BAT_INTERNAL_PORT->BCLR |= (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3);
			dbR_LedFlashVal[port] = (LED_BAT_INTERNAL_BIT1 | LED_BAT_INTERNAL_BIT2
																		|	LED_BAT_INTERNAL_BIT3 | LED_BAT_INTERNAL_BIT4);
			break;
		case LED_BAT_CAMERA1:
			LED_BAT_CAMERA1_PORT->BCLR |= (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3 | LED_BAT_CAMERA1_BIT4);
			dbR_LedFlashVal[port] = (LED_BAT_CAMERA1_BIT1 | LED_BAT_CAMERA1_BIT2
																		|	LED_BAT_CAMERA1_BIT3 | LED_BAT_CAMERA1_BIT4);
			break;
		case LED_BAT_CAMERA2:
			LED_BAT_CAMERA2_PORT->BCLR |= (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3 | LED_BAT_CAMERA2_BIT4);
			dbR_LedFlashVal[port] = (LED_BAT_CAMERA2_BIT1 | LED_BAT_CAMERA2_BIT2
																		|	LED_BAT_CAMERA2_BIT3 | LED_BAT_CAMERA2_BIT4);
			break;
	}
}
