/*------------------------------------------------------------
File name:		I2C.c
Description:
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "I2C.h"
///------------------------------------------------------------

//----------------variable------------------------------------

//------------------------------------------------------------

//-------------statement--------------------------------------
uint8_t I2C_GetSdaStatus(uint8_t port);
void I2C_SetSdaIuput(uint8_t port);
void I2C_SetSdaOutput(uint8_t port);
void I2C_SetSclHigh(uint8_t port);
void I2C_SetSdaHigh(uint8_t port);
void I2C_SetSclLow(uint8_t port);
void I2C_SetSdaLow(uint8_t port);
void I2C_SetDelay(uint8_t port);
void I2C_Delay(uint32_t R_delay);
//------------------------------------------------------------

/*------------------------------------------------------------
Function:			I2C_Start
Description:
Input:
Output:
--------------------------------------------------------------*/
void I2C_Start(uint8_t port)
{
	I2C_SetSdaLow(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclLow(port);
	I2C_Delay(I2C_SPEED1);
}

/*------------------------------------------------------------
Function:			I2C_ReStart
Description:
Input:
Output:
--------------------------------------------------------------*/
void I2C_ReStart(uint8_t port)
{
	I2C_SetSdaHigh(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclHigh(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSdaLow(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclLow(port);
	I2C_Delay(I2C_SPEED1);
}

/*------------------------------------------------------------
Function:			I2C_Stop
Description:
Input:
Output:
--------------------------------------------------------------*/
void I2C_Stop(uint8_t port)
{
	I2C_SetSdaLow(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclHigh(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSdaHigh(port);
	I2C_Delay(I2C_SPEED1);
}

/*------------------------------------------------------------
Function:			I2C_ChkAck
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t I2C_ChkAck(uint8_t port)
{
	uint8_t ack = I2C_NACK;

	I2C_SetSdaIuput(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclHigh(port);
	I2C_Delay(I2C_SPEED1);

	ack = I2C_GetSdaStatus(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclLow(port);
	I2C_Delay(I2C_SPEED1);

	I2C_SetSdaOutput(port);

	return ack;
}

/*------------------------------------------------------------
Function:			I2C_Ack
Description:
Input:
Output:
--------------------------------------------------------------*/
void I2C_Ack(uint8_t port,uint8_t ack)
{
	if(ack == I2C_ACK)
	{
		I2C_SetSdaLow(port);
	}else
	{
		I2C_SetSdaHigh(port);
	}
	I2C_Delay(I2C_SPEED1);

	I2C_SetSclHigh(port);
	I2C_Delay(I2C_SPEED1);

	I2C_Delay(I2C_SPEED1);

	I2C_SetSclLow(port);
	I2C_Delay(I2C_SPEED1);
}

/*------------------------------------------------------------
Function:			I2C_WriteByte
Description:
Input:
Output:
--------------------------------------------------------------*/
void I2C_WriteByte(uint8_t port,uint8_t dat)
{
	uint8_t i;

	for(i = 0;i < 8;i++)
	{
		if((dat & 0x80) == 0)
		{
			I2C_SetSdaLow(port);
		}else
		{
			I2C_SetSdaHigh(port);
		}
		I2C_Delay(I2C_SPEED1);

		I2C_SetSclHigh(port);
		I2C_Delay(I2C_SPEED1);

		I2C_Delay(I2C_SPEED1);

		I2C_SetSclLow(port);
		I2C_Delay(I2C_SPEED1);

		dat <<= 1;
	}
}

/*------------------------------------------------------------
Function:			I2C_read_byte
Description:
Input:
Output:
--------------------------------------------------------------*/
uint8_t I2C_read_byte(uint8_t port)
{
	uint8_t i;
	uint8_t dat;

	I2C_SetSdaIuput(port);
	for(i = 0;i < 8;i++)
	{
		I2C_Delay(I2C_SPEED1);
		dat <<= 1;
		I2C_SetSclHigh(port);
		I2C_Delay(I2C_SPEED1);

		if(I2C_GetSdaStatus(port) == I2C_NACK)
		{
			dat |= 0x01;
		}
		I2C_Delay(I2C_SPEED1);

		I2C_SetSclLow(port);
		I2C_Delay(I2C_SPEED1);
	}
	I2C_SetSdaOutput(port);

	return dat;
}

/*------------------------------------------------------------
Function:			I2C_GetSdaStatus
Description:	讀取SDA應答狀態
Input:
Output:			I2C_ACK/I2C_NACK
--------------------------------------------------------------*/
uint8_t I2C_GetSdaStatus(uint8_t port)
{
	uint8_t status = I2C_NACK;

	switch(port)
	{
		case I2C_PORT1:
			if((I2C_SDA1_PORT->DATA & I2C_SDA1_BIT) == 0)
			{
				status = I2C_ACK;
			}
			break;
		case I2C_PORT2:
			if((I2C_SDA2_PORT->DATA & I2C_SDA2_BIT) == 0)
			{
				status = I2C_ACK;
			}
			break;
		case I2C_PORT3:
			if((I2C_SDA3_PORT->DATA & I2C_SDA3_BIT) == 0)
			{
				status = I2C_ACK;
			}
			break;
	}

	return status;
}

/*------------------------------------------------------------
Function:			I2C_SetSdaIuput
Description:	將SDA切換為輸入模式，釋放總線
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSdaIuput(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SDA1_PORT->MODE &= (~I2C_SDA1_BIT);
			break;
		case I2C_PORT2:
			I2C_SDA2_PORT->MODE &= (~I2C_SDA2_BIT);
			break;
		case I2C_PORT3:
			I2C_SDA3_PORT->MODE &= (~I2C_SDA3_BIT);
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetSdaOutput
Description:	將SDA切換為輸出模式
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSdaOutput(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SDA1_PORT->MODE |= I2C_SDA1_BIT;
			break;
		case I2C_PORT2:
			I2C_SDA2_PORT->MODE |= I2C_SDA2_BIT;
			break;
		case I2C_PORT3:
			I2C_SDA3_PORT->MODE |= I2C_SDA3_BIT;
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetSclHigh
Description:	SCL輸出高電位
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSclHigh(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SCL1_PORT->BSET |= I2C_SCL1_BIT;
			break;
		case I2C_PORT2:
			I2C_SCL2_PORT->BSET |= I2C_SCL2_BIT;
			break;
		case I2C_PORT3:
			I2C_SCL3_PORT->BSET |= I2C_SCL3_BIT;
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetSdaHigh
Description:	SDA輸出高電位
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSdaHigh(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SDA1_PORT->BSET |= I2C_SDA1_BIT;
			break;
		case I2C_PORT2:
			I2C_SDA2_PORT->BSET |= I2C_SDA2_BIT;
			break;
		case I2C_PORT3:
			I2C_SDA3_PORT->BSET |= I2C_SDA3_BIT;
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetSclLow
Description:	SCL輸出低電位
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSclLow(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SCL1_PORT->BCLR |= I2C_SCL1_BIT;
			break;
		case I2C_PORT2:
			I2C_SCL2_PORT->BCLR |= I2C_SCL2_BIT;
			break;
		case I2C_PORT3:
			I2C_SCL3_PORT->BCLR |= I2C_SCL3_BIT;
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetSdaLow
Description:	SDA輸出低電位
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetSdaLow(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_SDA1_PORT->BCLR |= I2C_SDA1_BIT;
			break;
		case I2C_PORT2:
			I2C_SDA2_PORT->BCLR |= I2C_SDA2_BIT;
			break;
		case I2C_PORT3:
			I2C_SDA3_PORT->BCLR |= I2C_SDA3_BIT;
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_SetDelay
Description:	設定延遲時間
Input:
Output:
--------------------------------------------------------------*/
void I2C_SetDelay(uint8_t port)
{
	switch(port)
	{
		case I2C_PORT1:
			I2C_Delay(I2C_SPEED1);
			break;
		case I2C_PORT2:
			I2C_Delay(I2C_SPEED2);
			break;
		case I2C_PORT3:
			I2C_Delay(I2C_SPEED3);
			break;
	}
}

/*------------------------------------------------------------
Function:			I2C_Delay
Description:	延遲
Input:
Output:
--------------------------------------------------------------*/
void I2C_Delay(uint32_t R_delay)
{
	while(R_delay != 0)
	{
		R_delay--;
	}
}
