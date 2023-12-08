#ifndef _I2C_SW_
#define _I2C_SW_

//--------------include-------------------------------
#include "..\..\src\include\mcu_type.h"
//----------------------------------------------------

//----------------macro-------------------------------

enum
{
	I2C_PORT1 = 0,
	I2C_PORT2,I2C_PORT3
};

#define	I2C_ACK						0
#define	I2C_NACK					1
//I2C1
#define	I2C_SCL1_PORT			SN_GPIO0
#define	I2C_SCL1_BIT			(1 << 6)
#define	I2C_SDA1_PORT			SN_GPIO0
#define	I2C_SDA1_BIT			(1 << 7)

#define I2C_SPEED1				10
//I2C2
#define	I2C_SCL2_PORT			SN_GPIO0
#define	I2C_SCL2_BIT			(1 << 2)
#define	I2C_SDA2_PORT			SN_GPIO0
#define	I2C_SDA2_BIT			(1 << 3)

#define I2C_SPEED2				10
//I2C3
#define	I2C_SCL3_PORT			SN_GPIO2
#define	I2C_SCL3_BIT			(1 << 6)
#define	I2C_SDA3_PORT			SN_GPIO2
#define	I2C_SDA3_BIT			(1 << 7)

#define I2C_SPEED3				10
//----------------------------------------------------

//----------------variable----------------------------

//----------------------------------------------------

//----------------function----------------------------
void I2C_Start(uint8_t port);
void I2C_ReStart(uint8_t port);
void I2C_Stop(uint8_t port);
uint8_t I2C_ChkAck(uint8_t port);
void I2C_Ack(uint8_t port,uint8_t ack);
void I2C_WriteByte(uint8_t port,uint8_t dat);
uint8_t I2C_read_byte(uint8_t port);
//----------------------------------------------------

#endif /* _I2C_SW_ */
