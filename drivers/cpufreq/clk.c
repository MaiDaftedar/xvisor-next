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



#include <drv/clk.h>
#include <linux/clkdev.h>

#include <linux/clk-provider.h>


//static struct clk_lookup lookups[AW_CCU_CLK_CNT];


int clk_init(void)
{
    int i, val;
    struct clk *clk;

    //CCU_INF("aw clock manager init\n");

    /* initialize clock controller unit */
    /*Intialize the CCM register base address*/
  

	vmm_printf("Initialize clock controller unit__\n");

	
	vmm_printf("PLL1\n");
	clk= __clk_lookup("pll1");	
	if(clk)
		__clk_get_rate(clk);
	

	//clk_set_rate(clk,3120000000);


	//vmm_printf("After clk change\n");
	//__clk_get_rate(clk);

	
	vmm_printf("PLL4\n");
	clk= __clk_lookup("pll4");	
	if(clk)
		__clk_get_rate(clk);


	vmm_printf("apb1\n");
	clk= __clk_lookup("apb1");	
	if(clk)
		__clk_get_rate(clk);

	
	vmm_printf("nand\n");
	clk= __clk_lookup("nand");	
	if(clk)
		__clk_get_rate(clk);
	
	vmm_printf("ms\n");
	clk= __clk_lookup("ms");	
	if(clk)
		__clk_get_rate(clk);

	vmm_printf("mmc0\n");
	clk= __clk_lookup("mmc0");	
	if(clk)
		__clk_get_rate(clk);


	vmm_printf("mmc1\n");
	clk= __clk_lookup("mmc1");	
	if(clk)
		__clk_get_rate(clk);


	vmm_printf("mmc2\n");
	clk= __clk_lookup("mmc2");	
	if(clk)
		__clk_get_rate(clk);

	
	vmm_printf("mmc3\n");
	clk= __clk_lookup("mmc3");	
	if(clk)
		__clk_get_rate(clk);
	
	vmm_printf("ts\n");
	clk= __clk_lookup("ts");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("ss");	
	if(clk)
		__clk_get_rate(clk);

	
	clk= __clk_lookup("spi0");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("spi1");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("spi2");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("pata");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("ir0");	
	if(clk)
		__clk_get_rate(clk);

	clk= __clk_lookup("ir1");	
	if(clk)
		__clk_get_rate(clk);


	
	//clk_set_rate(clk,9120000000);

	//__clk_get_rate(clk);
	#if 0
	 aw_ccu_init();
	/*TODO: CLOCK INITIALIZATIONS*/
    /* clear the data structure */
    memset((void *)aw_clock, 0, sizeof(aw_clock));
    memset((void *)lookups, 0, sizeof(lookups));

	vmm_printf("Initialize 1\n");
	for (i = 0; i < AW_CCU_CLK_NULL; i++) 
   	{
        	/* initiate clock */
      	 	if (aw_ccu_get_clk(i, &aw_clock[i]) != 0)
		{
            		vmm_printf("ERR: try to get clock %d informaiton failed\n", i);
        	}
		vmm_printf("Initialize %d\n",i);

		/* init clock spin lock */
       //CCU_LOCK_INIT(&aw_clock[i].lock);
        	/* register clk device */
        	lookups[i].con_id = aw_clock[i].aw_clk->name;
       	lookups[i].clk    = &aw_clock[i];
        	clkdev_add(&lookups[i]);
		
		vmm_printf("Adding Clk  %d\n",i);
    	}

   /* initiate some clocks */
    lookups[AW_MOD_CLK_SMPTWD].dev_id = "smp_twd";

  #if 0
   vmm_printf("Set clock AW_SYS_CLK_PLL3_\n");
   val = 297;
   clk = &aw_clock[AW_SYS_CLK_PLL3];
   //clk_enable(clk);
   sys_clk_set_status(clk->aw_clk->id,AW_CCU_CLK_ON);
   vmm_printf("Setting Clk Status\n");
   
   sys_clk_set_rate(clk->aw_clk->id, val * 1000000);
   vmm_printf("Setting Clk Rate\n");

   vmm_printf("Set clock AW_SYS_CLK_PLL4\n");
   val = 300;
    clk = &aw_clock[AW_SYS_CLK_PLL4];
  //  clk_enable(clk);
    sys_clk_set_status(clk->aw_clk->id,AW_CCU_CLK_ON);
    sys_clk_set_rate(clk->aw_clk->id, val * 1000000);
      
    vmm_printf("Set clock AW_SYS_CLK_PLL6\n");
    val = 600;
    clk = &aw_clock[AW_SYS_CLK_PLL6];
   // clk_enable(clk);
     sys_clk_set_status(clk->aw_clk->id,AW_CCU_CLK_ON);
    sys_clk_set_rate(clk->aw_clk->id, val * 1000000);

     vmm_printf("Set clock AW_SYS_CLK_PLL7\n");
    val = 297;
    clk = &aw_clock[AW_SYS_CLK_PLL7];
    //clk_enable(clk);
      sys_clk_set_status(clk->aw_clk->id,AW_CCU_CLK_ON);
    sys_clk_set_rate(clk->aw_clk->id, val * 1000000);
        
    vmm_printf("Set clock AW_SYS_CLK_PLL8\n");
  val = 336;
   clk = &aw_clock[AW_SYS_CLK_PLL8];
  // clk_enable(clk);
    sys_clk_set_status(clk->aw_clk->id,AW_CCU_CLK_ON);
   sys_clk_set_rate(clk->aw_clk->id, val * 1000000);
    #endif

#endif
    return 0;
}
