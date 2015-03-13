/*
 * arch/arm/mach-sun7i/clock/ccu_dbg.c
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


#include "cpu-freq/cpufreq.h"
#include <vmm_manager.h>
#include <vmm_scheduler.h>
#include <vmm_cpumask.h>
#include <vmm_stdio.h>
#include <vmm_delay.h>
#include <libs/mathlib.h>

#include <drv/clk.h>
#include <linux/clkdev.h>

#include <linux/clk-provider.h>



static struct clk *clk_pll; /* pll clock handler */
static struct clk *clk_cpu; /* cpu clock handler */
static struct clk *clk_axi; /* axi clock handler */
static struct clk *clk_ahb; /* ahb clock handler */
static struct clk *clk_apb0; /* apb clock handler */
static struct clk *clk_apb1; /* apb clock handler */

#define AHB_APB_CLK_ASYNC
static int count;
void vmm_cpufreq_measure_util(void)
{
	u32 hcpu,idle_percent,irqpercent;
	u64 irq_time,idle_time,sample_period,util;
	unsigned long clk_rate;
	struct sunxi_cpu_freq_t old_freq,new_freq;
  	 //Get the IRQ time
  	// AFAIK Freq scaling is for both cores at the same time

  for_each_online_cpu(hcpu)
  {
  	sample_period =
	   vmm_scheduler_get_sample_period(hcpu);
	
   	irq_time = vmm_scheduler_irq_time(hcpu);
	util = udiv64(irq_time * 1000,
			      sample_period);
	util = (util > 1000) ? 1000 : util;
	
	vmm_printf("UTIL:  %10d.%01d\n",
			    udiv32(util, 10), umod32(util, 10));

	irqpercent = umod32(util, 10) * 10;

	vmm_printf("IRQ : %d\n",irqpercent);
	
	//Get idle time
	idle_time = vmm_scheduler_idle_time(hcpu);
	
   	//Idle percentage
	idle_percent = udiv64(idle_time * 100,
						sample_period);
	
	vmm_printf("HCPU : %d   IDLE Percent : %d\n",hcpu,idle_percent);
	//Scale frequency every 8 sample
	if(idle_percent >= 60 && count==20)
	{
		count = 0;
		clk_rate = __clk_get_rate(clk_pll);
		old_freq.pll = clk_rate;

		//Down scale the clock
		if(clk_rate >= 960000000)
		{
			new_freq.pll = 912000000;
			vmm_printf("New Freq:912000000\n ");
		}
		else if(clk_rate >= 912000000)
		{
			new_freq.pll = 864000000;
			vmm_printf("New Freq:864000000\n ");
		}
		else if(clk_rate >= 864000000)
		{
			new_freq.pll = 816000000;
			vmm_printf("New Freq:816000000\n ");
		}
		else if(clk_rate >= 816000000)
		{
			new_freq.pll = 768000000;
			vmm_printf("New Freq:816000000\n ");
		}
		else if(clk_rate >= 768000000)
		{
			new_freq.pll = 744000000;
			vmm_printf("New Freq:744000000\n ");
		}
		else if(clk_rate >= 744000000)
		{
			new_freq.pll = 720000000;
			vmm_printf("New Freq:720000000\n ");
		}
		else if(clk_rate >= 720000000)
		{
			vmm_printf("Lowest Freq reached\n");
		}

		set_cpufreq_target(&old_freq,&new_freq);
		calibrate_new_delay(hcpu);
	}
   }
   vmm_printf("Count : %d\n",count);
   count++;
}

void vmm_cpufreq_set_powersave_mode(void)
{


}

void vmm_cpufreq_set_performance_mode(void)
{







}

void vmm_cpufreq_set_ondemand_mode(void)
{







}

