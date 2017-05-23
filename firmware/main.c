#include "samd20e18.h"

#include "adc.h"
#include "clock.h"
#include "extint.h"
#include "gclk.h"
#include "spi.h"
#include "uart.h"
#include "printf.h"

#include "enc28j60.h"
#include "enc28j60_constants.h"

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

void EIC_Handler(void)
{
	// Handle ethernet interrupts
}

void puts(char *ptr)
{
	while (*ptr != 0)
	{
		// Wait for the USART to be ready
		while (!(SERCOM1.USART.INTFLAG & SERCOM_USART_INTFLAG_DRE));
		// Wait until synchronization is complete
		while (SERCOM1.USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
		// Write data to USART module
		SERCOM1.USART.DATA = *ptr++;
		// Wait for the byte to be written
		while (!(SERCOM1.USART.INTFLAG & SERCOM_USART_INTFLAG_TXC));
	}
}

void init(void)
{
	cli();

	configure_osc32k();
	configure_dfll();
	configure_osc8m();
	//configure_systick();

	/*// Write ADC peripheral multiplexer values
	PORTA.PMUX[3] = PORT_PMUX_PMUXO_B;
	// Configure ADC pin as input and enable peripheral multiplexing
	PORTA.PINCFG[7] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;

	adc_init();
	adc_set_mux(ADC_INPUTCTRL_MUXPOS_PIN7, ADC_INPUTCTRL_MUXNEG_GND);*/

	PORTA.PMUX[0] = PORT_PMUX_PMUXO_D | PORT_PMUX_PMUXE_D;
	PORTA.PINCFG[0] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[1] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;

	uart_apb_enable(1);
	gclk_clkctrl(GCLK_CLKCTRL_ID_SERCOM1_CORE, GCLK_CLKCTRL_GEN_GCLK3);
	gclk_clkctrl(GCLK_CLKCTRL_ID_SERCOMX_SLOW, GCLK_CLKCTRL_GEN_GCLK3);
	uart_set_baud(&SERCOM1, 0x1412);
	uart_init(&SERCOM1);
	uart_set_pads(&SERCOM1, SERCOM_USART_CTRLA_RXPO_PAD1, SERCOM_USART_CTRLA_TXPO_PAD0);
	uart_enable(&SERCOM1);

	// Write SPI peripheral multiplexer values
	PORTA.PMUX[7] = PORT_PMUX_PMUXO_C | PORT_PMUX_PMUXE_C;
	PORTA.PMUX[8] = PORT_PMUX_PMUXO_C;
	// Configure pins as inputs and enable peripheral multiplexing
	PORTA.PINCFG[16] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[17] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[19] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	// Set Slave Select as an output and drive it high
	PORTA.OUTSET = PORT_PA18;
	PORTA.DIRSET = PORT_PA18;

	//SERCOM1.SPI.BAUD = 0;

	//spi_apb_enable(1);
	//gclk_clkctrl(GCLK_CLKCTRL_ID_SERCOM1_CORE, GCLK_CLKCTRL_GEN_GCLK3);
	/*spi_set_baud(&SERCOM1, 0x00);
	spi_init(&SERCOM1);
	spi_set_pads(&SERCOM1, SERCOM_SPI_CTRLA_DIPO(0x03), SERCOM_SPI_CTRLA_DOPO(0x00));
	spi_enable(&SERCOM1);*/

	/*extint_init();
	extint_enable();
	// Configure INT pin to input
	PORTA.DIRCLR = PORT_PA15;
	// Enable pin pull resistor, input buffer, and peripheral multiplexing
	PORTA.PINCFG[15] = PORT_PINCFG_PULLEN | PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	// Set internal pull
	PORTA.OUTSET = PORT_PA15;
	// Set EXTINT[15] input sense configuration to falling edge, and enable input filter
	EIC.CONFIG[1] |= EIC_CONFIG_SENSE7_FALL | EIC_CONFIG_FILTEN7;
	// Enable interrupts for EXTINT[15]
	EIC.INTENSET = EIC_INTENSET_EXTINT15;
	// Globally enable EIC interrupts
	extint_nvic_enable();

	enc28j60_init();
	enc28j60_enable();*/
	sei();
}

int main(void)
{
	init();

	//uint8_t value = read(ERDPTL_ADDR);

	printf("Hello, World!\r\n");
	//printf("Value: 0x%02X\r\n", value);

	while(1);
}
