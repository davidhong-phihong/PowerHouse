#ifndef _APP_
#define	_APP_

//--------------include-------------------------------
#include "mcu_type.h"
//--------------include-------------------------------

//----------------APPfifo----------------------------

//----------------APPfifo----------------------------

//----------------macro-------------------------------
#define APP_FIFO_LEN			(16)
enum
{
	APP_NC = 0,
	APP_POWER_ON,
	APP_WT6673_INT,
	APP_WT6673_C_IN,APP_WT6673_C_OUT,
	APP_BAT_NUM_CHANGE,
};

//IO
#define		CAMERA1_BAT_1S_CONNECT								{SN_GPIO2->BCLR_b.BCLR9 = 1;SN_GPIO2->BSET_b.BSET8 = 1;}
#define		CAMERA1_BAT_2S_CONNECT								{SN_GPIO2->BCLR_b.BCLR8 = 1;SN_GPIO2->BSET_b.BSET9 = 1;}
#define		CAMERA1_BAT_DISCONNECT								{SN_GPIO2->BCLR_b.BCLR8 = 1;SN_GPIO2->BCLR_b.BCLR9 = 1;}

#define		CAMERA2_BAT_1S_CONNECT								{SN_GPIO2->BCLR_b.BCLR1 = 1;SN_GPIO2->BSET_b.BSET0 = 1;}
#define		CAMERA2_BAT_2S_CONNECT								{SN_GPIO2->BCLR_b.BCLR0 = 1;SN_GPIO2->BSET_b.BSET1 = 1;}
#define		CAMERA2_BAT_DISCONNECT								{SN_GPIO2->BCLR_b.BCLR0 = 1;SN_GPIO2->BCLR_b.BCLR1 = 1;}

enum
{
	SYSTEM_POWER_ON = 0,
	SYSTEM_NO_CHARGE,//1
	SYSTEM_C1_TO_C2,//2
	SYSTEM_C1_TO_CAMERA1,//3
	SYSTEM_C1_TO_CAMERA2,//4
	SYSTEM_C1_TO_CAMERA12,//5
	SYSTEM_C1_TO_BAT,//6
	SYSTEM_BAT_TO_C2,//7
	SYSTEM_BAT_TO_C1,//8
	SYSTEM_BAT_TO_CAMERA1,//9
	SYSTEM_BAT_TO_CAMERA2,//10
	SYSTEM_BAT_TO_CAMERA12,//11
	SYSTEM_CAMERA1_TO_C2,//12
	SYSTEM_CAMERA2_TO_C2,//13
	SYSTEM_CAMERA12_TO_C2,//14
};

//----------------macro-------------------------------

//----------------variable----------------------------

//----------------variable----------------------------

//----------------function----------------------------
void Mn_App(void);
void AppFifoWrite(uint8_t dat);
uint8_t AppFifoRead(void);
//----------------function----------------------------

#endif /* _APP_ */
