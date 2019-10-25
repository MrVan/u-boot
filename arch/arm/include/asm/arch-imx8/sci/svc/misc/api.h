/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright 2018 NXP
 */

#ifndef SC_MISC_API_H
#define SC_MISC_API_H

/* Defines for sc_misc_boot_status_t */
#define SC_MISC_BOOT_STATUS_SUCCESS	0U	/* Success */
#define SC_MISC_BOOT_STATUS_SECURITY	1U	/* Security violation */

/* Defines for sc_misc_temp_t */
#define SC_MISC_TEMP			0U	/* Temp sensor */
#define SC_MISC_TEMP_HIGH		1U	/* Temp high alarm */
#define SC_MISC_TEMP_LOW		2U	/* Temp low alarm */

typedef u8 sc_misc_boot_status_t;
typedef u8 sc_misc_temp_t;

#endif /* SC_MISC_API_H */
