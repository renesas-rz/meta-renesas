/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/*
 * This header provides constants for Renesas RZ/G2L family pinctrl bindings.
 *
 * Copyright (C) 2023 Renesas Electronics Corp.
 *
 */

#ifndef __DT_BINDINGS_RZG2L_PINCTRL_H
#define __DT_BINDINGS_RZG2L_PINCTRL_H

#define RZG2L_PINS_PER_PORT	8

/*
 * Store the pin index from its port and position number in bits[15-0].
 * And store its peripheral function mode identifier in 3 bits [18-16].
 * This macro is used in Linux device drivers
 */
#define RZG2L_PORT_PINMUX(b, p, f)	((b) * RZG2L_PINS_PER_PORT + (p) | ((f) << 16))

/* Convert a port and pin label to its global pin index */
 #define RZG2L_GPIO(port, pin)	((port) * RZG2L_PINS_PER_PORT + (pin))

/*
 * Store the pin index from its port and position number in bits[11-0].
 * And store its peripheral function mode identifier in 3 bits [14-12]
 */
#define RZG2L_PINMUX(port, pos, func)	\
	(((port) * RZG2L_PINS_PER_PORT + (pos)) | ((func) << 12))

#endif /* __DT_BINDINGS_RZG2L_PINCTRL_H */
