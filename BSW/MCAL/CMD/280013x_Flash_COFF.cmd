MEMORY
{
PAGE 0:
   RAMLS0_1                 		: origin = 0x00009800,   length = 0x00000800

   /* without user bootloader, set 1, otherwise configure to 0*/
   BEGIN_BOOT                    	: origin = 0x00080000,   length = 0x00000002
   BOOT_FLASH                 		: origin = 0x00080002,   length = 0x00003FFE

   APP_FLASH                        : origin = 0x00084000,   length = 0x0000C000
   /***any reset vector entry, in this place, branch to the boot code ********/
   RESET                    		: origin = 0x003FFFC0,  length = 0x00000002
   /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
PAGE 1:
   BOOT_RSVD                	    : origin = 0x00000002, 	 length = 0x00000126
   RAMM0            		    	: origin = 0x00000128, 	 length = 0x000002D8
   //Why is it not the 0x400?
   RAMM1            		    	: origin = 0x00000400, 	 length = 0x000003F8
   RAMLS0_0                    		: origin = 0x00008000, 	 length = 0x00001800
   // Combine two sections RAMLS0_2 RAMLS0_3
   RAMLS1           		        : origin = 0x0000A000, 	 length = 0x00001FFE
   RAMGS_APP_FLAG      				: origin = 0x0000BFFE,   length = 2
}

SECTIONS
{
   /* RAMM0 */
   .CtrlVariableSector     : > RAMM0,			PAGE = 1
   /* RAMM1 */
   .stack                  :   	RUN = RAMM1,
							   		RUN_START(_HWI_STKBOTTOM),
						       		RUN_SIZE(_HWI_STKSIZE),
						       		RUN_END(_HWI_STKTOP),
						       		PAGE = 1
//  .jumpboot                : > JumpBoot_Data,   PAGE = 0, ALIGN(8)
   /*
    * ROM sections
    */
   codestart       		   : > BEGIN_BOOT,			 									PAGE = 0
   .reset           	   : > RESET,                  									PAGE = 0,  TYPE = DSECT /* not used, */
   .cinit                  : > BOOT_FLASH,  											PAGE = 0, ALIGN(8)
   .pinit              	   : > BOOT_FLASH, 												PAGE = 0, ALIGN(8)
//   .econst          	   : >> CONSTANTS, 	     									    PAGE = 0, ALIGN(8)
   .econst          	   : > BOOT_FLASH, 				    							PAGE = 0, ALIGN(8)
   .text               	   : > BOOT_FLASH, 												PAGE = 0, ALIGN(8)
   .switch           	   : > BOOT_FLASH,  											PAGE = 0, ALIGN(8)

   /* LSRAM0 */
   .SCOPE_BUFF_SECTION  :>RAMLS0_0,  	    											PAGE = 1
   /* LSRAM1 */
   .ebss              	   					: >  RAMLS0_0,  							PAGE = 1
   .esysmem     		   					: >  RAMLS0_0,   							PAGE = 1
   .cio                    					: >  RAMLS0_0,   							PAGE = 1
  .RING_BUFF_SECTION       					: >  RAMLS1,   								PAGE = 1
  .APP_UPDATA_FLAG     						: >  RAMGS_APP_FLAG,       					PAGE = 1

  .APP_TEST							        : > APP_FLASH,								PAGE = 0, ALIGN(8)
  GROUP
   {
       .TI.ramfunc
 //      { -l FAPI_F280013x_COFF_v2.00.10.lib}
   }                      LOAD 	 = BOOT_FLASH,
                           RUN		 = RAMLS0_1,
                           LOAD_START(_RamfuncsLoadStart),
                           LOAD_SIZE(_RamfuncsLoadSize),
                           LOAD_END(_RamfuncsLoadEnd),
                           RUN_START(_RamfuncsRunStart),
                           RUN_SIZE(_RamfuncsRunSize),
                           RUN_END(_RamfuncsRunEnd),
                           PAGE = 0, ALIGN(4)
   .RING_REG_SECTION     : LOAD = BOOT_FLASH,
                           LOAD_START(_RingRegLoadStart),
                           LOAD_SIZE(_RingRegLoadSize),
                           LOAD_END(_RingRegLoadEnd),
                           PAGE = 0, ALIGN(4)


   .TASK_REG_SECTION     : LOAD = BOOT_FLASH,
                           LOAD_START(_TaskRegLoadStart),
                           LOAD_SIZE(_TaskRegLoadSize),
                           LOAD_END(_TaskRegLoadEnd),
                           PAGE = 0, ALIGN(4)


   .AUTO_REG_SECTION     : LOAD = BOOT_FLASH,
                      	   LOAD_START(_AutoRegLoadStart),
                      	   LOAD_SIZE(_AutoRegLoadSize),
                      	   LOAD_END(_AutoRegLoadEnd),
                      	   PAGE = 0, ALIGN(4)
}
