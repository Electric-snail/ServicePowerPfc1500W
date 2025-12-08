MEMORY
{
PAGE 0:
   RAMLS0_1                 		: origin = 0x00009000,   length = 0x00001000

   /* without user bootloader, set 1, otherwise configure to 0*/
#if 1
   BEGIN_APP                    			: origin = 0x00080000,   length = 0x00000002
#else
/******************  24 k for user boot ***********/
   BOOT_FLASH                 		 	: origin = 0x00080000,   length = 0x00006000
   BEGIN_APP                    			: origin = 0x00086000,   length = 0x00000002
#endif
   FLASH_APP    							: origin = 0x00086002,   length = 0x0000BFFE

   /***any reset vector entry, in this place, branch to the boot code ********/
   RESET                    					: origin = 0x003FFFC0,  length = 0x00000002
   /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
PAGE 1:
   BOOT_RSVD                	: origin = 0x00000002, length = 0x00000126
   RAMM0            		    	: origin = 0x00000128, length = 0x000002D8
   //Why is it not the 0x400?
   RAMM1            		    	: origin = 0x00000400, length = 0x000003F8
   RAMLS0_0                    	: origin = 0x00008000, length = 0x00001000
   // Combine two sections RAMLS0_2 RAMLS0_3
   RAMLS1           		        : origin = 0x0000A000, length = 0x00002000
   FLASH_STORAGE_SEC   : origin = 0x0009E000, length = 0x00001000	/* on-chip Flash */
   APP_KEY_LOCATION		: origin = 0x0009F000, length = 0x00001000 /* Marker Location, and the end of flash for 0x000A0000*/
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
   codestart       		   : > BEGIN_APP,			 									PAGE = 0, ALIGN(4)
   .reset              	   : > RESET,            												PAGE = 0, TYPE = DSECT // not used
   .cinit                    : > FLASH_APP,  												PAGE = 0, ALIGN(8)
   .pinit              	   : >> FLASH_APP, 												PAGE = 0, ALIGN(8)
//   .econst          	   : >> CONSTANTS, 	     									PAGE = 0, ALIGN(8)
   .econst          	   	   : >> FLASH_APP, 				    						PAGE = 0, ALIGN(8)
   .text               	   : >> FLASH_APP, 												PAGE = 0, ALIGN(8)
   .switch           	   : > FLASH_APP,  												PAGE = 0, ALIGN(8)

   /* LSRAM0 */
   .SCOPE_BUFF_SECTION  :>RAMLS0_0,  	    						PAGE = 1
   /* LSRAM1 */
   .ebss              	   						: > RAMLS1,  								PAGE = 1
   .esysmem     		   					: > RAMLS1,   								PAGE = 1
   .cio                    						: > RAMLS1,   								PAGE = 1
  .RING_BUFF_SECTION       : > RAMLS1,   								PAGE = 1

  .Key_Location          			    : > APP_KEY_LOCATION,        				PAGE = 1, ALIGN(8)
  GROUP
   {
       .TI.ramfunc
 //      { -l FAPI_F280013x_COFF_v2.00.10.lib}
   }                      LOAD 	 = FLASH_APP,
                           RUN		 = RAMLS0_1,
                           LOAD_START(_RamfuncsLoadStart),
                           LOAD_SIZE(_RamfuncsLoadSize),
                           LOAD_END(_RamfuncsLoadEnd),
                           RUN_START(_RamfuncsRunStart),
                           RUN_SIZE(_RamfuncsRunSize),
                           RUN_END(_RamfuncsRunEnd),
                           PAGE = 0, ALIGN(4)
   .RING_REG_SECTION     : LOAD = FLASH_APP,
                           LOAD_START(_RingRegLoadStart),
                           LOAD_SIZE(_RingRegLoadSize),
                           LOAD_END(_RingRegLoadEnd),
                           PAGE = 0, ALIGN(4)

  .DEV_DRV_REG_SECTION   : LOAD = FLASH_APP,
                           LOAD_START(_DevDrvRegLoadStart),
                           LOAD_SIZE(_DevDrvRegLoadSize),
                           LOAD_END(_DevDrvRegLoadEnd),
                           PAGE = 0, ALIGN(4)

   .SVC_REG_SECTION      : LOAD = FLASH_APP,
                           LOAD_START(_SvcRegLoadStart),
                           LOAD_SIZE(_SvcRegLoadSize),
                           LOAD_END(_SvcRegLoadEnd),
                           PAGE = 0, ALIGN(4)

   .ASW_REG_SECTION      : LOAD = FLASH_APP,
                           LOAD_START(_AswRegLoadStart),
                           LOAD_SIZE(_AswRegLoadSize),
                           LOAD_END(_AswRegLoadEnd),
                           PAGE = 0, ALIGN(4)

   .TASK_REG_SECTION     : LOAD = FLASH_APP,
                           LOAD_START(_TaskRegLoadStart),
                           LOAD_SIZE(_TaskRegLoadSize),
                           LOAD_END(_TaskRegLoadEnd),
                           PAGE = 0, ALIGN(4)

   .ISR_TEST_REG_SECTION : LOAD = FLASH_APP,
                           LOAD_START(_IsrTestRegLoadStart),
                           LOAD_SIZE(_IsrTestRegLoadSize),
                           LOAD_END(_IsrTestRegLoadEnd),
                           PAGE = 0, ALIGN(4)

   .AUTO_REG_SECTION     : LOAD = FLASH_APP,
                      	   LOAD_START(_AutoRegLoadStart),
                      	   LOAD_SIZE(_AutoRegLoadSize),
                      	   LOAD_END(_AutoRegLoadEnd),
                      	   PAGE = 0, ALIGN(4)


   .STORAGE_REG_SECTION: > FLASH_STORAGE_SEC,     PAGE = 1, ALIGN(4)
    /*  Allocate IQ math areas: */
   IQmath           	: > FLASH_APP, PAGE = 0,  ALIGN(8)
   IQmathTables     : > FLASH_APP, PAGE = 0,  ALIGN(8)
}
