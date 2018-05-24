/*
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Configuration settings for the Xilinx Zynq ZC702 and ZC706 boards
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_ZC70X_H
#define __CONFIG_ZYNQ_ZC70X_H

#define CONFIG_ZYNQ_I2C0
#define CONFIG_ZYNQ_EEPROM

#define CONFIG_CMD_UBI
#define CONFIG_RBTREE
#define CONFIG_CMD_UBIFS
#define CONFIG_LZO

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS

#define CONFIG_SYS_MAX_FLASH_BANKS 1

#define CONFIG_MTD_UBI_WL_THRESHOLD 4096
#define CONFIG_MTD_UBI_BEB_LIMIT 0

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_ZC70X_H */
