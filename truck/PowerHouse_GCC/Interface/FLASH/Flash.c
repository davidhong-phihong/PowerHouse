/******************** (C) COPYRIGHT 2019 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2019/01
* AUTHOR:				SA1
* IC:						SN32F760B
* DESCRIPTION:	Flash related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
*	1.0				2017/07/07	SA1			First release
*	1.3				2019/01/04	SA1			1. Remove FLASH_MassErase function and FLASH_EraseSector function.
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
#include "Flash.h"


/*_____ D E C L A R A T I O N S ____________________________________________*/
uint32_t wFLASH_PGRAM[2];


/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: Flash_ProgramPage
* Description	: Program assigned page in Flash ROM
* Input			: adr - Page start address (word-alignment) of Flash
*				  		sz - Content size to be programmed (Bytes)
*				  		pBuf - pointer to the Source data
* Output		: None
* Return		: OK or FAIL
* Note			: None
*****************************************************************************/
uint32_t FLASH_ProgramPage (uint32_t adr, uint32_t sz, uint8_t *pBuf)
{
	SN_FLASH->CTRL = FLASH_PG;                  // Programming Enabled
	SN_FLASH->ADDR = adr;

	FLASH_WAIT_FOR_DONE	
	
	while (sz){

		SN_FLASH->DATA = *((uint32_t *)pBuf);

		FLASH_WAIT_FOR_DONE

		// Go to next Word
		//adr += 4;
		pBuf += 4;
		sz  -= 4;
	}
	
	// Check for Errors
	if ((SN_FLASH->STATUS & FLASH_ERR) == FLASH_ERR) {
		SN_FLASH->STATUS = 0;
		return (FAIL);
	}

	SN_FLASH->CTRL |= FLASH_START;				// Start Program

	FLASH_WAIT_FOR_DONE

	// Check for Errors
	if ((SN_FLASH->STATUS & FLASH_ERR) == FLASH_ERR) {
		SN_FLASH->STATUS = 0;
		return (FAIL);
	}

	return (OK);
}

/*****************************************************************************
* Function		: FLASH_Checksum
* Description	: Calculate Checksum in Flash ROM
* Input			: None
* Output		: Checksum of User ROM
* Return		: None
* Note			: None
*****************************************************************************/
uint16_t FLASH_Checksum (void)
{
 	SN_FLASH->CTRL = FLASH_CHK;

	FLASH_WAIT_FOR_DONE
	
	return	(uint16_t) (SN_FLASH->CHKSUM);
}
