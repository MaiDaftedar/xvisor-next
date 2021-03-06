/**
 * Copyright (c) 2012 Sukanto Ghosh.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @file arm_plat.h
 * @author Sukanto Ghosh (sukantoghosh@gmail.com)
 * @brief ARM platform configuration
 */
#ifndef _ARM_PLAT_H__
#define _ARM_PLAT_H__

/*
 * On-Chip Peripherials Physical Addresses
 */
    /* 0x2a430000: system counter: not modelled */
    /* 0x2e000000: system SRAM */
    /* 0x7ffb0000: DMA330 DMA controller: not modelled */
    /* 0x7ffd0000: PL354 static memory controller: not modelled */
/* HDLCD controller: not modelled */
#define CT_CA15X4_HDLCD			(0x2b000000)
#define CT_CA15X4_AXIRAM		(0x10060000)
/* PL341 dynamic memory controller: not modelled */
#define CT_CA15X4_DMC			(0x2b0a0000)
#define CT_CA15X4_SMC			(0x100e1000)
/* SCC: not modelled */
#define CT_CA15X4_SCC			(0x2a420000)
#define CT_CA15X4_SP804_TIMER		(0x100e4000)
/* SP805 watchdog: not modelled */
#define CT_CA15X4_SP805_WDT		(0x2b060000)
/* PL301 AXI interconnect: not modelled */
#define CT_CA15X4_AXI			(0x2a000000)
/* CoreSight interfaces: not modelled */
#define CT_CA15X4_CORESIGHT		(0x20000000)
/* A15MPCore private memory region (GIC) */
#define CT_CA15X4_MPIC			(0x2c000000)

#define CT_CA15X4_TIMER0		(CT_CA15X4_SP804_TIMER + 0x000)
#define CT_CA15X4_TIMER1		(CT_CA15X4_SP804_TIMER + 0x020)

#define A15_MPCORE_GIC_CPU		(CT_CA15X4_MPIC + 0x2000)
#define A15_MPCORE_GIC_DIST		(CT_CA15X4_MPIC + 0x1000)

/*
 * Interrupts.  Those in {} are for AMBA devices
 */
#define IRQ_CT_CA15X4_HDLCD		{ 76 }
#define IRQ_CT_CA15X4_DMC		{ -1 }
#define IRQ_CT_CA15X4_SMC		{ 77, 78 }
#define IRQ_CT_CA15X4_TIMER0		80
#define IRQ_CT_CA15X4_TIMER1		81
#define IRQ_CT_CA15X4_GPIO		{ 82 }
#define IRQ_CT_CA15X4_PMU_CPU0		92
#define IRQ_CT_CA15X4_PMU_CPU1		93
#define IRQ_CT_CA15X4_PMU_CPU2		94
#define IRQ_CT_CA15X4_PMU_CPU3		95

#define IRQ_CT_CA15X4_LOCALTIMER		29
#define IRQ_CT_CA15X4_LOCALWDOG		30

#define IRQ_CA15X4_GIC_START		29
#define NR_IRQS_CA15X4			128
#define NR_GIC_CA15X4			1

/*
 * V2M Chip Select Physical Addresses 
 */
/* CS0: 0x00000000 .. 0x0c000000 */
#define V2M_PA_CS0		0x00000000
/* CS4: 0x0c000000 .. 0x10000000 */
#define V2M_PA_CS4		0x0c000000
/* CS5: 0x10000000 .. 0x14000000 */
#define V2M_PA_CS5		0x10000000
/* CS1: 0x14000000 .. 0x18000000 */
#define V2M_PA_CS1		0x14000000
/* CS2: 0x18000000 .. 0x1c000000 */
#define V2M_PA_CS2		0x18000000
/* CS3: 0x1c000000 .. 0x20000000 */
#define V2M_PA_CS3		0x1c000000

/*
 * Physical addresses, offset from V2M_PA_CS0-3
 */
#define V2M_NOR0		(V2M_PA_CS0)
#define V2M_NOR0ALIAS		(V2M_PA_CS0 + 0x08000000)
#define V2M_NOR1		(V2M_PA_CS4)
#define V2M_SRAM		(V2M_PA_CS1)
#define V2M_VIDEO_SRAM		(V2M_PA_CS2 + 0x00000000)
#define V2M_LAN9118		(V2M_PA_CS2 + 0x02000000)
#define V2M_ISP1761		(V2M_PA_CS2 + 0x03000000)

