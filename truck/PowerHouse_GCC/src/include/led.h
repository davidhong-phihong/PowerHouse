#ifndef _LED_H_
#define	_LED_H_

//--------------include-------------------------------
#include "mcu_type.h"
#include "bat.h"
//----------------------------------------------------

//----------------macro-------------------------------
#define 	LED_PORT_NUM						(BAT_PORT_NUM)

#define 	LED_BAT_INTERNAL				(BAT_INTERNAL)
#define 	LED_BAT_CAMERA1					(BAT_CAMERA1)
#define 	LED_BAT_CAMERA2					(BAT_CAMERA2)

#define		LED_BAT_INTERNAL_PORT				SN_GPIO1
#define		LED_BAT_INTERNAL_BIT1				(1 << 10)
#define		LED_BAT_INTERNAL_BIT2				(1 << 11)
#define		LED_BAT_INTERNAL_BIT3				(1 << 12)
#define		LED_BAT_INTERNAL_BIT4				(1 << 13)

#define		LED_BAT_CAMERA1_PORT				SN_GPIO1
#define		LED_BAT_CAMERA1_BIT1				(1 << 4)
#define		LED_BAT_CAMERA1_BIT2				(1 << 5)
#define		LED_BAT_CAMERA1_BIT3				(1 << 6)
#define		LED_BAT_CAMERA1_BIT4				(1 << 7)

#define		LED_BAT_CAMERA2_PORT				SN_GPIO3
#define		LED_BAT_CAMERA2_BIT1				(1 << 8)
#define		LED_BAT_CAMERA2_BIT2				(1 << 9)
#define		LED_BAT_CAMERA2_BIT3				(1 << 10)
#define		LED_BAT_CAMERA2_BIT4				(1 << 11)

#define		LED_FLASH_TIME							(50)

enum
{
	LED_MODE_NO_BAT = 0,
	LED_MODE_CHARGE_25,
	LED_MODE_CHARGE_50,
	LED_MODE_CHARGE_75,
	LED_MODE_CHARGE_100,
	LED_MODE_CHARGE_FULL,
	LED_MODE_CHARGE_ERROR,
	LED_MODE_DISCHARGE_25,
	LED_MODE_DISCHARGE_50,
	LED_MODE_DISCHARGE_75,
	LED_MODE_DISCHARGE_100,
	LED_MODE_DISCHARGE_ERROR,
};
//----------------------------------------------------

//----------------variable----------------------------

//----------------------------------------------------

//----------------function----------------------------
void Led_TimeChk(void);
void Led_SetDisplayMode(uint8_t port,uint8_t mode);
//----------------------------------------------------

#endif /* _LED_H_ */
