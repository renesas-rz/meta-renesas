// SPDX-License-Identifier: GPL-2.0+
/*
 * GPIO driver for Renesas RZ/G2L SoCs.
 *
 * Copyright (C) 2020 Renesas Electronics Corporation
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <errno.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <dm/device_compat.h>

#define P(n)	(0x0000 + 0x10 + (n))	  /* Port Register */
#define PM(n)	(0x0100 + 0x20 + (n) * 2) /* Port Mode Register */
#define PMC(n)	(0x0200 + 0x10 + (n))	  /* Port Mode Control Register */
#define PFC(n)	(0x0400 + 0x40 + (n) * 4) /* Port Function Control Register */
#define PIN(n)	(0x0800 + 0x10 + (n))	  /* Port Input Register */
#define PWPR	(0x3014)		  /* Port Write Protection Register */

#define PM_INPUT			0x1 /* Input Mode */
#define PM_OUTPUT			0x2 /* Output Mode (disable Input) */
#define PM_OUTPUT_INPUT			0x3 /* Output Mode (enable Input) */
#define PM_MASK				0x03

#define RZG2L_MAX_GPIO_PER_BANK		8

DECLARE_GLOBAL_DATA_PTR;
struct rzg2l_gpio_priv {
	void __iomem	*regs;
	int		bank;
};

static int rzg2l_gpio_get_value(struct udevice *dev, unsigned int offset)
{
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);
	const u8 bit = BIT(offset);
	u16 reg16;

	reg16 = readw(priv->regs + PM(priv->bank));
	reg16 = (reg16 >> offset * 2) & PM_MASK;

	if (reg16 == PM_INPUT || reg16 == PM_OUTPUT_INPUT)
		return !!(readb(priv->regs + PIN(priv->bank)) & bit);
	else if (reg16 == PM_OUTPUT)
		return !!(readb(priv->regs + P(priv->bank)) & bit);
	else
		return 0;
}

static int rzg2l_gpio_set_value(struct udevice *dev, unsigned int offset,
				int value)
{
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);
	const u8 bit = BIT(offset);

	if (value)
		setbits_8(priv->regs + P(priv->bank), bit);
	else
		clrbits_8(priv->regs + P(priv->bank), bit);

	return 0;
}

static void rzg2l_gpio_set_direction(struct rzg2l_gpio_priv *priv,
				     unsigned int offset, bool output)
{
	u16 reg16;

	/* Select GPIO mode in PMC Register */
	clrbits_8(priv->regs + PMC(priv->bank), BIT(offset));

	reg16 = readw(priv->regs + PM(priv->bank));
	reg16 = reg16 & ~(PM_MASK << (offset * 2));

	if (output)
		writew(reg16 | (PM_OUTPUT << (offset * 2)),
		       priv->regs + PM(priv->bank));
	else
		writew(reg16 | (PM_INPUT << (offset * 2)),
		       priv->regs + PM(priv->bank));
}

static int rzg2l_gpio_direction_input(struct udevice *dev, unsigned int offset)
{
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);

	rzg2l_gpio_set_direction(priv, offset, false);

	return 0;
}

static int rzg2l_gpio_direction_output(struct udevice *dev, unsigned int offset,
				       int value)
{
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);

	/* write GPIO value to output before selecting output mode of pin */
	rzg2l_gpio_set_value(dev, offset, value);
	rzg2l_gpio_set_direction(priv, offset, true);

	return 0;
}

static int rzg2l_gpio_get_function(struct udevice *dev, unsigned int offset)
{
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);
	const u8 bit = BIT(offset);

	if (!(readb(priv->regs + PMC(priv->bank)) & bit)) {
		u16 reg16;

		reg16 = readw(priv->regs + PM(priv->bank));
		reg16 = (reg16 >> offset * 2) & PM_MASK;
		if (reg16 == PM_OUTPUT || reg16 == PM_OUTPUT_INPUT)
			return GPIOF_OUTPUT;
		else if (reg16 == PM_INPUT)
			return GPIOF_INPUT;
		else
			return GPIOF_UNUSED;
	}

	return GPIOF_FUNC;
}

static const struct dm_gpio_ops rzg2l_gpio_ops = {
	.direction_input	= rzg2l_gpio_direction_input,
	.direction_output	= rzg2l_gpio_direction_output,
	.get_value		= rzg2l_gpio_get_value,
	.set_value		= rzg2l_gpio_set_value,
	.get_function		= rzg2l_gpio_get_function,
};

static int rzg2l_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	struct rzg2l_gpio_priv *priv = dev_get_priv(dev);
	int ret;
	struct ofnode_phandle_args args;

	priv->regs = dev_read_addr_ptr(dev_get_parent(dev));
	if (!priv->regs) {
		dev_err(dev, "can't get address\n");
		return -EINVAL;
	}

	uc_priv->bank_name = dev->name;

	ret = ofnode_parse_phandle_with_args(dev_ofnode(dev), "gpio-ranges",
					     NULL, 3, 0, &args);
	priv->bank = ret == 0 ? (args.args[1] / RZG2L_MAX_GPIO_PER_BANK) : -1;
	uc_priv->gpio_count = ret == 0 ? args.args[2] : RZG2L_MAX_GPIO_PER_BANK;

	return 0;
}

U_BOOT_DRIVER(rzg2l_gpio) = {
	.name   	= "rzg2l-gpio",
	.id     	= UCLASS_GPIO,
	.ops    	= &rzg2l_gpio_ops,
	.priv_auto	= sizeof(struct rzg2l_gpio_priv),
	.probe  	= rzg2l_gpio_probe,
};
