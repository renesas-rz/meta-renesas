// SPDX-License-Identifier: GPL-2.0+
/*
 * drivers/i2c/rzg2l_riic.c
 *
 * Copyright (C)  Hiep Pham <hiep.pham.zy@renesas.com>
 * Copyright (C) 2021 Renesas Electronics Corp.
 * 
 */

#include <errno.h>
#include <common.h>
#include <asm/io.h>
#ifdef CONFIG_ARCH_RMOBILE
#include <asm/arch/rmobile.h>
#endif
#include <clk.h>
#include <dm.h>
#include <i2c.h>
#include <wait_bit.h>
#include <dm/device_compat.h>
#include <linux/bitops.h>
#include <linux/delay.h>

#define RIIC_ICCR1	0x00
#define RIIC_ICCR2	0x04
#define RIIC_ICMR1	0x08
#define RIIC_ICMR2	0x0c
#define RIIC_ICMR3	0x10
#define RIIC_ICFER	0x14
#define RIIC_ICSER	0x18
#define RIIC_ICIER	0x1c
#define RIIC_ICSR1	0x20
#define RIIC_ICSR2	0x24
#define RIIC_ICSAR0	0x28
#define RIIC_ICBRL	0x34
#define RIIC_ICBRH	0x38
#define RIIC_ICDRT	0x3c
#define RIIC_ICDRR	0x40

/* ICCR1 */
#define ICCR1_ICE	0x80
#define ICCR1_IICRST	0x40
#define ICCR1_CLO	0x20
#define ICCR1_SOWP	0x10
#define ICCR1_SCLO	0x08
#define ICCR1_SDAO	0x04
#define ICCR1_SCLI	0x02
#define ICCR1_SDAI	0x01

/* ICCR2 */
#define ICCR2_BBSY	0x80
#define ICCR2_MST	0x40
#define ICCR2_TRS	0x20
#define ICCR2_SP	0x08
#define ICCR2_RS	0x04
#define ICCR2_ST	0x02

/* ICMR1 */
#define ICMR1_MTWP	0x80
#define ICMR1_CKS_MASK	0x70
#define ICMR1_BCWP	0x08
#define ICMR1_BC_MASK	0x07

#define ICMR1_CKS(_x)	((_x << 4) & ICMR1_CKS_MASK)
#define ICMR1_BC(_x)	(_x & ICMR1_BC_MASK)

/* ICMR2 */
#define ICMR2_DLCS	0x80
#define ICMR2_SDDL_MASK	0x70
#define ICMR2_TMOH	0x04
#define ICMR2_TMOL	0x02
#define ICMR2_TMOS	0x01

/* ICMR3 */
#define ICMR3_SMBS	0x80
#define ICMR3_WAIT	0x40
#define ICMR3_RDRFS	0x20
#define ICMR3_ACKWP	0x10
#define ICMR3_ACKBT	0x08
#define ICMR3_ACKBR	0x04
#define ICMR3_NF_MASK	0x03

/* ICFER */
#define ICFER_FMPE	0x80
#define ICFER_SCLE	0x40
#define ICFER_NFE	0x20
#define ICFER_NACKE	0x10
#define ICFER_SALE	0x08
#define ICFER_NALE	0x04
#define ICFER_MALE	0x02
#define ICFER_TMOE	0x01

/* ICSER */
#define ICSER_HOAE	0x80
#define ICSER_DIDE	0x20
#define ICSER_GCAE	0x08
#define ICSER_SAR2E	0x04
#define ICSER_SAR1E	0x02
#define ICSER_SAR0E	0x01

/* ICIER */
#define ICIER_TIE	0x80
#define ICIER_TEIE	0x40
#define ICIER_RIE	0x20
#define ICIER_NAKIE	0x10
#define ICIER_SPIE	0x08
#define ICIER_STIE	0x04
#define ICIER_ALIE	0x02
#define ICIER_TMOIE	0x01

