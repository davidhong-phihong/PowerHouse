/*------------------------------------------------------------
File name:		App.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "include\app.h"
#include "include\bat.h"
//
#include "..\module\WT6673\WT6673.h"
#include "..\module\BQ25798\BQ25798.h"
//------------------------------------------------------------

//----------------variable------------------------------------
//FIFO
uint8_t bR_AppFifo[APP_FIFO_LEN];
uint8_t bR_AppFifoWr = 0,bR_AppFifoRd = 0;
uint8_t bR_AppFifoLen = 0;
//系統狀態
uint8_t bR_SysStatus = SYSTEM_POWER_ON;

//------------------------------------------------------------

//-------------statement--------------------------------------
void App_StatusChk(void);
//------------------------------------------------------------

/*------------------------------------------------------------
Function:			Mn_App
Description:	FIFO事件處理
Input:			無
Output:			無
--------------------------------------------------------------*/
void Mn_App(void)
{
	uint8_t appfifo;

	appfifo = AppFifoRead();
	switch(appfifo)
	{
		case APP_POWER_ON:

			break;
		case APP_WT6673_INT:
			break;
		case APP_WT6673_C_IN:
			sR_UsbC1.IsUsbIn = USB_IN;
			sR_UsbC1.UsbDir = USB_SINK;
			sR_UsbC1.UsbVol = 5000;
			sR_UsbC1.UsbCurrent = 2000;

			App_StatusChk();
			break;
		case APP_WT6673_C_OUT:
			sR_UsbC1.IsUsbIn = USB_NC;

			App_StatusChk();
			break;
		case APP_BAT_NUM_CHANGE:
			App_StatusChk();
			break;
	}

	switch(bR_SysStatus)
	{
		default:
		case SYSTEM_POWER_ON:
			WT6673_Chk();
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:			無
Output:			無
--------------------------------------------------------------*/
void App_StatusChk(void)
{
	uint8_t status = 0;

	if((sR_UsbC1.IsUsbIn == USB_IN)
		&&(sR_UsbC1.UsbDir == USB_SINK))
	{
		//C1接入充電器
		if((sR_UsbC2.IsUsbIn == USB_IN)
		&&(sR_UsbC2.UsbDir == USB_SOURCE))
		{
			//C1->C2
			status = SYSTEM_C1_TO_C2;
		}else if((sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
		&&(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN))
		{
			//C1->相機1、2
			status = SYSTEM_C1_TO_CAMERA12;
		}else if(sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
		{
			//C1->相機1
			status = SYSTEM_C1_TO_CAMERA1;
		}else if(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN)
		{
			//C1->相機2
			status = SYSTEM_C1_TO_CAMERA2;
		}else if(sR_Bat[BAT_INTERNAL].IsBatIn == BAT_IN)
		{
			//C1->內部電池
			status = SYSTEM_C1_TO_BAT;
		}else
		{
			status = SYSTEM_NO_CHARGE;
		}
	}else if(sR_Bat[BAT_INTERNAL].IsBatIn == BAT_IN)
	{
		if((sR_UsbC2.IsUsbIn == USB_IN)
		&&(sR_UsbC2.UsbDir == USB_SOURCE))
		{
			//BAT->C2
			status = SYSTEM_BAT_TO_C2;
		}else if((sR_UsbC1.IsUsbIn == USB_IN)
		&&(sR_UsbC1.UsbDir == USB_SOURCE))
		{
			//BAT->C1
			status = SYSTEM_BAT_TO_C1;
		}else if((sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
		&&(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN))
		{
			//BAT->相機1、2
			status = SYSTEM_BAT_TO_CAMERA12;
		}else if(sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
		{
			//BAT->相機1
			status = SYSTEM_BAT_TO_CAMERA1;
		}else if(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN)
		{
			//BAT->相機2
			status = SYSTEM_BAT_TO_CAMERA2;
		}else
		{
			status = SYSTEM_NO_CHARGE;
		}
	}else if((sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
		&&(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN))
	{
		if((sR_UsbC2.IsUsbIn == USB_IN)
		&&(sR_UsbC2.UsbDir == USB_SOURCE))
		{
			//相機1、2->C2
			status = SYSTEM_CAMERA12_TO_C2;
		}else
		{
			status = SYSTEM_NO_CHARGE;
		}
	}else if(sR_Bat[BAT_CAMERA1].IsBatIn == BAT_IN)
	{
		if((sR_UsbC2.IsUsbIn == USB_IN)
		&&(sR_UsbC2.UsbDir == USB_SOURCE))
		{
			//相機1->C2
			status = SYSTEM_CAMERA1_TO_C2;
		}else
		{
			status = SYSTEM_NO_CHARGE;
		}
	}else if(sR_Bat[BAT_CAMERA2].IsBatIn == BAT_IN)
	{
		if((sR_UsbC2.IsUsbIn == USB_IN)
		&&(sR_UsbC2.UsbDir == USB_SOURCE))
		{
			//相機2->C2
			status = SYSTEM_CAMERA2_TO_C2;
		}else
		{
			status = SYSTEM_NO_CHARGE;
		}
	}else
	{
		//無任何設備接入
		NVIC_SystemReset();
	}

	if(bR_SysStatus != status)
	{
		//切換模式
		switch(status)
		{
			case SYSTEM_NO_CHARGE:
				BQ25798_BatChargeDis(BAT_INTERNAL);

				BQ25798_BatChargeDis(BAT_CAMERA1);
				BQ25798_BatChargeDis(BAT_CAMERA2);

				CAMERA1_BAT_DISCONNECT;
				CAMERA2_BAT_DISCONNECT;

				BQ25798_ACFET1Dis(BAT_CAMERA1);
				BQ25798_ACFET1Dis(BAT_CAMERA2);

				WT6673_C1GateOff();
				WT6673_C2GateOff();
				break;
			case SYSTEM_C1_TO_C2:

				break;
			case SYSTEM_C1_TO_CAMERA1:
				BQ25798_BatChargeDis(BAT_INTERNAL);

				BQ25798_BatChargeDis(BAT_CAMERA2);
				CAMERA2_BAT_DISCONNECT;
				BQ25798_ACFET1Dis(BAT_CAMERA2);

				WT6673_C2GateOff();
				WT6673_C1GateOn();

				BQ25798_ACFET1En(BAT_CAMERA1);
				if(sR_Bat[BAT_CAMERA1].BatNum == BAT_1S)
				{
					CAMERA1_BAT_1S_CONNECT;
				}else if(sR_Bat[BAT_CAMERA1].BatNum == BAT_2S)
				{
					CAMERA1_BAT_2S_CONNECT;
				}else
				{
					CAMERA1_BAT_DISCONNECT;
				}

				BQ25798_BatChargeEn(BAT_CAMERA1);
				break;
			case SYSTEM_C1_TO_CAMERA2:
				BQ25798_BatChargeDis(BAT_INTERNAL);

				BQ25798_BatChargeDis(BAT_CAMERA1);
				CAMERA1_BAT_DISCONNECT;
				BQ25798_ACFET1Dis(BAT_CAMERA1);

				WT6673_C2GateOff();
				WT6673_C1GateOn();

				BQ25798_ACFET1En(BAT_CAMERA2);
				if(sR_Bat[BAT_CAMERA2].BatNum == BAT_1S)
				{
					CAMERA2_BAT_1S_CONNECT;
				}else if(sR_Bat[BAT_CAMERA2].BatNum == BAT_2S)
				{
					CAMERA2_BAT_2S_CONNECT;
				}else
				{
					CAMERA2_BAT_DISCONNECT;
				}

				BQ25798_BatChargeEn(BAT_CAMERA2);
				break;
			case SYSTEM_C1_TO_CAMERA12:
				BQ25798_BatChargeDis(BAT_INTERNAL);

				WT6673_C2GateOff();
				WT6673_C1GateOn();

				BQ25798_ACFET1En(BAT_CAMERA1);
				BQ25798_ACFET1En(BAT_CAMERA2);

				if(sR_Bat[BAT_CAMERA1].BatNum == BAT_1S)
				{
					CAMERA1_BAT_1S_CONNECT;
				}else if(sR_Bat[BAT_CAMERA1].BatNum == BAT_2S)
				{
					CAMERA1_BAT_2S_CONNECT;
				}else
				{
					CAMERA1_BAT_DISCONNECT;
				}
				if(sR_Bat[BAT_CAMERA2].BatNum == BAT_1S)
				{
					CAMERA2_BAT_1S_CONNECT;
				}else if(sR_Bat[BAT_CAMERA2].BatNum == BAT_2S)
				{
					CAMERA2_BAT_2S_CONNECT;
				}else
				{
					CAMERA2_BAT_DISCONNECT;
				}

				BQ25798_BatChargeEn(BAT_CAMERA1);
				BQ25798_BatChargeEn(BAT_CAMERA2);
				break;
			case SYSTEM_C1_TO_BAT:
				BQ25798_BatChargeDis(BAT_CAMERA1);
				BQ25798_BatChargeDis(BAT_CAMERA2);
				CAMERA1_BAT_DISCONNECT;
				CAMERA2_BAT_DISCONNECT;
				BQ25798_ACFET1Dis(BAT_CAMERA2);
				BQ25798_ACFET1Dis(BAT_CAMERA2);

				WT6673_C2GateOff();
				WT6673_C1GateOn();

				BQ25798_BatChargeEn(BAT_INTERNAL);
				break;

			case SYSTEM_BAT_TO_C2:
			case SYSTEM_BAT_TO_C1:
			case SYSTEM_BAT_TO_CAMERA1:
			case SYSTEM_BAT_TO_CAMERA2:
			case SYSTEM_BAT_TO_CAMERA12:
			case SYSTEM_CAMERA1_TO_C2:
			case SYSTEM_CAMERA2_TO_C2:
			case SYSTEM_CAMERA12_TO_C2:
				break;
		}
		bR_SysStatus = status;
	}
}

/*------------------------------------------------------------
Function:			AppFifoWrite
Description:
Input:
Output:
--------------------------------------------------------------*/
void AppFifoWrite(uint8_t dat)
{
	if(bR_AppFifoLen < APP_FIFO_LEN)
	{
		bR_AppFifoLen++;
		bR_AppFifo[bR_AppFifoWr++] = dat;
		if(bR_AppFifoWr >= APP_FIFO_LEN)
		{
			bR_AppFifoWr = 0;
		}
	}
}

/*------------------------------------------------------------
Function:			AppFifoRead
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t AppFifoRead(void)
{
	uint8_t dat = APP_NC;

	if(bR_AppFifoLen > 0)
	{
		bR_AppFifoLen--;
		dat = bR_AppFifo[bR_AppFifoRd];
		bR_AppFifoRd++;
		if(bR_AppFifoRd >= APP_FIFO_LEN)
		{
			bR_AppFifoRd = 0;
		}
	}

	return dat;
}
