#ifndef _SAMD20E18_SPI_H_
#define _SAMD20E18_SPI_H_

#include "samd20e18.h"

void spi_init(Sercom *sercom)
{
	// Wait until synchronization is complete
	while (sercom->SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Enable SERCOM1 SPI receiver
	sercom->SPI.CTRLB = SERCOM_SPI_CTRLB_RXEN;
	// Wait until synchronization is complete
	while (sercom->SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Write configuration to CTRLA
	sercom->SPI.CTRLA = SERCOM_SPI_CTRLA_RUNSTDBY | SERCOM_SPI_CTRLA_MODE_SPI_MASTER;
}

void spi_set_pads(Sercom *sercom, uint32_t dipo, uint32_t dopo)
{
	// Wait until synchronization is complete
	while (sercom->SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Write configuration to CTRLA
	sercom->SPI.CTRLA |= dipo | dopo;
}

void spi_enable(Sercom *sercom)
{
	// Wait until synchronization is complete
	while (sercom->SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Set enable bit
	sercom->SPI.CTRLA |= SERCOM_SPI_CTRLA_ENABLE;
}

void spi_disable(Sercom *sercom)
{
	// Wait until synchronization is complete
	while (sercom->SPI.STATUS & SERCOM_SPI_STATUS_SYNCBUSY);
	// Clear enable bit
	sercom->SPI.CTRLA &= ~SERCOM_SPI_CTRLA_ENABLE;
}

void spi_set_baud(Sercom *sercom, uint8_t baud)
{
	sercom->SPI.BAUD = baud;
}

void spi_apb_enable(uint32_t sercom)
{
	PM.APBCMASK |= PM_APBCMASK_SERCOM0 + sercom;
}

void spi_flush(Sercom *sercom)
{
	if (sercom->SPI.STATUS & SERCOM_SPI_STATUS_BUFOVF)
	{
		// Clear buffer overflow bit
		sercom->SPI.STATUS |= SERCOM_SPI_STATUS_BUFOVF;
	}

	sercom->SPI.DATA;
	sercom->SPI.DATA;
}


void spi_read(Sercom *sercom, uint8_t *data)
{
	// Wait for any bytes that need to be shifted out
	while (!(sercom->SPI.INTFLAG & SERCOM_USART_INTFLAG_DRE));
	// Shift out a dummy byte
	sercom->SPI.DATA = 0x00;
	// Wait for the byte to be shifted in
	while (!(sercom->SPI.INTFLAG & SERCOM_SPI_INTFLAG_RXC));
	// Otherwise, return the byte read from the usart
	*data = sercom->USART.DATA;
}

int spi_read_buffer(Sercom *sercom, uint8_t *buffer, uint32_t length)
{
	uint32_t index = 0;

	for (; length != 0; length--)
	{
		spi_read(sercom, &buffer[index++]);
	}

	return index;
}

void spi_write(Sercom *sercom, uint8_t data)
{
	// Wait for any bytes that need to be shifted out
	while (!(sercom->SPI.INTFLAG & SERCOM_USART_INTFLAG_DRE));
	// Write data
	sercom->SPI.DATA = data;
}

int spi_write_buffer(Sercom *sercom, uint8_t *buffer, uint32_t length)
{
	uint32_t index = 0;

	for (; length != 0; length--)
	{
		spi_write(sercom, buffer[index]);
	}

	return index;
}

int spi_transfer_complete(Sercom *sercom)
{
	return (sercom->SPI.INTFLAG & SERCOM_SPI_INTFLAG_TXC) != 0;
}

#endif
