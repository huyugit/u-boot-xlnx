/******************************************************************************
 * Copyright (c) 2005-2018 Innosilicon.
 * Filename:    dm_gpio.c
 * Author:      duanhao
 * Create:      20180103
 * Version:     1.0
 * Description: Dm gpio driver
 * Change Log:  Modified by zhangyh 20180411
 *******************************************************************************/

/************************************ Header ***********************************/
#include <common.h>

/************************************ Macros ***********************************/
#define DM_PERIPHERAL_BASE            (0x43C00000)
//#define DM_SPI_BASE                   (0x43c30000)
//#define DM_FAN_BASE                   (0x43C00000)

#define DM_PERIPHERAL_REG0_OFFSET     (0)
#define DM_PERIPHERAL_REG1_OFFSET     (4)
#define DM_PERIPHERAL_REG2_OFFSET     (8)
#define DM_PERIPHERAL_REG3_OFFSET     (12)
#define DM_PERIPHERAL_REG4_OFFSET     (16)
#define DM_PERIPHERAL_REG5_OFFSET     (20)
#define DM_PERIPHERAL_REG6_OFFSET     (24)
#define DM_PERIPHERAL_REG7_OFFSET     (28)
#define DM_PERIPHERAL_REG8_OFFSET     (32)
#define DM_PERIPHERAL_REG9_OFFSET     (36)
#define DM_PERIPHERAL_REG10_OFFSET    (40)

#define DM_KEY_IPSET_REG              (DM_PERIPHERAL_REG10_OFFSET)
#define DM_KEY_IPSET_BIT              (16)

#define DM_LED_GREEN_REG              (DM_PERIPHERAL_REG9_OFFSET)
#define DM_LED_GREEN_BIT              (9)

#define DM_LED_RED_REG                (DM_PERIPHERAL_REG9_OFFSET)
#define DM_LED_RED_BIT                (10)

/********************************* Global Defines ******************************/


/********************************** Prototypes *********************************/
static int dm_reg_read(u32 regaddr);

static void dm_reg_write(u32 regaddr, u32 regval);

/*********************************** Functions *********************************/
/*******************************************************************************
 * Name:        dm_reg_read
 * Description: read register
 * Input:       regaddr - physical address of the register
 * Output:      none
 * Return:      register value
 ******************************************************************************/
static int dm_reg_read(u32 regaddr)
{
    return *(volatile u32*) regaddr;  
}

/*******************************************************************************
 * Name:        dm_reg_write
 * Description: write register
 * Input:       regaddr - physical address of the register
 *              regval  - value to be set to the register
 * Output:      none
 * Return:      none
 ******************************************************************************/
static void dm_reg_write(u32 regaddr, u32 regval)
{
    *(volatile u32*) regaddr = regval; 
}

/*******************************************************************************
 * Name:        dm_gpio_getkey_ipset
 * Description: get the state of IPSET key
 * Input:       none
 * Output:      none
 * Return:      state of IPSET key
 ******************************************************************************/
int dm_gpio_getkey_ipset(void)
{
    uint32_t regval;
    regval = dm_reg_read(DM_PERIPHERAL_BASE + DM_KEY_IPSET_REG);
    return (regval >> DM_KEY_IPSET_BIT) & 0x1;
}

/*******************************************************************************
 * Name:        dm_gpio_setled_green
 * Description: set the green led state
 * Input:       value - 0. led off; others. led on
 * Output:      none
 * Return:      none
 ******************************************************************************/
void dm_gpio_setled_green(int value)
{
    uint32_t regaddr = 0;
    uint32_t regval  = 0;

    regaddr = DM_PERIPHERAL_BASE + DM_LED_GREEN_REG;

    regval = dm_reg_read(regaddr);
    if (value)
        regval |= (1 << DM_LED_GREEN_BIT);    // led on
    else
        regval &= ~(1 << DM_LED_GREEN_BIT);   // led off 
    
    dm_reg_write(regaddr, regval);
}

/*******************************************************************************
 * Name:        dm_gpio_setled_red
 * Description: set the red led state
 * Input:       value - 0. led off; others. led on
 * Output:      none
 * Return:      none
 ******************************************************************************/
void dm_gpio_setled_red(int value)
{
    uint32_t regaddr = 0;
    uint32_t regval  = 0;

    regaddr = DM_PERIPHERAL_BASE + DM_LED_RED_REG;
    regval = dm_reg_read(DM_PERIPHERAL_BASE + DM_LED_RED_REG);
    if (value)
        regval |= (1 << DM_LED_RED_BIT);      // led on
    else
        regval &= ~(1 << DM_LED_RED_BIT);     // led off

    dm_reg_write(regaddr, regval);
}

