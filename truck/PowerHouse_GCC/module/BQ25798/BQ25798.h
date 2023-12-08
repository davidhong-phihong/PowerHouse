#ifndef _BQ25798_H_
#define	_BQ25798_H_

//--------------include-------------------------------
#include "../../src/include\mcu_type.h"
#include "../../interface/I2C/I2C.h"

//----------------------------------------------------

//----------------macro-------------------------------
#define		BQ25798_DEVICE_ADDR			(0x6B << 1)
#define	 	BQ25798_WR							(0x00)
#define 	BQ25798_RD							(0x01)

#define	 	BQ25798_OK							(0x00)
#define 	BQ25798_FAIL						(0x01)

#define 	BQ25798_PART_ID					(0x19)

//暫存器
#define		BQ25798_REG00_MIN_SYS_VOL							(0x00)
#define		BQ25798_REG01_CHARGE_VOL_LIMIT				(0x01)
#define		BQ25798_REG03_CHARGE_CUR_LIMIT				(0x03)
#define		BQ25798_REG05_INPUT_VOL_LIMIT					(0x05)
#define		BQ25798_REG06_INPUT_CUR_LIMIT					(0x06)

#define		BQ25798_REG72_PART_INFO								(0x48)
//----------------variable----------------------------

//----------------------------------------------------

//----------------function----------------------------
uint8_t BQ25798_GetBatVol(uint8_t port,int16_t *buf);
uint8_t BQ25798_GetBatCurrent(uint8_t port,int16_t *buf);
uint8_t BQ25798_GetBatTemp(uint8_t port,int16_t *buf);
uint8_t BQ25798_ReadChargeStatus(uint8_t port,uint8_t *buf);

void BQ25798_CeOutputHigh(uint8_t port);
void BQ25798_CeOutputLow(uint8_t port);
void BQ25798_BatChargeEn(uint8_t port);
void BQ25798_BatChargeDis(uint8_t port);
void BQ25798_ShipFETEn(uint8_t port);
void BQ25798_ShipFETDis(uint8_t port);
void BQ25798_ACFET1En(uint8_t port);
void BQ25798_ACFET1Dis(uint8_t port);
void BQ25798_FeedWatchDog(uint8_t port);
uint8_t BQ25798_ChkI2cIsOk(uint8_t port);

uint8_t BQ25798_Write(uint8_t port,uint8_t reg,uint8_t *buf,uint8_t len);
uint8_t BQ25798_Read(uint8_t port,uint8_t reg,uint8_t *buf,uint8_t len);

#endif /* _WS8805_H_ */
