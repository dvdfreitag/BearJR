#ifndef _SAMD20E18_EXTINT_H_
#define _SAMD20E18_EXTINT_H_

#include "samd20e18.h"
#include "gclk.h"

void extint_init(void)
{
	// Set bit in APB mask
	PM.APBAMASK |= PM_APBAMASK_EIC;
	// Enable peripheral clock for EIC
	gclk_clkctrl(GCLK_CLKCTRL_GEN_GCLK0, GCLK_CLKCTRL_ID_EIC);
	// Wait for EIC synchronization
	while (EIC.STATUS & EIC_STATUS_SYNCBUSY);
}

void extint_enable(void)
{
	// Wait for EIC synchronization
	while (EIC.STATUS & EIC_STATUS_SYNCBUSY);
	// Enable EIC
	EIC.CTRL |= EIC_CTRL_ENABLE;	
}

void extint_nvic_enable(void)
{
	NVIC_EnableIRQ(EIC_IRQn);
}

#endif
