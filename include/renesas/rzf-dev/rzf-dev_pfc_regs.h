// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef __RZF_DEV_PFC_REGS_H__
#define __RZF_DEV_PFC_REGS_H__

#define	PFC_BASE					(0x11030000)			/* PFC base address */

#define PFC_P10							(PFC_BASE + 0x0010)	/* Port register */
#define PFC_P11							(PFC_BASE + 0x0011)	/* Port register */
#define PFC_P12							(PFC_BASE + 0x0012)	/* Port register */
#define PFC_P13							(PFC_BASE + 0x0013)	/* Port register */
#define PFC_P14							(PFC_BASE + 0x0014)	/* Port register */
#define PFC_P15							(PFC_BASE + 0x0015)	/* Port register */
#define PFC_P16							(PFC_BASE + 0x0016)	/* Port register */
#define PFC_P17							(PFC_BASE + 0x0017)	/* Port register */
#define PFC_P18							(PFC_BASE + 0x0018)	/* Port register */
#define PFC_P19							(PFC_BASE + 0x0019)	/* Port register */
#define PFC_P1A							(PFC_BASE + 0x001A)	/* Port register */
#define PFC_P1B							(PFC_BASE + 0x001B)	/* Port register */
#define PFC_P1C							(PFC_BASE + 0x001C)	/* Port register */
#define PFC_P1D							(PFC_BASE + 0x001D)	/* Port register */
#define PFC_P1E							(PFC_BASE + 0x001E)	/* Port register */
#define PFC_P1F							(PFC_BASE + 0x001F)	/* Port register */
#define PFC_P20							(PFC_BASE + 0x0020)	/* Port register */
#define PFC_P21							(PFC_BASE + 0x0021)	/* Port register */
#define PFC_P22							(PFC_BASE + 0x0022)	/* Port register */
#define PFC_P23							(PFC_BASE + 0x0023)	/* Port register */
#define PFC_P24							(PFC_BASE + 0x0024)	/* Port register */
#define PFC_P25							(PFC_BASE + 0x0025)	/* Port register */
#define PFC_P26							(PFC_BASE + 0x0026)	/* Port register */
#define PFC_P27							(PFC_BASE + 0x0027)	/* Port register */
#define PFC_P28							(PFC_BASE + 0x0028)	/* Port register */
#define PFC_P29							(PFC_BASE + 0x0029)	/* Port register */
#define PFC_P2A							(PFC_BASE + 0x002A)	/* Port register */
#define PFC_P2B							(PFC_BASE + 0x002B)	/* Port register */
#define PFC_P2C							(PFC_BASE + 0x002C)	/* Port register */
#define PFC_P2D							(PFC_BASE + 0x002D)	/* Port register */
#define PFC_P2E							(PFC_BASE + 0x002E)	/* Port register */
#define PFC_P2F							(PFC_BASE + 0x002F)	/* Port register */
#define PFC_P30							(PFC_BASE + 0x0030)	/* Port register */
#define PFC_P31							(PFC_BASE + 0x0031)	/* Port register */
#define PFC_P32							(PFC_BASE + 0x0032)	/* Port register */
#define PFC_P33							(PFC_BASE + 0x0033)	/* Port register */
#define PFC_P34							(PFC_BASE + 0x0034)	/* Port register */
#define PFC_P35							(PFC_BASE + 0x0035)	/* Port register */
#define PFC_P36							(PFC_BASE + 0x0036)	/* Port register */
#define PFC_P37							(PFC_BASE + 0x0037)	/* Port register */
#define PFC_P38							(PFC_BASE + 0x0038)	/* Port register */
#define PFC_P39							(PFC_BASE + 0x0039)	/* Port register */
#define PFC_P3A							(PFC_BASE + 0x003A)	/* Port register */
#define PFC_P3B							(PFC_BASE + 0x003B)	/* Port register */
#define PFC_P3C							(PFC_BASE + 0x003C)	/* Port register */
#define PFC_P3D							(PFC_BASE + 0x003D)	/* Port register */
#define PFC_P3E							(PFC_BASE + 0x003E)	/* Port register */
#define PFC_P3F							(PFC_BASE + 0x003F)	/* Port register */
#define PFC_P40							(PFC_BASE + 0x0040)	/* Port register */
#define PFC_PM10						(PFC_BASE + 0x0120)	/* Port mode register */
#define PFC_PM11						(PFC_BASE + 0x0122)	/* Port mode register */
#define PFC_PM12						(PFC_BASE + 0x0124)	/* Port mode register */
#define PFC_PM13						(PFC_BASE + 0x0126)	/* Port mode register */
#define PFC_PM14						(PFC_BASE + 0x0128)	/* Port mode register */
#define PFC_PM15						(PFC_BASE + 0x012A)	/* Port mode register */
#define PFC_PM16						(PFC_BASE + 0x012C)	/* Port mode register */
#define PFC_PM17						(PFC_BASE + 0x012E)	/* Port mode register */
#define PFC_PM18						(PFC_BASE + 0x0130)	/* Port mode register */
#define PFC_PM19						(PFC_BASE + 0x0132)	/* Port mode register */
#define PFC_PM1A						(PFC_BASE + 0x0134)	/* Port mode register */
#define PFC_PM1B						(PFC_BASE + 0x0136)	/* Port mode register */
#define PFC_PM1C						(PFC_BASE + 0x0138)	/* Port mode register */
#define PFC_PM1D						(PFC_BASE + 0x013A)	/* Port mode register */
#define PFC_PM1E						(PFC_BASE + 0x013C)	/* Port mode register */
#define PFC_PM1F						(PFC_BASE + 0x013E)	/* Port mode register */
#define PFC_PM20						(PFC_BASE + 0x0140)	/* Port mode register */
#define PFC_PM21						(PFC_BASE + 0x0142)	/* Port mode register */
#define PFC_PM22						(PFC_BASE + 0x0144)	/* Port mode register */
#define PFC_PM23						(PFC_BASE + 0x0146)	/* Port mode register */
#define PFC_PM24						(PFC_BASE + 0x0148)	/* Port mode register */
#define PFC_PM25						(PFC_BASE + 0x014A)	/* Port mode register */
#define PFC_PM26						(PFC_BASE + 0x014C)	/* Port mode register */
#define PFC_PM27						(PFC_BASE + 0x014E)	/* Port mode register */
#define PFC_PM28						(PFC_BASE + 0x0150)	/* Port mode register */
#define PFC_PM29						(PFC_BASE + 0x0152)	/* Port mode register */
#define PFC_PM2A						(PFC_BASE + 0x0154)	/* Port mode register */
#define PFC_PM2B						(PFC_BASE + 0x0156)	/* Port mode register */
#define PFC_PM2C						(PFC_BASE + 0x0158)	/* Port mode register */
#define PFC_PM2D						(PFC_BASE + 0x015A)	/* Port mode register */
#define PFC_PM2E						(PFC_BASE + 0x015C)	/* Port mode register */
#define PFC_PM2F						(PFC_BASE + 0x015E)	/* Port mode register */
#define PFC_PM30						(PFC_BASE + 0x0160)	/* Port mode register */
#define PFC_PM31						(PFC_BASE + 0x0162)	/* Port mode register */
#define PFC_PM32						(PFC_BASE + 0x0164)	/* Port mode register */
#define PFC_PM33						(PFC_BASE + 0x0166)	/* Port mode register */
#define PFC_PM34						(PFC_BASE + 0x0168)	/* Port mode register */
#define PFC_PM35						(PFC_BASE + 0x016A)	/* Port mode register */
#define PFC_PM36						(PFC_BASE + 0x016C)	/* Port mode register */
#define PFC_PM37						(PFC_BASE + 0x016E)	/* Port mode register */
#define PFC_PM38						(PFC_BASE + 0x0170)	/* Port mode register */
#define PFC_PM39						(PFC_BASE + 0x0172)	/* Port mode register */
#define PFC_PM3A						(PFC_BASE + 0x0174)	/* Port mode register */
#define PFC_PM3B						(PFC_BASE + 0x0176)	/* Port mode register */
#define PFC_PM3C						(PFC_BASE + 0x0178)	/* Port mode register */
#define PFC_PM3D						(PFC_BASE + 0x017A)	/* Port mode register */
#define PFC_PM3E						(PFC_BASE + 0x017C)	/* Port mode register */
#define PFC_PM3F						(PFC_BASE + 0x017E)	/* Port mode register */
#define PFC_PM40						(PFC_BASE + 0x0180)	/* Port mode register */
#define PFC_PMC06						(PFC_BASE + 0x0206)	/* Port mode control register */
#define PFC_PMC07						(PFC_BASE + 0x0207)	/* Port mode control register */
#define PFC_PMC08						(PFC_BASE + 0x0208)	/* Port mode control register */
#define PFC_PMC09						(PFC_BASE + 0x0209)	/* Port mode control register */
#define PFC_PMC0A						(PFC_BASE + 0x020A)	/* Port mode control register */
#define PFC_PMC0C						(PFC_BASE + 0x020C)	/* Port mode control register */
#define PFC_PMC10						(PFC_BASE + 0x0210)	/* Port mode control register */
#define PFC_PMC11						(PFC_BASE + 0x0211)	/* Port mode control register */
#define PFC_PMC12						(PFC_BASE + 0x0212)	/* Port mode control register */
#define PFC_PMC13						(PFC_BASE + 0x0213)	/* Port mode control register */
#define PFC_PMC14						(PFC_BASE + 0x0214)	/* Port mode control register */
#define PFC_PMC15						(PFC_BASE + 0x0215)	/* Port mode control register */
#define PFC_PMC16						(PFC_BASE + 0x0216)	/* Port mode control register */
#define PFC_PMC17						(PFC_BASE + 0x0217)	/* Port mode control register */
#define PFC_PMC18						(PFC_BASE + 0x0218)	/* Port mode control register */
#define PFC_PMC19						(PFC_BASE + 0x0219)	/* Port mode control register */
#define PFC_PMC1A						(PFC_BASE + 0x021A)	/* Port mode control register */
#define PFC_PMC1B						(PFC_BASE + 0x021B)	/* Port mode control register */
#define PFC_PMC1C						(PFC_BASE + 0x021C)	/* Port mode control register */
#define PFC_PMC1D						(PFC_BASE + 0x021D)	/* Port mode control register */
#define PFC_PMC1E						(PFC_BASE + 0x021E)	/* Port mode control register */
#define PFC_PMC1F						(PFC_BASE + 0x021F)	/* Port mode control register */
#define PFC_PMC20						(PFC_BASE + 0x0220)	/* Port mode control register */
#define PFC_PMC21						(PFC_BASE + 0x0221)	/* Port mode control register */
#define PFC_PMC22						(PFC_BASE + 0x0222)	/* Port mode control register */
#define PFC_PMC23						(PFC_BASE + 0x0223)	/* Port mode control register */
#define PFC_PMC24						(PFC_BASE + 0x0224)	/* Port mode control register */
#define PFC_PMC25						(PFC_BASE + 0x0225)	/* Port mode control register */
#define PFC_PMC26						(PFC_BASE + 0x0226)	/* Port mode control register */
#define PFC_PMC27						(PFC_BASE + 0x0227)	/* Port mode control register */
#define PFC_PMC28						(PFC_BASE + 0x0228)	/* Port mode control register */
#define PFC_PMC29						(PFC_BASE + 0x0229)	/* Port mode control register */
#define PFC_PMC2A						(PFC_BASE + 0x022A)	/* Port mode control register */
#define PFC_PMC2B						(PFC_BASE + 0x022B)	/* Port mode control register */
#define PFC_PMC2C						(PFC_BASE + 0x022C)	/* Port mode control register */
#define PFC_PMC2D						(PFC_BASE + 0x022D)	/* Port mode control register */
#define PFC_PMC2E						(PFC_BASE + 0x022E)	/* Port mode control register */
#define PFC_PMC2F						(PFC_BASE + 0x022F)	/* Port mode control register */
#define PFC_PMC30						(PFC_BASE + 0x0230)	/* Port mode control register */
#define PFC_PMC31						(PFC_BASE + 0x0231)	/* Port mode control register */
#define PFC_PMC32						(PFC_BASE + 0x0232)	/* Port mode control register */
#define PFC_PMC33						(PFC_BASE + 0x0233)	/* Port mode control register */
#define PFC_PMC34						(PFC_BASE + 0x0234)	/* Port mode control register */
#define PFC_PMC35						(PFC_BASE + 0x0235)	/* Port mode control register */
#define PFC_PMC36						(PFC_BASE + 0x0236)	/* Port mode control register */
#define PFC_PMC37						(PFC_BASE + 0x0237)	/* Port mode control register */
#define PFC_PMC38						(PFC_BASE + 0x0238)	/* Port mode control register */
#define PFC_PMC39						(PFC_BASE + 0x0239)	/* Port mode control register */
#define PFC_PMC3A						(PFC_BASE + 0x023A)	/* Port mode control register */
#define PFC_PMC3B						(PFC_BASE + 0x023B)	/* Port mode control register */
#define PFC_PMC3C						(PFC_BASE + 0x023C)	/* Port mode control register */
#define PFC_PMC3D						(PFC_BASE + 0x023D)	/* Port mode control register */
#define PFC_PMC3E						(PFC_BASE + 0x023E)	/* Port mode control register */
#define PFC_PMC3F						(PFC_BASE + 0x023F)	/* Port mode control register */
#define PFC_PMC40						(PFC_BASE + 0x0240)	/* Port mode control register */
#define PFC_PFC06						(PFC_BASE + 0x0418)	/* Port function control register */
#define PFC_PFC07						(PFC_BASE + 0x041C)	/* Port function control register */
#define PFC_PFC08						(PFC_BASE + 0x0420)	/* Port function control register */
#define PFC_PFC09						(PFC_BASE + 0x0424)	/* Port function control register */
#define PFC_PFC0A						(PFC_BASE + 0x0428)	/* Port function control register */
#define PFC_PFC0C						(PFC_BASE + 0x0430)	/* Port function control register */
#define PFC_PFC10						(PFC_BASE + 0x0440)	/* Port function control register */
#define PFC_PFC11						(PFC_BASE + 0x0444)	/* Port function control register */
#define PFC_PFC12						(PFC_BASE + 0x0448)	/* Port function control register */
#define PFC_PFC13						(PFC_BASE + 0x044C)	/* Port function control register */
#define PFC_PFC14						(PFC_BASE + 0x0450)	/* Port function control register */
#define PFC_PFC15						(PFC_BASE + 0x0454)	/* Port function control register */
#define PFC_PFC16						(PFC_BASE + 0x0458)	/* Port function control register */
#define PFC_PFC17						(PFC_BASE + 0x045C)	/* Port function control register */
#define PFC_PFC18						(PFC_BASE + 0x0460)	/* Port function control register */
#define PFC_PFC19						(PFC_BASE + 0x0464)	/* Port function control register */
#define PFC_PFC1A						(PFC_BASE + 0x0468)	/* Port function control register */
#define PFC_PFC1B						(PFC_BASE + 0x046C)	/* Port function control register */
#define PFC_PFC1C						(PFC_BASE + 0x0470)	/* Port function control register */
#define PFC_PFC1D						(PFC_BASE + 0x0474)	/* Port function control register */
#define PFC_PFC1E						(PFC_BASE + 0x0478)	/* Port function control register */
#define PFC_PFC1F						(PFC_BASE + 0x047C)	/* Port function control register */
#define PFC_PFC20						(PFC_BASE + 0x0480)	/* Port function control register */
#define PFC_PFC21						(PFC_BASE + 0x0484)	/* Port function control register */
#define PFC_PFC22						(PFC_BASE + 0x0488)	/* Port function control register */
#define PFC_PFC23						(PFC_BASE + 0x048C)	/* Port function control register */
#define PFC_PFC24						(PFC_BASE + 0x0490)	/* Port function control register */
#define PFC_PFC25						(PFC_BASE + 0x0494)	/* Port function control register */
#define PFC_PFC26						(PFC_BASE + 0x0498)	/* Port function control register */
#define PFC_PFC27						(PFC_BASE + 0x049C)	/* Port function control register */
#define PFC_PFC28						(PFC_BASE + 0x04A0)	/* Port function control register */
#define PFC_PFC29						(PFC_BASE + 0x04A4)	/* Port function control register */
#define PFC_PFC2A						(PFC_BASE + 0x04A8)	/* Port function control register */
#define PFC_PFC2B						(PFC_BASE + 0x04AC)	/* Port function control register */
#define PFC_PFC2C						(PFC_BASE + 0x04B0)	/* Port function control register */
#define PFC_PFC2D						(PFC_BASE + 0x04B4)	/* Port function control register */
#define PFC_PFC2E						(PFC_BASE + 0x04B8)	/* Port function control register */
#define PFC_PFC2F						(PFC_BASE + 0x04BC)	/* Port function control register */
#define PFC_PFC30						(PFC_BASE + 0x04C0)	/* Port function control register */
#define PFC_PFC31						(PFC_BASE + 0x04C4)	/* Port function control register */
#define PFC_PFC32						(PFC_BASE + 0x04C8)	/* Port function control register */
#define PFC_PFC33						(PFC_BASE + 0x04CC)	/* Port function control register */
#define PFC_PFC34						(PFC_BASE + 0x04D0)	/* Port function control register */
#define PFC_PFC35						(PFC_BASE + 0x04D4)	/* Port function control register */
#define PFC_PFC36						(PFC_BASE + 0x04D8)	/* Port function control register */
#define PFC_PFC37						(PFC_BASE + 0x04DC)	/* Port function control register */
#define PFC_PFC38						(PFC_BASE + 0x04E0)	/* Port function control register */
#define PFC_PFC39						(PFC_BASE + 0x04E4)	/* Port function control register */
#define PFC_PFC3A						(PFC_BASE + 0x04E8)	/* Port function control register */
#define PFC_PFC3B						(PFC_BASE + 0x04EC)	/* Port function control register */
#define PFC_PFC3C						(PFC_BASE + 0x04F0)	/* Port function control register */
#define PFC_PFC3D						(PFC_BASE + 0x04F4)	/* Port function control register */
#define PFC_PFC3E						(PFC_BASE + 0x04F8)	/* Port function control register */
#define PFC_PFC3F						(PFC_BASE + 0x04FC)	/* Port function control register */
#define PFC_PFC40						(PFC_BASE + 0x0500)	/* Port function control register */
#define PFC_IOLH02						(PFC_BASE + 0x1010)	/* IOLH switch register */
#define PFC_IOLH03						(PFC_BASE + 0x1018)	/* IOLH switch register */
#define PFC_IOLH06						(PFC_BASE + 0x1030)	/* IOLH switch register */
#define PFC_IOLH07						(PFC_BASE + 0x1038)	/* IOLH switch register */
#define PFC_IOLH08						(PFC_BASE + 0x1040)	/* IOLH switch register */
#define PFC_IOLH09						(PFC_BASE + 0x1048)	/* IOLH switch register */
#define PFC_IOLH0A						(PFC_BASE + 0x1050)	/* IOLH switch register */
#define PFC_IOLH0B						(PFC_BASE + 0x1058)	/* IOLH switch register */
#define PFC_IOLH0C						(PFC_BASE + 0x1060)	/* IOLH switch register */
#define PFC_IOLH0D						(PFC_BASE + 0x1068)	/* IOLH switch register */
#define PFC_IOLH10						(PFC_BASE + 0x1080)	/* IOLH switch register */
#define PFC_IOLH11						(PFC_BASE + 0x1088)	/* IOLH switch register */
#define PFC_IOLH12						(PFC_BASE + 0x1090)	/* IOLH switch register */
#define PFC_IOLH13						(PFC_BASE + 0x1098)	/* IOLH switch register */
#define PFC_IOLH14						(PFC_BASE + 0x10A0)	/* IOLH switch register */
#define PFC_IOLH15						(PFC_BASE + 0x10A8)	/* IOLH switch register */
#define PFC_IOLH16						(PFC_BASE + 0x10B0)	/* IOLH switch register */
#define PFC_IOLH17						(PFC_BASE + 0x10B8)	/* IOLH switch register */
#define PFC_IOLH18						(PFC_BASE + 0x10C0)	/* IOLH switch register */
#define PFC_IOLH19						(PFC_BASE + 0x10C8)	/* IOLH switch register */
#define PFC_IOLH1A						(PFC_BASE + 0x10D0)	/* IOLH switch register */
#define PFC_IOLH1B						(PFC_BASE + 0x10D8)	/* IOLH switch register */
#define PFC_IOLH1C						(PFC_BASE + 0x10E0)	/* IOLH switch register */
#define PFC_IOLH1D						(PFC_BASE + 0x10E8)	/* IOLH switch register */
#define PFC_IOLH1E						(PFC_BASE + 0x10F0)	/* IOLH switch register */
#define PFC_IOLH1F						(PFC_BASE + 0x10F8)	/* IOLH switch register */
#define PFC_IOLH20						(PFC_BASE + 0x1100)	/* IOLH switch register */
#define PFC_IOLH21						(PFC_BASE + 0x1108)	/* IOLH switch register */
#define PFC_IOLH22						(PFC_BASE + 0x1120)	/* IOLH switch register */
#define PFC_IOLH23						(PFC_BASE + 0x1128)	/* IOLH switch register */
#define PFC_IOLH36						(PFC_BASE + 0x11B0)	/* IOLH switch register */
#define PFC_IOLH37						(PFC_BASE + 0x11B8)	/* IOLH switch register */
#define PFC_IOLH38						(PFC_BASE + 0x11C0)	/* IOLH switch register */
#define PFC_IOLH39						(PFC_BASE + 0x11C8)	/* IOLH switch register */
#define PFC_IOLH3A						(PFC_BASE + 0x11D0)	/* IOLH switch register */
#define PFC_IOLH3B						(PFC_BASE + 0x11D8)	/* IOLH switch register */
#define PFC_IOLH3C						(PFC_BASE + 0x11E0)	/* IOLH switch register */
#define PFC_IOLH3D						(PFC_BASE + 0x11E8)	/* IOLH switch register */
#define PFC_IOLH3E						(PFC_BASE + 0x11F0)	/* IOLH switch register */
#define PFC_IOLH3F						(PFC_BASE + 0x11F8)	/* IOLH switch register */
#define PFC_IOLH40						(PFC_BASE + 0x1200)	/* IOLH switch register */
#define PFC_SR06						(PFC_BASE + 0x1430)	/* Slew-Rate switch register */
#define PFC_SR07						(PFC_BASE + 0x1438)	/* Slew-Rate switch register */
#define PFC_SR08						(PFC_BASE + 0x1440)	/* Slew-Rate switch register */
#define PFC_SR09						(PFC_BASE + 0x1448)	/* Slew-Rate switch register */
#define PFC_SR0A						(PFC_BASE + 0x1450)	/* Slew-Rate switch register */
#define PFC_SR0B						(PFC_BASE + 0x1458)	/* Slew-Rate switch register */
#define PFC_SR0C						(PFC_BASE + 0x1460)	/* Slew-Rate switch register */
#define PFC_SR10						(PFC_BASE + 0x1480)	/* Slew-Rate switch register */
#define PFC_SR15						(PFC_BASE + 0x14A8)	/* Slew-Rate switch register */
#define PFC_SR16						(PFC_BASE + 0x14B0)	/* Slew-Rate switch register */
#define PFC_SR18						(PFC_BASE + 0x14C0)	/* Slew-Rate switch register */
#define PFC_SR1B						(PFC_BASE + 0x14D8)	/* Slew-Rate switch register */
#define PFC_SR1C						(PFC_BASE + 0x14E0)	/* Slew-Rate switch register */
#define PFC_SR1D						(PFC_BASE + 0x14E8)	/* Slew-Rate switch register */
#define PFC_SR1E						(PFC_BASE + 0x14F0)	/* Slew-Rate switch register */
#define PFC_SR1F						(PFC_BASE + 0x14F8)	/* Slew-Rate switch register */
#define PFC_SR20						(PFC_BASE + 0x1500)	/* Slew-Rate switch register */
#define PFC_SR21						(PFC_BASE + 0x1508)	/* Slew-Rate switch register */
#define PFC_SR22						(PFC_BASE + 0x1510)	/* Slew-Rate switch register */
#define PFC_SR23						(PFC_BASE + 0x1518)	/* Slew-Rate switch register */
#define PFC_SR36						(PFC_BASE + 0x15B0)	/* Slew-Rate switch register */
#define PFC_SR37						(PFC_BASE + 0x15B8)	/* Slew-Rate switch register */
#define PFC_IEN06						(PFC_BASE + 0x1830)	/* IEN switch register */
#define PFC_IEN07						(PFC_BASE + 0x1838)	/* IEN switch register */
#define PFC_IEN08						(PFC_BASE + 0x1840)	/* IEN switch register */
#define PFC_IEN09						(PFC_BASE + 0x1848)	/* IEN switch register */
#define PFC_IEN0E						(PFC_BASE + 0x1870)	/* IEN switch register */
#define PFC_PUPD06						(PFC_BASE + 0x1C30)	/* PU/PD switch register */
#define PFC_PUPD07						(PFC_BASE + 0x1C38)	/* PU/PD switch register */
#define PFC_PUPD08						(PFC_BASE + 0x1C40)	/* PU/PD switch register */
#define PFC_PUPD09						(PFC_BASE + 0x1C48)	/* PU/PD switch register */
#define PFC_PUPD0A						(PFC_BASE + 0x1C50)	/* PU/PD switch register */
#define PFC_PUPD0B						(PFC_BASE + 0x1C58)	/* PU/PD switch register */
#define PFC_PUPD0C						(PFC_BASE + 0x1C60)	/* PU/PD switch register */
#define PFC_PUPD10						(PFC_BASE + 0x1C80)	/* PU/PD switch register */
#define PFC_PUPD15						(PFC_BASE + 0x1CA8)	/* PU/PD switch register */
#define PFC_PUPD16						(PFC_BASE + 0x1CB0)	/* PU/PD switch register */
#define PFC_PUPD18						(PFC_BASE + 0x1CC0)	/* PU/PD switch register */
#define PFC_PUPD1B						(PFC_BASE + 0x1CD8)	/* PU/PD switch register */
#define PFC_PUPD1C						(PFC_BASE + 0x1CE0)	/* PU/PD switch register */
#define PFC_PUPD1D						(PFC_BASE + 0x1CE8)	/* PU/PD switch register */
#define PFC_PUPD1E						(PFC_BASE + 0x1CF0)	/* PU/PD switch register */
#define PFC_PUPD1F						(PFC_BASE + 0x1CF8)	/* PU/PD switch register */
#define PFC_PUPD20						(PFC_BASE + 0x1D00)	/* PU/PD switch register */
#define PFC_PUPD21						(PFC_BASE + 0x1D08)	/* PU/PD switch register */
#define PFC_PUPD22						(PFC_BASE + 0x1D10)	/* PU/PD switch register */
#define PFC_PUPD23						(PFC_BASE + 0x1D18)	/* PU/PD switch register */
#define PFC_PUPD36						(PFC_BASE + 0x1DB0)	/* PU/PD switch register */
#define PFC_PUPD37						(PFC_BASE + 0x1DB8)	/* PU/PD switch register */
#define PFC_SD_ch0						(PFC_BASE + 0x3000)	/* SD ch0 IO voltage control register */
#define PFC_SD_ch1						(PFC_BASE + 0x3004)	/* SD ch1 IO voltage control register */
#define PFC_QSPI						(PFC_BASE + 0x3008)	/* QSPI IO voltage control register */
#define PFC_ETH_ch0						(PFC_BASE + 0x300C)	/* ETH ch0 voltage control register */
#define PFC_ETH_ch1						(PFC_BASE + 0x3010)	/* ETH ch1 voltage control register */
#define PFC_PWPR						(PFC_BASE + 0x3014)	/* Write protect */
#define PFC_FILONOFF01					(PFC_BASE + 0x2008)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF10					(PFC_BASE + 0x2080)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF11					(PFC_BASE + 0x2088)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF12					(PFC_BASE + 0x2090)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF13					(PFC_BASE + 0x2098)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF14					(PFC_BASE + 0x20A0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF15					(PFC_BASE + 0x20A8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF16					(PFC_BASE + 0x20B0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF17					(PFC_BASE + 0x20B8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF18					(PFC_BASE + 0x20C0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF19					(PFC_BASE + 0x20C8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1A					(PFC_BASE + 0x20D0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1B					(PFC_BASE + 0x20D8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1C					(PFC_BASE + 0x20E0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1D					(PFC_BASE + 0x20E8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1E					(PFC_BASE + 0x20F0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF1F					(PFC_BASE + 0x20F8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF20					(PFC_BASE + 0x2100)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF21					(PFC_BASE + 0x2108)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF22					(PFC_BASE + 0x2110)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF23					(PFC_BASE + 0x2118)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF24					(PFC_BASE + 0x2120)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF25					(PFC_BASE + 0x2128)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF26					(PFC_BASE + 0x2130)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF27					(PFC_BASE + 0x2138)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF28					(PFC_BASE + 0x2140)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF29					(PFC_BASE + 0x2148)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2A					(PFC_BASE + 0x2150)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2B					(PFC_BASE + 0x2158)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2C					(PFC_BASE + 0x2160)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2D					(PFC_BASE + 0x2168)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2E					(PFC_BASE + 0x2170)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF2F					(PFC_BASE + 0x2178)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF30					(PFC_BASE + 0x2180)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF31					(PFC_BASE + 0x2188)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF32					(PFC_BASE + 0x2190)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF33					(PFC_BASE + 0x2198)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF34					(PFC_BASE + 0x21A0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF35					(PFC_BASE + 0x21A8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF36					(PFC_BASE + 0x21B0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF37					(PFC_BASE + 0x21B8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF38					(PFC_BASE + 0x21C0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF39					(PFC_BASE + 0x21C8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3A					(PFC_BASE + 0x21D0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3B					(PFC_BASE + 0x21D8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3C					(PFC_BASE + 0x21E0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3D					(PFC_BASE + 0x21E8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3E					(PFC_BASE + 0x21F0)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF3F					(PFC_BASE + 0x21F8)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILONOFF40					(PFC_BASE + 0x2200)	/* Digital noise filter (FILONOFF) register */
#define PFC_FILNUM01					(PFC_BASE + 0x2408)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM10					(PFC_BASE + 0x2480)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM11					(PFC_BASE + 0x2488)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM12					(PFC_BASE + 0x2490)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM13					(PFC_BASE + 0x2498)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM14					(PFC_BASE + 0x24A0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM15					(PFC_BASE + 0x24A8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM16					(PFC_BASE + 0x24B0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM17					(PFC_BASE + 0x24B8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM18					(PFC_BASE + 0x24C0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM19					(PFC_BASE + 0x24C8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1A					(PFC_BASE + 0x24D0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1B					(PFC_BASE + 0x24D8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1C					(PFC_BASE + 0x24E0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1D					(PFC_BASE + 0x24E8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1E					(PFC_BASE + 0x24F0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM1F					(PFC_BASE + 0x24F8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM20					(PFC_BASE + 0x2500)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM21					(PFC_BASE + 0x2508)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM22					(PFC_BASE + 0x2510)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM23					(PFC_BASE + 0x2518)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM24					(PFC_BASE + 0x2520)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM25					(PFC_BASE + 0x2528)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM26					(PFC_BASE + 0x2530)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM27					(PFC_BASE + 0x2538)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM28					(PFC_BASE + 0x2540)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM29					(PFC_BASE + 0x2548)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2A					(PFC_BASE + 0x2550)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2B					(PFC_BASE + 0x2558)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2C					(PFC_BASE + 0x2560)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2D					(PFC_BASE + 0x2568)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2E					(PFC_BASE + 0x2570)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM2F					(PFC_BASE + 0x2578)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM30					(PFC_BASE + 0x2580)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM31					(PFC_BASE + 0x2588)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM32					(PFC_BASE + 0x2590)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM33					(PFC_BASE + 0x2598)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM34					(PFC_BASE + 0x25A0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM35					(PFC_BASE + 0x25A8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM36					(PFC_BASE + 0x25B0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM37					(PFC_BASE + 0x25B8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM38					(PFC_BASE + 0x25C0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM39					(PFC_BASE + 0x25C8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3A					(PFC_BASE + 0x25D0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3B					(PFC_BASE + 0x25D8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3C					(PFC_BASE + 0x25E0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3D					(PFC_BASE + 0x25E8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3E					(PFC_BASE + 0x25F0)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM3F					(PFC_BASE + 0x25F8)	/* Digital noise filter (FILNUM) register */
#define PFC_FILNUM40					(PFC_BASE + 0x2600)	/* Digital noise filter (FILNUM) register */
#define PFC_FILCLKSEL01					(PFC_BASE + 0x2808)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL10					(PFC_BASE + 0x2880)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL11					(PFC_BASE + 0x2888)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL12					(PFC_BASE + 0x2890)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL13					(PFC_BASE + 0x2898)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL14					(PFC_BASE + 0x28A0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL15					(PFC_BASE + 0x28A8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL16					(PFC_BASE + 0x28B0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL17					(PFC_BASE + 0x28B8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL18					(PFC_BASE + 0x28C0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL19					(PFC_BASE + 0x28C8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1A					(PFC_BASE + 0x28D0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1B					(PFC_BASE + 0x28D8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1C					(PFC_BASE + 0x28E0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1D					(PFC_BASE + 0x28E8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1E					(PFC_BASE + 0x28F0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL1F					(PFC_BASE + 0x28F8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL20					(PFC_BASE + 0x2900)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL21					(PFC_BASE + 0x2908)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL22					(PFC_BASE + 0x2910)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL23					(PFC_BASE + 0x2918)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL24					(PFC_BASE + 0x2920)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL25					(PFC_BASE + 0x2928)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL26					(PFC_BASE + 0x2930)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL27					(PFC_BASE + 0x2938)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL28					(PFC_BASE + 0x2940)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL29					(PFC_BASE + 0x2948)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2A					(PFC_BASE + 0x2950)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2B					(PFC_BASE + 0x2958)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2C					(PFC_BASE + 0x2960)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2D					(PFC_BASE + 0x2968)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2E					(PFC_BASE + 0x2970)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL2F					(PFC_BASE + 0x2978)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL30					(PFC_BASE + 0x2980)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL31					(PFC_BASE + 0x2988)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL32					(PFC_BASE + 0x2990)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL33					(PFC_BASE + 0x2998)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL34					(PFC_BASE + 0x29A0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL35					(PFC_BASE + 0x29A8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL36					(PFC_BASE + 0x29B0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL37					(PFC_BASE + 0x29B8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL38					(PFC_BASE + 0x29C0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL39					(PFC_BASE + 0x29C8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3A					(PFC_BASE + 0x29D0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3B					(PFC_BASE + 0x29D8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3C					(PFC_BASE + 0x29E0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3D					(PFC_BASE + 0x29E8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3E					(PFC_BASE + 0x29F0)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL3F					(PFC_BASE + 0x29F8)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_FILCLKSEL40					(PFC_BASE + 0x2A00)	/* Digital noise filter (FILCLKSEL) register */
#define PFC_ETH_MII						(PFC_BASE + 0x3018)	/* Register for setting the mode of ETH MII / RGMII */

