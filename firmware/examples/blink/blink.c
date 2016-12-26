#include "samd20e18.h"

#include "core_cmFunc.h"
#include "core_cmInstr.h"

#define DFLL_MULTIPLY_FACTOR (48000000 / 32768)
#define DFLL_MAX_COARSE_STEP 0x1C00
#define DFLL_MAX_FINE_STEP 0x3F

void sei()
{	// Generate a Data Memory Barrier
	__DMB();
	// Clear I-bit in the CPSR enabling interrupts
	__enable_irq();
}

void cli()
{	// Set the I-bit in the CPSR, disabling interrupts
	__disable_irq();
	// Generate a Data Memory Barrier
	__DMB();
}

void system_clock_init(void)
{	// Ensure BOD33 and DFLL flags are cleared in SYSCTRL
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET | SYSCTRL_INTFLAG_DFLLRDY;
	// Disable interrupts
	cli();
	// Enable GCLK0
	uint16_t channel = 0x0100;
	// Set the current GCLK channel
	GCLK->CLKCTRL.reg = channel;

	/*
		Enabling the DFLL (Digital Frequency-Locked Loop) 48MHz main clock source

		- Disable the GCLK (Generic ClocK)
		- Set the GCLK channel ID
		- Enable the GCLK

		Per Errata 9905:
			- Set the ONDEMAND bit in SYSCTRL->CFLLCTRL
			- Wait for DFLL sync
			- Set SYSCTRL->DFLLMUL and SYSCTRL->DFLLVAL
			- Set configurations bits in SYSCTRL->CFLLCTRL


	 */

	// Clear the CLKEN bit, disabling the GCLK channel
	GCLK->CLKCTRL.reg &= ~GCLK_CLKCTRL_CLKEN;
	// Wait until the GCLK is disabled
	while (GCLK->CLKCTRL.reg & GCLK_CLKCTRL_CLKEN);
	// Set GCLK ID to DFLL48
	GCLK->CLKCTRL.reg = SYSCTRL_GCLK_ID_DFLL48;
	// Wait until the GCLK is enabled
	while (!GCLK->CLKCTRL.reg & GCLK_CLKCTRL_CLKEN);
	// Disable unused GCLKs
	for (; channel < 0x0800; channel += 0x0100)
	{	// Set the current GCLK channel
		GCLK->CLKCTRL.reg = channel;
		// Clear the CLKEN bit, disabling the GCLK channel
		GCLK->CLKCTRL.reg &= ~GCLK_CLKCTRL_CLKEN;
		// Wait until the GCLK is disabled
		while (GCLK->CLKCTRL.reg & GCLK_CLKCTRL_CLKEN);
	}
	// Set the GCLK bit in the PM APBA register
	PM->APBAMASK.reg |= PM_APBAMASK_GCLK;
	// Initialize the GCLK module with the configured values
	GCLK->CTRL.reg = GCLK_CTRL_SWRST;
	while (GCLK->CTRL.reg & GCLK_CTRL_SWRST);
	// Set coarse value
	uint32_t coarse, fine;
	// Revision D and later silicon has DFLL calibration values
	if ((DSU->DID.reg & 0xF00) > 0x300)
	{
		#define NVM_DFLL_COARSE_POS		58 /* DFLL48M Coarse calibration position */
		#define NVM_DFLL_COARSE_SIZE	6  /* DFLL48M Coarse calibration size */
		#define SYSCTRL_DFLL_COARSE_POS	10 /* DFLL48M Coarse SYSCTRL bit position */

		#define NVM_DFLL_FINE_POS		64 /* DFLL48M Fine calibration position */
		#define NVM_DFLL_FINE_SIZE		10 /* DFLL48M Fine calibration size */

		coarse = ((uint32_t *)(NVMCTRL_OTP4)[1] >> 16) & (((1 << NVM_DFLL_COARSE_SIZE) - 1) << SYSCTRL_DFLL_COARSE_POS);
		/* In some revision chip, the coarse calibration value is not correct. */
		if (coarse == 0x3f) {
			coarse = 0x1f;
		}

		fine = (uint32_t *)(NVMCTRL_OTP4)[2] & ((1 << NVM_DFLL_FINE_SIZE) - 1);
	}
	else
	{
		coarse = 0;
		fine = 512;
	}
	// Clear ONDEMAND bit in SYSCTRL.DFLLCTRL
	SYSCTRL.DFLLCTRL.reg &= ~SYSCTRL_DFLLCTRL_ONDEMAND;
	// Wait for DFLL sync
	while (!(SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY));
	// Set DFLL multiplier
	SYSCTRL->DFLLMUL.reg = DFLL_MAX_COARSE_STEP | DFLL_MAX_FINE_STEP | DFLL_MULTIPLY_FACTOR;
	// Set DFLL value
	SYSCTRL->DFLLVAL.reg = coarse | fine;
	// Set DFLLCTRL config bits
	STSCRTL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_QLDIS | SYSCTRL_DFLLCTRL_CCDIS | SYSCTRL_DFLLCTRL_ONDEMAND | SYSCTRL_DFLLCTRL_LLAW | SYSCTRL_DFLLCTRL_STABLE | SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_ENABLE;
	// Wait for DFLL to be ready
	while (!((SYSCTRL->PCLKSR.reg & (SYSCTRL_PCLKSR_DFLLRDY | SYSCTRL_PCLKSR_DFLLLCKF | SYSCTRL_PCLKSR_DFLLLCKC)) == (SYSCTRL_PCLKSR_DFLLRDY | SYSCTRL_PCLKSR_DFLLLCKF | SYSCTRL_PCLKSR_DFLLLCKC)));


	


	sei();
}

void system_init(void)
{	// Configure clocks
	system_clock_init();
}

int main(void)
{
	while(1);
}
