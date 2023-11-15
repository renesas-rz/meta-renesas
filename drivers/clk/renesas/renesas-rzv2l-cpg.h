// SPDX-License-Identifier: GPL-2.0
/*
 * RZV2L Clock Pulse Generator
 *
 * Copyright (C) 2021 Renesas Electronics Corp.
 *
 */

#ifndef __RENESAS_RZV2L_CPG_H__
#define __RENESAS_RZV2L_CPG_H__

/*Register offset*/
/*n : 0, 1, 2 : PLL1, PLL4, PLL6*/
#define PLL146_CLK1_R(n)	(0x04 + (16 * n))
#define PLL146_CLK2_R(n)	(0x08 + (16 * n))
#define PLL146_MON_R(n)		(0x0C + (16 * n))
#define PLL146_STBY_R(n)	(0x00 + (16 * n))
/*n : 0, 1, 2 : PLL2, PLL3, PLL5*/
#define PLL235_CLK1_R(n)	(0x104 + (32 * n))
#define PLL235_CLK3_R(n)	(0x10c + (32 * n))
#define PLL235_CLK4_R(n)	(0x110 + (32 * n))
#define PLL235_MON_R(n)		(0x100 + (32 * n))
#define PLL235_STBY_R(n)	(0x11C + (32 * n))
/*offset(32->16):shift(15->8):mask(7->0)*/
#define PLL1_DIV_R		(0x200)
#define PLL2_DIV_R		(0x204)
#define PLL3A_DIV_R		(0x208)
#define PLL3B_DIV_R		(0x20c)
#define PLL6_DIV_R		(0x210)
#define PL2SDHI_SEL_R		(0x218)
#define CLK_STATUS_R		(0x280)
#define CA55_SSEL_R		(0x400)
#define PL2_SSEL_R		(0x404)
#define PL3_SSEL_R		(0x408)
#define PL4_DSEL_R		(0x21C)
#define PL5_SSEL_R		(0x410)
#define PL6_SSEL_R		(0x414)
#define PL6_ETH_SSEL_R		(0x418)
#define PL5_SDIV_R		(0x420)
#define OTHERFUNC1_R		(0xBE8)
#define CLK_ON_R(reg)		(0x500 + reg)
#define CLK_MON_R(reg)		(0x680 + reg)
#define CLK_RST_R(reg)		(0x800 + reg)
#define CLK_MRST_R(reg)		(0x980 + reg)

/*12bits register offset, 8bits shifter, 4bits width, 8bits reserved*/
#define SEL_PLL1	(CA55_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL2_1	(PL2_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL2_2	(PL2_SSEL_R << 20	| 4 << 12	| 1 << 8)
#define SEL_PLL3_1	(PL3_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL3_2	(PL3_SSEL_R << 20	| 4 << 12	| 1 << 8)
#define SEL_PLL3_3	(PL3_SSEL_R << 20	| 8 << 12	| 1 << 8)
#define SEL_PLL4	(PL4_DSEL_R << 20	| 8 << 12	| 1 << 8)
#define SEL_PLL5_1	(PL5_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL5_2	(PL5_SSEL_R << 20	| 4 << 12	| 1 << 8)
#define SEL_PLL5_3	(PL5_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL5_4	(OTHERFUNC1_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL6_1	(PL6_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_PLL6_2	(PL6_ETH_SSEL_R << 20	| 0 << 12	| 1 << 8)
#define SEL_ETH		(PL6_ETH_SSEL_R << 20	| 4 << 12	| 1 << 8)
#define SEL_G1_1	(PL6_SSEL_R << 20	| 4 << 12	| 1 << 8)
#define SEL_G1_2	(PL6_SSEL_R << 20	| 8 << 12	| 1 << 8)
#define SEL_G2		(PL6_SSEL_R << 20	| 12 << 12	| 1 << 8)
#define SEL_SDHI0	(PL2SDHI_SEL_R << 20	| 0 << 12	| 2 << 8)
#define SEL_SDHI1	(PL2SDHI_SEL_R << 20	| 4 << 12	| 2 << 8)
#define DIVPL1		(PLL1_DIV_R << 20	| 0 << 12	| 2 << 8)
#define DIVPL2A		(PLL2_DIV_R << 20	| 0 << 12	| 3 << 8)
#define DIVPL2B		(PLL2_DIV_R << 20	| 4 << 12	| 3 << 8)
#define DIVPL2C		(PLL2_DIV_R << 20	| 8 << 12	| 3 << 8)
#define DIVDSILPCL	(PLL2_DIV_R << 20	| 12 << 12	| 2 << 8)
#define DIVPL3A		(PLL3A_DIV_R << 20	| 0 << 12	| 3 << 8)
#define DIVPL3B		(PLL3A_DIV_R << 20	| 4 << 12	| 3 << 8)
#define DIVPL3C		(PLL3A_DIV_R << 20	| 8 << 12	| 3 << 8)
#define DIVPL3CLK200FIX	(PLL3B_DIV_R << 20	| 0 << 12	| 3 << 8)
#define DIVGPU		(PLL6_DIV_R << 20	| 0 << 12	| 2 << 8)
#define DIVDSIB		(PL5_SDIV_R << 20	| 8 << 12	| 4 << 8)
#define DIVDSIA		(PL5_SDIV_R << 20	| 0 << 12	| 2 << 8)