int set_cpufreq_hw(struct sunxi_cpu_freq_t *freq)
{
	  int             ret;
	  unsigned int    frequency;

	vmm_printf("Setting HW Freq: PLL: %d\n",freq->pll);
   	 /* try to adjust pll frequency */
    	ret = clk_set_rate(clk_pll, freq->pll);
    	/* try to adjust cpu frequency */
    	frequency = udiv32(freq->pll,freq->div.cpu_div);
	
	vmm_printf("Setting HW Freq: CPU: %d\n",frequency);
    	ret |= clk_set_rate(clk_cpu, frequency);
    	/* try to adjuxt axi frequency */
    	frequency = udiv32(frequency,freq->div.axi_div);
	vmm_printf("Setting HW Freq: AXI: %d\n",frequency);
    	ret |= clk_set_rate(clk_axi, frequency);

	#ifndef AHB_APB_CLK_ASYNC
    	/* try to adjust ahb frequency */
    	frequency = udiv32(frequency,freq->div.ahb_div);
	vmm_printf("Setting HW Freq: AHB: %d\n",frequency);
    	ret |= clk_set_rate(clk_ahb, frequency);
    	/* try to adjust apb frequency */
    	frequency = udiv32(frequency,freq->div.apb_div);
	vmm_printf("Setting HW Freq: APB0: %d\n",frequency);
    	ret |= clk_set_rate(clk_apb0, frequency);
	#endif

    	return ret;

}
  int set_cpufreq_target(struct sunxi_cpu_freq_t *old,struct sunxi_cpu_freq_t *new)
{
 	 int     ret = 0;

	 struct sunxi_cpu_freq_t old_freq, new_freq;

    	if(!old || !new) {
        return -EINVAL;
    	}

    	old_freq = *old;
    	new_freq = *new;

  
	if(new_freq.pll > old_freq.pll) 
	{
 	//For now lets not go as low as 204
 	#if 0
        if((old_freq.pll <= 204000000) && (new_freq.pll >= 204000000)) {
            /* set to 204Mhz (1:1:1:2) */
            old_freq.pll = 204000000;
            old_freq.div.cpu_div = 1;
            old_freq.div.axi_div = 1;
#ifndef AHB_APB_CLK_ASYNC
            old_freq.div.ahb_div = 1;
            old_freq.div.apb_div = 2;
#endif
            ret |= __set_cpufreq_hw(&old_freq);
#ifndef AHB_APB_CLK_ASYNC
            /* set to 204Mhz (1:1:2:2) */
            old_freq.div.ahb_div = 2;
            ret |= __set_cpufreq_hw(&old_freq);
#endif
        }
        if((old_freq.pll <= 408000000) && (new_freq.pll >= 408000000)) {
            /* set to 408Mhz (1:1:2:2) */
            old_freq.pll = 408000000;
            old_freq.div.cpu_div = 1;
            old_freq.div.axi_div = 1;
#ifndef AHB_APB_CLK_ASYNC
            old_freq.div.ahb_div = 2;
            old_freq.div.apb_div = 2;
#endif
            ret |= __set_cpufreq_hw(&old_freq);
            /* set to 408Mhz (1:2:2:2) */
            old_freq.div.axi_div = 2;
            ret |= __set_cpufreq_hw(&old_freq);
        }
	#endif
        if((old_freq.pll <= 816000000) && (new_freq.pll >= 816000000)) {
            /* set to 816Mhz (1:2:2:2) */
	 
            old_freq.pll = 816000000;
            old_freq.div.cpu_div = 1;
            old_freq.div.axi_div = 2;
#ifndef AHB_APB_CLK_ASYNC
            old_freq.div.ahb_div = 2;
            old_freq.div.apb_div = 2;
#endif
            ret |=set_cpufreq_hw(&old_freq);
            /* set to 816Mhz (1:3:2:2) */
            old_freq.div.axi_div = 3;
            ret |= set_cpufreq_hw(&old_freq);
        }
        /* adjust to target frequency */
	   vmm_printf("SETTING TARGET TO: 816000000");
        ret |= set_cpufreq_hw(&new_freq);
    }
    else if(new_freq.pll < old_freq.pll) {
     
        if((old_freq.pll > 816000000) && (new_freq.pll <= 816000000)) {
            /* set to 816Mhz (1:3:2:2) */
            old_freq.pll = 816000000;
            old_freq.div.cpu_div = 1;
            old_freq.div.axi_div = 3;
#ifndef AHB_APB_CLK_ASYNC
            old_freq.div.ahb_div = 2;
            old_freq.div.apb_div = 2;
#endif
            ret |= set_cpufreq_hw(&old_freq);
            /* set to 816Mhz (1:2:2:2) */
            old_freq.div.axi_div = 2;
            ret |= set_cpufreq_hw(&old_freq);
        }
        if((old_freq.pll > 408000000) && (new_freq.pll <= 408000000)) {
            /* set to 408Mhz (1:2:2:2) */
            old_freq.pll = 408000000;
            old_freq.div.cpu_div = 1;
            old_freq.div.axi_div = 2;
#ifndef AHB_APB_CLK_ASYNC
            old_freq.div.ahb_div = 2;
            old_freq.div.apb_div = 2;
#endif
            ret |= set_cpufreq_hw(&old_freq);
            /* set to 816Mhz (1:1:2:2) */
            old_freq.div.axi_div = 1;
            ret |=set_cpufreq_hw(&old_freq);
        }
	 vmm_printf("SETTING TARGET TO: 816000000");
        /* adjust to target frequency */
        ret |= set_cpufreq_hw(&new_freq);
    }
    return ret;
}

void calibrate_new_delay(u32 hcpu)
{

	vmm_printf("Scale new delay");
	/* Try to migrate running/ready VCPU to new host CPU */
	vmm_smp_ipi_async_call(vmm_cpumask_of(hcpu),
			       vmm_delay_recaliberate,
			       NULL, NULL,
			       NULL);



}
void cpufreq_init(void)
{

	vmm_printf("PLL1\n");
	clk_pll = __clk_lookup("pll1");

	if(clk_pll)
		__clk_get_rate(clk_pll);
	

	vmm_printf("CPU\n");
	clk_cpu = __clk_lookup( "cpu");

	if(clk_cpu)
		__clk_get_rate(clk_cpu);


	vmm_printf("axi\n");
	clk_axi = __clk_lookup("axi");

	if(clk_axi)
		__clk_get_rate(clk_axi);
	//clk_set_rate(clk,3120000000);

	vmm_printf("ahb\n");
	clk_ahb = __clk_lookup("ahb");

	if(clk_ahb)
		__clk_get_rate(clk_ahb);
	
	vmm_printf("apb0\n");
	clk_apb0 = __clk_lookup("apb0");

	if(clk_apb0)
		__clk_get_rate(clk_apb0);

		vmm_printf("apb1\n");
	clk_apb1 = __clk_lookup("apb1");

	if(clk_apb1)
		__clk_get_rate(clk_apb1);
  
}