/*
 * Physical addresses, offset from V2M_PA_CS3
 */
#define V2M_SYSREGS		(V2M_PA_CS3 + 0x00010000)
#define V2M_SYSCTL		(V2M_PA_CS3 + 0x00020000)
#define V2M_SERIAL_BUS_PCI	(V2M_PA_CS3 + 0x00030000)

#define V2M_AACI		(V2M_PA_CS3 + 0x00040000)
#define V2M_MMCI		(V2M_PA_CS3 + 0x00050000)
#define V2M_KMI0		(V2M_PA_CS3 + 0x00060000)
#define V2M_KMI1		(V2M_PA_CS3 + 0x00070000)

#define V2M_UART0		(V2M_PA_CS3 + 0x00090000)
#define V2M_UART1		(V2M_PA_CS3 + 0x000a0000)
#define V2M_UART2		(V2M_PA_CS3 + 0x000b0000)
#define V2M_UART3		(V2M_PA_CS3 + 0x000c0000)

#define V2M_WDT			(V2M_PA_CS3 + 0x000f0000)

#define V2M_TIMER01		(V2M_PA_CS3 + 0x00110000)
#define V2M_TIMER23		(V2M_PA_CS3 + 0x00120000)

#define V2M_SERIAL_BUS_DVI	(V2M_PA_CS3 + 0x00160000)
#define V2M_RTC			(V2M_PA_CS3 + 0x00170000)

#define V2M_CF			(V2M_PA_CS3 + 0x001a0000)
#define V2M_CLCD		(V2M_PA_CS3 + 0x001f0000)

#define V2M_SYS_ID		(V2M_SYSREGS + 0x000)
#define V2M_SYS_SW		(V2M_SYSREGS + 0x004)
#define V2M_SYS_LED		(V2M_SYSREGS + 0x008)
#define V2M_SYS_100HZ		(V2M_SYSREGS + 0x024)
#define V2M_SYS_FLAGS		(V2M_SYSREGS + 0x030)
#define V2M_SYS_FLAGSSET	(V2M_SYSREGS + 0x030)
#define V2M_SYS_FLAGSCLR	(V2M_SYSREGS + 0x034)
#define V2M_SYS_NVFLAGS		(V2M_SYSREGS + 0x038)
#define V2M_SYS_NVFLAGSSET	(V2M_SYSREGS + 0x038)
#define V2M_SYS_NVFLAGSCLR	(V2M_SYSREGS + 0x03c)
#define V2M_SYS_MCI		(V2M_SYSREGS + 0x048)
#define V2M_SYS_FLASH		(V2M_SYSREGS + 0x03c)
#define V2M_SYS_CFGSW		(V2M_SYSREGS + 0x058)
#define V2M_SYS_24MHZ		(V2M_SYSREGS + 0x05c)
#define V2M_SYS_MISC		(V2M_SYSREGS + 0x060)
#define V2M_SYS_DMA		(V2M_SYSREGS + 0x064)
#define V2M_SYS_PROCID0		(V2M_SYSREGS + 0x084)
#define V2M_SYS_PROCID1		(V2M_SYSREGS + 0x088)
#define V2M_SYS_CFGDATA		(V2M_SYSREGS + 0x0a0)
#define V2M_SYS_CFGCTRL		(V2M_SYSREGS + 0x0a4)
#define V2M_SYS_CFGSTAT		(V2M_SYSREGS + 0x0a8)

#define V2M_TIMER0		(V2M_TIMER01 + 0x000)
#define V2M_TIMER1		(V2M_TIMER01 + 0x020)

#define V2M_TIMER2		(V2M_TIMER23 + 0x000)
#define V2M_TIMER3		(V2M_TIMER23 + 0x020)

/*
 * Interrupts.  Those in {} are for AMBA devices
 */
