/*-
 * Copyright (c) 2011
 *	Ben Gray <ben.r.gray@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BEN GRAY ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BEN GRAY BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Modified from head/sys/arm/ti/omap4/pandaboard/pandaboard.c
 * We only need the AUXCLK3 activation piece. The rest is handled by the
 * usb host driver and FDT settings and u-boot gpio pin muxing.
 */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/kernel.h>

#include <vm/vm.h>
#include <vm/pmap.h>

#include <machine/bus.h>
#include <machine/pte.h>
#include <machine/vmparam.h>
#include <machine/fdt.h>

#include <arm/ti/omap4/omap4var.h>
#include <arm/ti/omap4/omap4_reg.h>

/* Registers in the SCRM that control the AUX clocks */
#define SCRM_AUXCLK3                         (0x031C)

#define REG_WRITE32(r, x)    *((volatile uint32_t*)(r)) = (uint32_t)(x)

/**
 *	usb_hub_init - initialises and resets the external USB hub
 *	
 *	The USB hub needs to be held in reset while the power is being applied
 *	and the reference clock is enabled at 19.2MHz.  The following is the
 *	layout of the USB hub taken from the Pandaboard reference manual.
 *
 *
 *	   .-------------.         .--------------.
 *	   |  OMAP4430   |         |   USB3326    |
 *	   |             |         |              |
 *	   |         CLK | <------ | CLKOUT       |
 *	   |         STP | ------> | STP          |
 *	   |         DIR | <------ | DIR          |
 *	   |         NXT | <------ | NXT          |
 *	   |        DAT0 | <-----> | DAT0         |
 *	   |        DAT1 | <-----> | DAT1      DP |
 *	   |        DAT2 | <-----> | DAT2      DM |
 *	   |        DAT3 | <-----> | DAT3         |
 *	   |        DAT4 | <-----> | DAT4         |
 *	   |        DAT5 | <-----> | DAT5         |
 *	   |        DAT6 | <-----> | DAT6         |
 *	   |        DAT7 | <-----> | DAT7         |
 *	   |             |         |              |
 *	   |    AUX_CLK3 | ------> | REFCLK       |
 *	   |             |         |              |
 *	   |     GPIO_62 | ------> | RESET        |
 *	   |             |         |              |
 *	   '-------------'         '--------------'
 *
 *	RETURNS:
 *	nothing.
 */
static void
usb_hub_init(void)
{
	bus_space_handle_t scrm_addr;

	if (bus_space_map(fdtbus_bs_tag, OMAP44XX_SCRM_HWBASE,
	                  OMAP44XX_SCRM_SIZE, 0, &scrm_addr) != 0)
		panic("Couldn't map SCRM registers");

	/* Need to set FREF_CLK3_OUT to 19.2 MHz and pump it out on pin GPIO_WK31.
	 * We know the SYS_CLK is 38.4Mhz and therefore to get the needed 19.2Mhz,
	 * just use a 2x divider and ensure the SYS_CLK is used as the source.
	 */
	REG_WRITE32(scrm_addr + SCRM_AUXCLK3,
	                          (1 << 16) |    /* Divider of 2 */
	                          (0 << 1) |     /* Use the SYS_CLK as the source */
	                          (1 << 8));     /* Enable the clock */

	bus_space_unmap(fdtbus_bs_tag, scrm_addr, OMAP44XX_SCRM_SIZE);
}

/**
 *	board_init - initialises the duovero 
 *	@dummy: ignored
 * 
 *	This function is called before any of the driver are initialised, which is
 *	annoying because it means we can't use the SCM, PRCM and GPIO modules which
 *	would really be useful.
 *
 *	So we don't have:
 *	   - any drivers
 *	   - no interrupts
 *
 *	What we do have:
 *	   - virt/phys mappings from the devmap (see omap4.c)
 *
 */
static void
board_init(void *dummy)
{
	/* Initialise the USB phy ref clock */
	usb_hub_init();
}

SYSINIT(board_init, SI_SUB_CPU, SI_ORDER_THIRD, board_init, NULL);
