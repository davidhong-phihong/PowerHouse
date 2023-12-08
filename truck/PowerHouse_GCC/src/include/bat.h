#ifndef _BAT_H_
#define	_BAT_H_

//--------------include-------------------------------
#include "mcu_type.h"
#include "..\..\module\BQ25798\BQ25798.h"
//----------------------------------------------------

//----------------macro-------------------------------
//UART發送接收緩沖區大小
#define 	UART_BUF_LEN				(1024)

#define 	BAT_PORT_NUM				(3)
#define 	BAT_IN_ADC_VAL			(840)
#define 	BAT_IN_CHECK_TIME		(3)

#define 	BAT_INTERNAL				(I2C_PORT1)
#define 	BAT_CAMERA1					(I2C_PORT2)
#define 	BAT_CAMERA2					(I2C_PORT3)

#define 	BAT_2S_ADC_VAL			(3000)

enum
{
	BAT_NC = 0,
	BAT_IN,
};
enum
{
	BAT_0S = 0,
	BAT_1S,BAT_2S,
};
enum
{
	BAT_STATUS_NOMAL = 0,
	BAT_STATUS_CHARGE,
	BAT_STATUS_CHARGE_OK,
	BAT_STATUS_DISCHARGE,
	BAT_STATUS_LOW_POWER,
};
typedef struct
{
	uint8_t IsI2cOk;
	uint8_t Stat[7];

	uint8_t IsBatIn;
	uint8_t BatNum;
	uint8_t BatInChkCnt;
	uint8_t BatStatus;

	int16_t BatVolMax;
	int16_t BatCurrentMax;

	int16_t BatVolSet;
	int16_t BatCurrentSet;

	int16_t BatVolReal;
	int16_t BatCurrentReal;

	int16_t BatTempReal;
	int16_t :16;
}BAT_INFO;
//----------------------------------------------------

//----------------variable----------------------------
extern BAT_INFO sR_Bat[BAT_PORT_NUM];
//----------------------------------------------------

//----------------function----------------------------
void Bat_ChkStatus(void);
//----------------------------------------------------

#endif /* _BAT_H_ */