#define IRQ_V2M_WDT		{ (32 + 0) }
#define IRQ_V2M_TIMER0		(32 + 2)
#define IRQ_V2M_TIMER1		(32 + 2)
#define IRQ_V2M_TIMER2		(32 + 3)
#define IRQ_V2M_TIMER3		(32 + 3)
#define IRQ_V2M_RTC		{ (32 + 4) }
#define IRQ_V2M_UART0		{ (32 + 5) }
#define IRQ_V2M_UART1		{ (32 + 6) }
#define IRQ_V2M_UART2		{ (32 + 7) }
#define IRQ_V2M_UART3		{ (32 + 8) }
#define IRQ_V2M_MMCI		{ (32 + 9), (32 + 10) }
#define IRQ_V2M_AACI		{ (32 + 11) }
#define IRQ_V2M_KMI0		{ (32 + 12) }
#define IRQ_V2M_KMI1		{ (32 + 13) }
#define IRQ_V2M_CLCD		{ (32 + 14) }
#define IRQ_V2M_LAN9118		(32 + 15)
#define IRQ_V2M_ISP1761		(32 + 16)
#define IRQ_V2M_PCIE		(32 + 17)

/*
 * Configuration
 */
#define SYS_CFG_START		(1 << 31)
#define SYS_CFG_WRITE		(1 << 30)
#define SYS_CFG_OSC		(1 << 20)
#define SYS_CFG_VOLT		(2 << 20)
#define SYS_CFG_AMP		(3 << 20)
#define SYS_CFG_TEMP		(4 << 20)
#define SYS_CFG_RESET		(5 << 20)
#define SYS_CFG_SCC		(6 << 20)
#define SYS_CFG_MUXFPGA		(7 << 20)
#define SYS_CFG_SHUTDOWN	(8 << 20)
#define SYS_CFG_REBOOT		(9 << 20)
#define SYS_CFG_DVIMODE		(11 << 20)
#define SYS_CFG_POWER		(12 << 20)
#define SYS_CFG_SITE_MB		(0 << 16)
#define SYS_CFG_SITE_DB1	(1 << 16)
#define SYS_CFG_SITE_DB2	(2 << 16)
#define SYS_CFG_STACK(n)	((n) << 12)

#define SYS_CFG_ERR		(1 << 1)
#define SYS_CFG_COMPLETE	(1 << 0)

/*
 * Core tile IDs
 */
#define V2M_CT_ID_CA9		0x0c000191
#define V2M_CT_ID_UNSUPPORTED	0xff000191
#define V2M_CT_ID_MASK		0xff000fff

/* Following taken from sp810.h */

/* sysctl registers offset */
#define SCCTRL				0x000
#define SCSYSSTAT			0x004
#define SCIMCTRL			0x008
#define SCIMSTAT			0x00C
#define SCXTALCTRL			0x010
#define SCPLLCTRL			0x014
#define SCPLLFCTRL			0x018
#define SCPERCTRL0			0x01C
#define SCPERCTRL1			0x020
#define SCPEREN				0x024
#define SCPERDIS			0x028
#define SCPERCLKEN			0x02C
#define SCPERSTAT			0x030
#define SCSYSID0			0xEE0
#define SCSYSID1			0xEE4
#define SCSYSID2			0xEE8
#define SCSYSID3			0xEEC
#define SCITCR				0xF00
#define SCITIR0				0xF04
#define SCITIR1				0xF08
#define SCITOR				0xF0C
#define SCCNTCTRL			0xF10
#define SCCNTDATA			0xF14
#define SCCNTSTEP			0xF18
#define SCPERIPHID0			0xFE0
#define SCPERIPHID1			0xFE4
#define SCPERIPHID2			0xFE8
#define SCPERIPHID3			0xFEC
#define SCPCELLID0			0xFF0
#define SCPCELLID1			0xFF4
#define SCPCELLID2			0xFF8
#define SCPCELLID3			0xFFC
	
#define SCCTRL_TIMEREN0SEL_REFCLK	(0 << 15)
#define SCCTRL_TIMEREN0SEL_TIMCLK	(1 << 15)

#define SCCTRL_TIMEREN1SEL_REFCLK	(0 << 17)
#define SCCTRL_TIMEREN1SEL_TIMCLK	(1 << 17)

/*
 * Defines required by common code
 */
#define ARM_PLAT_SPIN_ADDR	(V2M_SYS_FLAGS)

#endif