/* ICSR1 */
#define ICSR1_HOA	0x80
#define ICSR1_DID	0x20
#define ICSR1_GCA	0x08
#define ICSR1_AAS2	0x04
#define ICSR1_AAS1	0x02
#define ICSR1_AAS0	0x01

/* ICSR2 */
#define ICSR2_TDRE	0x80
#define ICSR2_TEND	0x40
#define ICSR2_RDRF	0x20
#define ICSR2_NACKF	0x10
#define ICSR2_STOP	0x08
#define ICSR2_START	0x04
#define ICSR2_AL	0x02
#define ICSR2_TMOF	0x01

/* ICBRH */
#define ICBRH_RESERVED	0xe0	/* The write value should always be 1 */
#define ICBRH_BRH_MASK	0x1f

/* ICBRL */
#define ICBRL_RESERVED	0xe0	/* The write value should always be 1 */
#define ICBRL_BRL_MASK	0x1f

#define RIIC_TIMEOUT	(100)	/* 100 msec */

struct riic_priv {
	void __iomem *base;
	struct clk clk;
	int bus;
	int offset;
};

static unsigned char riic_read(struct riic_priv *priv, unsigned long addr)
{
	return readl(priv->base + addr);
}

static void riic_write(struct riic_priv *priv, unsigned char data,
		       unsigned long addr)
{
	writel(data, priv->base + addr);
}

static void riic_set_bit(struct riic_priv *priv, unsigned char val,
			 unsigned long offset)
{
	unsigned char tmp;

	tmp = riic_read(priv, offset) | val;
	riic_write(priv, tmp, offset);
}

static void riic_clear_bit(struct riic_priv *priv, unsigned char val,
			   unsigned long offset)
{
	unsigned char tmp;

	tmp = riic_read(priv, offset) & ~val;
	riic_write(priv, tmp, offset);
}

static int riic_set_clock(struct udevice *dev, int clock)
{
	struct riic_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);

	switch (clock) {
	case 100000:
		riic_clear_bit(priv, ICFER_FMPE, RIIC_ICFER);
		riic_clear_bit(priv, ICMR1_CKS_MASK, RIIC_ICMR1);
		riic_set_bit(priv, ICMR1_CKS(3), RIIC_ICMR1);
		riic_write(priv, ICBRH_RESERVED | 23, RIIC_ICBRH);
		riic_write(priv, ICBRL_RESERVED | 23, RIIC_ICBRL);
		break;
	case 400000:
		riic_clear_bit(priv, ICFER_FMPE, RIIC_ICFER);
		riic_clear_bit(priv, ICMR1_CKS_MASK, RIIC_ICMR1);
		riic_set_bit(priv, ICMR1_CKS(1), RIIC_ICMR1);
		riic_write(priv, ICBRH_RESERVED | 20, RIIC_ICBRH);
		riic_write(priv, ICBRL_RESERVED | 19, RIIC_ICBRL);
		break;
	case 1000000:
		riic_set_bit(priv, ICFER_FMPE, RIIC_ICFER);
		riic_clear_bit(priv, ICMR1_CKS_MASK, RIIC_ICMR1);
		riic_set_bit(priv, ICMR1_CKS(0), RIIC_ICMR1);
		riic_write(priv, ICBRH_RESERVED | 14, RIIC_ICBRH);
		riic_write(priv, ICBRL_RESERVED | 14, RIIC_ICBRL);
		break;

	default:
		debug("%s: unsupported clock (%dkHz)\n", __func__, clock);
		return -EINVAL;
	}

	return 0;
}

static int riic_check_busy(struct udevice *dev)
{
	struct riic_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	/* As for I2C specification, min. bus-free-time is
		4.7 us(Sm) and 1.3 us(Fm). */

	ulong start, timeout = (ulong)RIIC_TIMEOUT;
	start = get_timer(0);

	do {
		if (!(riic_read(priv, RIIC_ICCR2) & ICCR2_BBSY))
			return 0;

	} while (get_timer(start) < timeout);

	debug("%s: i2c bus is busy.\n", __func__);
	return -EBUSY;
}

