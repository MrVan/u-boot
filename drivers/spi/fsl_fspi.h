/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2019 NXP
 *
 * Register definitions for NXP FLEXSPI
 */

#ifndef _FSL_FSPI_H_
#define _FSL_FSPI_H_

#include <linux/bitops.h>

struct fsl_fspi_regs {
	u32 mcr0;
	u32 mcr1;
	u32 mcr2;
	u32 ahbcr;
	u32 inten;
	u32 intr;
	u32 lutkey;
	u32 lutcr;
	u32 ahbrxbuf0cr0;
	u32 ahbrxbuf1cr0;
	u32 ahbrxbuf2cr0;
	u32 ahbrxbuf3cr0;
	u32 ahbrxbuf4cr0;
	u32 ahbrxbuf5cr0;
	u32 ahbrxbuf6cr0;
	u32 ahbrxbuf7cr0;
	u32 ahbrxbuf0cr1;
	u32 ahbrxbuf1cr1;
	u32 ahbrxbuf2cr1;
	u32 ahbrxbuf3cr1;
	u32 ahbrxbuf4cr1;
	u32 ahbrxbuf5cr1;
	u32 ahbrxbuf6cr1;
	u32 ahbrxbuf7cr1;
	u32 flsha1cr0;
	u32 flsha2cr0;
	u32 flshb1cr0;
	u32 flshb2cr0;
	u32 flsha1cr1;
	u32 flsha2cr1;
	u32 flshb1cr1;
	u32 flshb2cr1;
	u32 flsha1cr2;
	u32 flsha2cr2;
	u32 flshb1cr2;
	u32 flshb2cr2;
	u32 flshcr3;
	u32 flshcr4;
	u32 flshcr5;
	u32 flshcr6;
	u32 ipcr0;
	u32 ipcr1;
	u32 ipcr2;
	u32 ipcr3;
	u32 ipcmd;
	u32 dlpr;
	u32 iprxfcr;
	u32 iptxfcr;
	u32 dllacr;
	u32 dllbcr;
	u32 soccr;
	u32 misccr2;
	u32 misccr3;
	u32 misccr4;
	u32 misccr5;
	u32 misccr6;
	u32 sts0;
	u32 sts1;
	u32 sts2;
	u32 ahbspndsts;
	u32 iprxfsts;
	u32 iptxfsts;
	u32 rsvd[2];
	u32 rfdr[32];
	u32 tfdr[32];
	u32 lut[128];
};

/* The registers */
#define FLEXSPI_MCR0_MDIS_SHIFT		1
#define FLEXSPI_MCR0_MDIS_MASK		BIT(1)
#define FLEXSPI_MCR0_SWRST_SHIFT	0
#define FLEXSPI_MCR0_SWRST_MASK		BIT(0)

#define FLEXSPI_AHBCR_PREF_EN_SHIFT	5
#define FLEXSPI_AHBCR_PREF_EN_MASK	BIT(5)

#define FLEXSPI_INTR_IPTXWE_SHIFT	6
#define FLEXSPI_INTR_IPTXWE_MASK	BIT(6)
#define FLEXSPI_INTR_IPRXWA_SHIFT	5
#define FLEXSPI_INTR_IPRXWA_MASK	BIT(5)
#define FLEXSPI_INTR_IPCMDDONE_SHIFT	0
#define FLEXSPI_INTR_IPCMDDONE_MASK	BIT(0)

#define FLEXSPI_LUTKEY_VALUE		0x5AF05AF0

#define FLEXSPI_LCKER_LOCK		0x1
#define FLEXSPI_LCKER_UNLOCK		0x2

#define FLEXSPI_BUFXCR_INVALID_MSTRID	0xe
#define FLEXSPI_AHBRXBUF0CR7_PREF_SHIFT	31
#define FLEXSPI_AHBRXBUF0CR7_PREF_MASK	BIT(31)

#define FLEXSPI_IPCR1_SEQID_SHIFT	16

#define FLEXSPI_IPRXFCR_CLR_SHIFT	0
#define FLEXSPI_IPRXFCR_CLR_MASK	BIT(0)

#define FLEXSPI_IPTXFCR_CLR_SHIFT	0
#define FLEXSPI_IPTXFCR_CLR_MASK	BIT(0)

#define FLEXSPI_IPRXFSTS_FILL_SHIFT	0
#define FLEXSPI_IPRXFSTS_FILL_MASK	(0xFF << FLEXSPI_IPRXFSTS_FILL_SHIFT)

/* register map end */

#define OPRND0_SHIFT			0
#define OPRND0(x)			((x) << OPRND0_SHIFT)
#define PAD0_SHIFT			8
#define PAD0(x)				((x) << PAD0_SHIFT)
#define INSTR0_SHIFT			10
#define INSTR0(x)			((x) << INSTR0_SHIFT)
#define OPRND1_SHIFT			16
#define OPRND1(x)			((x) << OPRND1_SHIFT)
#define PAD1_SHIFT			24
#define PAD1(x)				((x) << PAD1_SHIFT)
#define INSTR1_SHIFT			26
#define INSTR1(x)			((x) << INSTR1_SHIFT)

#define LUT_STOP		0x00
#define LUT_CMD			0x01
#define LUT_ADDR		0x02
#define LUT_CADDR_SDR		0x03
#define LUT_MODE		0x04
#define LUT_MODE2		0x05
#define LUT_MODE4		0x06
#define LUT_MODE8		0x07
#define LUT_WRITE		0x08
#define LUT_READ		0x09
#define LUT_LEARN_SDR		0x0A
#define LUT_DATSZ_SDR		0x0B
#define LUT_DUMMY		0x0C
#define LUT_DUMMY_RWDS_SDR	0x0D
#define LUT_JMP_ON_CS		0x1F
#define LUT_CMD_DDR		0x21
#define LUT_ADDR_DDR		0x22
#define LUT_CADDR_DDR		0x23
#define LUT_MODE_DDR		0x24
#define LUT_MODE2_DDR		0x25
#define LUT_MODE4_DDR		0x26
#define LUT_MODE8_DDR		0x27
#define LUT_WRITE_DDR		0x28
#define LUT_READ_DDR		0x29
#define LUT_LEARN_DDR		0x2A
#define LUT_DATSZ_DDR		0x2B
#define LUT_DUMMY_DDR		0x2C
#define LUT_DUMMY_RWDS_DDR	0x2D

#define LUT_PAD1		0
#define LUT_PAD2		1
#define LUT_PAD4		2
#define LUT_PAD8		3

#define ADDR24BIT		0x18
#define ADDR32BIT		0x20

#endif /* _FSL_FSPI_H_ */
