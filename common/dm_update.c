/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <autoboot.h>
#include <bootretry.h>
#include <cli.h>
#include <console.h>
#include <mmc.h>
#include <dm_update.h>

// driver/gpio/dm_gpio.c
extern int dm_gpio_getkey_ipset(void);
extern void dm_gpio_setled_green(int);
extern void dm_gpio_setled_red(int);

bool dm_check_update_condition(void)
{
	int i;
	struct mmc *mmc = NULL;

	
	mmc = find_mmc_device(0);
	if(mmc == NULL)
	{
		return false;
	}

	if(mmc_init(mmc) != 0)
	{
		return false;
	}

	for(i = 0; i < 10; i++)
	{
		mdelay(100);
		
       		if(dm_gpio_getkey_ipset())
		{
			return false;
		}
		//printf("ipset detect:%d\n",i);
	}
	
	return true;
}

void dm_auto_update_nand(void)
{
	#define UPDATE_CMD	"run update"
	
	if(!dm_check_update_condition())
	{
		return;
	}

	printf("****************** update start ********************** \n");
	
   	dm_gpio_setled_red(1);
	printf("cmd >>> %s \n", UPDATE_CMD);
	run_command_list(UPDATE_CMD, -1, 0);

	// light out red led
    dm_gpio_setled_red(0);
	
	printf("****************** update finshed ********************** \n");

	while(0)
	{
        dm_gpio_setled_green(1);
		mdelay(500);
        dm_gpio_setled_green(0);
		mdelay(500);
	}
        run_command_list("boot", -1, 0);

}

