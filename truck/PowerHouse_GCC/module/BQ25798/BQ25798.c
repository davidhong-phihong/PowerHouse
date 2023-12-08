/*------------------------------------------------------------
File name:		BQ25798.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "BQ25798.h"
//
#include "..\..\interface\Uart\UART.h"
//
#include "..\..\Utility\Utility.h"
//------------------------------------------------------------

//----------------variable------------------------------------
uint8_t bR_BqReadBuf[0x64];
//------------------------------------------------------------

//-------------statement--------------------------------------

//------------------------------------------------------------
/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_GetBatVol(uint8_t port,int16_t *buf)
{
	if(BQ25798_Read(port,0x3B,bR_BqReadBuf,2) == BQ25798_OK)
	{
		*buf = bR_BqReadBuf[0] << 8;
		*buf |= bR_BqReadBuf[1];

		return BQ25798_OK;
	}else
	{
		return BQ25798_FAIL;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_GetBatCurrent(uint8_t port,int16_t *buf)
{
	if(BQ25798_Read(port,0x33,bR_BqReadBuf,2) == BQ25798_OK)
	{
		*buf = bR_BqReadBuf[0] << 8;
		*buf |= bR_BqReadBuf[1];

		return BQ25798_OK;
	}else
	{
		return BQ25798_FAIL;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_GetBatTemp(uint8_t port,int16_t *buf)
{
	if(BQ25798_Read(port,0x3F,bR_BqReadBuf,2) == BQ25798_OK)
	{
		*buf = bR_BqReadBuf[0] << 8;
		*buf |= bR_BqReadBuf[1];

		return BQ25798_OK;
	}else
	{
		return BQ25798_FAIL;
	}
}

/*------------------------------------------------------------
Function:
Description:	讀取5個狀態暫存器+2個錯誤暫存器
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_ReadChargeStatus(uint8_t port,uint8_t *buf)
{
	uint8_t i;

	if(BQ25798_Read(port,0x1B,bR_BqReadBuf,7) == BQ25798_OK)
	{
		for(i = 0;i < 7;i++)
		{
			buf[i] = bR_BqReadBuf[i];
		}

		return BQ25798_OK;
	}else
	{
		return BQ25798_FAIL;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_CeOutputHigh(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			SN_GPIO0->BSET_b.BSET12 = 1;
			break;
		case I2C_PORT2:
			SN_GPIO2->BSET_b.BSET11 = 1;
			break;
		case I2C_PORT3:
			SN_GPIO2->BSET_b.BSET5 = 1;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_CeOutputLow(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			SN_GPIO0->BCLR_b.BCLR12 = 1;
			break;
		case I2C_PORT2:
			SN_GPIO2->BCLR_b.BCLR11 = 1;
			break;
		case I2C_PORT3:
			SN_GPIO2->BCLR_b.BCLR5 = 1;
			break;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_BatChargeEn(uint8_t port)
{
	BQ25798_Read(port,0x0F,bR_BqReadBuf,1);
	bR_BqReadBuf[0] |= (1 << 5);
	BQ25798_Write(port,0x0F,bR_BqReadBuf,1);
	BQ25798_CeOutputLow(port);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_BatChargeDis(uint8_t port)
{
	BQ25798_Read(port,0x0F,bR_BqReadBuf,1);
	bR_BqReadBuf[0] &= ~(1 << 5);
	BQ25798_Write(port,0x0F,bR_BqReadBuf,1);
	BQ25798_CeOutputHigh(port);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_ShipFETEn(uint8_t port)
{
	BQ25798_Read(port,0x11,bR_BqReadBuf,1);
	bR_BqReadBuf[0] &= ~(7 << 1);
	BQ25798_Write(port,0x11,bR_BqReadBuf,1);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_ShipFETDis(uint8_t port)
{
	BQ25798_Read(port,0x11,bR_BqReadBuf,1);
	bR_BqReadBuf[0] &= ~(7 << 1);
	bR_BqReadBuf[0] |= (2 << 1);
	BQ25798_Write(port,0x11,bR_BqReadBuf,1);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_ACFET1En(uint8_t port)
{
	BQ25798_Read(port,0x13,bR_BqReadBuf,1);
	bR_BqReadBuf[0] |= (1 << 7);
	BQ25798_Write(port,0x11,bR_BqReadBuf,1);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_ACFET1Dis(uint8_t port)
{
	BQ25798_Read(port,0x13,bR_BqReadBuf,1);
	bR_BqReadBuf[0] &= ~(1 << 7);
	BQ25798_Write(port,0x11,bR_BqReadBuf,1);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void BQ25798_FeedWatchDog(uint8_t port)
{
	BQ25798_Read(port,0x10,bR_BqReadBuf,1);
	bR_BqReadBuf[0] |= (1 << 3);
	BQ25798_Write(port,0x10,bR_BqReadBuf,1);
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_ChkI2cIsOk(uint8_t port)
{
	if((BQ25798_Read(port,BQ25798_REG72_PART_INFO,bR_BqReadBuf,1) == BQ25798_OK)
		&& (bR_BqReadBuf[0] == BQ25798_PART_ID))
	{
		return BQ25798_OK;
	}else
	{
		return BQ25798_FAIL;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_Write(uint8_t port,uint8_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t status = BQ25798_OK;
	uint8_t i;

	if(len == 0)
	{
		return status;
	}
	//Start
	I2C_Start(port);
	//Addr+W
	I2C_WriteByte(port,BQ25798_DEVICE_ADDR|BQ25798_WR);
	if(I2C_ChkAck(port) == I2C_ACK)
	{
		//Reg
		I2C_WriteByte(port,reg);
		if(I2C_ChkAck(port) == I2C_ACK)
		{
			//Dat
			for(i = 0;i < len;i++)
			{
				I2C_WriteByte(port,buf[i]);
				if(I2C_ChkAck(port) != I2C_ACK)
				{
					status = BQ25798_FAIL;
					break;
				}
			}
		}else
		{
			status = BQ25798_FAIL;
		}
	}else
	{
		status = BQ25798_FAIL;
	}
	//stop
	I2C_Stop(port);

	return status;
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t BQ25798_Read(uint8_t port,uint8_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t status = BQ25798_OK;
	uint8_t i;

	if(len == 0)
	{
		return status;
	}
	//Start
	I2C_Start(port);
	//Addr+W
	I2C_WriteByte(port,BQ25798_DEVICE_ADDR|BQ25798_WR);
	if(I2C_ChkAck(port) == I2C_ACK)
	{
		//Reg
		I2C_WriteByte(port,reg);
		if(I2C_ChkAck(port) == I2C_ACK)
		{
			//ReStart
			I2C_ReStart(port);
			//Addr+R
			I2C_WriteByte(port,BQ25798_DEVICE_ADDR|BQ25798_RD);
			if(I2C_ChkAck(port) == I2C_ACK)
			{
				//Dat
				for(i = 0;i < (len - 1);i++)
				{
					buf[i] = I2C_read_byte(port);
					I2C_Ack(port,I2C_ACK);
				}
				buf[i] = I2C_read_byte(port);
				I2C_Ack(port,I2C_NACK);
			}else
			{
				status = BQ25798_FAIL;
			}
		}else
		{
			status = BQ25798_FAIL;
		}
	}else
	{
		status = BQ25798_FAIL;
	}
	//stop
	I2C_Stop(port);

	return status;
}
