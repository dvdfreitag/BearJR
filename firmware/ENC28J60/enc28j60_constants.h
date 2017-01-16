#ifndef _ENC28J60_H_
#define _ENC28J60_H_

// Bank 0				Bank 1				Bank 2				Bank 3
// 0x00 ERDPTL			0x00 EHT0			0x00 MACON1			0x00 MAADR5
// 0x01 ERDPTH			0x01 EHT1			0x01 Reserved		0x01 MAADR6
// 0x02 EWRPTL			0x02 EHT2			0x02 MACON3			0x02 MAADR3
// 0x03 EWRPTH			0x03 EHT3			0x03 MACON4			0x03 MAADR4
// 0x04 ETXSTL			0x04 EHT4			0x04 MABBIPG		0x04 MAADR1
// 0x05 ETXSTH			0x05 EHT5			0x05 —				0x05 MAADR2
// 0x06 ETXNDL			0x06 EHT6			0x06 MAIPGL			0x06 EBSTSD
// 0x07 ETXNDH			0x07 EHT7			0x07 MAIPGH			0x07 EBSTCON
// 0x08 ERXSTL			0x08 EPMM0			0x08 MACLCON1		0x08 EBSTCSL
// 0x09 ERXSTH			0x09 EPMM1			0x09 MACLCON2		0x09 EBSTCSH
// 0x0A ERXNDL			0x0A EPMM2			0x0A MAMXFLL		0x0A MISTAT
// 0x0B ERXNDH			0x0B EPMM3			0x0B MAMXFLH		0x0B —
// 0x0C ERXRDPTL		0x0C EPMM4			0x0C Reserved		0x0C —
// 0x0D ERXRDPTH		0x0D EPMM5			0x0D Reserved		0x0D —
// 0x0E ERXWRPTL		0x0E EPMM6			0x0E Reserved		0x0E —
// 0x0F ERXWRPTH		0x0F EPMM7			0x0F —				0x0F —
// 0x10 EDMASTL			0x10 EPMCSL			0x10 Reserved		0x10 —
// 0x11 EDMASTH			0x11 EPMCSH			0x11 Reserved		0x11 —
// 0x12 EDMANDL			0x12 —				0x12 MICMD			0x12 EREVID
// 0x13 EDMANDH			0x13 —				0x13 —				0x13 —
// 0x14 EDMADSTL		0x14 EPMOL			0x14 MIREGADR		0x14 —
// 0x15 EDMADSTH		0x15 EPMOH			0x15 Reserved		0x15 ECOCON
// 0x16 EDMACSL			0x16 Reserved		0x16 MIWRL			0x16 Reserved
// 0x17 EDMACSH			0x17 Reserved		0x17 MIWRH			0x17 EFLOCON
// 0x18 —				0x18 ERXFCON		0x18 MIRDL			0x18 EPAUSL
// 0x19 —				0x19 EPKTCNT		0x19 MIRDH			0x19 EPAUSH
// 0x1A Reserved		0x1A Reserved		0x1A Reserved		0x1A Reserved
// 0x1B EIE				0x1B EIE			0x1B EIE			0x1B EIE
// 0x1C EIR				0x1C EIR			0x1C EIR			0x1C EIR
// 0x1D ESTAT			0x1D ESTAT			0x1D ESTAT			0x1D ESTAT
// 0x1E ECON2			0x1E ECON2			0x1E ECON2			0x1E ECON2
// 0x1F ECON1			0x1F ECON1			0x1F ECON1			0x1F ECON1

#define BANK_MASK				0x60
#define BANK0					0x00
#define BANK1					0x20
#define BANK2					0x40
#define BANK3					0x60

