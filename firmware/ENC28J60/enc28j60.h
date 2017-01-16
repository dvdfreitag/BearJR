#ifndef _SAMD20E18_ENC28J60_H_
#define _SAMD20E18_ENC28J60_H_

#include "samd20e18.h"
#include "enc28j60_constants.h"

/* ENC28J60 Silicon errata B7 #2:
 *
 * Module: Memory (Ethernet Buffer)
 *   The receive hardware maintains an internal Write Pointer which defines the 
 *   area in the receive buffer where bytes arriving over the Ethernet are 
 *   written. This internal Write Pointer should be updated with the value 
 *   stored in ERXST whenever the Receive Buffer Start Pointer, ERXST, or the 
 *   Receive Buffer End Pointer, ERXND, is written to by the host 
 *   microcontroller. Sometimes, when ERXST or ERXND is written to, the exact 
 *   value, 0000h, is stored in the internal receive Write Pointer instead of 
 *   the ERXST address.
 *
 * Work around:
 *   Use the lower segment of the buffer memory for the receive buffer, starting
 *   at address 0000h. For example, use the range (0000h to n) for the receive 
 *   buffer and ((n + 1) to 8191) for the transmit buffer.
 */

#define ENC28J60_RXSTART 	0x0000
#define ENC28J60_RXEND		0x19FF // 6656 Bytes, enough for 4 full packets + 0.5kB
#define ENC28J60_TXSTART 	0x1A00 
#define ENC28J60_TXEND		0x2000 // 1536 Bytes, enough for 1 full packet
#define ENC28J60_TXLEN		(ENC28J60_TXEND - ENC28J60_TXSTART)

#define ENC28J60_MAXFRAME	1500 // Maximum ethernet frame length in bytes
// ENC28J60 silicon revisions
#define ENC28J60_EREVID_B1 0x02
#define ENC28J60_EREVID_B4 0x04
#define ENC28J60_EREVID_B5 0x05
#define ENC28J60_EREVID_B7 0x06

static uint8_t CurrentBank = 0;

static void cs_clear(void)
{
	PORTA.OUTCLR = PORT_PA18;
}

static void cs_set(void)
{
	PORTA.OUTSET = PORT_PA18;	
}

static void set_bank(uint8_t address)
{
	uint8_t bank = address & BANK_MASK;

	if (bank != CurrentBank)
	{
		cs_clear();
		
		spi_write(&SERCOM1, OPCODE_BFC | ECON1_ADDR);
		spi_write(&SERCOM1, ECON1_BSEL1 | ECON1_BSEL0);

		spi_write(&SERCOM1, OPCODE_BFS | ECON1_ADDR);
		spi_write(&SERCOM1, bank >> 5);
		
		cs_set();

		CurrentBank = bank;
	}
}

static uint8_t read(uint8_t address)
{
	uint8_t temp = address & OPCODE_ADDR_MSK;
	if (temp < EIE_ADDR) set_bank(address);

	uint8_t retval = 0;

	cs_clear();
	spi_write(&SERCOM1, temp);
	spi_read(&SERCOM1, &retval);
	cs_set();

	return retval;
}

static uint16_t read_pair(uint8_t address)
{
	uint8_t temp = address & OPCODE_ADDR_MSK;
	if (temp < EIE_ADDR) set_bank(address);
	uint16_t retval = 0;

	cs_clear();
	spi_write(&SERCOM1, temp);
	spi_read(&SERCOM1, &(((uint8_t *)&retval)[0]));
	spi_write(&SERCOM1, temp + 1);
	spi_read(&SERCOM1, &(((uint8_t *)&retval)[1]));
	cs_set();

	return retval;
}

static void write(uint8_t opcode, uint8_t address, uint8_t data)
{
	uint8_t temp = address & OPCODE_ADDR_MSK;
	if (temp < EIE_ADDR) set_bank(address);

	cs_clear();
	spi_write(&SERCOM1, opcode | temp);
	spi_write(&SERCOM1, data);
	cs_set();
}

static uint16_t read_phy(uint8_t address)
{
	write(OPCODE_WCR, MIREGADR_ADDR, address);
	write(OPCODE_WCR, MICMD_ADDR, MICMD_MIIRD);

	while (read(MISTAT_ADDR) & MISTAT_BUSY);

	write(OPCODE_WCR, MICMD_ADDR, 0x00);
	return read_pair(MIRDL_ADDR);
}

static void write_pair(uint8_t opcode, uint8_t address, uint16_t data)
{
	uint8_t temp = address & OPCODE_ADDR_MSK;
	if (temp < EIE_ADDR) set_bank(address);

	cs_clear();
	spi_write(&SERCOM1, opcode | temp);
	spi_write(&SERCOM1, ((uint8_t *)&data)[0]);
	spi_write(&SERCOM1, temp + 1);
	spi_write(&SERCOM1, ((uint8_t *)&data)[1]);
	cs_set();
}

