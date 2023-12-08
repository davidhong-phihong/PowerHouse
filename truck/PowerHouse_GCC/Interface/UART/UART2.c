/******************** (C) COPYRIGHT 2019 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2019/05
* AUTHOR:				SA1
* IC:						SN32F760B
* DESCRIPTION:	UART2 related functions.
*____________________________________________________________________________
*	REVISION	Date				User	Description
*	1.0				2017/07/07	SA1		First release
*	1.4				2019/05/31	SA1			1. Fix variable issue in UART2_IRQHandler.
*____________________________________________________________________________
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS TIME TO MARKET.
* SONiX SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL
* DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
* AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN
* IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F760B.h>
#include "UART.h"
#include "..\..\Utility\Utility.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/


/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ F U N C T I O N S __________________________________________________*/


/*****************************************************************************
* Function		: UART2_Init
* Description	: Initialization of UART2
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void UART2_Init (void)
{
	SN_SYS1->AHBCLKEN |= UART2_CLK_EN;			//Enables clock for UART2

	//===Line Control===
	//setting character Word length(5/6/7/8 bit)
	SN_UART2->LC = (UART_CHARACTER_LEN8BIT		//8bit character length.
								|	UART_STOPBIT_1BIT					//stop bit of 1 bit
								|	UART_PARITY_BIT_DISEN			//parity bit is disable
								|	UART_PARITY_SELECTODD			//parity bit is odd
								|	UART_BREAK_DISEN		//Break Transmission control disable
								|	UART_DIVISOR_EN);		//Divisor Latch Access enable

	//===Baud Rate Calculation===
	//UART PCLK = 48MHz, Baud rate = 115200
	SN_UART2->FD = (UART_OVER_SAMPLE_16|UART_MULVAL_7|UART_DIVADDVAL_5);
  SN_UART2->DLM  = 0;
  SN_UART2->DLL  = 16;

	SN_UART2->LC &= ~(UART_DIVISOR_EN);		//Disable divisor latch

	//===FIFO Control===
	SN_UART2->FIFOCTRL  =(UART_FIFO_ENABLE				//Enable UART FIFOs
											|	UART_RXFIFO_RESET				//RX FIFO Reset
											|	UART_TXFIFO_RESET				//TX FIFO Reset
											|	UART_RXTRIGGER_LEVEL1);	//RX Trigger Level(1/4/8/14 characters)

	//===Scratch Pad===
	//SN_UART2->SP = 0;												//A readable, writable byte

	//===Oversampling===
	//SN_UART2->FD |= UART_OVER_SAMPLE_8;		//OVER8(Oversampling Value), 1:Oversampling by 8. 0:Oversampling by 16

	//===Half-duplex===
	SN_UART2->HDEN = 1;											//Half-duplex mode enable

	//===Interrupt Enable===
	SN_UART2->IE_b.RDAIE = 1;

	//===UART Control===
	SN_UART2->CTRL =(UART_EN										//Enable UART0
									|	UART_RX_EN									//Enable RX
									| UART_TX_EN);								//Enable TX
	//===NVIC===
	NVIC_SetPriority(UART2_IRQn,0);
	NVIC_EnableIRQ(UART2_IRQn);			//Enable UART2 INT

}

/*****************************************************************************
* Function		:
* Description	:
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void UART2_ReConfigBaud(uint32_t rate)
{
	//關閉UART
	SN_UART2->CTRL_b.UARTEN = 0;

	SN_UART2->LC |= UART_DIVISOR_EN;
	switch(rate)
	{
		case UART_BAUD_9600:
			SN_UART2->FD = (UART_OVER_SAMPLE_16|UART_MULVAL_7|UART_DIVADDVAL_5);
			SN_UART2->DLM  = 0;
			SN_UART2->DLL  = 192;
			break;
		case UART_BAUD_19200:
			SN_UART2->FD = (UART_OVER_SAMPLE_16|UART_MULVAL_7|UART_DIVADDVAL_5);
			SN_UART2->DLM  = 0;
			SN_UART2->DLL  = 96;
			break;
		case UART_BAUD_57600:
			SN_UART2->FD = (UART_OVER_SAMPLE_16|UART_MULVAL_7|UART_DIVADDVAL_5);
			SN_UART2->DLM  = 0;
			SN_UART2->DLL  = 32;
			break;
		default:
		case UART_BAUD_115200:
			SN_UART2->FD = (UART_OVER_SAMPLE_16|UART_MULVAL_7|UART_DIVADDVAL_5);
			SN_UART2->DLM  = 0;
			SN_UART2->DLL  = 16;
			break;
	}
	SN_UART2->LC &= ~(UART_DIVISOR_EN);
	//Enable UART
	SN_UART2->CTRL_b.UARTEN = 1;
}