// Bank 0 addresses
#define ERDPTL_ADDR				((BANK0) | (0x00))
#define ERDPTH_ADDR				((BANK0) | (0x01))
#define EWRPTL_ADDR				((BANK0) | (0x02))
#define EWRPTH_ADDR				((BANK0) | (0x03))
#define ETXSTL_ADDR				((BANK0) | (0x04))
#define ETXSTH_ADDR				((BANK0) | (0x05))
#define ETXNDL_ADDR				((BANK0) | (0x06))
#define ETXNDH_ADDR				((BANK0) | (0x07))
#define ERXSTL_ADDR				((BANK0) | (0x08))
#define ERXSTH_ADDR				((BANK0) | (0x09))
#define ERXNDL_ADDR				((BANK0) | (0x0A))
#define ERXNDH_ADDR				((BANK0) | (0x0B))
#define ERXRDPTL_ADDR			((BANK0) | (0x0C))
#define ERXRDPTH_ADDR			((BANK0) | (0x0D))
#define ERXWRPTL_ADDR			((BANK0) | (0x0E))
#define ERXWRPTH_ADDR			((BANK0) | (0x0F))
#define EDMASTL_ADDR			((BANK0) | (0x10))
#define EDMASTH_ADDR			((BANK0) | (0x11))
#define EDMANDL_ADDR			((BANK0) | (0x12))
#define EDMANDH_ADDR			((BANK0) | (0x13))
#define EDMADSTL_ADDR			((BANK0) | (0x14))
#define EDMADSTH_ADDR			((BANK0) | (0x15))
#define EDMACSL_ADDR			((BANK0) | (0x16))
#define EDMACSH_ADDR			((BANK0) | (0x17))
#define EIE_ADDR				((BANK0) | (0x1B))
#define EIR_ADDR				((BANK0) | (0x1C))
#define ESTAT_ADDR				((BANK0) | (0x1D))
#define ECON2_ADDR				((BANK0) | (0x1E))
#define ECON1_ADDR				((BANK0) | (0x1F))

// Bank 1 addresses
#define EHT0_ADDR				((BANK1) | (0x00))
#define EHT1_ADDR				((BANK1) | (0x01))
#define EHT2_ADDR				((BANK1) | (0x02))
#define EHT3_ADDR				((BANK1) | (0x03))
#define EHT4_ADDR				((BANK1) | (0x04))
#define EHT5_ADDR				((BANK1) | (0x05))
#define EHT6_ADDR				((BANK1) | (0x06))
#define EHT7_ADDR				((BANK1) | (0x07))
#define EPMM0_ADDR				((BANK1) | (0x08))
#define EPMM1_ADDR				((BANK1) | (0x09))
#define EPMM2_ADDR				((BANK1) | (0x0A))
#define EPMM3_ADDR				((BANK1) | (0x0B))
#define EPMM4_ADDR				((BANK1) | (0x0C))
#define EPMM5_ADDR				((BANK1) | (0x0D))
#define EPMM6_ADDR				((BANK1) | (0x0E))
#define EPMM7_ADDR				((BANK1) | (0x0F))
#define EPMCSL_ADDR				((BANK1) | (0x10))
#define EPMCSH_ADDR				((BANK1) | (0x11))
#define EPMOL_ADDR				((BANK1) | (0x14))
#define EPMOH_ADDR				((BANK1) | (0x15))
#define ERXFCON_ADDR			((BANK1) | (0x18))
#define EPKTCNT_ADDR			((BANK1) | (0x19))

// Bank 2 addresses
#define MACON1_ADDR				((BANK2) | (0x00))
#define MACON2_ADDR				((BANK2) | (0x01))
#define MACON3_ADDR				((BANK2) | (0x02))
#define MACON4_ADDR				((BANK2) | (0x03))
#define MABBIPG_ADDR			((BANK2) | (0x04))
#define MAIPGL_ADDR				((BANK2) | (0x06))
#define MAIPGH_ADDR				((BANK2) | (0x07))
#define MACLCON1_ADDR			((BANK2) | (0x08))
#define MACLCON2_ADDR			((BANK2) | (0x09))
#define MAMXFLL_ADDR			((BANK2) | (0x0A))
#define MAMXFLH_ADDR			((BANK2) | (0x0B))
#define MICMD_ADDR				((BANK2) | (0x12))
#define MIREGADR_ADDR			((BANK2) | (0x14))
#define MIWRL_ADDR				((BANK2) | (0x16))
#define MIWRH_ADDR				((BANK2) | (0x17))
#define MIRDL_ADDR				((BANK2) | (0x18))
#define MIRDH_ADDR				((BANK2) | (0x19))

