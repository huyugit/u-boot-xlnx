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
#include <asm-generic/gpio.h>

#define LED_RED_ON "gpio set 37"
#define LED_GREEN_ON "gpio set 38"
#define LED_RED_OFF "gpio clear 37"
#define LED_GREEN_OFF "gpio clear 38"

// driver/gpio/dm_gpio.c
/*
extern int dm_gpio_getkey_ipset(void);
extern void dm_gpio_setled_green(int);
extern void dm_gpio_setled_red(int);

extern void Zynq_SetDirectionPin(u32 Pin, u32 Direction);
extern void Zynq_SetOutputEnablePin(u32 Pin, u32 OpEnable);
extern void Zynq_GpioInitialize();
extern void Zynq_WritePin(u32 Pin, u32 Data);
extern u32 Zynq_ReadPin( u32 Pin);

extern u32 Zynq_GetDirectionPin(u32 Pin);
extern u32 Zynq_GetOutputEnablePin( u32 Pin);
*/
extern int gpio_direction_output(unsigned gpio, int value);
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

    int i = 0;

	run_command_list(LED_RED_ON, -1, 0);
	run_command_list(LED_GREEN_ON, -1, 0);
	mdelay(500);

	if(!dm_check_update_condition())
	{
		return;
	}
	run_command_list(LED_RED_OFF, -1, 0);
	run_command_list(LED_GREEN_OFF, -1, 0);

	mdelay(500);
	run_command_list(LED_GREEN_ON, -1, 0);


	printf("****************** update start ********************** \n");
	

	printf("cmd >>> %s \n", UPDATE_CMD);
	run_command_list(UPDATE_CMD, -1, 0);

	
	printf("****************** update finshed ********************** \n");


	while(i<10)
	{
		run_command_list(LED_GREEN_OFF, -1, 0);

		mdelay(500);
		run_command_list(LED_GREEN_ON, -1, 0);
		mdelay(500);
        i++;
	}
	printf("auto start from nand...\n");
    run_command_list("run nandboot", -1, 0);
}

