/*------------------------------------------------------------
File name:		Intgnd.c
Description:	this file provide function to calculate time
--------------------------------------------------------------*/

//--------------include---------------------------------------
#include "include\intgnd.h"
#include "include\bat.h"
#include "include\led.h"
//
#include "..\module\WT6673\WT6673.h"
#include "..\module\BQ25798\BQ25798.h"
//
#include "..\interface\Systick\SysTick.h"



//------------------------------------------------------------

//----------------variable------------------------------------
uint8_t bT_10ms,bT_100ms;
//------------------------------------------------------------

//-------------statement--------------------------------------

//------------------------------------------------------------

/*------------------------------------------------------------
Function:		intgnd
Description:	timer deal
Input:
Output:
--------------------------------------------------------------*/
void Mn_Intgnd()
{
	if(bF_Tick)
	{
		bF_Tick = 0;
		//10ms
		WT6673_TimeChk();
		Bat_ChkStatus();
		Led_TimeChk();

		bT_10ms++;
		if(bT_10ms >= TIME_100MS)
		{
			bT_10ms = 0;
			bT_100ms++;

		}

		if(bT_100ms >= TIME_1S)
		{
			bT_100ms = 0;

		}
	}
}