static void write_phy(uint8_t address, uint16_t data)
{
	write(OPCODE_WCR, MIREGADR_ADDR, address);
	write_pair(OPCODE_WCR, MIWRL_ADDR, data);

	while (read(MISTAT_ADDR) & MISTAT_BUSY);
}

void enc28j60_reset(void)
{
	/* ENC28J60 Silicon errata B7 #2:
	 *
	 * Module: Reset
	 *   After sending an SPI Reset command, the PHY clock is stopped but the 
	 *   ESTAT.CLKRDY bit is not cleared. Therefore, polling the CLKRDY bit 
	 *   will not work to detect if the PHY is ready. Additionally, the 
	 *   hardware start-up time of 300us may expire before the device is 
	 *   ready to operate.
	 *
	 * Work around:
	 *   After issuing the Reset command, wait at least 1 ms in firmware for 
	 *   the device to be ready
	 */

	cs_clear();
	spi_write(&SERCOM1, OPCODE_SRC);
	spi_write(&SERCOM1, OPCODE_SRC);
	cs_set();

	uint32_t start = millis;
	while ((millis - start) < 1UL);

	while (!(read(ESTAT_ADDR) & ESTAT_CLKRDY));
}

void enc28j60_set_mac(uint8_t octet, uint8_t value)
{
	switch (octet)
	{
		case 0:
			write(OPCODE_WCR, MAADR0_ADDR, value);
			break;
		case 1:
			write(OPCODE_WCR, MAADR1_ADDR, value);
			break;
		case 2:
			write(OPCODE_WCR, MAADR2_ADDR, value);
			break;
		case 3:
			write(OPCODE_WCR, MAADR3_ADDR, value);
			break;
		case 4:
			write(OPCODE_WCR, MAADR4_ADDR, value);
			break;
		case 5:
			write(OPCODE_WCR, MAADR5_ADDR, value);
			break;
	}
}

