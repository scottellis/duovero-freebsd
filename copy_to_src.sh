#!/bin/sh

FREEBSD_SRC=~/src-work

GITDIR=`pwd`

cd $FREEBSD_SRC

patch -p1 -i ${GITDIR}/patches/0001-omap4-add-aux-clks-to-prcm.patch
patch -p1 -i ${GITDIR}/patches/0002-ti-ehci-add-support-for-2-gpio-reset-pins.patch
patch -p1 -i ${GITDIR}/patches/0003-pandaboard-usb-let-ehci-driver-initialize-usb-phy.patch
patch -p1 -i ${GITDIR}/patches/0004-add-duovero-support.patch
patch -p1 -i ${GITDIR}/patches/0005-omap4-prcm-use-defined-constants-in-reset-function.patch
patch -p1 -i ${GITDIR}/patches/0006-omap4-do-warm-reset-on-reboot.patch