/* Combined terminal setting */
/* Definition for port register */
#define P_P0				(1 << 0)
#define P_P1				(1 << 1)
#define P_P2				(1 << 2)
#define P_P3				(1 << 3)
#define P_P4				(1 << 4)
#define P_P5				(1 << 5)
#define P_P6				(1 << 6)
#define P_P7				(1 << 7)
/* Definition for port mode register */
#define PM0_HIZ				(0 << 0)
#define PM0_IN				(1 << 0)
#define PM0_OUT_DIS			(2 << 0)
#define PM0_OUT_EN			(3 << 0)
#define PM1_HIZ				(0 << 2)
#define PM1_IN				(1 << 2)
#define PM1_OUT_DIS			(2 << 2)
#define PM1_OUT_EN			(3 << 2)
#define PM2_HIZ				(0 << 4)
#define PM2_IN				(1 << 4)
#define PM2_OUT_DIS			(2 << 4)
#define PM2_OUT_EN			(3 << 4)
#define PM3_HIZ				(0 << 6)
#define PM3_IN				(1 << 6)
#define PM3_OUT_DIS			(2 << 6)
#define PM3_OUT_EN			(3 << 6)
#define PM4_HIZ				(0 << 8)
#define PM4_IN				(1 << 8)
#define PM4_OUT_DIS			(2 << 8)
#define PM4_OUT_EN			(3 << 8)
/* Definition for port mode control register */
#define PMC_PMC0			(1 << 0)
#define PMC_PMC1			(1 << 1)
#define PMC_PMC2			(1 << 2)
#define PMC_PMC3			(1 << 3)
#define PMC_PMC4			(1 << 4)
#define PMC_PMC5			(1 << 5)
#define PMC_PMC6			(1 << 6)
#define PMC_PMC7			(1 << 7)
/* Definition for port function control register */
#define PFC0_MODE0			(0 << 0)
#define PFC0_MODE1			(1 << 0)
#define PFC0_MODE2			(2 << 0)
#define PFC0_MODE3			(3 << 0)
#define PFC0_MODE4			(4 << 0)
#define PFC0_MODE5			(5 << 0)
#define PFC1_MODE0			(0 << 4)
#define PFC1_MODE1			(1 << 4)
#define PFC1_MODE2			(2 << 4)
#define PFC1_MODE3			(3 << 4)
#define PFC1_MODE4			(4 << 4)
#define PFC1_MODE5			(5 << 4)
#define PFC2_MODE0			(0 << 8)
#define PFC2_MODE1			(1 << 8)
#define PFC2_MODE2			(2 << 8)
#define PFC2_MODE3			(3 << 8)
#define PFC2_MODE4			(4 << 8)
#define PFC2_MODE5			(5 << 8)
#define PFC3_MODE0			(0 << 12)
#define PFC3_MODE1			(1 << 12)
#define PFC3_MODE2			(2 << 12)
#define PFC3_MODE3			(3 << 12)
#define PFC3_MODE4			(4 << 12)
#define PFC3_MODE5			(5 << 12)
#define PFC4_MODE0			(0 << 16)
#define PFC4_MODE1			(1 << 16)
#define PFC4_MODE2			(2 << 16)
#define PFC4_MODE3			(3 << 16)
#define PFC4_MODE4			(4 << 16)
#define PFC4_MODE5			(5 << 16)
/* Definition for IOLH switch register */
#define IOLH0_2MA			(0 << 0)
#define IOLH0_4MA			(1 << 0)
#define IOLH0_8MA			(2 << 0)
#define IOLH0_12MA			(3 << 0)
#define IOLH1_2MA			(0 << 8)
#define IOLH1_4MA			(1 << 8)
#define IOLH1_8MA			(2 << 8)
#define IOLH1_12MA			(3 << 8)
#define IOLH2_2MA			(0 << 16)
#define IOLH2_4MA			(1 << 16)
#define IOLH2_8MA			(2 << 16)
#define IOLH2_12MA			(3 << 16)
#define IOLH3_2MA			(0 << 24)
#define IOLH3_4MA			(1 << 24)
#define IOLH3_8MA			(2 << 24)
#define IOLH3_12MA			(3 << 24)
#define IOLH4_2MA			(0 << 32)
#define IOLH4_4MA			(1 << 32)
#define IOLH4_8MA			(2 << 32)
#define IOLH4_12MA			(3 << 32)
#define IOLH5_2MA			(0 << 40)
#define IOLH5_4MA			(1 << 40)
#define IOLH5_8MA			(2 << 40)
#define IOLH5_12MA			(3 << 40)
#define IOLH6_2MA			(0 << 48)
#define IOLH6_4MA			(1 << 48)
#define IOLH6_8MA			(2 << 48)
#define IOLH6_12MA			(3 << 48)
#define IOLH7_2MA			(0 << 56)
#define IOLH7_4MA			(1 << 56)
#define IOLH7_8MA			(2 << 56)
#define IOLH7_12MA			(3 << 56)
/* Definition for Slew-Rate switch register */
#define SR0_FAST			(1 << 0)
#define SR1_FAST			(1 << 8)
#define SR2_FAST			(1 << 16)
#define SR3_FAST			(1 << 24)
#define SR4_FAST			(1 << 32)
#define SR5_FAST			(1 << 40)
#define SR6_FAST			(1 << 48)
#define SR7_FAST			(1 << 56)
/* Definition for IEN switching register */
#define IEN0_ENABLE			(1 << 0)
#define IEN1_ENABLE			(1 << 8)
#define IEN2_ENABLE			(1 << 16)
#define IEN3_ENABLE			(1 << 24)
#define IEN4_ENABLE			(1 << 32)
#define IEN5_ENABLE			(1 << 40)
#define IEN6_ENABLE			(1 << 48)
#define IEN7_ENABLE			(1 << 56)
/* Definition for PUPD switching register */
#define PUPD0_NO			(0 << 0)
#define PUPD0_UP			(1 << 0)
#define PUPD0_DOWN			(2 << 0)
#define PUPD1_NO			(0 << 8)
#define PUPD1_UP			(1 << 8)
#define PUPD1_DOWN			(2 << 8)
#define PUPD2_NO			(0 << 16)
#define PUPD2_UP			(1 << 16)
#define PUPD2_DOWN			(2 << 16)
#define PUPD3_NO			(0 << 24)
#define PUPD3_UP			(1 << 24)
#define PUPD3_DOWN			(2 << 24)
#define PUPD4_NO			(0 << 32)
#define PUPD4_UP			(1 << 32)
#define PUPD4_DOWN			(2 << 32)
#define PUPD5_NO			(0 << 40)
#define PUPD5_UP			(1 << 40)
#define PUPD5_DOWN			(2 << 40)
#define PUPD6_NO			(0 << 48)
#define PUPD6_UP			(1 << 48)
#define PUPD6_DOWN			(2 << 48)
#define PUPD7_NO			(0 << 56)
#define PUPD7_UP			(1 << 56)
#define PUPD7_DOWN			(2 << 56)
/* SD ch0 IO Definition for voltage control register */
#define SD0_PVDD			(1 << 0)
/* SD ch1 IO Definition for voltage control register */
#define SD1_PVDD			(1 << 0)
/* Definition for QSPI IO voltage control register */
#define QSPI_PVDD			(1 << 0)
/* ETH ch0 voltage control register */
#define ETH_ch0_3_3			(0 << 0)
#define ETH_ch0_1_8			(1 << 0)
#define ETH_ch0_2_5			(2 << 0)
/* ETH ch1 voltage control register */
#define ETH_ch1_3_3			(0 << 0)
#define ETH_ch1_1_8			(1 << 0)
#define ETH_ch1_2_5			(2 << 0)
/* Write protection definition */
#define PWPR_B0Wl			(1 << 7)
#define PWPR_PFCWE			(1 << 6)
/* Digital noise filter (FILONOFF) register */
#define FILONOFF_FILON0		(1 << 0)
#define FILONOFF_FILON1		(1 << 8)
#define FILONOFF_FILON2		(1 << 16)
#define FILONOFF_FILON3		(1 << 24)
#define FILONOFF_FILON4		(1 << 32)
#define FILONOFF_FILON5		(1 << 40)
#define FILONOFF_FILON6		(1 << 48)
#define FILONOFF_FILON7		(1 << 56)
/* Digital noise filter (FILNUM) register */
#define FILNUM_FILNUM0_4	(0 << 0)
#define FILNUM_FILNUM0_8	(1 << 0)
#define FILNUM_FILNUM0_12	(2 << 0)
#define FILNUM_FILNUM0_16	(3 << 0)
#define FILNUM_FILNUM1_4	(0 << 8)
#define FILNUM_FILNUM1_8	(1 << 8)
#define FILNUM_FILNUM1_12	(2 << 8)
#define FILNUM_FILNUM1_16	(3 << 8)
#define FILNUM_FILNUM2_4	(0 << 16)
#define FILNUM_FILNUM2_8	(1 << 16)
#define FILNUM_FILNUM2_12	(2 << 16)
#define FILNUM_FILNUM2_16	(3 << 16)
#define FILNUM_FILNUM3_4	(0 << 24)
#define FILNUM_FILNUM3_8	(1 << 24)
#define FILNUM_FILNUM3_12	(2 << 24)
#define FILNUM_FILNUM3_16	(3 << 24)
#define FILNUM_FILNUM4_4	(0 << 32)
#define FILNUM_FILNUM4_8	(1 << 32)
#define FILNUM_FILNUM4_12	(2 << 32)
#define FILNUM_FILNUM4_16	(3 << 32)
#define FILNUM_FILNUM5_4	(0 << 40)
#define FILNUM_FILNUM5_8	(1 << 40)
#define FILNUM_FILNUM5_12	(2 << 40)
#define FILNUM_FILNUM5_16	(3 << 40)
#define FILNUM_FILNUM6_4	(0 << 48)
#define FILNUM_FILNUM6_8	(1 << 48)
#define FILNUM_FILNUM6_12	(2 << 48)
#define FILNUM_FILNUM6_16	(3 << 48)
#define FILNUM_FILNUM7_4	(0 << 56)
#define FILNUM_FILNUM7_8	(1 << 56)
#define FILNUM_FILNUM7_12	(2 << 56)
#define FILNUM_FILNUM7_16	(3 << 56)
/* Digital noise filter (FILCLKSEL) register */
#define FILCLKSEL_FILCLK0_0	(0 << 0)
#define FILCLKSEL_FILCLK0_1	(1 << 0)
#define FILCLKSEL_FILCLK0_2	(2 << 0)
#define FILCLKSEL_FILCLK0_3	(3 << 0)
#define FILCLKSEL_FILCLK1_0	(0 << 8)
#define FILCLKSEL_FILCLK1_1	(1 << 8)
#define FILCLKSEL_FILCLK1_2	(2 << 8)
#define FILCLKSEL_FILCLK1_3	(3 << 8)
#define FILCLKSEL_FILCLK2_0	(0 << 16)
#define FILCLKSEL_FILCLK2_1	(1 << 16)
#define FILCLKSEL_FILCLK2_2	(2 << 16)
#define FILCLKSEL_FILCLK2_3	(3 << 16)
#define FILCLKSEL_FILCLK3_0	(0 << 24)
#define FILCLKSEL_FILCLK3_1	(1 << 24)
#define FILCLKSEL_FILCLK3_2	(2 << 24)
#define FILCLKSEL_FILCLK3_3	(3 << 24)
#define FILCLKSEL_FILCLK4_0	(0 << 32)
#define FILCLKSEL_FILCLK4_1	(1 << 32)
#define FILCLKSEL_FILCLK4_2	(2 << 32)
#define FILCLKSEL_FILCLK4_3	(3 << 32)
#define FILCLKSEL_FILCLK5_0	(0 << 40)
#define FILCLKSEL_FILCLK5_1	(1 << 40)
#define FILCLKSEL_FILCLK5_2	(2 << 40)
#define FILCLKSEL_FILCLK5_3	(3 << 40)
#define FILCLKSEL_FILCLK6_0	(0 << 48)
#define FILCLKSEL_FILCLK6_1	(1 << 48)
#define FILCLKSEL_FILCLK6_2	(2 << 48)
#define FILCLKSEL_FILCLK6_3	(3 << 48)
#define FILCLKSEL_FILCLK7_0	(0 << 56)
#define FILCLKSEL_FILCLK7_1	(1 << 56)
#define FILCLKSEL_FILCLK7_2	(2 << 56)
#define FILCLKSEL_FILCLK7_3	(3 << 56)
/* Register for setting the mode of ETH MII / RGMII */
#define ETH_MII_0_MII		(1 << 0)
#define ETH_MII_1_MII		(1 << 1)

#define	PFC_SET_TBL_NUM		(11)
#define	PFC_OFF				(0)
#define PFC_ON				(1)

#define PFC_SCIF_TBL_NUM	(1)
#define PFC_QSPI_TBL_NUM	(2)
#define PFC_SD_TBL_NUM		(5)

typedef struct {
	int			flg;
	uintptr_t	reg;
	uint8_t		val;
} PFC_REG_UINT8;

typedef struct {
	int			flg;
	uintptr_t	reg;
	uint32_t	val;
} PFC_REG_UINT32;

typedef struct {
	int			flg;
	uintptr_t	reg;
	uint64_t	val;
} PFC_REG_UINT64;


typedef struct {
	PFC_REG_UINT8	pmc;
	PFC_REG_UINT32	pfc;
	PFC_REG_UINT64	iolh;
	PFC_REG_UINT64	pupd;
	PFC_REG_UINT64	sr;
	PFC_REG_UINT64	ien;
} PFC_REGS;

#endif	/* __RZF_DEV_PFC_REGS_H__ */