static int riic_init_setting(struct udevice *dev, int clock)
{
	struct riic_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);

	int ret;

	riic_clear_bit(priv, ICCR1_ICE, RIIC_ICCR1);
	riic_set_bit(priv, ICCR1_IICRST, RIIC_ICCR1);
	riic_clear_bit(priv, ICCR1_IICRST, RIIC_ICCR1);
	ret = riic_read(priv, RIIC_ICCR1);

	riic_write(priv, ICSER_SAR0E, RIIC_ICSER);

	riic_write(priv, ICMR1_BC(7), RIIC_ICMR1);
	ret = riic_read(priv, RIIC_ICMR1);
	ret = riic_set_clock(dev, clock);
	if (ret < 0)
		return ret;

	riic_set_bit(priv, ICCR1_ICE, RIIC_ICCR1);	/* Enable RIIC */
	riic_set_bit(priv, ICMR3_RDRFS | ICMR3_WAIT | ICMR3_ACKWP, RIIC_ICMR3);
	ret = riic_read(priv, RIIC_ICMR3);

	return 0;
}

static int riic_wait_for_icsr2(struct udevice *dev, unsigned short bit)
{
	struct riic_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);

	unsigned long icsr2;
	ulong start, timeout = (ulong)RIIC_TIMEOUT;

	start = get_timer(0);
	do {
		icsr2 = riic_read(priv, RIIC_ICSR2);
		if (icsr2 & ICSR2_NACKF)
			return -EIO;
		if (icsr2 & bit)
			return 0;

	} while (get_timer(start) < timeout);

	debug("%s: timeout!(bit = %x icsr2 = %x, iccr2 = %x)\n", __func__,
		bit, riic_read(priv, RIIC_ICSR2), riic_read(priv, RIIC_ICCR2));

	return -ETIMEDOUT;
}

static int riic_check_nack_receive(struct udevice *dev)
{
	struct riic_priv *priv = dev_get_priv(dev);


	if (riic_read(priv, RIIC_ICSR2) & ICSR2_NACKF) {
		/* received NACK */
		riic_clear_bit(priv, ICSR2_NACKF, RIIC_ICSR2);
		riic_set_bit(priv, ICCR2_SP, RIIC_ICCR2);
		riic_read(priv, RIIC_ICDRR);	/* dummy read */
		return -1;
	}
	return 0;
}

static void riic_set_receive_ack(struct riic_priv *priv, int ack)
{

	if (ack)
		riic_clear_bit(priv, ICMR3_ACKBT, RIIC_ICMR3);
	else
		riic_set_bit(priv, ICMR3_ACKBT, RIIC_ICMR3);
}

static int riic_i2c_raw_write_addr(struct udevice *dev, u8 *buf, int len)
{
	struct riic_priv *priv = dev_get_priv(dev);

	int ret = 0;
	int index = 0;

	do {
		ret = riic_check_nack_receive(dev);
		if (ret < 0)
			return -1;

		ret = riic_wait_for_icsr2(dev, ICSR2_TDRE);
		if (ret < 0)
			return -1;

		riic_write(priv, buf[index++], RIIC_ICDRT);
	} while (len > index);

	return ret;
}

static int riic_i2c_raw_write(struct udevice *dev, struct i2c_msg *msg)
{
	struct riic_priv *priv = dev_get_priv(dev);

	int ret = 0;
	int index = 0;

	for (index = 0; index < msg->len; index++) {
		ret = riic_check_nack_receive(dev);
		if (ret < 0)
			return -1;

		ret = riic_wait_for_icsr2(dev, ICSR2_TDRE);
		if (ret < 0)
			return -1;

		riic_write(priv, msg->buf[index], RIIC_ICDRT);
	}

	return ret;
}

