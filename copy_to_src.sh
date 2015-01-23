#!/bin/sh

FREEBSD_SRC=~/src-current

GITDIR=`pwd`

cd $FREEBSD_SRC

patch -p0 -i ${GITDIR}/patches/0000-omap4-prcm-fix-uart-clock-reg-address.patch
patch -p0 -i ${GITDIR}/patches/0001-omap4-add-aux-clks-to-prcm.patch
patch -p0 -i ${GITDIR}/patches/0002-ti-ehci-add-support-for-2-gpio-reset-pins.patch
patch -p0 -i ${GITDIR}/patches/0003-pandaboard-usb-let-ehci-driver-initialize-usb-phy.patch
patch -p0 -i ${GITDIR}/patches/0004-add-duovero-support.patch
patch -p0 -i ${GITDIR}/patches/0005-omap4-prcm-use-defined-constants-in-reset-function.patch
patch -p0 -i ${GITDIR}/patches/0006-omap4-do-warm-reset-on-reboot.patch
patch -p0 -i ${GITDIR}/patches/0007-omap4-add-omap443x-dtsi.patch
patch -p0 -i ${GITDIR}/patches/0008-omap4-duovero-pandaboard-use-omap443x-dtsi.patch

#patch -p0 -i ${GITDIR}/patches/0010-add-kernconf-for-bbb.patch

