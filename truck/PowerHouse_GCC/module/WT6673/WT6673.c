/*------------------------------------------------------------
File name:		WT6673.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "WT6673.h"
#include "..\..\src\include\App.h"
//------------------------------------------------------------

//----------------variable------------------------------------
//IO狀態檢測
uint8_t bR_WT6673In,bR_WT6673Chk,bR_WT6673Cvt = 0,bR_WT6673Old = 0;
uint8_t bT_WT6673Debounce = WT6673_DEBOUNCE_TIME;
//
USB_INFO sR_UsbC1;
USB_INFO sR_UsbC2;
//------------------------------------------------------------

//-------------statement--------------------------------------

//------------------------------------------------------------
/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_Chk(void)
{
	bR_WT6673In = 0;
	if(WT6673_INT_PIN_STATUS == 0)
	{
		//INT事件
		bR_WT6673In |= WT6673_EVENT_INT;
	}
//	if(WT6673_C1_PIN_STATUS == 0)
	{
		//C口接入
		bR_WT6673In |= WT6673_EVENT_C_IN;
	}

	if(bR_WT6673In == bR_WT6673Chk)
	{
		if(bT_WT6673Debounce == 0)
		{
			bR_WT6673Cvt = bR_WT6673In;
		}
	}else
	{
		bT_WT6673Debounce = WT6673_DEBOUNCE_TIME;
	}
	bR_WT6673Chk = bR_WT6673In;

	if(bR_WT6673Cvt != bR_WT6673Old)
	{
		bR_WT6673In = bR_WT6673Cvt ^ bR_WT6673Old;
		if((bR_WT6673In & WT6673_EVENT_INT) != 0)
		{
			if((bR_WT6673Cvt & WT6673_EVENT_INT) != 0)
			{
				//INT事件
				AppFifoWrite(APP_WT6673_INT);
			}
		}

		if((bR_WT6673In & WT6673_EVENT_C_IN) != 0)
		{
			if((bR_WT6673Cvt & WT6673_EVENT_C_IN) != 0)
			{
				//C口接入
				AppFifoWrite(APP_WT6673_C_IN);
			}else
			{
				//C口拔出
				AppFifoWrite(APP_WT6673_C_OUT);
			}
		}
		bR_WT6673Old = bR_WT6673Cvt;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_TimeChk(void)
{
	//10ms
	if(bT_WT6673Debounce != 0)
	{
		bT_WT6673Debounce--;
	}
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_C1GateOn(void)
{

}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_C1GateOff(void)
{

}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_C2GateOn(void)
{

}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
void WT6673_C2GateOff(void)
{

}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t WT6673_Write(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t status = WT6673_OK;
	uint8_t i;

	if(len == 0)
	{
		return status;
	}
	//Start
	I2C_Start(WT6673_PORT);
	//Addr+W
	I2C_WriteByte(WT6673_PORT,WT6673_DEVICE_ADDR|WT6673_WR);
	if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
	{
		//Reg高8 bytes
		I2C_WriteByte(WT6673_PORT,reg >> 8);
		if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
		{
			//Reg低8 bytes
			I2C_WriteByte(WT6673_PORT,reg & 0xff);
			if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
			{
				//Dat
				for(i = 0;i < len;i++)
				{
					I2C_WriteByte(WT6673_PORT,buf[i]);
					if(I2C_ChkAck(WT6673_PORT) != I2C_ACK)
					{
						status = WT6673_FAIL;
						break;
					}
				}
			}else
			{
				status = WT6673_FAIL;
			}
		}else
		{
			status = WT6673_FAIL;
		}
	}else
	{
		status = WT6673_FAIL;
	}
	//stop
	I2C_Stop(WT6673_PORT);

	return status;
}

/*------------------------------------------------------------
Function:
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t WT6673_Read(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t status = WT6673_OK;
	uint8_t i;

	if(len == 0)
	{
		return status;
	}
	//Start
	I2C_Start(WT6673_PORT);
	//Addr+W
	I2C_WriteByte(WT6673_PORT,WT6673_DEVICE_ADDR|WT6673_WR);
	if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
	{
		//Reg高8 bytes
		I2C_WriteByte(WT6673_PORT,reg >> 8);
		if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
		{
			//Reg低8 bytes
			I2C_WriteByte(WT6673_PORT,reg & 0xff);
			if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
			{
				//ReStart
				I2C_ReStart(WT6673_PORT);
				//Addr+R
				I2C_WriteByte(WT6673_PORT,WT6673_DEVICE_ADDR|WT6673_RD);
				if(I2C_ChkAck(WT6673_PORT) == I2C_ACK)
				{
					//Dat
					for(i = 0;i < (len - 1);i++)
					{
						buf[i] = I2C_read_byte(WT6673_PORT);
						I2C_Ack(WT6673_PORT,I2C_ACK);
					}
					buf[i] = I2C_read_byte(WT6673_PORT);
					I2C_Ack(WT6673_PORT,I2C_NACK);
				}else
				{
					status = WT6673_FAIL;
				}
			}else
			{
				status = WT6673_FAIL;
			}
		}else
		{
			status = WT6673_FAIL;
		}
	}else
	{
		status = WT6673_FAIL;
	}
	//stop
	I2C_Stop(WT6673_PORT);

	return status;
}