static int riic_i2c_raw_read(struct udevice *dev, struct i2c_msg *msg)
{
	struct riic_priv *priv = dev_get_priv(dev);

	int dummy_read = 1;
	int ret = 0;
	int index = 0;

	do {
		ret = riic_wait_for_icsr2(dev, ICSR2_RDRF);
		if (ret < 0)
			return ret;

		msg->buf[index] = riic_read(priv, RIIC_ICDRR);
		if (dummy_read)
			dummy_read = 0;
		else
			index++;
		riic_set_receive_ack(priv, 1);
	} while (index < (msg->len - 1));

	ret = riic_wait_for_icsr2(dev, ICSR2_RDRF);
	if (ret < 0)
		return ret;

	riic_clear_bit(priv, ICSR2_STOP, RIIC_ICSR2);
	riic_set_bit(priv, ICCR2_SP, RIIC_ICCR2);

	msg->buf[index++] = riic_read(priv, RIIC_ICDRR);
	riic_set_receive_ack(priv, 0);

	return ret;
}

static int riic_send_mem_addr(struct udevice *dev, u32 addr, int alen)
{
	int i;
	u8 b[4];

	if (alen > 4 || alen <= 0)
		return -1;
	/* change byte order and shift bit */
	for (i = alen - 1; i >= 0; i--, addr >>= 8)
		b[i] = addr & 0xff;

	return riic_i2c_raw_write_addr(dev, b, alen);
}

static int riic_send_start_cond(struct udevice *dev, int restart)
{
	struct riic_priv *priv = dev_get_priv(dev);
	int ret;
	priv->base = dev_read_addr_ptr(dev);

	if (restart)
		riic_set_bit(priv, ICCR2_RS, RIIC_ICCR2);
	else
		riic_set_bit(priv, ICCR2_ST, RIIC_ICCR2);

	ret = riic_wait_for_icsr2(dev, ICSR2_START);
	if (ret < 0)
		return ret;
	riic_clear_bit(priv, ICSR2_START, RIIC_ICSR2);

	return ret;
}

static int riic_send_stop_cond(struct udevice *dev)
{
	struct riic_priv *priv = dev_get_priv(dev);

	int ret;

	riic_clear_bit(priv, ICSR2_STOP | ICSR2_NACKF, RIIC_ICSR2);
	riic_set_bit(priv, ICCR2_SP, RIIC_ICCR2);

	ret = riic_wait_for_icsr2(dev, ICSR2_STOP);
	if (ret < 0)
		return ret;

	riic_clear_bit(priv, ICSR2_STOP | ICSR2_NACKF, RIIC_ICSR2);
	return ret;
}

static int riic_send_dev_addr(struct udevice *dev, u8 addr, int read)
{
	u8 buf = ((addr << 1) | read);

	return riic_i2c_raw_write_addr(dev, &buf, 1);
}


static int riic_set_addr(struct udevice *dev, u8 addr, int alen)
{
	int ret;

	ret = riic_check_busy(dev);

	if (ret < 0)
		return ret;

	ret = riic_send_start_cond(dev, 0);

	if (ret < 0)
		goto force_exit;


	if (alen > 0) {
		ret = riic_send_dev_addr(dev, addr, 0);
		if (ret < 0)
			goto force_exit;

		ret = riic_send_mem_addr(dev, addr, alen);
		if (ret < 0)
			goto force_exit;

		ret = riic_wait_for_icsr2(dev, ICSR2_TEND);
		if (ret < 0)
			goto force_exit;
	}

force_exit:
	riic_send_stop_cond(dev);

	return ret;

}