/*16bits register offset, 8bits ON/MON, 8bits RESET*/
#define MSSR(off, on, res)	((off & 0xffff) << 16	\
				| (on & 0xff) << 8	\
				| (res & 0xff))
#define MSSR_OFF(val)		((val >> 16) & 0xffff)
#define MSSR_ON(val)		((val >> 8) & 0xff)
#define MSSR_RES(val)		(val & 0xff)

/*
 * Definitions of CPG Core Clocks
 *
 * These include:
 *   - Clock outputs exported to DT
 *   - External input clocks
 *   - Internal CPG clocks
 */

struct cpg_core_clk {
	/* Common */
	const char *name;
	unsigned int id;
	unsigned int parent;
	unsigned int div;
	unsigned int mult;
	unsigned int type;
	unsigned int conf;
	struct clk_div_table *dtable;
	int flag;
	char const **parent_names;
	int num_parents;
	/*used for clocks have two config info*/
	unsigned int confs;
	struct clk_div_table *dtables;
};

enum clk_types {
	/* Generic */
	CLK_TYPE_IN,		/* External Clock Input */
	CLK_TYPE_FF,		/* Fixed Factor Clock */
	CLK_TYPE_PLL1,
	CLK_TYPE_PLL2,
	CLK_TYPE_PLL3,
	CLK_TYPE_PLL4,
	CLK_TYPE_PLL5,
	CLK_TYPE_PLL6,

	/*Clock have divider*/
	CLK_TYPE_DIV,
	CLK_TYPE_2DIV,

	/*Clock have selector*/
	CLK_TYPE_MUX,

	/* Custom definitions start here */
	CLK_TYPE_CUSTOM,
};

#define DEF_TYPE(_name, _id, _type...) \
	{ .name = _name, .id = _id, .type = _type }
#define DEF_BASE(_name, _id, _type, _parent...) \
	DEF_TYPE(_name, _id, _type, .parent = _parent)
#define DEF_INPUT(_name, _id) \
	DEF_TYPE(_name, _id, CLK_TYPE_IN)
#define DEF_FIXED(_name, _id, _parent, _mult, _div) \
	DEF_BASE(_name, _id, CLK_TYPE_FF, _parent, .div = _div, .mult = _mult)
#define DEF_DIV(_name, _id, _parent, _conf, _dtable, _flag) \
	DEF_TYPE(_name, _id, CLK_TYPE_DIV, .conf = _conf, \
		.parent = _parent, .dtable = _dtable, .flag = _flag)
