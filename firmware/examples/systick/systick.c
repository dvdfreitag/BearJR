#include "samd20e18.h"

void sei()
{   // Generate a Data Memory Barrier
	__DMB();
	// Clear I-bit in the CPSR enabling interrupts
	__enable_irq();
}

void cli()
{   // Set the I-bit in the CPSR, disabling interrupts
	__disable_irq();
	// Generate a Data Memory Barrier
	__DMB();
}

void clock_init(void)
{   // Set the NVM controller to use two wait states when reading
	NVMCTRL.CTRLB = (NVMCTRL.CTRLB & ~NVMCTRL_CTRLB_RWS_Msk) | NVMCTRL_CTRLB_RWS(2);
	// Load internal 32kHz oscillator calibration from NVM
	uint32_t cal = ((*(uint32_t *)FUSES_OSC32KCAL_ADDR) & FUSES_OSC32KCAL_Msk) >> FUSES_OSC32KCAL_Pos;
	// Enable internal 32kHz oscillator with 130 cycle startup time
	SYSCTRL.OSC32K = SYSCTRL_OSC32K_CALIB(cal) | SYSCTRL_OSC32K_STARTUP_Msk | SYSCTRL_OSC32K_EN32K | SYSCTRL_OSC32K_ENABLE;
	// Set the GCLK bit in the power manager for APBA
	PM.APBAMASK |= PM_APBAMASK_GCLK;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Set GCLK Generator 2 prescaler to 1
	GCLK.GENDIV = GCLK_GENDIV_ID_GCLK2;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Configure GCLK Generator 2 to use the internal 32kHz oscillator as a source, enable improved duty cyles (due to odd prescaler) and enable it
	GCLK.GENCTRL = GCLK_GENCTRL_ID_GCLK2 | GCLK_GENCTRL_SRC_OSC32K | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;

	// Clear ONDEMAND from DFLLCTRL as per errata
	SYSCTRL.DFLLCTRL &= ~SYSCTRL_DFLLCTRL_ONDEMAND;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Set DFLL multiplier for 40MHz output with 32.768kHz source (48MHz / 32.768kHz = 0x05B8) and maximum step values to 0x07 and 0x3F (50%)
	SYSCTRL.DFLLMUL = SYSCTRL_DFLLMUL_CSTEP(0x1F / 4) | SYSCTRL_DFLLMUL_FSTEP(0xFF / 4) | SYSCTRL_DFLLMUL_MUL(48000000UL / 32768UL);
	// Write DFLL configuration
	SYSCTRL.DFLLCTRL = SYSCTRL_DFLLCTRL_QLDIS | SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_ENABLE;
	// Map GCLK Generator 2 as the DFLL reference, and enable it
	GCLK.CLKCTRL = GCLK_CLKCTRL_GEN_GCLK2 | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_DFLL48M;   
	// Wait for DFLL to synchronize
	while (!(SYSCTRL.PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
	// Set GCLK Generator 0 (Main clock) prescaler to 1, at POR it's set to 8.
	GCLK.GENDIV = GCLK_GENDIV_ID_GCLK0;
	// Wait for DFLL to synchronize
	while (!(SYSCTRL.PCLKSR & SYSCTRL_PCLKSR_DFLLRDY));
	// Configure GCLK Generator 0 (Main clock) to use the DFLL 48MHz output
	GCLK.GENCTRL = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;

	// Clear config bits from OSC8M leaving calibration values
	SYSCTRL.OSC8M &= 0xFFFF0000;
	// Set OSC8M prescaler and re-enable
	SYSCTRL.OSC8M |= SYSCTRL_OSC8M_PRESC(2) | SYSCTRL_OSC8M_ENABLE;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Set GCLK Generator 3 prescaler to 1
	GCLK.GENDIV = GCLK_GENDIV_ID_GCLK3;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Configure GCLK Generator 3 to use the internal 8MHz oscillator with a prescaler of 4, resulting in 2MHz
	GCLK.GENCTRL = GCLK_GENCTRL_ID_GCLK3 | GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_GENEN;
}

void gpio_init(void)
{   // Set LED0 to output
	PORTA.DIRSET = PORT_PA14;
}

void systick_init(void)
{
	// Set SysTick to trigger every 16,777,215 clock cycles (0.3495253125s at 48MHz)
	SYSTICK.LOAD = 0x00FFFFFF;
	// Set SysTick NVIC priority to highest
	NVIC_SetPriority(SysTick_IRQn, __NVIC_PRIO_Msk);
	// Preload the counter value
	SYSTICK.VAL = 0;
	// Set clock source to main CPU clock, enable the SysTick interrupt and counter
	SYSTICK.CTRL = SYSTICK_CTRL_CLKSOURCE_Msk | SYSTICK_CTRL_TICKINT_Msk | SYSTICK_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
	PORTA.OUTTGL = PORT_PA14;
}

void system_init(void)
{   // Disable interrupts
	cli();
	// Configure 48MHz DFLL
	clock_init();
	// Configure GPIOs
	gpio_init();
	// Configure SysTick
	systick_init();
	// Enable interrupts
	sei();
}

void main(void)
{
	system_init();
	while(1);
}