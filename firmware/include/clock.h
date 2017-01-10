#ifndef _SAMD20E18_CLOCK_H_
#define _SAMD20E18_CLOCK_H_

#include "samd20e18.h"
#include "gclk.h"

/* Configures GCLK generator 2 to output the clock generated by the internal
 *  32.768kHz oscillator. This clock will later be used by the DFLL in closed-loop
 *  mode to generate the 48MHz clock for the CPU/APB. This generator could
 *  also be used by other peripherals including the RTC, SERCOM, TC, etc.
 */
void configure_osc32k(void)
{
	// Load internal 32kHz oscillator calibration from NVM
	uint32_t cal = ((*(uint32_t *)FUSES_OSC32KCAL_ADDR) & FUSES_OSC32KCAL_Msk) >> FUSES_OSC32KCAL_Pos;
	// Enable internal 32kHz oscillator with 130 cycle startup time
	SYSCTRL.OSC32K = SYSCTRL_OSC32K_CALIB(cal) | SYSCTRL_OSC32K_STARTUP_Msk | SYSCTRL_OSC32K_EN32K | SYSCTRL_OSC32K_ENABLE;
	// Set GCLK divider
	gclk_gendiv(GCLK_GENDIV_ID_GCLK2, 0);
	// Setup GCLK generator 2 for OSC32K
	gclk_genctrl(GCLK_GENCTRL_ID_GCLK2, GCLK_GENCTRL_SRC_OSC32K, 0, GCLK_GENCTRL_IDC);
}

/* Configures the main clock generator (GCLK0) to the output of the 48MHz DFLL.
 *  By default at startup the CPU and APB clock prescalers are set to 1, so they
 *  do not need to be changed.
 */
void configure_dfll(void)
{
	// Clear ONDEMAND from DFLLCTRL as per errata
	SYSCTRL.DFLLCTRL &= ~SYSCTRL_DFLLCTRL_ONDEMAND;
	// Wait for GCLK sync
	while (GCLK.STATUS & GCLK_STATUS_SYNCBUSY);
	// Set DFLL multiplier for 40MHz output with 32.768kHz source (48MHz / 32.768kHz = 0x05B8) and maximum step values to 0x07 and 0x3F (50%)
	SYSCTRL.DFLLMUL = SYSCTRL_DFLLMUL_CSTEP(0x1F / 4) | SYSCTRL_DFLLMUL_FSTEP(0xFF / 4) | SYSCTRL_DFLLMUL_MUL(48000000UL / 32768UL);
	// Write DFLL configuration
	SYSCTRL.DFLLCTRL = SYSCTRL_DFLLCTRL_QLDIS | SYSCTRL_DFLLCTRL_MODE | SYSCTRL_DFLLCTRL_ENABLE;
	// Configure GCLK generator 2 (OSC32K) as source clock
	gclk_clkctrl(GCLK_CLKCTRL_GEN_GCLK2, GCLK_CLKCTRL_ID_DFLL48M);
	// Set GCLK divider
	gclk_gendiv(GCLK_GENDIV_ID_GCLK0, 0);
	// Setup GCLK generator 0 (main clock) for DFLL output
	gclk_genctrl(GCLK_GENCTRL_ID_GCLK0, GCLK_GENCTRL_SRC_DFLL48M, 0, GCLK_GENCTRL_IDC);
}

/* Configures GCLK generator 3 to output the clock generated by the internal 8MHz
 *  oscillator with a prescaler of 4. The result is a clock of 2MHz, which is
 *  useful for generating accurate UART baud rates from 9600 to 115200.
 */
void configure_osc8m(void)
{
	// Clear config bits from OSC8M leaving calibration values
	SYSCTRL.OSC8M &= 0xFFFF0000;
	// Set OSC8M prescaler to div4 (producing 2MHz output) and re-enable
	SYSCTRL.OSC8M |= SYSCTRL_OSC8M_PRESC(2) | SYSCTRL_OSC8M_ENABLE;
	// Set GCLK divider
	gclk_gendiv(GCLK_GENDIV_ID_GCLK3, 0);
	// Setup GCLK generator 3 for OSC8M
	gclk_genctrl(GCLK_GENCTRL_ID_GCLK3, GCLK_GENCTRL_SRC_OSC8M, 0, GCLK_GENCTRL_IDC);
}

#endif
