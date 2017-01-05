#include <stdarg.h>
#include <stddef.h>
#include "samd20e18.h"

int printf(const char *fmt, ...);

volatile uint32_t millis = 0;

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
	// Set peripheral multiplexing for SERCOM3
	PORTA.PMUX[12] = PORT_PMUX_PMUXO_C | PORT_PMUX_PMUXE_C;
	// Configure PA24 and PA25
	PORTA.PINCFG[24] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[25] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
}

void usart_init(void)
{   // Set the SERCOM3 bit in the APBC mask
	PM.APBCMASK |= PM_APBCMASK_SERCOM3;
	// Configure SERCOM3 core and slow clocks
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM3_CORE | GCLK_CLKCTRL_GEN_GCLK3;
	GCLK.CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOMX_SLOW | GCLK_CLKCTRL_GEN_GCLK3;
	// Set uart baud register for 115200bps
	SERCOM3.USART.BAUD = 0x1412;
	// Wait for SERCOM synchronization
	while (SERCOM3.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Enable transmit and recieve
	SERCOM3.USART.CTRLB = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN;
	// Wait for SERCOM synchronization
	while (SERCOM3.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set data order, RX/TX mux, standby mode, and enable SERCOM3
	SERCOM3.USART.CTRLA = SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_RXPO_PAD3 | SERCOM_USART_CTRLA_TXPO_PAD2 | SERCOM_USART_CTRLA_RUNSTDBY | SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_ENABLE;
}

void tc_init(void)
{	// Enable APBC clock for TC0
	PM.APBCMASK |= PM_APBCMASK_TC0;
	// Map GCLK Generator 2 as the TC0 input clock and enable it
	GCLK.CLKCTRL = GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_TC0_TC1;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Configure TC0 to synchronize with the GCLK, DIV1024 prescaler, match frequency mode, 16bit mode, and enable it
	TC0.COUNT16.CTRLA = TC_CTRLA_PRESCSYNC_GCLK | TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_WAVEGEN_MFRQ | TC_CTRLA_MODE_COUNT16;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Clear CTRLB
	TC0.COUNT16.CTRLBCLR = 0xFF;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Count up
	TC0.COUNT16.CTRLBSET = TC_CTRLBSET_DIR;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Set TC period to 2000, 2MHz / 1000Hz = 2000Hz
	TC0.COUNT16.CC[0] = 0x0002;
	// Wait TC0 to finish synchronizing
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Enable TC overflow interrupts
	TC0.COUNT16.INTENSET = TC_INTENSET_OVF;
	// Enable TC0 IRQ vector
	NVIC_EnableIRQ(TC0_IRQn);
}

void system_init(void)
{   // Disable interrupts
	cli();
	// Configure 48MHz DFLL
	clock_init();
	// Configure GPIOs
	gpio_init();
	// Configure EDBG CDC USART
	usart_init();
	// Configure TC0
	tc_init();
	// Enable interrupts
	sei();
}

uint32_t benchmark(void (*func)(void*), void *data)
{
	// Sanity check
	if (!func)
	{
		printf("Invalid function pointer passed to benchmark\r\n");
		return 0;
	}

	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Enable TC0 - start counting
	TC0.COUNT16.CTRLA |= TC_CTRLA_ENABLE;
	// Call function under test
	(*func)(data);
	// Capture millis
	uint32_t time = millis;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Stop TC0
	TC0.COUNT16.CTRLA &= ~TC_CTRLA_ENABLE;
	// Wait for TC0 to synchronize
	while (TC0.COUNT16.STATUS & TC_STATUS_SYNCBUSY);
	// Clear TC0 counter
	TC0.COUNT16.COUNT = 0;
	// Clear millis
	millis = 0;

	return time;
}

void empty_benchmark(void *data) { asm volatile("nop"); }


#define COUNT 0x00FFFFFF
void count_benchmark(void *data)
{
	uint32_t *ptr = data;
	uint32_t count;

	if (ptr) count = *ptr;
	else count = COUNT;

	for (volatile uint32_t i = 0; i < count; i++);
}

void TC0_Handler(void)
{
	millis++;
	TC0.COUNT8.INTFLAG = TC_INTFLAG_OVF;
}

int main(void)
{
	system_init();

	printf("Empty benchmark took %dus\r\n", benchmark(&empty_benchmark, NULL));

	uint32_t count = 0x000FFFFF;
	printf("Counting to %d took %dus\r\n", COUNT, benchmark(&count_benchmark, &count));

	while(1);
}