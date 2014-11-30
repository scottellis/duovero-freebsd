#!/bin/sh

FREEBSD_SRC=~/src-current

cp sys/arm/conf/DUOVERO* ${FREEBSD_SRC}/sys/arm/conf

cp -r sys/arm/ti/omap4/duovero ${FREEBSD_SRC}/sys/arm/ti/omap4

cp sys/boot/fdt/dts/arm/duovero.dts ${FREEBSD_SRC}/sys/boot/fdt/dts/arm

