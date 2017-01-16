#include "samd20e18.h"

#include "adc.h"
#include "clock.h"
#include "gclk.h"
#include "spi.h"

#include "enc28j60.h"

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

void init(void)
{
	sei();
	gclk_apb_enable();

	configure_osc32k();
	configure_dfll();
	configure_osc8m();
	configure_systick();

	// Write ADC peripheral multiplexer values
	PORTA.PMUX[3] = PORT_PMUX_PMUXO_B;
	// Configure ADC pin as input and enable peripheral multiplexing
	PORTA.PINCFG[7] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;

	adc_init();
	adc_set_mux(ADC_INPUTCTRL_MUXPOS_PIN7, ADC_INPUTCTRL_MUXNEG_GND);

	// Write SPI peripheral multiplexer values
	PORTA.PMUX[8] = PORT_PMUX_PMUXO_C | PORT_PMUX_PMUXE_C;
	PORTA.PMUX[9] = PORT_PMUX_PMUXO_C;
	// Configure pins as inputs and enable peripheral multiplexing
	PORTA.PINCFG[16] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[17] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	PORTA.PINCFG[19] = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
	// Set Slave Select as an output and drive it high
	PORTA.OUTSET = PORT_PA18;
	PORTA.DIRSET = PORT_PA18;

	spi_apb_enable(1);
	spi_init(&SERCOM1);
	spi_set_pads(&SERCOM1, SERCOM_SPI_CTRLA_DIPO(0x03), SERCOM_SPI_CTRLA_DOPO(0x00));
	spi_set_baud(&SERCOM1, 0x00);
	spi_enable(&SERCOM1);

	enc28j60_init();
	enc28j60_enable();
	cli();
}

int main(void)
{
	init();
	while(1);
}
