#include "samd20e18.h"

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

void clock_init(void)
{	// Set the NVM controller to use two wait states when reading
	NVMCTRL.CTRLB = 0x04;
	// Load internal 32kHz oscillator calibration from NVM
	uint32_t cal = ((*(uint32_t *)FUSES_OSC32KCAL_ADDR) & FUSES_OSC32KCAL_Msk) >> FUSES_OSC32KCAL_Pos;
	// Enable internal 32kHz oscillator with 130 cycle startup time
	SYSCTRL.OSC32K = SYSCTRL_OSC32K_CALIB(cal) | SYSCTRL_OSC32K_STARTUP_Msk | SYSCTRL_OSC32K_EN32K | SYSCTRL_OSC32K_ENABLE;
	// Set the GCLK bit in the power manager for APBA
	PM.APBAMASK |= PM_APBAMASK_GCLK;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Set GCLK Generator 2 prescaler to 1
	GCLK.GENDIV = GCLK_GENDIV_ID_GCLK2 | GCLK_GENDIV_DIV(1);
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Configure GCLK Generator 2 to use the internal 32kHz oscillator as a source, enable improved duty cyles (due to odd prescaler) and enable it
	GCLK.GENCTRL = GCLK_GENCTRL_ID_GCLK2 | GCLK_GENCTRL_SRC_OSC32K | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Map GCLK Generator 2 as the DFLL reference, and enable it
	GCLK.CLKCTRL = GCLK_CLKCTRL_GEN_GCLK2 | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_DFLL48M;
	// Disable DFLL ONDEMAND per errata
	SYSCTRL.DFLLCTRL = SYSCTRL_DFLLCTRL_QLDIS | SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_ENABLE;
	// Wait for DFLL to synchronize
	while (!(SYSCTRL.PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
	// Set DFLL multiplier for 40MHz output with 32.768kHz source (48MHz / 32.768kHz = 0x05B8) and maximum step values to 0x07 and 0x3F (50%)
	SYSCTRL.DFLLMUL = SYSCTRL_DFLLMUL_CSTEP(0x1F / 4) | SYSCTRL_DFLLMUL_FSTEP(0xFF / 4) | SYSCTRL_DFLLMUL_MUL(48000000UL / 32768UL);
	// Wait until the DFLL is ready, has a coarse lock, and has a fine lock
	while ((SYSCTRL.PCLKSR & (SYSCTRL_PCLKSR_DFLLRDY | SYSCTRL_PCLKSR_DFLLLCKF | SYSCTRL_PCLKSR_DFLLLCKC)) != (SYSCTRL_PCLKSR_DFLLRDY | SYSCTRL_PCLKSR_DFLLLCKF | SYSCTRL_PCLKSR_DFLLLCKC));
	// Wait for DFLL to synchronize
	while (!(SYSCTRL.PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
	// Set GCLK Generator 0 (Main clock) prescaler to 1, at POR it's set to 8.
	GCLK.GENDIV = GCLK_GENDIV_ID_GCLK0 | GCLK_GENDIV_DIV(1);
	// Wait for DFLL to synchronize
	while (!(SYSCTRL.PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
	// Configure GCLK Generator 0 (Main clock) to use the DFLL 48MHz output
	GCLK.GENCTRL = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
}

void gpio_init(void)
{	// Set LED0 to output
	PORTA.DIRSET = PORT_PA14;
}

void eic_init(void)
{	// Set EIC bit in the power manager for APBA
	PM.APBAMASK |= PM_APBAMASK_EIC;
	// Configure the GCLK for EIC and enable it
	GCLK.CLKCTRL = GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_EIC;
	// Wait for EIC to sync
	while (EIC.STATUS & EIC_STATUS_SYNCBUSY);
	// Enable EIC peripheral
	EIC.CTRL |= EIC_CTRL_ENABLE;
	// Clear the port DIR bit to disable the output buffer
	PORTA.DIRCLR = PORT_PA15;
	// Enable pin internal pull resistor, input buffer, and peripheral multiplexing
	PORTA.PINCFG[15] = PORT_PINCFG_PULLEN | PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	// Set internal pull resistor
	PORTA.OUTSET = PORT_PA15;
	// Configre input filtering, and edge detection
	EIC.CONFIG[1] |= EIC_CONFIG_FILTEN7 | EIC_CONFIG_SENSE7_FALL;
	// Enable interrupts for EXTINT15 (user button)
	EIC.INTENSET |= EIC_INTENSET_EXTINT15;
	// Enable EIC interrupt handler
	NVIC_EnableIRQ(EIC_IRQn);
}

void EIC_Handler(void)
{
	if (EIC.INTFLAG & EIC_INTFLAG_EXTINT15)
	{
		PORTA.OUTTGL = PORT_PA14;
		EIC.INTFLAG = EIC_INTFLAG_EXTINT15;
	}
}

void system_init(void)
{	// Disable interrupts
	cli();
	// Configure 48MHz DFLL
	clock_init();
	// Configure GPIOs
	gpio_init();
	// Configure Timers
	eic_init();
	// Enable interrupts
	sei();
}

int main(void)
{
	system_init();

	while(1);
}
