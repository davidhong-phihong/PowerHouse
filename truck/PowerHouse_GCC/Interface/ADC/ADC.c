/******************** (C) COPYRIGHT 2017 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2017/07
* AUTHOR:				SA1
* IC:						SN32F760B
* DESCRIPTION:	ADC related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2017/07/07	SA1			First release
*
*____________________________________________________________________________
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS TIME TO MARKET.
* SONiX SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL
* DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
* AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN
* IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "..\ADC\ADC.h"

#include <SN32F760B.h>
#include <SN32F700_Def.h>
#include "..\..\Utility\Utility.h"


/*_____ D E C L A R A T I O N S ____________________________________________*/
uint8_t	bADC_StartConv;

/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: ADC_Init
* Description	: Initialization of ADC
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void ADC_Init(void)
{
	SN_SYS1->AHBCLKEN_b.ADCCLKEN = 1;										//Enables HCLK for ADC

	SN_ADC->ADM_b.AVREFHSEL = ADC_AVREFHSEL_INTERNAL;		//Set ADC high reference voltage source from internal reference

	SN_ADC->ADM_b.VHS = ADC_VHS_INTERNAL_2V;

	SN_ADC->ADM_b.CHS = ADC_CHS_AIN4;

	SN_ADC->ADM_b.GCHS = ADC_GCHS_EN;										//Enable ADC global channel

	SN_ADC->ADM_b.ADLEN = ADC_ADLEN_12BIT;							//Set ADC resolution = 12-bit

//	SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV1;							//ADC_CLK = ADC_PCLK/1
	//SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV2;							//ADC_CLK = ADC_PCLK/2
	//SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV4;							//ADC_CLK = ADC_PCLK/4
	SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV8;							//ADC_CLK = ADC_PCLK/8
	//SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV16;							//ADC_CLK = ADC_PCLK/16
	//SN_ADC->ADM_b.ADCKS = ADC_ADCKS_DIV32;							//ADC_CLK = ADC_PCLK/32

	SN_ADC->ADM_b.ADENB = ADC_ADENB_EN;									//Enable ADC

	UT_DelayNx10us(10);																	//Delay 100us
}

/*****************************************************************************
* Function		:
* Description	:
* Input			: channel:ADC_CHS_AINx
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
uint16_t ADC_Sample(uint8_t channel)
{
	uint16_t val;

	//ÇÐ»»Í¨µÀ
	SN_ADC->ADM_b.GCHS = ADC_GCHS_DIS;
	SN_ADC->ADM_b.CHS = channel;
	SN_ADC->ADM_b.GCHS = ADC_GCHS_EN;

	SN_ADC->ADM_b.ADS = 1;
	while(SN_ADC->ADM_b.EOC == 0);
	val = SN_ADC->ADB;

	return val;
}
