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

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttyPS0,115200\0" \
	"mtdids=nand0=nand0\0" \
	"mtdparts=mtdparts=nand0:0x400000@0x0(bootloader),0x400000@0x80000(env),0x480000@0x80000(dtb-main),0x500000@0x80000(dtb-alt),0x580000@0x400000(fpga-main),0x980000@0x400000(fpga-alt),0xd80000@0x500000(kernel-main),0x1280000@0x500000(kernel-alt),0x1780000@0xba80000(rootfs-main),0xd200000@0xa00000(config)\0" \
	"mmc_fat_num=0\0" \
	"boot_copy_ram_address=0x2000000\0" \
	"boot_image=BOOT.bin\0" \
	"boot_nand_address=0x0\0" \
	"boot_size=0x400000\0" \
	"env_nand_address=0x400000\0" \
	"env_size=0x80000\0" \
	"devicetree_image=devicetree.dtb\0" \
	"devicetree_load_address=0x2000000\0" \
	"devicetree0_nand_address=0x480000\0" \
	"devicetree1_nand_address=0x500000\0" \
	"devicetree_size=0x80000\0" \
	"fpga_image=system.bit\0" \
	"fpga_load_address=0x400000\0" \
	"fpga0_nand_address=0x580000\0" \
	"fpga1_nand_address=0x980000\0" \
	"fpga_size=0x400000\0" \
	"kernel_image=uImage\0" \
	"kernel_load_address=0x2080000\0" \
	"kernel0_nand_address=0xd80000\0" \
	"kernel1_nand_address=0x1280000\0" \
	"kernel_size=0x500000\0" \
	"image_flag=0\0" \
	"rootfs_image=rootfs.ubi\0" \
	"rootfs0_nand_address=0x1780000\0" \
	"rootfs1_nand_address=0x74c0000\0" \
	/*"rootfs_size=0x5d40000\0" */\
        "rootfs_size=0xba80000\0" \
 	"configfs_image=config.ubi\0" \
 	"configfs_nand_address=0xd200000\0" \
 	"configfs_size=0xa00000\0" \
	"nandboot=echo Booting from NAND... && " \
			 "if test $image_flag = 0; then " \
				 "echo image_0 && " \
				 "nand read ${fpga_load_address} ${fpga0_nand_address} ${fpga_size} && fpga loadb 0 ${fpga_load_address} ${fpga_size} && " \
                                 "nand read ${devicetree_load_address} ${devicetree0_nand_address} ${devicetree_size} && " \
				 "nand read ${kernel_load_address} ${kernel0_nand_address} ${kernel_size} && " \
				 "bootm ${kernel_load_address} - ${devicetree_load_address}; " \
			 "fi; " \
			 "if test $image_flag = 1; then " \
				 "echo image_1 && " \
				 "nand read ${fpga_load_address} ${fpga1_nand_address} ${fpga_size} && fpga loadb 0 ${fpga_load_address} ${fpga_size} && " \
				 "setenv bootargs console=ttyPS0,115200 noinitrd root=ubi0:rootfs ro ubi.mtd=9 earlyprintk rootfstype=ubifs rootwait && saveenv && " \
				 "nand read ${devicetree_load_address} ${devicetree1_nand_address} ${devicetree_size} && " \
				 "nand read ${kernel_load_address} ${kernel1_nand_address} ${kernel_size} && " \
				 "bootm ${kernel_load_address} - ${devicetree_load_address}; " \
			 "fi\0" \
	"bootenv=uEnv.txt\0" \
	"sdboot=echo Booting from SdCard... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${bootenv} && " \
		   "env import -t ${boot_copy_ram_address} $filesize && " \
		   "fatload mmc ${mmc_fat_num} ${fpga_load_address} ${fpga_image} && " \
		   "fpga loadb 0 ${fpga_load_address} ${fpga_size} && " \
		   "fatload mmc ${mmc_fat_num} ${devicetree_load_address} ${devicetree_image} && " \
		   "fatload mmc ${mmc_fat_num} ${kernel_load_address} ${kernel_image} && " \
		   "bootm ${kernel_load_address} - ${devicetree_load_address};\0" \
	"update=echo runing nand update... && " \
                   "echo erase nand for needed... && " \
		   "echo Updating ${boot_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${boot_image} && " \
                   "nand erase ${boot_nand_address} ${boot_size} && " \
		   "nand write ${boot_copy_ram_address} ${boot_nand_address} ${boot_size} && " \
		   "echo " \
		   "echo Saving env... && " \
		   "saveenv && " \
		   "echo " \
		   "echo Updating ${devicetree_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${devicetree_image} && " \
                   "nand erase ${devicetree0_nand_address} ${devicetree_size} && " \
		   "nand write ${boot_copy_ram_address} ${devicetree0_nand_address} ${devicetree_size} && " \
		   "echo " \
		   "echo Updating ${fpga_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${fpga_image} && " \
		   "nand erase  ${fpga0_nand_address} ${fpga_size} && " \
		   "nand write ${boot_copy_ram_address} ${fpga0_nand_address} ${fpga_size} && " \
		   "echo " \
		   "echo Updating ${kernel_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${kernel_image} && " \
		   "nand erase ${kernel0_nand_address} ${kernel_size} && " \
		   "nand write ${boot_copy_ram_address} ${kernel0_nand_address} ${kernel_size} && " \
		   "echo " \
		   "echo Updating 0 ${rootfs_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${rootfs_image} && " \
		   "nand erase ${rootfs0_nand_address} ${filesize} && " \
		   "nand write.jffs2 ${boot_copy_ram_address} ${rootfs0_nand_address} $filesize && " \
		   "echo " \
 	           "echo Updating ${configfs_image}... && " \
 	           "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${configfs_image}  && " \
 	           "nand write ${boot_copy_ram_address} ${configfs_nand_address} ${configfs_size} && " \
		   "echo \0"
	"updateall=echo runing nand update... && " \
                   "echo erase nand for needed... && " \
                   "nand erase.chip && " \
		   "echo Updating ${boot_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${boot_image} && " \
                   "nand erase ${boot_nand_address} ${boot_size} && " \
		   "nand write ${boot_copy_ram_address} ${boot_nand_address} ${boot_size} && " \
		   "echo " \
		   "echo Saving env... && " \
		   "saveenv && " \
		   "echo " \
		   "echo Updating ${devicetree_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${devicetree_image} && " \
                   "nand erase ${devicetree0_nand_address} ${devicetree_size} && " \
		   "nand write ${boot_copy_ram_address} ${devicetree0_nand_address} ${devicetree_size} && " \
                   "nand erese ${devicetree1_nand_address} ${devicetree_size} && " \
		   "nand write ${boot_copy_ram_address} ${devicetree1_nand_address} ${devicetree_size} && " \
		   "echo " \
		   "echo Updating ${fpga_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${fpga_image} && " \
		   "nand erase  ${fpga0_nand_address} ${fpga_size} && " \
		   "nand write ${boot_copy_ram_address} ${fpga0_nand_address} ${fpga_size} && " \
		   "nand erase  ${fpga1_nand_address} ${fpga_size} && " \
		   "nand write ${boot_copy_ram_address} ${fpga1_nand_address} ${fpga_size} && " \
		   "echo " \
		   "echo Updating ${kernel_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${kernel_image} && " \
		   "nand erase ${kernel0_nand_address} ${kernel_size} && " \
		   "nand write ${boot_copy_ram_address} ${kernel0_nand_address} ${kernel_size} && " \
		   "nand erase ${kernel1_nand_address} ${kernel_size} && " \
		   "nand write ${boot_copy_ram_address} ${kernel1_nand_address} ${kernel_size} && " \
		   "echo " \
		   "echo Updating 0 ${rootfs_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${rootfs_image} && " \
		   "nand erase ${rootfs0_nand_address} ${filesize} && " \
		   "nand write.jffs2 ${boot_copy_ram_address} ${rootfs0_nand_address} $filesize && " \
		   "echo " \
		   /*"echo Updating 1 ${rootfs_image}... && " \
		   "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${rootfs_image} && " \
		   "nand erase ${rootfs1_nand_address} ${filesize} && " \
		   "nand write.jffs2 ${boot_copy_ram_address} ${rootfs1_nand_address} $filesize && " */\
 		   "echo " \
 	           "echo Updating ${configfs_image}... && " \
 	           "fatload mmc ${mmc_fat_num} ${boot_copy_ram_address} ${configfs_image}  && " \
 	           "nand write ${boot_copy_ram_address} ${configfs_nand_address} ${configfs_size} && " \
		   "echo \0"

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_ZC70X_H */
