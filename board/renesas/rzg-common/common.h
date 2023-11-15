/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef __RZG_COMMON_H__
#define __RZG_COMMON_H__

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#endif

/* This SiP service command must be gotten from IPL document.*/
#define RZG_SIP_SVC_GET_ECC_MODE	(0x8200000F)

/*
 * The parameters must be defined with below requirement.
 * * The size must is multiply of 3.
 * * The list of char array with size is multiply of 3.
 *   Each 3 properties are present for:
 *       "FDT full path of Node", "Property", "Value of Property"
 * * If none of define "Property", "Node" will be deleted
 * * "Value of Property" will be:
 *   "<xxx yyy>":
 *       xxx, yyy: have '&' prefix, they are as phandle reference
 *       xxx, yyy: are number, otherwise won't be process
 *   "xxx yyy": They are processed as string
 */
int update_fdt(void *fdt, const char **list_dt_change, int size);
#endif //__RZG_COMMON_H__
