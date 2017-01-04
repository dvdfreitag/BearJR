/**
 * \file
 *
 * \brief gcc starttup file for SAMD20
 *
 * Copyright (c) 2016 Atmel Corporation,
 *					a wholly owned subsidiary of Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#include "samd20e18.h"

/* Segment boundary symbols defined in linker script */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

/* Default empty handler */
void Dummy_Handler(void);
/* Cortex-M0+ core handlers */
void NMI_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
/* Peripherals handlers */
void PM_Handler              ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SYSCTRL_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void NVMCTRL_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_Handler           ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AC_Handler              ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PTC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
	/* Configure Initial Stack Pointer, using linker-generated symbols */
	.pvStack				= (void*) (&_estack),
	/* Cortex-M0+ interrupt handlers */
	.pfnReset_Handler		= (void*) Reset_Handler,
	.pfnNMI_Handler			= (void*) NMI_Handler,
	.pfnHardFault_Handler	= (void*) HardFault_Handler,
	.pvReservedM12			= (void*) (0UL),			/* Reserved */
	.pvReservedM11			= (void*) (0UL),			/* Reserved */
	.pvReservedM10			= (void*) (0UL),			/* Reserved */
	.pvReservedM9			= (void*) (0UL),			/* Reserved */
	.pvReservedM8			= (void*) (0UL),			/* Reserved */
	.pvReservedM7			= (void*) (0UL),			/* Reserved */
	.pvReservedM6			= (void*) (0UL),			/* Reserved */
	.pfnSVC_Handler			= (void*) SVC_Handler,
	.pvReservedM4			= (void*) (0UL),			/* Reserved */
	.pvReservedM3			= (void*) (0UL),			/* Reserved */
	.pfnPendSV_Handler		= (void*) PendSV_Handler,
	.pfnSysTick_Handler		= (void*) SysTick_Handler,
	/* Configurable peripheral interrupts */
	.pfnPM_Handler			= (void*) PM_Handler,	/*  0 Power Manager */
	.pfnSYSCTRL_Handler		= (void*) SYSCTRL_Handler,	/*  1 System Control */
	.pfnWDT_Handler			= (void*) WDT_Handler,	/*  2 Watchdog Timer */
	.pfnRTC_Handler			= (void*) RTC_Handler,	/*  3 Real-Time Counter */
	.pfnEIC_Handler			= (void*) EIC_Handler,	/*  4 External Interrupt Controller */
	.pfnNVMCTRL_Handler		= (void*) NVMCTRL_Handler,	/*  5 Non-Volatile Memory Controller */
	.pfnEVSYS_Handler		= (void*) EVSYS_Handler,	/*  6 Event System Interface */
	.pfnSERCOM0_Handler		= (void*) SERCOM0_Handler,	/*  7 Serial Communication Interface 0 */
	.pfnSERCOM1_Handler		= (void*) SERCOM1_Handler,	/*  8 Serial Communication Interface 1 */
	.pfnSERCOM2_Handler		= (void*) SERCOM2_Handler,	/*  9 Serial Communication Interface 2 */
	.pfnSERCOM3_Handler		= (void*) SERCOM3_Handler,	/* 10 Serial Communication Interface 3 */
	.pvReserved11           = (void*) (0UL),			/* 11 Reserved */
	.pvReserved12           = (void*) (0UL),			/* 12 Reserved */
	.pfnTC0_Handler			= (void*) TC0_Handler,	/* 13 Basic Timer Counter 0 */
	.pfnTC1_Handler			= (void*) TC1_Handler,	/* 14 Basic Timer Counter 1 */
	.pfnTC2_Handler			= (void*) TC2_Handler,	/* 15 Basic Timer Counter 2 */
	.pfnTC3_Handler			= (void*) TC3_Handler,	/* 16 Basic Timer Counter 3 */
	.pfnTC4_Handler			= (void*) TC4_Handler,	/* 17 Basic Timer Counter 4 */
	.pfnTC5_Handler			= (void*) TC5_Handler,	/* 18 Basic Timer Counter 5 */
	.pvReserved19           = (void*) (0UL),			/* 19 Reserved */
	.pvReserved20           = (void*) (0UL),			/* 20 Reserved */
	.pfnADC_Handler			= (void*) ADC_Handler,	/* 21 Analog Digital Converter */
	.pfnAC_Handler			= (void*) AC_Handler,	/* 22 Analog Comparators */
	.pfnDAC_Handler			= (void*) PTC_Handler,	/* 23 Digital Analog Converter */
	.pfnPTC_Handler			= (void*) PTC_Handler		/* 24 Peripheral Touch Controller */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
	uint32_t *src = &_etext;
	uint32_t *dest = &_sdata;
	/* The linker script places .data just after .text in Flash, so
		lets copy it prior to running */
	if (src != dest)
	{
		while (dest < &_edata) *dest++ = *src++;
	}

	/* Zero the bss segment */
	for (dest = &_sbss; dest < &_ebss;) *dest++ = 0;
	/* Set the vector table base address */
	src = (uint32_t *)(&_sfixed);
	SCB.VTOR = ((uint32_t)src & SCB_VTOR_TBLOFF_Msk);
	/* Overwriting the default value of the NVMCTRL.CTRLB.MANW bit (errata reference 13134) */
	NVMCTRL.CTRLB = NVMCTRL_CTRLB_MANW;
		
	main();
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	while (1);
}
