#ifndef __SN32F760B_SYSTICK_H
#define __SN32F760B_SYSTICK_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F760B.h>
#include <SN32F700_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	SYSTICK_IRQ		INTERRUPT_METHOD		//INTERRUPT_METHOD:	Enable SysTick timer and interrupt
																					//POLLING_METHOD: 	Enable SysTick timer ONLY

/*_____ M A C R O S ________________________________________________________*/
#define	__SYSTICK_CLEAR_COUNTER_AND_FLAG	SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Msk;

/*_____ D E C L A R A T I O N S ____________________________________________*/
extern volatile uint8_t bF_Tick;
extern volatile uint32_t wR_Tick;

void SysTick_Init(void);
void SysTick_ConfigTime(uint32_t);

#endif	/*__SN32F760B_SYSTICK_H*/
