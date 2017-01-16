#ifndef _SAMD20E18_ADC_H_
#define _SAMD20E18_ADC_H_

#include "samd20e18.h"
#include "gclk.h"

void adc_init(void)
{
	// Set bit in APB mask
	PM.APBCMASK |= PM_APBCMASK_ADC;
	// Enable the bandgap reference
	SYSCTRL.VREF |= SYSCTRL_VREF_BGOUTEN;
	// Enable peripheral clock for ADC
	gclk_clkctrl(GCLK_CLKCTRL_GEN_GCLK0, GCLK_CLKCTRL_ID_ADC);
	// Wait for ADC synchronization
	while (!(ADC.STATUS & ADC_STATUS_SYNCBUSY));
	// Setup 16x gain
	ADC.INPUTCTRL = ADC_INPUTCTRL_GAIN_16X_Val;
	// Load ADCcalibration from NVM
	ADC.CALIB = (uint16_t)(((uint8_t *)NVMCTRL_OTP4)[3] >> 3) | (((uint8_t *)NVMCTRL_OTP4)[4] << 5);
}

void adc_set_mux(uint32_t muxneg, uint32_t muxpos)
{
	// Wait for ADC synchronization
	while (!(ADC.STATUS & ADC_STATUS_SYNCBUSY));
	// Set mux bits
	ADC.INPUTCTRL = (ADC.INPUTCTRL & ~(ADC_INPUTCTRL_MUXNEG_Msk | ADC_INPUTCTRL_MUXPOS_Msk)) | muxneg | muxpos;
}

void adc_trigger(void)
{
	while (!(ADC.STATUS & ADC_STATUS_SYNCBUSY));
	// Set Software Trigger Start bit to start a conversion
	ADC.SWTRIG |= ADC_SWTRIG_START;
}

uint16_t adc_read_wait(void)
{
	adc_trigger();
	// Wait for the result to be ready
	while (!(ADC.INTFLAG & ADC_INTFLAG_RESRDY));
	while (!(ADC.STATUS & ADC_STATUS_SYNCBUSY));
	// Read the conversion result
	return ADC.RESULT;
}

int adc_read(uint16_t *result)
{
	if (!(ADC.INTFLAG & ADC_INTFLAG_RESRDY)) return -1;

	while (!(ADC.STATUS & ADC_STATUS_SYNCBUSY));
	// Read the conversion result
	*result = ADC.RESULT;

	return 1;
}

#endif
