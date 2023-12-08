#ifndef _WT6673_H_
#define	_WT6673_H_

//--------------include-------------------------------
#include "../../src/include\mcu_type.h"
#include "../../interface/I2C/I2C.h"
//----------------------------------------------------

//----------------macro-------------------------------
#define		WT6673_DEVICE_ADDR		(0x60 << 1)
#define	 	WT6673_WR							(0x00)
#define 	WT6673_RD							(0x01)

#define 	WT6673_PORT						I2C_PORT1

#define	 	WT6673_OK							(0x00)
#define 	WT6673_FAIL						(0x01)
//暫存器
#define		WT6673_INT_REQUEST				(0x8049)
#define		WT6673_SINK_RQQUEST_MSG		(0x804C)
#define		WT6673_SINK_PDO1					(0x8050)
#define		WT6673_SINK_PDO2					(0x8054)
#define		WT6673_SOURCE_SET_PDO			(0x8058)

//狀態IO
#define		WT6673_INT_PIN_STATUS			SN_GPIO0->DATA_b.DATA4
#define		WT6673_C1_PIN_STATUS			SN_GPIO0->DATA_b.DATA5

#define		WT6673_DEBOUNCE_TIME			(5)

enum
{
	USB_NC = 0,
	USB_IN,
};

enum
{
	USB_TYPE_NONE = 0,
	USB_TYPE_DCP ,//1
	USB_TYPE_CDP ,//2
	USB_TYPE_SDP ,//3
	USB_TYPE_APPLE_2A = 4,
	USB_TYPE_APPLE_1A = 5,
	USB_TYPE_APPLE_0A5 = 6,
	USB_TYPE_HAMMERHEAD_3A = 7,
	USB_TYPE_HAMMERHEAD_1A5 = 8 ,
	USB_TYPE_TYPEC_3A = 9,
	USB_TYPE_TYPEC_1A5 ,	//A
	USB_TYPE_APPLE_2A4 , //B
	USB_TYPE_DC_SOURCE ,  //C
};

enum
{
	USB_SOURCE = 0,
	USB_SINK,
};

typedef struct
{
	uint8_t IsUsbIn;
	uint8_t UsbType;
	uint8_t UsbDir;
	uint8_t :8;

	uint16_t UsbVol;
	uint16_t UsbCurrent;
}USB_INFO;

//事件
#define		WT6673_EVENT_INT					(0x01)
#define		WT6673_EVENT_C_IN					(0x02)
#define		WT6673_EVENT_C_OUT				(0x04)
//----------------variable----------------------------
extern USB_INFO sR_UsbC1;
extern USB_INFO sR_UsbC2;
//----------------------------------------------------

//----------------function----------------------------
void WT6673_Chk(void);
void WT6673_TimeChk(void);
void WT6673_C1GateOn(void);
void WT6673_C1GateOff(void);
void WT6673_C2GateOn(void);
void WT6673_C2GateOff(void);

uint8_t WT6673_Write(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t WT6673_Read(uint16_t reg,uint8_t *buf,uint8_t len);
//----------------------------------------------------

#endif /* _WT6673_H_ */