// Bank 3 addresses
#define MAADR4_ADDR				((BANK3) | (0x00))
#define MAADR5_ADDR				((BANK3) | (0x01))
#define MAADR2_ADDR				((BANK3) | (0x02))
#define MAADR3_ADDR				((BANK3) | (0x03))
#define MAADR0_ADDR				((BANK3) | (0x04))
#define MAADR1_ADDR				((BANK3) | (0x05))
#define EBSTSD_ADDR				((BANK3) | (0x06))
#define EBSTCON_ADDR			((BANK3) | (0x07))
#define EBSTCSL_ADDR			((BANK3) | (0x08))
#define EBSTCSH_ADDR			((BANK3) | (0x09))
#define MISTAT_ADDR				((BANK3) | (0x0A))
#define EREVID_ADDR				((BANK3) | (0x12))
#define ECOCON_ADDR				((BANK3) | (0x15))
#define EFLOCON_ADDR			((BANK3) | (0x17))
#define EPAUSL_ADDR				((BANK3) | (0x18))
#define EPAUSH_ADDR				((BANK3) | (0x19))

// Control register reset values
#define EIE_RESET_VAL			0x00	// INTIE PKTIE DMAIE LINKIE TXIE r TXERIE RXERIE
#define EIR_RESET_VAL			0x00	// PKTIF DMAIF LINKIF TXIF r TXERIF RXERIF
#define ESTAT_RESET_VAL			0x00	// INT BUFER r LATECOL RXBUSY TXABRT CLKRDY(1)
#define ECON2_RESET_VAL			0x80	// AUTOINC PKTDEC PWRSV r VRPS —
#define ECON1_RESET_VAL			0x00	// TXRST RXRST DMAST CSUMEN TXRTS RXEN BSEL1 BSEL0
#define ERDPTL_RESET_VAL		0xFA	// Read Pointer Low Byte ERDPT<7:0>)
#define ERDPTH_RESET_VAL		0x05	// Read Pointer High Byte (ERDPT<12:8>)
#define EWRPTL_RESET_VAL		0x00	// Write Pointer Low Byte (EWRPT<7:0>)
#define EWRPTH_RESET_VAL		0x00	// Write Pointer High Byte (EWRPT<12:8>)
#define ETXSTL_RESET_VAL		0x00	// TX Start Low Byte (ETXST<7:0>)
#define ETXSTH_RESET_VAL		0x00	// TX Start High Byte (ETXST<12:8>)
#define ETXNDL_RESET_VAL		0x00	// TX End Low Byte (ETXND<7:0>)
#define ETXNDH_RESET_VAL		0x00	// TX End High Byte (ETXND<12:8>)
#define ERXSTL_RESET_VAL		0xFA	// RX Start Low Byte (ERXST<7:0>)
#define ERXSTH_RESET_VAL		0x05	// RX Start High Byte (ERXST<12:8>)
#define ERXNDL_RESET_VAL		0xFF	// RX End Low Byte (ERXND<7:0>)
#define ERXNDH_RESET_VAL		0x1F	// RX End High Byte (ERXND<12:8>)
#define ERXRDPTL_RESET_VAL		0xFA	// RX RD Pointer Low Byte (ERXRDPT<7:0>)
#define ERXRDPTH_RESET_VAL		0x05	// RX RD Pointer High Byte (ERXRDPT<12:8>)
#define ERXWRPTL_RESET_VAL		0x00	// RX WR Pointer Low Byte (ERXWRPT<7:0>)
#define ERXWRPTH_RESET_VAL		0x00	// RX WR Pointer High Byte (ERXWRPT<12:8>)
#define EDMASTL_RESET_VAL		0x00	// DMA Start Low Byte (EDMAST<7:0>)
#define EDMASTH_RESET_VAL		0x00	// DMA Start High Byte (EDMAST<12:8>)
#define EDMANDL_RESET_VAL		0x00	// DMA End Low Byte (EDMAND<7:0>)
#define EDMANDH_RESET_VAL		0x00	// DMA End High Byte (EDMAND<12:8>)
#define EDMADSTL_RESET_VAL		0x00	// DMA Destination Low Byte (EDMADST<7:0>)
#define EDMADSTH_RESET_VAL		0x00	// DMA Destination High Byte (EDMADST<12:8>)
#define EDMACSL_RESET_VAL		0x00	// DMA Checksum Low Byte (EDMACS<7:0>)
#define EDMACSH_RESET_VAL		0x00	// DMA Checksum High Byte (EDMACS<15:8>)
#define EHT0_RESET_VAL			0x00	// Hash Table Byte 0 (EHT<7:0>)
#define EHT1_RESET_VAL			0x00	// Hash Table Byte 1 (EHT<15:8>)
#define EHT2_RESET_VAL			0x00	// Hash Table Byte 2 (EHT<23:16>)
#define EHT3_RESET_VAL			0x00	// Hash Table Byte 3 (EHT<31:24>)
#define EHT4_RESET_VAL			0x00	// Hash Table Byte 4 (EHT<39:32>)
#define EHT5_RESET_VAL			0x00	// Hash Table Byte 5 (EHT<47:40>)
#define EHT6_RESET_VAL			0x00	// Hash Table Byte 6 (EHT<55:48>)
#define EHT7_RESET_VAL			0x00	// Hash Table Byte 7 (EHT<63:56>)
#define EPMM0_RESET_VAL			0x00	// Pattern Match Mask Byte 0 (EPMM<7:0>)
#define EPMM1_RESET_VAL			0x00	// Pattern Match Mask Byte 1 (EPMM<15:8>)
#define EPMM2_RESET_VAL			0x00	// Pattern Match Mask Byte 2 (EPMM<23:16>)
#define EPMM3_RESET_VAL			0x00	// Pattern Match Mask Byte 3 (EPMM<31:24>)
#define EPMM4_RESET_VAL			0x00	// Pattern Match Mask Byte 4 (EPMM<39:32>)
#define EPMM5_RESET_VAL			0x00	// Pattern Match Mask Byte 5 (EPMM<47:40>)
#define EPMM6_RESET_VAL			0x00	// Pattern Match Mask Byte 6 (EPMM<55:48>)
#define EPMM7_RESET_VAL			0x00	// Pattern Match Mask Byte 7 (EPMM<63:56>)
#define EPMCSL_RESET_VAL		0x00	// Pattern Match Checksum Low Byte (EPMCS<7:0>)
#define EPMCSH_RESET_VAL		0x00	// Pattern Match Checksum High Byte (EPMCS<15:0>)
#define EPMOL_RESET_VAL			0x00	// Pattern Match Offset Low Byte (EPMO<7:0>)
#define EPMOH_RESET_VAL			0x00	// Pattern Match Offset High Byte (EPMO<12:8>)
#define ERXFCON_RESET_VAL		0xA1	// UCEN ANDOR CRCEN PMEN MPEN HTEN MCEN BCEN
#define EPKTCNT_RESET_VAL		0x00	// Ethernet Packet Count
#define MACON1_RESET_VAL		0x00	// r TXPAUS RXPAUS PASSALL MARXEN
#define MACON3_RESET_VAL		0x00	// PADCFG2 PADCFG1 PADCFG0 TXCRCEN PHDREN HFRMEN FRMLNEN FULDPX
#define MACON4_RESET_VAL		0x00	// DEFER BPEN NOBKOFF r r
#define MABBIPG_RESET_VAL		0x00	// Back-to-Back Inter-Packet Gap (BBIPG<6:0>)
#define MAIPGL_RESET_VAL		0x00	// Non-Back-to-Back Inter-Packet Gap Low Byte (MAIPGL<6:0>)
#define MAIPGH_RESET_VAL		0x00	// Non-Back-to-Back Inter-Packet Gap High Byte (MAIPGH<6:0>)
#define MACLCON1_RESET_VAL		0x0F	// Retransmission Maximum (RETMAX<3:0>)
#define MACLCON2_RESET_VAL		0x37	// Collision Window (COLWIN<5:0>)
#define MAMXFLL_RESET_VAL		0x00	// Maximum Frame Length Low Byte (MAMXFL<7:0>)
#define MAMXFLH_RESET_VAL		0x06	// Maximum Frame Length High Byte (MAMXFL<15:8>)
#define MICMD_RESET_VAL			0x00	// MIISCAN MIIRD
#define MIREGADR_RESET_VAL		0x00	// MII Register Address (MIREGADR<4:0>)
#define MIWRL_RESET_VAL			0x00	// MII Write Data Low Byte (MIWR<7:0>)
#define MIWRH_RESET_VAL			0x00	// MII Write Data High Byte (MIWR<15:8>)
#define MIRDL_RESET_VAL			0x00	// MII Read Data Low Byte (MIRD<7:0>)
#define MIRDH_RESET_VAL			0x00	// MII Read Data High Byte(MIRD<15:8>)
#define MAADR5_RESET_VAL		0x00	// MAC Address Byte 5 (MAADR<15:8>)
#define MAADR6_RESET_VAL		0x00	// MAC Address Byte 6 (MAADR<7:0>)
#define MAADR3_RESET_VAL		0x00	// MAC Address Byte 3 (MAADR<31:24>), OUI Byte 3
#define MAADR4_RESET_VAL		0x00	// MAC Address Byte 4 (MAADR<23:16>)
#define MAADR1_RESET_VAL		0x00	// MAC Address Byte 1 (MAADR<47:40>), OUI Byte 1
#define MAADR2_RESET_VAL		0x00	// MAC Address Byte 2 (MAADR<39:32>), OUI Byte 2
#define EBSTSD_RESET_VAL		0x00	// Built-in Self-Test Fill Seed (EBSTSD<7:0>)
#define EBSTCON_RESET_VAL		0x00	// PSV2 PSV1 PSV0 PSEL TMSEL1 TMSEL0 TME BISTST
#define EBSTCSL_RESET_VAL		0x00	// Built-in Self-Test Checksum Low Byte (EBSTCS<7:0>)
#define EBSTCSH_RESET_VAL		0x00	// Built-in Self-Test Checksum High Byte (EBSTCS<15:8>)
#define MISTAT_RESET_VAL		0x00	// r NVALID SCAN BUSY
#define ECOCON_RESET_VAL		0x04	// COCON2 COCON1 COCON0
#define EFLOCON_RESET_VAL		0x00	// FULDPXS FCEN1 FCEN0
#define EPAUSL_RESET_VAL		0x00	// Pause Timer Value Low Byte (EPAUS<7:0>)
#define EPAUSH_RESET_VAL		0x10	// Pause Timer Value High Byte (EPAUS<15:8>)