uint8_t enc28j60_init(void)
{
	// Trigger a software-reset
	enc28j60_reset();

	// Set Ethernet Receive addresses
	write_pair(OPCODE_WCR, ERXSTL_ADDR, ENC28J60_RXSTART);
	write_pair(OPCODE_WCR, ERXRDPTL_ADDR, ENC28J60_RXSTART);
	write_pair(OPCODE_WCR, ERXNDL_ADDR, ENC28J60_RXEND);
	// Set Ethernet Transmit addresses
	write_pair(OPCODE_WCR, ETXSTL_ADDR, ENC28J60_TXSTART);
	write_pair(OPCODE_WCR, ETXNDL_ADDR, ENC28J60_TXEND);
	// Configure Ethernet Receive Filter Control register
	write(OPCODE_WCR, ERXFCON_ADDR, ERXFCON_UCEN | ERXFCON_CRCEN | ERXFCON_PMEN | ERXFCON_BCEN);
	// Configure Ethernet Pattern Matching
	write_pair(OPCODE_WCR, EPMM0_ADDR, 0x0303);
	write_pair(OPCODE_WCR, EPMCSL_ADDR, 0xF7F9);
	
	// Configure MAC
	write(OPCODE_WCR, MACON1_ADDR, MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS);
	write(OPCODE_BFS, MACON3_ADDR, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
	// Configure maximum frame length
	write_pair(OPCODE_WCR, MAMXFLL_ADDR, ENC28J60_MAXFRAME);
	// Configure inter-packet gaps
	write(OPCODE_WCR, MABBIPG_ADDR, 0x12);
	write_pair(OPCODE_WCR, MAIPGL_ADDR, 0x0C12);

	// Configure PHY
	write_phy(PHCON2_ADDR, PHCON2_HDLDIS);

	// Read silicon revision and return it
	return read(EREVID_ADDR);
}

void enc28j60_enable(void)
{
	// Enable ethernet interrupts
	write(OPCODE_BFS, EIE_ADDR, EIE_INTIE | EIE_PKTIE);
	// Enable Ethernet receiver
	write(OPCODE_BFS, ECON1_ADDR, ECON1_RXEN);
}

uint8_t enc28j60_link_status(void)
{
	return (read_phy(PHSTAT2_ADDR) & PHSTAT2_LSTAT) != 0;
}

uint8_t enc28j60_selftest(void)
{
	enc28j60_reset();
	// Set start to 0	
	write_pair(OPCODE_WCR, EDMASTL_ADDR, 0x0000);
	// Set end to 8191
	write_pair(OPCODE_WCR, EDMANDL_ADDR, 0x1FFF);
	write_pair(OPCODE_WCR, ERXNDL_ADDR, 0x1FFF);

	// Enable test mode, configure address fill
	write(OPCODE_WCR, EBSTCON_ADDR, EBSTCON_TME | EBSTCON_BISTST | EBSTCON_TMSEL_ADDRESS);
	// Wait for BISTST to be reset
	while (read(EBSTCON_ADDR) & EBSTCON_BISTST);
	// Clear TME bit
	write(OPCODE_BFC, EBSTCON_ADDR, EBSTCON_TME);
	// Configure DMA with checksum generation
	write(OPCODE_WCR, ECON1_ADDR, ECON1_DMAST | ECON1_CSUMEN);
	// Wait for DMAST to be reset
	while (read(ECON1_ADDR) & ECON1_DMAST);
	// Read the checksum computed by the Ethernet DMA
	uint16_t dma_checksum = read_pair(EDMACSL_ADDR);
	// Read the checksum computed by the SelfTest
	uint16_t test_checksum = read_pair(EBSTCSL_ADDR);
	// Return on failed test
	if (dma_checksum != test_checksum) return 0;
	// Clear test bit
	write(OPCODE_BFC, EBSTCON_ADDR, EBSTCON_TME);

	// Set BIST seed value
	write(OPCODE_WCR, EBSTSD_ADDR, 0xAA);
	// Enable test mode, configure random fill mode with alternating DMA/BIST ports
	write(OPCODE_WCR, EBSTCON_ADDR, EBSTCON_TME | EBSTCON_PSEL | EBSTCON_TMSEL_RANDOM);
	// Wait for BISTST to be reset
	while (read(EBSTCON_ADDR) & EBSTCON_BISTST);
	// Clear TME bit
	write(OPCODE_BFC, EBSTCON_ADDR, EBSTCON_TME);
	// Configure DMA with checksum generation
	write(OPCODE_WCR, ECON1_ADDR, ECON1_DMAST | ECON1_CSUMEN);
	// Wait for DMAST to be reset
	while (read(ECON1_ADDR) & ECON1_DMAST);
	// Read the checksum computed by the Ethernet DMA
	dma_checksum = read_pair(EDMACSL_ADDR);
	// Read the checksum computed by the SelfTest
	test_checksum = read_pair(EBSTCSL_ADDR);
	return dma_checksum == test_checksum;
}

void enc28j60_sleep(void)
{
	// Disable receiver
	write(OPCODE_BFC, ECON1_ADDR, ECON1_RXEN);
	// Finish transmitting / receiving all data
	while (read(ESTAT_ADDR) & ESTAT_RXBUSY);
	while (read(ECON1_ADDR) & ECON1_TXRTS);
	// Configure internal voltage regulator to enter power save mode
	write(OPCODE_BFS, ECON2_ADDR, ECON2_PWRSV | ECON2_VRPS);
}

void enc28j60_wake(void)
{
	// Clear power save bit
	write(OPCODE_BFC, ECON2_ADDR, ECON2_PWRSV);
	// Wait for the chip to be ready
	while (!(read(ESTAT_ADDR) & ESTAT_CLKRDY));
	// Enable receiver
	write(OPCODE_BFS, ECON1_ADDR, ECON1_RXEN);
}

uint8_t enc28j60_packets_available(void)
{
	return read(EPKTCNT_ADDR);
}

void enc28j60_packet_decrement(void)
{
	write(OPCODE_BFS, ECON2_ADDR, ECON2_PKTDEC);
}

void enc28j60_read_position(uint16_t address)
{
	write_pair(OPCODE_WCR, ERXRDPTL_ADDR, address);
}

void enc28j60_read_buffer(uint16_t length, uint8_t *data)
{
	cs_clear();
	spi_write(&SERCOM1, OPCODE_RBM);
	spi_read_buffer(&SERCOM1, data, (uint32_t)length);
	cs_set();
}

void enc28j60_write_position(uint16_t address, uint16_t length)
{
	write_pair(OPCODE_WCR, EWRPTL_ADDR, address);
	write_pair(OPCODE_WCR, ETXNDL_ADDR, address + length);
}

void enc28j60_write_buffer(uint16_t length, uint8_t *data)
{
	cs_clear();
	spi_write(&SERCOM1, OPCODE_WBM);
	spi_write_buffer(&SERCOM1, data, (uint32_t)length);
	cs_set();
}

uint8_t enc28j60_packet_send(uint16_t length, uint8_t *data)
{
	uint8_t retry_count = 0;

	// Initialize Ethernet transmitter addresses
	write_pair(OPCODE_WCR, EWRPTL_ADDR, ENC28J60_TXSTART);
	write_pair(OPCODE_WCR, ETXNDL_ADDR, ENC28J60_TXSTART + length);
	// Write packet data
	write(OPCODE_WBM, 0, 0x00);
	enc28j60_write_buffer(length, data);

	while (1)
	{
		/* ENC28J60 Silicon errata B7 #12:
		 *
		 * Module: Transmit Logic
		 *   In Half-Duplex mode, a hardware transmission abort caused by 
		 *   excessive collisions, a late collision or excessive deferrals, 
		 *   may stall the internal transmit logic. The next packet transmit 
		 *   initiated by the host controller may never succeed (ECON1.TXRTS 
		 *   will remain set indefinitely). 
		 *
		 * Work around:
		 *   Before attempting to transmit a packet (setting ECON1.TXRTS), reset 
		 *   the internal transmit logic by setting ECON1.TXRST and then clearing
		 *   ECON1.TXRST. The host controller may wish to issue this Reset before 
		 *   any packet is transmitted (for simplicity), or it may wish to 
		 *   conditionally reset the internal transmit logic based on the Transmit
		 *   Error Interrupt Flag (EIR.TXERIF), which will become set whenever a 
		 *   transmit abort occurs. Clearing ECON1.TXRST may cause a new transmit
		 *   error interrupt event (EIR.TXERIF will become set). Therefore, the 
		 *   interrupt flag should be cleared after the Reset is completed.
		 */

		// Reset Ethernet transmitter
		write(OPCODE_BFS, ECON1_ADDR, ECON1_TXRST);
		write(OPCODE_BFC, ECON1_ADDR, ECON1_TXRST);
		write(OPCODE_BFC, EIR_ADDR, EIR_TXERIF | EIR_TXIF);
		// Initiate transmission
		write(OPCODE_BFS, ECON1_ADDR, ECON1_TXRTS);

		/* ENC28J60 Silicon errata B7 #13:
		 *
		 * Module: PHY
		 *   When transmitting in Half-Duplex mode with some link partners, the 
		 *   PHY will sometimes incorrectly interpret a received link pulse as a 
		 *   collision event. If less than, or equal to, MACLCON2 bytes have been 
		 *   transmitted when the false collision occurs, the MAC will abort the 
		 *   current transmission, wait a random back-off delay and then 
		 *   automatically attempt to retransmit the packet from the beginning, 
		 *   as it would for a genuine collision. If greater than MACLCON2 bytes 
		 *   have been transmitted when the false collision occurs, the event 
		 *   will be considered a late collision by the MAC and the packet will 
		 *   be aborted without retrying. This causes the packet to not be 
		 *   delivered to the remote node. In some cases, the abort will fail to 
		 *   reset the transmit state machine.
		 *
		 * Work around:
		 *   Implement a software retransmit mechanism whenever a late 
		 *   collision occurs. When a late collision occurs, the associated bit 
		 *   in the transmit status vector will be set. Also, the EIR.TXERIF bit 
		 *   will become set, and if enabled, the transmit error interrupt will 
		 *   occur. If the transmit state machine does not get reset, the 
		 *   ECON1.TXRTS bit will remain set and no transmit interrupt will 
		 *   occur (the EIR.TXIF bit will remain clear).
		 *
		 *   As a result, software should detect the completion of a transmit 
		 *   attempt by checking both TXIF and TXERIF. If the Transmit Interrupt 
		 *   (TXIF) did not occur, software must clear the ECON1.TXRTS bit to 
		 *   force the transmit state machine into the correct state.
		 */

		uint16_t count = 0;
		while ((read(EIR_ADDR) & EIR_TXERIF) && (++count < 1000U));
		// If TXERIF is clear and we did not exceed our counter, we succeeded
		if (!(read(EIR_ADDR) & EIR_TXERIF) && count < 1000U) return 1;
		// Otherwise, we're stuck and need to retry
		write(OPCODE_BFC, ECON1_ADDR, ECON1_TXRTS);

		// Check the transmit status vector
		uint16_t etxnd = read_pair(ETXNDL_ADDR);
		// LATECOL is bit 5 in TSV[3]
		write_pair(OPCODE_WCR, ERDPTL_ADDR, etxnd + 4);

		uint8_t data = 0;

		cs_clear();
		spi_write(&SERCOM1, OPCODE_RBM);
		spi_read(&SERCOM1, &data);
		cs_set();

		/* If TXERIF is not set and LATECOL is set in the TSV, we truly have a 
		 *   late collision. If we're not out of retries, try again. Otherwise 
		 *   something else is wrong.
		 */
		if ((!(read(EIR_ADDR) & EIR_TXERIF) && (data & 0x20)) || (retry_count > 16U)) return 0;

		retry_count++;
	}

	// Should never happen, this is here to satiate the compiler.
	return 0;
}

#endif