#define DEF_MUX(_name, _id, _conf, _parent_names, _num_parents, _flag) \
	DEF_TYPE(_name, _id, CLK_TYPE_MUX, .conf = _conf, \
		.parent_names = _parent_names, \
		.num_parents = _num_parents, .flag = _flag)
/*Clock have two dividors */
#define DEF_2DIV(_name, _id, _parent, _conf, _confs, _dtable, _dtables, _flag) \
	DEF_TYPE(_name, _id, CLK_TYPE_2DIV, .parent = _parent, \
		.conf = _conf, .confs = _confs, \
		.dtable = _dtable, .dtables = _dtables, .flag = _flag)

/*
 * Definitions of Module Clocks
 * @name: handle between common and hardware-specific interfaces
 * @id: clock index in array containing all Core and Module Clocks
 * @parent: id of parent clock
 * @offset: CLK_ON/MON register offset
 * @bit: 16bits register offset, 8bits ON/MON, 8bits RESET
 */

struct mssr_mod_clk {
	const char *name;
	unsigned int id;
	unsigned int parent;
	unsigned int bit;
};

/* Convert from sparse base-100 to packed index space */
#define MOD_CLK_PACK(x)	((x) - ((x) / 100) * (100 - 32))

#define DEF_MOD(_name, _id, _parent, _bit)	\
	{ .name = _name, .id = CLK_MODE_BASE + _id, .parent = _parent,\
	.bit = _bit }

struct device_node;

/*
 * PLL register info
 * @type: PLL Clock type
 * @reg1: PLL register offset 1
 * @reg2: PLL register offset 2
 * @reg3: PLL register offset 3
 */
struct cpg_pll_info {
	unsigned int type;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int reg3;
};

/**
 * SoC-specific CPG/MSSR Description
 *
 * @core_clks: Array of Core Clock definitions
 * @num_core_clks: Number of entries in core_clks[]
 * @last_dt_core_clk: ID of the last Core Clock exported to DT
 * @num_total_core_clks: Total number of Core Clocks (exported + internal)
 *
 * @pll_info: array of PLL register info
 * @pll_info_size: Total number of PLL registers info
 *
 * @mod_clks: Array of Module Clock definitions
 * @num_mod_clks: Number of entries in mod_clks[]
 * @num_hw_mod_clks: Number of Module Clocks supported by the hardware
 *
 * @crit_mod_clks: Array with Module Clock IDs of critical clocks that
 *                 should not be disabled without a knowledgeable driver
 * @num_crit_mod_clks: Number of entries in crit_mod_clks[]
 */

struct cpg_mssr_info {
	const struct cpg_core_clk	*core_clk;
	unsigned int			core_clk_size;
	const struct mssr_mod_clk	*mod_clk;
	unsigned int			mod_clk_size;
	const struct mstp_stop_table	*mstp_table;
	unsigned int			mstp_table_size;
	const char			*reset_node;
	const char			*extalr_node;
	const char			*extal_usb_node;
	unsigned int			mod_clk_base;
	unsigned int			clk_extal_id;
	unsigned int			clk_extalr_id;
	unsigned int			clk_extal_usb_id;
	unsigned int			pll0_div;
	const void			*(*get_pll_config)(const u32 cpg_mode);
};

/* FIXME */
struct rzg2l_cpg_pll_config {
	u8 extal_div;
	u8 pll1_mult;
	u8 pll1_div;
	u8 pll3_mult;
	u8 pll3_div;
	u8 osc_prediv;
};
struct rzv2l_clk_priv {
	void __iomem		*base;
	struct cpg_mssr_info	*info;
	struct clk		clk_extal;
	struct clk		clk_extalr;
	bool			sscg;
	const struct rcar_gen3_cpg_pll_config *cpg_pll_config;
};

extern const struct cpg_mssr_info r9a07g054l_cpg_info;

static inline bool is_mod_clk(struct clk *clk)
{
	return (clk->id >> 16) == CPG_MOD;
}

#endif