// SPI Instruction set opcodes
#define OPCODE_RCR				0x00	// Read Control Register
#define OPCODE_RBM				0x3A	// Read Buffer Memory
#define OPCODE_WCR				0x40	// Write Control Register
#define OPCODE_WBM				0x7A	// Write Buffer Memory
#define OPCODE_BFS				0x80	// Bit-Field Set
#define OPCODE_BFC				0xA0	// Bit-Field Clear
#define OPCODE_SRC				0xFF	// System Reset Command

#define OPCODE_ADDR_MSK 		0x1F	// Opcode address mask

// ENC28J60 ERXFCON Register Bit Definitions
#define ERXFCON_UCEN			0x80
#define ERXFCON_ANDOR			0x40
#define ERXFCON_CRCEN			0x20
#define ERXFCON_PMEN			0x10
#define ERXFCON_MPEN			0x08
#define ERXFCON_HTEN			0x04
#define ERXFCON_MCEN			0x02
#define ERXFCON_BCEN			0x01
// ENC28J60 EIE Register Bit Definitions
#define EIE_INTIE				0x80
#define EIE_PKTIE				0x40
#define EIE_DMAIE				0x20
#define EIE_LINKIE				0x10
#define EIE_TXIE				0x08
#define EIE_WOLIE				0x04
#define EIE_TXERIE				0x02
#define EIE_RXERIE				0x01
// ENC28J60 EIR Register Bit Definitions
#define EIR_PKTIF				0x40
#define EIR_DMAIF				0x20
#define EIR_LINKIF				0x10
#define EIR_TXIF				0x08
#define EIR_WOLIF				0x04
#define EIR_TXERIF				0x02
#define EIR_RXERIF				0x01
// ENC28J60 ESTAT Register Bit Definitions
#define ESTAT_INT				0x80
#define ESTAT_LATECOL			0x10
#define ESTAT_RXBUSY			0x04
#define ESTAT_TXABRT			0x02
#define ESTAT_CLKRDY			0x01
// ENC28J60 ECON2 Register Bit Definitions
#define ECON2_AUTOINC			0x80
#define ECON2_PKTDEC			0x40
#define ECON2_PWRSV				0x20
#define ECON2_VRPS				0x08
// ENC28J60 ECON1 Register Bit Definitions
#define ECON1_TXRST				0x80
#define ECON1_RXRST				0x40
#define ECON1_DMAST				0x20
#define ECON1_CSUMEN			0x10
#define ECON1_TXRTS				0x08
#define ECON1_RXEN				0x04
#define ECON1_BSEL1				0x02
#define ECON1_BSEL0				0x01
// ENC28J60 MACON1 Register Bit Definitions
#define MACON1_LOOPBK			0x10
#define MACON1_TXPAUS			0x08
#define MACON1_RXPAUS			0x04
#define MACON1_PASSALL			0x02
#define MACON1_MARXEN			0x01
// ENC28J60 MACON2 Register Bit Definitions
#define MACON2_MARST			0x80
#define MACON2_RNDRST			0x40
#define MACON2_MARXRST			0x08
#define MACON2_RFUNRST			0x04
#define MACON2_MATXRST			0x02
#define MACON2_TFUNRST			0x01
// ENC28J60 MACON3 Register Bit Definitions
#define MACON3_PADCFG2			0x80
#define MACON3_PADCFG1			0x40
#define MACON3_PADCFG0			0x20
#define MACON3_TXCRCEN			0x10
#define MACON3_PHDRLEN			0x08
#define MACON3_HFRMLEN			0x04
#define MACON3_FRMLNEN			0x02
#define MACON3_FULDPX			0x01
// ENC28J60 MICMD Register Bit Definitions
#define MICMD_MIISCAN			0x02
#define MICMD_MIIRD				0x01
// ENC28J60 MISTAT Register Bit Definitions
#define MISTAT_NVALID			0x04
#define MISTAT_SCAN				0x02
#define MISTAT_BUSY				0x01

