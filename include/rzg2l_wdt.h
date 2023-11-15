/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef _RZG2L_WDT_
#define _RZG2L_WDT_

#define RZG2L_WDT_FLAG_WRITE_TO_ENV    (1 << 0)
#define RZG2L_WDT_FLAG_TIMEOUT_CHECKED (1 << 1)

int rzg2l_reinitr_wdt(void);

#endif
