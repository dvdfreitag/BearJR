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
}

void gpio_init(void)
{	// PA16 (SERCOM1 PAD0): MOSI
	// PA17 (SERCOM1 PAD1): SCK
	// PA18 (SERCOM1 PAD2): SS
	// PA19 (SERCOM1 PAD3): MISO
	
	// Write peripheral multiplexer values
	PORTA.PMUX[8] = PORT_PMUX_PMUXO_C | PORT_PMUX_PMUXE_C;
	PORTA.PMUX[9] = PORT_PMUX_PMUXO_C;
	// Configure pins as inputs and enable peripheral multiplexing
	PORTA.PINCFG[16] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[17] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[19] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	// Set Slave Select as an output and drive it high
	PORTA.OUTSET = PORT_PA18;
	PORTA.DIRSET = PORT_PA18 | PORT_PA14;
}

void spi_init(void)
{	// Enable APBC clock for SERCOM1
	PM.APBCMASK |= PM_APBCMASK_SERCOM1;
	// Configure SERCOM1 slow and core clocks
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM1_CORE | GCLK_CLKCTRL_GEN_GCLK0;
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOMX_SLOW | GCLK_CLKCTRL_GEN_GCLK0;
	// Set SERCOM1 SPI baud rate to 24MHz. baud = (48MHz / (2 * 24MHz)) - 1 = 0
	SERCOM1.SPI.BAUD = 0;
	// Wait until synchronization is complete
	while (SERCOM1.SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Enable SERCOM1 SPI receiver
	SERCOM1.SPI.CTRLB = SERCOM_SPI_CTRLB_RXEN;
	// Wait until synchronization is complete
	while (SERCOM1.SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Write configuration to CTRLA
	SERCOM1.SPI.CTRLA = SERCOM_SPI_CTRLA_DIPO(0x03) | SERCOM_SPI_CTRLA_RUNSTDBY | SERCOM_SPI_CTRLA_MODE_SPI_MASTER | SERCOM_SPI_CTRLA_ENABLE;
}

void system_init(void)
{	// Disable interrupts
	cli();
	// Configure 48MHz DFLL
	clock_init();
	// Configure GPIOs
	gpio_init();
	// Configure spi
	spi_init();
	// Enable interrupts
	sei();
}

int spi_writez(const uint8_t *ptr, int len)
{
	int nChars = 0;
	
	// Acquire slave
	PORTA.OUTCLR = PORT_PA18;
	// Write block
	for (; len != 0; --len)
	{	// Wait until the module is ready to write a character
		while (!(SERCOM1.SPI.INTFLAG & SERCOM_SPI_INTFLAG_DRE));
		// Write the next character
		SERCOM1.SPI.DATA = ptr[nChars++] & SERCOM_SPI_DATA_MASK;
	}
	// Wait for the last byte to be shifted out
	while (!(SERCOM1.SPI.INTFLAG & SERCOM_SPI_INTFLAG_TXC));
	// Release slave
	PORTA.OUTSET = PORT_PA18;
	
	return nChars;
}

int spi_read(uint8_t *ptr, int len)
{
	int nChars = 0;
	
	// Clear out the 2-byte receive buffer
	SERCOM1.SPI.DATA;
	SERCOM1.SPI.DATA;

	// Acquire slave
	PORTA.OUTCLR = PORT_PA18;
	// Read block
	for (; len != 0; --len)
	{	// Wait until the module is ready to write a character
		while (!(SERCOM1.SPI.INTFLAG & SERCOM_SPI_INTFLAG_DRE));
		// Write dummy character
		SERCOM1.SPI.DATA = 0x00;
		// Wait until the module is ready to read a character
		while (!(SERCOM1.SPI.INTFLAG & SERCOM_SPI_INTFLAG_RXC));
		// Read next byte
		ptr[nChars++] = SERCOM1.SPI.DATA;
	}
	// Release slave
	PORTA.OUTSET = PORT_PA18;
	
	return nChars;
}

int main(void)
{
	system_init();

	uint8_t *buffer = (uint8_t *)"Hello, World!\r\n";
	spi_write(buffer, 15);

	while(1);
}
