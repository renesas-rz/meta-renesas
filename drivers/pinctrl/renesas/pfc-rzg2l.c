// SPDX-License-Identifier: GPL-2.0+
/*
 * Pin controller driver for Renesas RZ/G2L SoCs.
 *
 * Copyright (C) 2023 Renesas Electronics Corporation
 */

#include <common.h>
#include <dm.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/err.h>
#include <dm/device_compat.h>

#define P(n)	(0x0000 + 0x10 + (n))	  /* Port Register */
#define PM(n)	(0x0100 + 0x20 + (n) * 2) /* Port Mode Register */
#define PMC(n)	(0x0200 + 0x10 + (n))	  /* Port Mode Control Register */
#define PFC(n)	(0x0400 + 0x40 + (n) * 4) /* Port Function Control Register */
#define PIN(n)	(0x0800 + 0x10 + (n))	  /* Port Input Register */
#define PFC(n)	(0x0400 + 0x40 + (n) * 4) /* Port Function Control Register */
#define PWPR	(0x3014)		  /* Port Write Protection Register */

#define PWPR_B0WI	BIT(7)		  /* Bit Write Disable */
#define PWPR_PFCWE	BIT(6)		  /* PFC Register Write Enable */

#define RZG2L_MAX_PINS_PER_PORT		8

DECLARE_GLOBAL_DATA_PTR;

struct rzg2l_pinctrl_priv {
	void __iomem	*regs;
};

static void rzg2l_pinctrl_set_function(struct rzg2l_pinctrl_priv *priv,
				       u16 port, u8 pin, u8 func)
{
	u32 reg32;
	u8 reg8;

	/* Set GPIO or Func in PMC, then set Func in PFC */
	reg8 = readb(priv->regs + PMC(port));
	reg8 = (reg8 & ~(1 << pin)) | BIT(pin);
	writeb(reg8, priv->regs + PMC(port));

	reg32 = readl(priv->regs + PFC(port));
	reg32 = (reg32 & ~(0x07 << (pin * 4))) | (func << (pin * 4));
	writel(reg32, priv->regs + PFC(port));

}

static int rzg2l_pinctrl_set_state(struct udevice *dev, struct udevice *config)
{
	struct rzg2l_pinctrl_priv *priv = dev_get_plat(dev);
	u16 port;
	u16 port_max = (u16)dev_get_driver_data(dev);
	u8 pin, func;
	int i, count;
	const u32 *data;
	u32 cells[port_max * RZG2L_MAX_PINS_PER_PORT];

	data = dev_read_prop(config, "pinmux", &count);
	if (count < 0) {
		debug("%s: bad array size %d\n", __func__, count);
		return -EINVAL;
	}

	count /= sizeof(u32);
	if (count > port_max * RZG2L_MAX_PINS_PER_PORT) {
		debug("%s: unsupported pins array count %d\n",
		      __func__, count);
		return -EINVAL;
	}
	writel(0, priv->regs + PWPR);
	writel(PWPR_PFCWE, priv->regs + PWPR);

	for (i = 0 ; i < count; i++) {
		cells[i] = fdt32_to_cpu(data[i]);
		func = (cells[i] >> 16) & 0xf;
		port = (cells[i] / RZG2L_MAX_PINS_PER_PORT) & 0x1ff;
		pin = cells[i] % RZG2L_MAX_PINS_PER_PORT;
		/* rz/g2lul serial port assigned to function 6*/
		if (func > 6 || port >= port_max || pin >= RZG2L_MAX_PINS_PER_PORT) {
			printf("Invalid cell %i func %x port %x pin %x in node %s!\n",
			       count,func,port,pin,ofnode_get_name(dev_ofnode(config)));
			continue;
		}

		rzg2l_pinctrl_set_function(priv, port, pin, func);
	}

	writel(0, priv->regs + PWPR);
	writel(PWPR_B0WI, priv->regs + PWPR);
	return 0;
}

const struct pinctrl_ops rzg2l_pinctrl_ops  = {
	.set_state = rzg2l_pinctrl_set_state,
};

static int rzg2l_pinctrl_probe(struct udevice *dev)
{
	struct rzg2l_pinctrl_priv *priv = dev_get_plat(dev);
	ofnode node;

	priv->regs = dev_read_addr_ptr(dev);
	if (!priv->regs) {
		dev_err(dev, "can't get address\n");
		return -EINVAL;
	}

	dev_for_each_subnode(node, dev) {
		struct udevice *gpiodev;

		if (!ofnode_read_bool(node, "gpio-controller"))
			continue;

		device_bind_driver_to_node(dev, "rzg2l-gpio",
					   ofnode_get_name(node),
					   node, &gpiodev);
	}

	return 0;
}

static const struct udevice_id rzg2l_pinctrl_match[] = {
	{ .compatible = "renesas,r9a07g044l-pinctrl", .data = 49 },
	{ .compatible = "renesas,r9a07g044c-pinctrl", .data = 49 },
	{ .compatible = "renesas,r9a07g054l-pinctrl", .data = 49 },
	{ .compatible = "renesas,r9a07g043u-pinctrl", .data = 19 },
	{ .compatible = "renesas,r9a07g043f-pinctrl", .data = 19 },
	{}
};

U_BOOT_DRIVER(rzg2l_pinctrl) = {
	.name		= "rzg2l_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rzg2l_pinctrl_match,
	.probe		= rzg2l_pinctrl_probe,
	.plat_auto	= sizeof(struct rzg2l_pinctrl_priv),
	.ops		= &rzg2l_pinctrl_ops,
};
