/*------------------------------------------------------------
File name:		Bat.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "include\bat.h"
#include "include\app.h"
#include "include\led.h"
//
#include "..\module\BQ25798\BQ25798.h"
//
#include "..\interface\ADC\ADC.h"
#include "..\interface\Uart\UART.h"
//------------------------------------------------------------

//----------------variable------------------------------------
volatile uint8_t bF_Uart0Rxing;
volatile uint8_t bF_Uart0RxTimeout;
volatile uint8_t bF_Uart0RxBuf[UART_BUF_LEN];
volatile uint16_t bF_Uart0RxCnt = 0;
//
BAT_INFO sR_Bat[BAT_PORT_NUM];
uint8_t bR_BatChkStep = 0;

//預設配置為2節電池
uint8_t const InterBat_InitTab[0x19] =
{
	0x12,					//VSYSMIN 7.0V
	0x03,0x48,		//VREG 8.4V
	0x00,0x64,		//ICHG 1000mA
	0x2F,					//VINDPM 4.7V
	0x00,0xC8,		//IINDPM 2000mA

	0xC3,					//預充電電壓71.4%*VREG 預充電電流120mA
	0x25,					//看門狗reset停止充電 充電截止電流200mA
	0x63,					//2節電池 1s內電池電壓低於VREG 200mv重新充電
	0x00,0xDC,		//OTG電壓 5.0V
	0x4B,					//預充電時間2h OTG電流 3040mA
	0x3D,					//Enable充電定時器
	0x02,					//關閉充電
	0x8A,					//VAC過壓26.0V 重設看門狗 看門狗重設時間1s
	0x00,					//關閉D+、D-偵測 IDLE模式
	0x00,					//關閉OTG 啟用PFM、OOA
	0x01,         //關閉ACFET-RBFET 啟用IBUS_OCP
	0x96,					//電池端有SHIP-FET 關閉OTG模式IBAT檢測
								//Enable IINDPM、ILIM_HIZ 關閉放電OCP
	0xAA,					//關閉MPPT
	0xC0,					//120度過溫調節,150度過溫關閉 BACK-UP模式關閉
	0x7A,					//JEITA高溫調整VREG為VREG-400mv,ICHG不變
								//JEITA低溫調整ICHG為20%*ICHG
	0x54,					//溫度參數設定
};
//預設配置為1節電池
uint8_t const CameraBat1S_InitTab[0x19] =
{
	0x04,					//VSYSMIN 3.5V
	0x01,0xC1,		//VREG 4.49V
	0x00,0xE6,		//ICHG 2300mA
	0x2F,					//VINDPM 4.7V
	0x00,0xC8,		//IINDPM 2000mA

	0xC3,					//預充電電壓71.4%*VREG 預充電電流120mA
	0x25,					//看門狗Reset停止充電	充電截止電流200mA
	0x23,					//1節電池 1s內電池電壓低於VREG 200mv重新充電
	0x00,0xDC,		//OTG電壓 5.0V
	0x4B,					//預充電時間2h OTG電流 3040mA
	0x3D,					//Enable充電定時器
	0x02,					//關閉充電
	0x8A,					//VAC過壓26.0V 重設看門狗 看門狗重設時間1s
	0x00,					//關閉D+、D-檢測 IDLE模式
	0x00,					//關閉OTG 使能PFM、OOA
	0x41,         //開啟ACFET-RBFET1 使能IBUS_OCP
	0x16,					//電池端無SHIP-FET 關閉OTG模式IBAT檢測
								//Enable IINDPM、ILIM_HIZ 關閉放電OCP
	0xAA,					//關閉MPPT
	0xC0,					//120度過溫調節,150度過溫關閉 BACK-UP模式關閉ACFET-RBFET1
	0x7A,					//JEITA高溫調整VREG為VREG-400mv,ICHG不變
								//JEITA低溫調整ICHG為20%*ICHG
	0x54,					//溫度參數設置
};
//預設配置為2節電池
uint8_t const CameraBat2S_InitTab[0x19] =
{
	0x12,					//VSYSMIN 7.0V
	0x03,0x48,		//VREG 8.4V
	0x00,0x64,		//ICHG 1000mA
	0x2F,					//VINDPM 4.7V
	0x00,0xC8,		//IINDPM 2000mA

	0xC3,					//預充電電壓71.4%*VREG 預充電電流120mA
	0x25,					//看門狗Reset停止充電	充電截止電流200mA
	0x63,					///2節電池 1s內電池電壓低於VREG 200mv重新充電
	0x00,0xDC,		//OTG電壓 5.0V
	0x4B,					//預充電時間2h OTG電流 3040mA
	0x3D,					//Enable充電定時器
	0x02,					//關閉充電
	0x8A,					//VAC過壓26.0V 重設看門狗 看門狗重設時間1s
	0x00,					//關閉D+、D-檢測 IDLE模式
	0x00,					//關閉OTG 使能PFM、OOA
	0x41,         //開啟ACFET-RBFET1 使能IBUS_OCP
	0x16,					//電池端無SHIP-FET 關閉OTG模式IBAT檢測
								//Enable IINDPM、ILIM_HIZ 關閉放電OCP
	0xAA,					//關閉MPPT
	0xC0,					//120度過溫調節,150度過溫關閉 BACK-UP模式關閉ACFET-RBFET1
	0x7A,					//JEITA高溫調整VREG為VREG-400mv,ICHG不變
								//JEITA低溫調整ICHG為20%*ICHG
	0x54,					//溫度參數設置
};
//------------------------------------------------------------

//-------------statement--------------------------------------
void Bat_Init(uint8_t port);
void Bat_ChkIn(uint8_t port);
void Bat_StatDeal(uint8_t port);
uint8_t Bat_GetBatNum(uint8_t port);
//------------------------------------------------------------

void Bat_Init(uint8_t port)
{
	uint8_t temp;

	switch(port)
	{
		case BAT_INTERNAL:
			//關閉充電
			BQ25798_CeOutputHigh(port);
			//關閉充電
			BQ25798_Write(port,0x08,(uint8_t *)(InterBat_InitTab + 8),0x19-8);
			BQ25798_Write(port,0x00,(uint8_t *)InterBat_InitTab,8);
			//ADC通道Enable
			temp = 0x00;
			BQ25798_Write(port,0x2F,&temp,1);
			temp = 0x00;
			BQ25798_Write(port,0x30,&temp,1);
			//ADCEnable 連續轉換模式 15bit
			temp = 0x8C;
			BQ25798_Write(port,0x2E,&temp,1);
			break;
		case BAT_CAMERA1:
			//關閉充電
			BQ25798_CeOutputHigh(port);
			//相機電池1
			if(sR_Bat[port].BatNum == BAT_2S)
			{
				BQ25798_Write(port,0x08,(uint8_t *)(CameraBat2S_InitTab + 8),0x19-8);
				BQ25798_Write(port,0x00,(uint8_t *)CameraBat2S_InitTab,8);
			}else
			{
				BQ25798_Write(port,0x08,(uint8_t *)(CameraBat1S_InitTab + 8),0x19-8);
				BQ25798_Write(port,0x00,(uint8_t *)CameraBat1S_InitTab,8);
			}
			//ADC通道Enable
			temp = 0x00;
			BQ25798_Write(port,0x2F,&temp,1);
			temp = 0x00;
			BQ25798_Write(port,0x30,&temp,1);
			//ADCEnable 連續轉換模式 15bit
			temp = 0x8C;
			BQ25798_Write(port,0x2E,&temp,1);
			break;
		case BAT_CAMERA2:
			//關閉充電
			BQ25798_CeOutputHigh(port);
			//相機電池2
			if(sR_Bat[port].BatNum == BAT_2S)
			{
				BQ25798_Write(port,0x08,(uint8_t *)(CameraBat2S_InitTab + 8),0x19-8);
				BQ25798_Write(port,0x00,(uint8_t *)CameraBat2S_InitTab,8);
			}else
			{
				BQ25798_Write(port,0x08,(uint8_t *)(CameraBat1S_InitTab + 8),0x19-8);
				BQ25798_Write(port,0x00,(uint8_t *)CameraBat1S_InitTab,8);
			}
			//ADC通道Enable
			temp = 0x00;
			BQ25798_Write(port,0x2F,&temp,1);
			temp = 0x00;
			BQ25798_Write(port,0x30,&temp,1);
			//ADCEnable 連續轉換模式 15bit
			temp = 0x8C;
			BQ25798_Write(port,0x2E,&temp,1);
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Bat_ChkIn(uint8_t port)
{
	if(sR_Bat[port].IsBatIn != 0)
	{
		//目前電池為已接入
		if(sR_Bat[port].BatTempReal < BAT_IN_ADC_VAL)
		{
			//電池接入
			sR_Bat[port].BatInChkCnt = 0;
		}else
		{
			sR_Bat[port].BatInChkCnt++;
			if(sR_Bat[port].BatInChkCnt >= BAT_IN_CHECK_TIME)
			{
				//檢測到電池拔出
				sR_Bat[port].BatInChkCnt = 0;
				sR_Bat[port].IsBatIn = BAT_NC;
				sR_Bat[port].BatNum = BAT_0S;

				AppFifoWrite(APP_BAT_NUM_CHANGE);
			}
		}
	}else
	{
		//目前電池為未接入
		if(sR_Bat[port].BatTempReal < BAT_IN_ADC_VAL)
		{
			sR_Bat[port].BatInChkCnt++;
			if(sR_Bat[port].BatInChkCnt >= BAT_IN_CHECK_TIME)
			{
				//檢測到電池插入
				sR_Bat[port].BatInChkCnt = 0;
				sR_Bat[port].IsBatIn = BAT_IN;
				sR_Bat[port].BatNum = Bat_GetBatNum(port);

				AppFifoWrite(APP_BAT_NUM_CHANGE);
			}
		}else
		{
			//電池未接入
			sR_Bat[port].BatInChkCnt = 0;
		}
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void Bat_StatDeal(uint8_t port)
{
	uint16_t fault;
	uint8_t status;

//	SN_UART0->TH = sR_Bat[port].Stat[5];
//	while(SN_UART0->LS_b.THRE == 0);
//	SN_UART0->TH = sR_Bat[port].Stat[6];

	if(sR_Bat[port].IsBatIn == BAT_NC)
	{
		return;
	}

	//Get錯誤狀態
	fault = sR_Bat[port].Stat[5] << 8;
	fault |= sR_Bat[port].Stat[6];

	//Get充電狀態
	status = sR_Bat[port].Stat[1] >> 5;
	status &= 0x07;

	if(fault == 0)
	{
		//無錯誤
		if(status == 0)
		{
			Led_SetDisplayMode(port,LED_MODE_DISCHARGE_25);
		}else
		{
			if(status == 7)
			{
				Led_SetDisplayMode(port,LED_MODE_CHARGE_FULL);
			}else
			{
				Led_SetDisplayMode(port,LED_MODE_CHARGE_25);
			}
		}
	}else
	{
		Led_SetDisplayMode(port,LED_MODE_CHARGE_ERROR);
	}
}

/*------------------------------------------------------------
Function:
Description:	10ms一次
Input:
Output:
--------------------------------------------------------------*/
void Bat_ChkStatus(void)
{
	uint8_t temp;

	temp = bR_BatChkStep%3;
	switch(bR_BatChkStep++)
	{
		//檢測BQ25798通訊
		case 0:
		case 1:
		case 2:
			if(BQ25798_ChkI2cIsOk(temp) == BQ25798_OK)
			{
				if(sR_Bat[temp].IsI2cOk == 0)
				{
					Bat_Init(temp);
				}
				sR_Bat[temp].IsI2cOk = 1;
			}else
			{
				sR_Bat[temp].IsI2cOk = 0;
				if(sR_Bat[temp].IsBatIn == BAT_IN)
				{
					sR_Bat[temp].BatInChkCnt = 0;
					sR_Bat[temp].IsBatIn = BAT_NC;
					sR_Bat[temp].BatNum = BAT_0S;

					Led_SetDisplayMode(temp,LED_MODE_NO_BAT);
					AppFifoWrite(APP_BAT_NUM_CHANGE);
				}
			}
			break;
		//讀取ADC
		case 3:
		case 4:
		case 5:
			if(sR_Bat[temp].IsI2cOk == 1)
			{
				BQ25798_GetBatVol(temp,&sR_Bat[temp].BatVolReal);
				BQ25798_GetBatCurrent(temp,&sR_Bat[temp].BatCurrentReal);

				if(BQ25798_GetBatTemp(temp,&sR_Bat[temp].BatTempReal) == BQ25798_OK)
				{
					Bat_ChkIn(temp);
				}
			}
			break;
		//讀取異常旗標
		case 6:
		case 7:
		case 8:
			if(sR_Bat[temp].IsI2cOk == 1)
			{
				if(BQ25798_ReadChargeStatus(temp,sR_Bat[temp].Stat) == BQ25798_OK)
				{
					Bat_StatDeal(temp);
				}
			}
			break;
		//清除看門狗timer
		case 9:
			for(temp = 0;temp < BAT_PORT_NUM;temp++)
			{
				if(sR_Bat[temp].IsI2cOk == 1)
				{
					BQ25798_FeedWatchDog(temp);
				}
			}
			break;
	}

	if(bR_BatChkStep >= 10)
	{
		bR_BatChkStep = 0;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t Bat_GetBatNum(uint8_t port)
{
	uint16_t val;

	switch(port)
	{
		case BAT_INTERNAL:
			val = 4095;
			break;
		case BAT_CAMERA1:
			val = ADC_Sample(ADC_CHS_AIN10);
			val = 0;
			break;
		case BAT_CAMERA2:
			val = ADC_Sample(ADC_CHS_AIN4);
			val = 0;
			break;
	}

	if(val >= BAT_2S_ADC_VAL)
	{
		return BAT_2S;
	}else
	{
		return BAT_1S;
	}
}

/*------------------------------------------------------------
Function:		UART0_IRQHandler
Description:	UART接收中斷
Input:
Output:
--------------------------------------------------------------*/
 void UART0_IRQHandler(void)
{
	uint32_t LS_Buf;

	if(SN_UART0->II_b.INTID == UART_RDA)
	{
		//收到UART數據
		bF_Uart0Rxing = 1;
		bF_Uart0RxTimeout = 0;
		LS_Buf = SN_UART0->RB;
		bF_Uart0RxBuf[bF_Uart0RxCnt++] = LS_Buf;
		if(bF_Uart0RxCnt >= UART_BUF_LEN)
		{
			bF_Uart0RxCnt = 0;
		}
	}
}

