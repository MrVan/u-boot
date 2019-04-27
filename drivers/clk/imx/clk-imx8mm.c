// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2019 NXP
 * Peng Fan <peng.fan@nxp.com>
 */

#include <common.h>
#include <clk-uclass.h>
#include <dm.h>
#include <asm/arch/clock.h>
#include <dt-bindings/clock/imx8mm-clock.h>

static ulong imx8mm_clk_get_rate(struct clk *clk)
{
	debug("%s(#%lu)\n", __func__, clk->id);

	switch (clk->id) {
	case IMX8MM_CLK_USDHC1_ROOT:
		return get_root_clk(USDHC1_CLK_ROOT);
	case IMX8MM_CLK_USDHC2_ROOT:
		return get_root_clk(USDHC2_CLK_ROOT);
	case IMX8MM_CLK_USDHC3_ROOT:
		return get_root_clk(USDHC3_CLK_ROOT);
	case IMX8MM_CLK_I2C1:
		return get_root_clk(I2C1_CLK_ROOT);
	case IMX8MM_CLK_I2C2:
		return get_root_clk(I2C2_CLK_ROOT);
	case IMX8MM_CLK_I2C3:
		return get_root_clk(I2C3_CLK_ROOT);
	case IMX8MM_CLK_I2C4:
		return get_root_clk(I2C4_CLK_ROOT);
	}

	return 0;
}

static int __imx8mm_clk_enable(struct clk *clk, bool enable)
{
	switch (clk->id) {
	case IMX8MM_CLK_USDHC1_ROOT:
		return clock_enable(CCGR_USDHC1, enable);
	case IMX8MM_CLK_USDHC2_ROOT:
		return clock_enable(CCGR_USDHC2, enable);
	case IMX8MM_CLK_USDHC3_ROOT:
		return clock_enable(CCGR_USDHC3, enable);
	case IMX8MM_CLK_I2C1:
		return clock_enable(CCGR_I2C1, enable);
	case IMX8MM_CLK_I2C2:
		return clock_enable(CCGR_I2C2, enable);
	case IMX8MM_CLK_I2C3:
		return clock_enable(CCGR_I2C3, enable);
	case IMX8MM_CLK_I2C4:
		return clock_enable(CCGR_I2C4, enable);
	}

	return -EINVAL;
}

static int imx8mm_clk_disable(struct clk *clk)
{
	debug("%s(#%lu)\n", __func__, clk->id);

	return __imx8mm_clk_enable(clk, false);
}

static int imx8mm_clk_enable(struct clk *clk)
{
	debug("%s(#%lu)\n", __func__, clk->id);

	return __imx8mm_clk_enable(clk, true);
}

static ulong imx8mm_clk_set_rate(struct clk *clk, unsigned long rate)
{
	debug("%s(#%lu)\n", __func__, clk->id);

	/* TODO: */

	return imx8mm_clk_get_rate(clk);
}

static struct clk_ops imx8mm_clk_ops = {
	.set_rate = imx8mm_clk_set_rate,
	.get_rate = imx8mm_clk_get_rate,
	.enable = imx8mm_clk_enable,
	.disable = imx8mm_clk_disable,
};

static int imx8mm_clk_probe(struct udevice *dev)
{
	return 0;
}

static const struct udevice_id imx8mm_clk_ids[] = {
	{ .compatible = "fsl,imx8mm-ccm" },
	{ },
};

U_BOOT_DRIVER(imx8mm_clk) = {
	.name = "clk_imx8mm",
	.id = UCLASS_CLK,
	.of_match = imx8mm_clk_ids,
	.ops = &imx8mm_clk_ops,
	.probe = imx8mm_clk_probe,
	.flags = DM_FLAG_PRE_RELOC,
};
