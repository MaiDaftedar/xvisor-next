/*
 * arch/arm/mach-sun7i/include/mach/clock.h
 * (c) Copyright 2010-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * James Deng <csjamesdeng@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef __CPUFREQ_H__
#define __CPUFREQ_H__

#include <vmm_limits.h>
#include <vmm_types.h>



#define SUNXI_CPUFREQ_MAX       (1008000000)    /* config the maximum frequency of sunxi core */
#define SUNXI_CPUFREQ_MIN       (60000000)      /* config the minimum frequency of sunxi core */
#define SUNXI_FREQTRANS_LATENCY (2000000)       /* config the transition latency, based on ns */

struct sunxi_clk_div_t {
    u32   cpu_div:4;      /* division of cpu clock, divide core_pll */
    u32   axi_div:4;      /* division of axi clock, divide cpu clock*/
    u32   ahb_div:4;      /* division of ahb clock, divide axi clock*/
    u32   apb_div:4;      /* division of apb clock, divide ahb clock*/
    u32   reserved:16;
};


struct sunxi_cpu_freq_t {
    u32                   pll;    /* core pll frequency value */
    struct sunxi_clk_div_t  div;    /* division configuration   */
};



void vmm_cpufreq_measure_util(void);
void cpufreq_init(void);
int set_cpufreq_target(struct sunxi_cpu_freq_t *old,struct sunxi_cpu_freq_t *new);
int set_cpufreq_hw(struct sunxi_cpu_freq_t *freq);
void calibrate_new_delay(u32 hcpu);
void cpufreq_init(void);
#endif
