/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2019 NXP
 */

#include <linux/linkage.h>

ENTRY(lowlevel_init)
	mrs	x0, CurrentEL
	cmp	x0, #8
	b.eq	1f
	ret
1:
	msr daifclr, #4

	/* set HCR_EL2.AMO to catch SERROR */
	mrs	x0, hcr_el2
	orr	x0, x0, #0x20
	msr	hcr_el2, x0
	isb
	ret
ENDPROC(lowlevel_init)

/*
 * Switch from AArch64 EL2 to AArch32 EL2
 * @param inputs:
 * x0: argument, zero
 * x1: machine nr
 * x2: fdt address
 * x3: input argument
 * x4: kernel entry point
 * @param outputs for secure firmware:
 * x0: function id
 * x1: kernel entry point
 * x2: machine nr
 * x3: fdt address
*/
.global armv8_el2_to_aarch32
armv8_el2_to_aarch32:
	mov     x3, x2
	mov     x2, x1
	mov     x1, x4
	ldr     x0, =0xc20000fd
	smc     #0
	ret
