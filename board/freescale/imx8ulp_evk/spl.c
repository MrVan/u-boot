// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2020 NXP
 */

#include <common.h>
#include <init.h>
#include <spl.h>
#include <asm/io.h>
#include <errno.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx8ulp-pins.h>
#include <dm/uclass.h>
#include <dm/device.h>
#include <dm/uclass-internal.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <asm/arch/ddr.h>

DECLARE_GLOBAL_DATA_PTR;

void spl_dram_init(void)
{
	init_clk_ddr();
	ddr_init(&dram_timing);
}

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_BOOTROM;
}

#define PMIC_I2C_PAD_CTRL	(PAD_CTL_PUS_UP | PAD_CTL_SRE_SLOW | PAD_CTL_ODE)
#define PMIC_MODE_PAD_CTRL	(PAD_CTL_PUS_UP)

static iomux_cfg_t const pmic_pads[] = {
	IMX8ULP_PAD_PTB7__PMIC0_MODE2 | MUX_PAD_CTRL(PMIC_MODE_PAD_CTRL),
	IMX8ULP_PAD_PTB8__PMIC0_MODE1 | MUX_PAD_CTRL(PMIC_MODE_PAD_CTRL),
	IMX8ULP_PAD_PTB9__PMIC0_MODE0 | MUX_PAD_CTRL(PMIC_MODE_PAD_CTRL),
	IMX8ULP_PAD_PTB10__PMIC0_SDA | MUX_PAD_CTRL(PMIC_I2C_PAD_CTRL),
	IMX8ULP_PAD_PTB11__PMIC0_SCL | MUX_PAD_CTRL(PMIC_I2C_PAD_CTRL),
};

static void setup_iomux_pmic(void)
{
	imx8ulp_iomux_setup_multiple_pads(pmic_pads, ARRAY_SIZE(pmic_pads));
}

static void xrdc_mrc_allow_access_sram1(void)
{
	ulong xrdc_base = 0x292f0000, off;

	/* The MRC8 is for SRAM1 */
	off = 0x2000 + 8 * 0x200;

	writel(0x21000000, xrdc_base + off);
	writel(0x2100FFFF, xrdc_base + off + 4);
	writel(0x241249, xrdc_base + off + 8);  /* allow for domain 2/3,  HIFI DSP/LPAV */
	writel(0x80000FFF, xrdc_base + off + 0x10);
}

static void xrdc_configure_mda(void)
{
	ulong xrdc_base = 0x292f0000, off;
	u32 i = 0;

	/* Set MDA3-5 for PXP, ENET, CAAM to DID 1*/
	for (i = 3; i <= 5; i++) {
		off = 0x800 + i * 0x20;
		writel(0x200000A1, xrdc_base + off);
		writel(0xA00000A1, xrdc_base + off);
	}

	/* Set MDA10 -15 to DID 3 for video */
	for (i = 10; i <= 15; i++) {
		off = 0x800 + i * 0x20;
		writel(0x200000A3, xrdc_base + off);
		writel(0xA00000A3, xrdc_base + off);
	}
}

static void xrdc_mrc_allow_video_ddr(void)
{
	ulong xrdc_base = 0x292f0000, off;

	/* The MRC6 is for video modules to ddr */
	off = 0x2000 + 6 * 0x200;

	writel(0x80000000, xrdc_base + off);
	writel(0xffffffff, xrdc_base + off + 4);
	writel(0x200, xrdc_base + off + 8);  /* allow for domain 3 video */
	writel(0x80000FFF, xrdc_base + off + 0x10);
}

void spl_board_init(void)
{
	struct udevice *dev;

	uclass_find_first_device(UCLASS_MISC, &dev);

	for (; dev; uclass_find_next_device(&dev)) {
		if (device_probe(dev))
			continue;
	}

	board_early_init_f();

	preloader_console_init();

	puts("Normal Boot\n");

	if (get_boot_mode() == SINGLE_BOOT)
		setup_iomux_pmic();

	/* DDR initialization */
	spl_dram_init();

	xrdc_configure_mda();

	xrdc_mrc_allow_access_sram1();

	xrdc_mrc_allow_video_ddr();
}

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* Just empty function now - can't decide what to choose */
	debug("%s: %s\n", __func__, name);

	return 0;
}
#endif

void board_init_f(ulong dummy)
{
	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	timer_init();

	arch_cpu_init();

	board_init_r(NULL, 0);
}
