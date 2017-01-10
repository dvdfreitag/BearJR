#ifndef _SAMD20E18_UART_H_
#define _SAMD20E18_UART_H_

#include "samd20e18.h"

void uart_init(Sercom *sercom)
{
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Enable transmit and recieve
	sercom->USART.CTRLB = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN;
	// Wait for SERCOM synchronization
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set data order, RX/TX mux, standby mode, and enable SERCOM3
	sercom->USART.CTRLA = SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_RUNSTDBY | SERCOM_USART_CTRLA_MODE_USART_INT_CLK;
}

void uart_set_pads(Sercom *sercom, uint32_t rx, uint32_t tx)
{
	// Wait for SERCOM synchronization
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set TX/RX pads
	sercom->USART.CTRLA |= rx | tx;
}

void uart_enable(Sercom *sercom)
{
	// Wait for SERCOM synchronization
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set enable bit
	sercom->USART.CTRLA |= SERCOM_USART_CTRLA_ENABLE;
}

void uart_disable(Sercom *sercom)
{
	// Wait for SERCOM synchronization
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Clear enable bit
	sercom->USART.CTRLA &= ~SERCOM_USART_CTRLA_ENABLE;
}

void uart_set_baud(Sercom *sercom, uint16_t baud)
{
	// Wait for SERCOM synchronization
	while (sercom->USART.STATUS & SERCOM_USART_STATUS_SYNCBUSY);
	// Set baud rate
	sercom->USART.BAUD = baud;
}

void uart_apb_enable(uint32_t sercom)
{
	PM.APBCMASK |= PM_APBCMASK_SERCOM0 + sercom;
}

uint8_t uart_read_block(Sercom *sercom)
{
	// Wait for the uart to receive some data
	while (!(sercom->USART.INTFLAG & SERCOM_USART_INTFLAG_RXC));
	// Read byte
	return sercom->USART.DATA;
}

uint8_t uart_read(Sercom *sercom, uint8_t *data)
{
	// If there is no byte to be read, return
	if (!(sercom->USART.INTFLAG & SERCOM_USART_INTFLAG_RXC)) return 0;
	// Otherwise, return the byte read from the usart
	*data = sercom->USART.DATA;

	return 1;
}

int uart_read_buffer_block(Sercom *sercom, uin8_t *buffer, uint32_t length)
{
	uint32_t index = 0;

	for (; length != 0; length--)
	{
		buffer[index++] = uart_read_block(sercom);
	}

	return index;
}

int uart_read_buffer(Sercom *sercom, uint8_t *buffer, uint32_t length)
{
	uint32_t index = 0;

	for (; length != 0; length--)
	{
		// If we didn't read a byte, exit the loop
		if (!uart_read(sercom, &buffer[index])) break;
		// Otherwise, increment index and continue reading
		index++;
	}

	return index;
}

void uart_write(Sercom *sercom, uint8_t data)
{
	// Wait for any bytes that need to be shifted out
	while (!(sercom->USART.INTFLAG & SERCOM_USART_INTFLAG_DRE));
	// Write data
	sercom->USART.DATA = data;
}

int uart_write_buffer(Sercom *sercom, uint8_t *buffer, uint32_t length)
{
	uint32_t index = 0;

	for (; length != 0; length--)
	{
		uart_write(sercom, buffer[index]);
	}

	return index;
}

#endif