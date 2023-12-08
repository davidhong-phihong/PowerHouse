//--------------------------------------
#include "include\mcu_type.h"



/*****************************************************************************
* Function		:
* Description	:
* Input			: None
* Output		: None
* Return		:
* Note			: None
*****************************************************************************/
void HardFault_Handler(void)
{
	NVIC_SystemReset();
}
