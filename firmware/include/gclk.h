#ifndef _SAMD20E18_TC_H_
#define _SAMD20E18_TC_H_

#include "samd20e18.h"

void gclk_clkctrl(uint32_t generator, uint32_t id)
{
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | generator | id;
}

void gclk_gendiv(uint32_t id, uint32_t div)
{
	GCLK.GENDIV = id | div;
}

void gclk_genctrl(uint32_t id, uint32_t source, uint32_t divsel, uint32_t idc)
{
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);

	GCLK.GENCTRL = divsel | idc | GCLK_GENCTRL_GENEN | source | id;
}

void gclk_apb_enable(void)
{
	// Set the GCLK bit in the power manager for APBA
	PM.APBAMASK |= PM_APBAMASK_GCLK;
}

#endif
