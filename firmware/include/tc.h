#ifndef _SAMD20E18_TC_H_
#define _SAMD20E18_TC_H_

#include "samd20e18.h"

void tc_init(Tc *timer)
{
	// Wait for TC0 to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Configure TC0 to synchronize with the GCLK, DIV1024 prescaler, match frequency mode, 16bit mode, and enable it
	timer->COUNT16.CTRLA = TC_CTRLA_PRESCSYNC_GCLK | TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_WAVEGEN_MFRQ | TC_CTRLA_MODE_COUNT16;
	// Wait for TC0 to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Clear CTRLB
	timer->COUNT16.CTRLBCLR = 0xFF;
	// Wait for TC0 to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Count up
	timer->COUNT16.CTRLBSET = TC_CTRLBSET_DIR;
	// Wait TC to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Enable TC overflow interrupts
	timer->COUNT16.INTENSET = TC_INTENSET_OVF;
}

void tc_set_period(Tc *timer, uint16_t period)
{
	// Wait for TC to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Set TC period to 2000, 2MHz / 1000Hz = 2000Hz
	timer->COUNT16.CC[0] = period;
}

void tc_enable(Tc *timer)
{
	// Wait TC to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Set enable bit
	timer->COUNT16.CTRLA |= TC_CTRLA_ENABLE;
}

void tc_disable(Tc *timer)
{
	// Wait TC to synchronize
	while (timer->COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Set enable bit
	timer->COUNT16.CTRLA &= ~TC_CTRLA_ENABLE;	
}

void tc_apb_enable(uint32_t timer)
{
	PM.APBCMASK |= (PM_APBCMASK_TC0 << timer);
}

void tc_nvic_enable(uint32_t timer)
{
	NVIC_EnableIRQ(timer + TC0_IRQn);
}

#endif
