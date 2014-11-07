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
#define SCRM_ALTCLKSRC			     (0x110)
#define SCRM_AUXCLK0                         (0x0310)
#define SCRM_AUXCLK1                         (0x0314)
#define SCRM_AUXCLK2                         (0x0318)
#define SCRM_AUXCLK3                         (0x031C)

/* Some of the GPIO register set */
#define GPIO1_OE                             (0x0134)
#define GPIO1_CLEARDATAOUT                   (0x0190)
#define GPIO1_SETDATAOUT                     (0x0194)
#define GPIO2_OE                             (0x0134)
#define GPIO2_CLEARDATAOUT                   (0x0190)
#define GPIO2_SETDATAOUT                     (0x0194)

/* Some of the PADCONF register set */
#define CONTROL_WKUP_PAD0_FREF_CLK3_OUT  (0x058)
#define CONTROL_CORE_PAD1_KPD_COL2       (0x186)
#define CONTROL_CORE_PAD0_GPMC_WAIT1     (0x08C)

#define REG_WRITE32(r, x)    *((volatile uint32_t*)(r)) = (uint32_t)(x)
#define REG_READ32(r)        *((volatile uint32_t*)(r))

#define REG_WRITE16(r, x)    *((volatile uint16_t*)(r)) = (uint16_t)(x)
#define REG_READ16(r)        *((volatile uint16_t*)(r))

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
 *	   - 
 *
 *
 *	So we are hamstrung without the useful drivers and we have to go back to
 *	direct register manupulation. Luckly we don't have to do to much, basically
 *	just setup the usb hub/ethernet.
 *
 */
static void
board_init(void *dummy)
{
	/*
	 * XXX Board identification e.g. read out from FPGA or similar should
	 * go here
	 */
}

SYSINIT(board_init, SI_SUB_CPU, SI_ORDER_THIRD, board_init, NULL);
