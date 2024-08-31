/*
 * GIE_prg.c
 *
 *  Created on: Aug 29, 2022
 *      Author: hp
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "GIE_reg.h"
#include"GIE_int.h"


void GIE_vEnableGlobalInterrupt()
{
	SET_BIT(SREG,I);
}
void GIE_vDisableGlobalInterrupt()
{
	CLR_BIT(SREG,I);
}