static int riic_read_common(struct udevice *dev, struct i2c_msg *msg, u32 addr, int alen)
{
	struct riic_priv *priv = dev_get_priv(dev);
	int ret;

	ret = riic_check_busy(dev);

	if (ret < 0)
		return ret;

	ret = riic_send_start_cond(dev, 0);

	if (ret < 0)
		goto force_exit;

	/* send addr */
	if (alen > 0) {
		ret = riic_send_dev_addr(dev, msg->addr, 0);
		if (ret < 0)
			goto force_exit;

		ret = riic_send_mem_addr(dev, priv->offset, alen);
		if (ret < 0)
			goto force_exit;

		ret = riic_wait_for_icsr2(dev, ICSR2_TEND);
		if (ret < 0)
			goto force_exit;

		/* restart */
		ret = riic_send_start_cond(dev, 1);
		if (ret < 0)
			goto force_exit;
	}

	ret = riic_send_dev_addr(dev, msg->addr, 1);
	if (ret < 0)
		goto force_exit;
	ret = riic_wait_for_icsr2(dev, ICSR2_RDRF);
	if (ret < 0)
		goto force_exit;

	ret = riic_check_nack_receive(dev);
	if (ret < 0)
		goto force_exit;

	/* receive data */
	ret = riic_i2c_raw_read(dev, msg);

force_exit:
	riic_send_stop_cond(dev);

	return ret;
}

static int riic_write_common(struct udevice *dev, struct i2c_msg *msg, u32 addr, int alen)
{
	struct riic_priv *priv = dev_get_priv(dev);
	int ret;

	ret = riic_check_busy(dev);
	if (ret < 0)
		return ret;

	ret = riic_send_start_cond(dev, 0);
	if (ret < 0)
		goto force_exit;

	/* send addr */
	ret = riic_send_dev_addr(dev, msg->addr, 0);
	if (ret < 0)
		goto force_exit;

	priv->offset = msg->buf[0];

	/* transmit data */
	ret = riic_i2c_raw_write(dev, msg);
	if (ret < 0)
		goto force_exit;

	ret = riic_wait_for_icsr2(dev, ICSR2_TEND);

force_exit:
	riic_send_stop_cond(dev);

	return ret;

}


static int riic_xfer(struct udevice *dev, struct i2c_msg *msg, int nmsgs)
{
	int ret;

	for (; nmsgs > 0; nmsgs--, msg++) {

		if (msg->flags & I2C_M_RD)
			ret = riic_read_common(dev, msg, 0, 1);
		else
			ret = riic_write_common(dev, msg, 0, 1);

		if (ret)
			return ret;
	}

	return 0;
}


static int riic_probe_chip(struct udevice *dev, uint addr, uint flags)
{
	return riic_set_addr(dev, addr, 1);
}


static int riic_probe(struct udevice *dev)
{
	struct riic_priv *priv = dev_get_priv(dev);
	int ret;

	writel(0x000F000F, 0x11010880);
	writel(0x01010101, 0x11031870);

	priv->base = dev_read_addr_ptr(dev);

	ret = clk_get_by_index(dev, 0, &priv->clk);
	if (ret)
		return ret;

	ret = clk_enable(&priv->clk);
	if (ret)
		return ret;

	riic_init_setting(dev, I2C_SPEED_STANDARD_RATE);

	return 0;
}

static const struct dm_i2c_ops riic_ops = {
	.xfer           = riic_xfer,
	.probe_chip     = riic_probe_chip,
};

static const struct udevice_id riic_ids[] = {
	{ .compatible = "renesas,riic-r9a07g044l", },
	{ .compatible = "renesas,riic-r9a07g044c", },
	{ .compatible = "renesas,riic-r9a07g054l", },
	{ .compatible = "renesas,riic-r9a07g043u", },
	{ .compatible = "renesas,riic-r9a07g043f", },
	{ .compatible = "renesas,riic-rz", },
	{ }
};

U_BOOT_DRIVER(riic_rzg2l) = {
	.name           = "riic_rzg2l",
	.id             = UCLASS_I2C,
	.of_match       = riic_ids,
	.probe          = riic_probe,
	.priv_auto	= sizeof(struct riic_priv),
	.ops            = &riic_ops,
};