// ENC28J60 EBSTCON Register Bit Definitions
#define EBSTCON_PSV2			0x80
#define EBSTCON_PSV1			0x40
#define EBSTCON_PSV0			0x20
#define EBSTCON_PSEL			0x10
#define EBSTCON_TMSEL1			0x08
#define EBSTCON_TMSEL0			0x04
#define EBSTCON_TMSEL_PATTERN	EBSTCON_TMSEL1
#define EBSTCON_TMSEL_ADDRESS	EBSTCON_TMSEL0
#define EBSTCON_TMSEL_RANDOM	0x00
#define EBSTCON_TME				0x02
#define EBSTCON_BISTST			0x01

// PHY registers
#define PHCON1_ADDR				0x00
#define PHSTAT1_ADDR			0x01
#define PHHID1_ADDR				0x02
#define PHHID2_ADDR				0x03
#define PHCON2_ADDR				0x10
#define PHSTAT2_ADDR			0x11
#define PHIE_ADDR				0x12
#define PHIR_ADDR				0x13
#define PHLCON_ADDR				0x14

// ENC28J60 PHY PHCON1 Register Bit Definitions
#define PHCON1_PRST				0x8000
#define PHCON1_PLOOPBK			0x4000
#define PHCON1_PPWRSV			0x0800
#define PHCON1_PDPXMD			0x0100
// ENC28J60 PHY PHSTAT1 Register Bit Definitions
#define PHSTAT1_PFDPX			0x1000
#define PHSTAT1_PHDPX			0x0800
#define PHSTAT1_LLSTAT			0x0004
#define PHSTAT1_JBSTAT			0x0002
// ENC28J60 PHY PHSTAT2 Register Bit Definitions
#define PHSTAT2_TXSTAT			0x2000
#define PHSTAT2_RXSTAT			0x1000
#define PHSTAT2_COLSTAT			0x0800
#define PHSTAT2_LSTAT			0x0400
#define PHSTAT2_DPXSTAT			0x0200
#define PHSTAT2_PLRITY			0x0020
// ENC28J60 PHY PHCON2 Register Bit Definitions
#define PHCON2_FRCLINK			0x4000
#define PHCON2_TXDIS			0x2000
#define PHCON2_JABBER			0x0400
#define PHCON2_HDLDIS			0x0100

// ENC28J60 Packet Control Byte Bit Definitions
#define PKTCTRL_PHUGEEN			0x08
#define PKTCTRL_PPADEN			0x04
#define PKTCTRL_PCRCEN			0x02
#define PKTCTRL_POVERRIDE		0x01

#endif
