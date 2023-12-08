#ifndef _INTGND_
#define	_INTGND_

//--------------include-------------------------------
#include "mcu_type.h"
//----------------------------------------------------

//----------------macro-------------------------------
#define TIME_100MS			(10)
#define TIME_1S					(10)

#define SEC_TO_MIN			(60)
#define MIN_TO_HOUR			(60)
#define HOUR_TO_DAY			(24)

#define SEC_TO_HOUR			(uint16_t)(SEC_TO_MIN * MIN_TO_HOUR)
#define SEC_TO_DAY			(uint32_t)(SEC_TO_HOUR * HOUR_TO_DAY)
#define MIN_TO_DAY			(uint16_t)(MIN_TO_HOUR * HOUR_TO_DAY)
//----------------------------------------------------

//----------------variable----------------------------

//----------------------------------------------------

//----------------function----------------------------
void Mn_Intgnd(void);							//time deal
//----------------------------------------------------

#endif /* _INTGND_ */
