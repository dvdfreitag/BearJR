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
{	// Set LED0 to output
	//PORTA.DIRSET = PORT_PA14;
	// Set peripheral multiplexing for SERCOM1
	PORTA.PMUX[0] = PORT_PMUX_PMUXO_D | PORT_PMUX_PMUXE_D;
	// Configure PA24 and PA25
	PORTA.PINCFG[0] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[1] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
}

void usart_init(void)
{	// Set the SERCOM1 bit in the APBC mask
	PM.APBCMASK |= PM_APBCMASK_SERCOM1;
	// Configure SERCOM1 core and slow clocks
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM1_CORE | GCLK_CLKCTRL_GEN_GCLK3;
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOMX_SLOW | GCLK_CLKCTRL_GEN_GCLK3;
	// Set uart baud register for 115200bps
	SERCOM1.USART.BAUD = 0x1412;
	// Wait for SERCOM synchronization
	while (SERCOM1.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Enable transmit and recieve
	SERCOM1.USART.CTRLB = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN;
	// Wait for SERCOM synchronization
	while (SERCOM1.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set data order, RX/TX mux, standby mode, and enable SERCOM1
	SERCOM1.USART.CTRLA = SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_RXPO_PAD1 | SERCOM_USART_CTRLA_TXPO_PAD0 | SERCOM_USART_CTRLA_RUNSTDBY | SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_ENABLE;
}

void system_init(void)
{	// Disable interrupts
	cli();
	// Configure 48MHz DFLL
	clock_init();
	// Configure GPIOs
	gpio_init();
	// Configure EDBG CDC USART
	usart_init();
	// Enable interrupts
	sei();
}

void puts(const char *ptr, uint32_t length)
{
	int index = 0;

	for (; length != 0; length--)
	{
		// Wait for the USART to be ready
		while (!(SERCOM1.USART.INTFLAG & SERCOM_USART_INTFLAG_DRE));
		// Wait until synchronization is complete
		while (SERCOM1.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
		// Write data to USART module
		SERCOM1.USART.DATA = ptr[index++];
		// Wait for the byte to be written
		while (!(SERCOM1.USART.INTFLAG & SERCOM_USART_INTFLAG_TXC));
	}
}

int main(void)
{
	system_init();

	puts("Hello World!\r\n", 14);

	while(1);
}
