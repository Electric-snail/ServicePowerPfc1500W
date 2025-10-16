/*****************************************************************************************************************
* File name:       BSW_MCAL_Flash.c 
* Purpose  :       flash 
* 
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
******************************************************************************************************************/
#include "f28x_project.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"
#include "MCAL_INC/BSW_MCAL_FLASH.h"
//#include "LIB/Constants/Constants.h"
//#include "LIB/FlashTech.h"

#pragma CODE_SECTION(bsw_mcal_flash_write, 		".TI.ramfunc");
#pragma CODE_SECTION(bsw_mcal_flash_erase, 		".TI.ramfunc");
#pragma CODE_SECTION(bsw_mcal_flash_init,  			".TI.ramfunc");
#pragma CODE_SECTION(ClearFSMStatus,       			".TI.ramfunc");

// Init_FlashAPI - Initialize the flash API
#pragma CODE_SECTION(bsw_mcal_flash_api_init, ".TI.ramfunc");

UINT16 g_u16FlashApiInitFault = 0;

UINT16 bsw_mcal_flash_api_init(void)
{
/*    Fapi_StatusType oReturnCheck;
    UINT16          retVal;
    retVal          = TRUE;
    EALLOW;
    // Initialize the Flash API by providing the Flash register base address
    // and operating frequency.
    // This function is required to initialize the Flash API based on System frequency
    // before any other Flash API operation can be performed.
    // This function must also be called whenever System frequency or RWAIT is changed.

    oReturnCheck = Fapi_initializeAPI(FlashTech_CPU0_BASE_ADDRESS, (uint32)100);

    if (oReturnCheck != Fapi_Status_Success)
    {
        __asm("    ESTOP0");
        retVal   = FALSE;
    }
    else{
        // Initialize the Flash banks and FMC for erase and program operations.
        // Fapi_setActiveFlashBank() function sets the Flash banks and FMC for further
        // Flash operations to be performed on the banks.
        // Note: It does not matter which bank is passed as the parameter to initialize.
        //       Both Banks and FMC get initialized with one function call unlike F2837xS.
        //       Hence there is no need to execute Fapi_setActiveFlashBank() for each bank.
        //       Executing for one bank is enough.

        oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

        if (oReturnCheck != Fapi_Status_Success)
        {
              __asm("    ESTOP0");
              retVal   = FALSE;
        }else{   *//*Setup if need flash function,
                  Disable Protection of Flash Section
                   for accepting flash operation*/
                /* Release segments for programming */
 /*               Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0xFFFFFFFF);
                Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000007FF);
                retVal   = TRUE;
        }
    }

    EDIS;
    return retVal;*/
	return 1;
}

void bsw_mcal_flash_init(void)
{
 //   UINT16 u16FlashApiRet;
    EALLOW;
    // Disable Cache and prefetch mechanism before changing wait states
    //
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN 	= 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN 		= 0;
    // Set waitstates according to frequency
    //      *CAUTION*
    // Minimum waitstates required for the flash operating at a given CPU rate
    // must be characterized by TI. Refer to the datasheet for the latest
    // information.
#if (SYS_CPU_CLK_FREQ_M == 120)
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x05;
#elif(SYS_CPU_CLK_FREQ_M == 100)
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x02; //0x04 before
#elif(SYS_CPU_CLK_FREQ_M == 80)
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x03;
#else
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x05;
#endif
    // Enable Cache and prefetch mechanism to improve performance of code
    // executed from Flash.
    //
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN 	= 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN 		= 1;

    //
    // Enable the Flash ECC
    //
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    EDIS;

    //
    // Force a pipeline flush to ensure that the write to the last register
    // configured occurs before returning.
    //
    __asm(" RPT #7 || NOP");

/* 没有对Flash 操作编程，可不进行该函数的调用
    u16FlashApiRet = bsw_mcal_flash_api_init();

    if(u16FlashApiRet == FALSE)
        g_u16FlashApiInitFault = TRUE;
*/
}

void ClearFSMStatus(void){
 /*   Fapi_FlashStatusType  oFlashStatus;
    Fapi_StatusType  oReturnCheck;

    //
    // Wait until FSM is done with the previous flash operation
    //
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
        oFlashStatus = Fapi_getFsmStatus();
        if(oFlashStatus != 0)
        {

       */     /* Clear the Status register */
 /*           oReturnCheck = Fapi_issueAsyncCommand(Fapi_ClearStatus);
            //
            // Wait until status is cleared
            //
            while (Fapi_getFsmStatus() != 0) {}

            if(oReturnCheck != Fapi_Status_Success)
            {
                //
                // Check Flash API documentation for possible errors
                //
                __asm("    ESTOP0");
            }
        }*/
}

UINT16 bsw_mcal_flash_write(UINT16 *p_u16FlashStartAddr, UINT16 *p_u16SrcAddr, UINT16 u16Len)
{
/*    Fapi_StatusType oReturnCheck = Fapi_Status_Success;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    UINT16 i = 0;
    UINT16 writeDataLen = 0;
    UINT32 dTmp = 0;
    uint32 *p_u32TempFlashAddr = (UINT32 *)p_u16FlashStartAddr;
    uint16 *p_u16TempDataAddr = (uint16 *)p_u16SrcAddr;
    uint32 u32_writeAddress = 0;
    uint32 *p_u32ArrayAddr = (uint32*)p_u16SrcAddr;

    u32_writeAddress = (uint32)p_u16FlashStartAddr;

    writeDataLen = (u16Len>>3);

    for (i = 0; i < writeDataLen; i++)
    {
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
       // Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0x013FFFF00);

        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0xFFFFFFFF);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000007FF);
						// Pengyuan 1017 change from 0x000000080 to 0x000006FF
//        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000000080);

        DINT;
        //oReturnCheck = Fapi_issueProgrammingCommand(p_u32TempFlashAddr, p_u16TempDataAddr, 8, 0, 0, Fapi_AutoEccGeneration);
        oReturnCheck = Fapi_issueProgrammingCommand((uint32*)u32_writeAddress, p_u16TempDataAddr, 8, 0, 0, Fapi_AutoEccGeneration);
        EINT;

        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");

//      p_u32TempFlashAddr += 4;
//      p_u16TempDataAddr += 8;
        // Wait until the Flash program operation is over
  */      /*Fapi_checkFsmForReady return value:
        Fapi_Status_FsmBusy (FSM is busy and cannot accept new command except for suspend commands)
        Fapi_Status_FsmReady (FSM is ready to accept new command, an Erase or Program operation has finished)*/
/*        while (Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if (oReturnCheck != Fapi_Status_Success)
        {
            // Check Flash API documentation for possible errors
            __asm("    ESTOP0");
            return 0;
        }

        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related errors
		__asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        oFlashStatus = Fapi_getFsmStatus();
		
        dTmp = oFlashStatus & STAT_CMDMASK;

        while((dTmp != STAT_CMDDONE) &&((STAT_CMDDONE | STAT_CMDPASS) != dTmp)){

        }		
		
   */     /**
         * STAT_CMDDONE = done but not pass, then fail
         * STATE_CMDDONE | STATE_CMDPASS = done and pass, then next
         * **/
/*        if(dTmp == STAT_CMDDONE){
            // Check Flash API documentation for FMSTAT and debug accordingly
            // Fapi_getFsmStatus() function gives the FMSTAT register contents.
            // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
            // VOLTSTAT bit is set (Refer to API documentation for more details).
            //Error(Fapi_Error_Fail);
            __asm("    ESTOP0");
            return 0;
        }else if((STAT_CMDDONE | STAT_CMDPASS) == dTmp){
            //pass
        }else{
            // should not be here
        }

		
        //if (oFlashStatus != 3)
        //{
            //Check FMSTAT and debug accordingly
            //if (oFlashStatus != 0x11)
            //{
                //__asm("    ESTOP0");
                //return 0;
            //}

        //}
        // Verify the programmed values.  Check for any ECC errors.
        // The program command itself does a verify as it goes.
        // Hence program verify by CPU reads (Fapi_doVerify()) is optional.
 */       /* here is the check action when any program operation finished */

        //oReturnCheck = Fapi_doVerify( p_u32TempFlashAddr, 4, (p_u16TempDataAddr + i>>1), &oFlashStatusWord);
 /*       oReturnCheck = Fapi_doVerify( (uint32*) u32_writeAddress, 4, (p_u32ArrayAddr + i*4), &oFlashStatusWord);

		p_u32TempFlashAddr += 8;
		u32_writeAddress +=8;
        p_u16TempDataAddr += 8;

        if (oReturnCheck != Fapi_Status_Success)
        {
            // Check Flash API documentation for possible errors
            //Error(Fapi_Error_Fail);
            __asm("    ESTOP0");
        }
		
#if 0
        if(oFlashStatus != 0x11)
        {
             //
             // Verify the programmed values.  Check for any ECC errors.
             //

             oReturnCheck = Fapi_doVerify((uint32 *)p_u32TempFlashAddr,
                                          4, (uint32 *)p_u16TempDataAddr,
                                          &oFlashStatusWord);

             if(oReturnCheck != Fapi_Status_Success)
             {
                 //
                 // Check Flash API documentation for possible errors
                 //
                 __asm("    ESTOP0");
                 return 0;
             }
        }
#endif
    }

    writeDataLen = u16Len&0x7;

    if(0 != writeDataLen)
    {
        ClearFSMStatus();

        // Enable program/erase protection for select sectors where this example is
        // located
        // CMDWEPROTA is applicable for sectors 0-31
        // Bits 0-11 of CMDWEPROTB is applicable for sectors 32-127, each bit represents
        // a group of 8 sectors, e.g bit 0 represents sectors 32-39, bit 1 represents
        // sectors 40-47, etc
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0xFFFFFFFF);
        Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000007FF);

        DINT;
        //oReturnCheck = Fapi_issueProgrammingCommand(p_u32TempFlashAddr, p_u16TempDataAddr, writeDataLen, 0, 0, Fapi_AutoEccGeneration);
        oReturnCheck = Fapi_issueProgrammingCommand((uint32*)u32_writeAddress, p_u16TempDataAddr, (uint16)writeDataLen, 0, 0, Fapi_AutoEccGeneration);
        EINT;

 
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        // Wait until the Flash program operation is over
 */       /*Fapi_checkFsmForReady return value:
        Fapi_Status_FsmBusy (FSM is busy and cannot accept new command except for suspend commands)
        Fapi_Status_FsmReady (FSM is ready to accept new command, an Erase or Program operation has finished)*/
 /*       while (Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if (oReturnCheck != Fapi_Status_Success)
        {
            // Check Flash API documentation for possible errors
            __asm("    ESTOP0");
            return 0;
        }

        // Read FMSTAT register contents to know the status of FSM after
        // program command to see if there are any program operation related errors
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");
        __asm("    NOP");

        oFlashStatus = Fapi_getFsmStatus();
		
        dTmp = oFlashStatus & STAT_CMDMASK;

        while((dTmp != STAT_CMDDONE) &&((STAT_CMDDONE | STAT_CMDPASS) != dTmp)){

        }		
		
//        if (oFlashStatus != 3)
//        {
//            //Check FMSTAT and debug accordingly
//            if (oFlashStatus != 0x11)
//            {
//                __asm("    ESTOP0");
//                return 0;
//            }

//        }

 */       /**
         * STAT_CMDDONE = done but not pass, then fail
         * STATE_CMDDONE | STATE_CMDPASS = done and pass, then next
         * **/
/*        if(dTmp == STAT_CMDDONE){
            // Check Flash API documentation for FMSTAT and debug accordingly
            // Fapi_getFsmStatus() function gives the FMSTAT register contents.
            // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
            // VOLTSTAT bit is set (Refer to API documentation for more details).
            //Error(Fapi_Error_Fail);
            __asm("    ESTOP0");
        }else if((STAT_CMDDONE | STAT_CMDPASS) == dTmp){
            //pass
        }else{
            // should not be here
        }
		
		

#if 0
        if(oFlashStatus != 0x11)
        {
             //
             // Verify the programmed values.  Check for any ECC errors.
             //

             oReturnCheck = Fapi_doVerify((uint32 *)p_u32TempFlashAddr,
                                          4, (uint32 *)p_u16TempDataAddr,
                                          &oFlashStatusWord);

             if(oReturnCheck != Fapi_Status_Success)
             {
                 //
                 // Check Flash API documentation for possible errors
                 //
                 __asm("    ESTOP0");
                 return 0;
             }
        }
#endif

        // Verify the programmed values.  Check for any ECC errors.
        // The program command itself does a verify as it goes.
        // Hence program verify by CPU reads (Fapi_doVerify()) is optional.
 */       /* here is the check action when any program operation finished */

        //oReturnCheck = Fapi_doVerify( p_u32TempFlashAddr, (uint32)writeDataLen>>1, (p_u16TempDataAddr), &oFlashStatusWord);
//        oReturnCheck = Fapi_doVerify( (uint32*) u32_writeAddress, (uint32)(writeDataLen>>1), (p_u32ArrayAddr + i*4), &oFlashStatusWord);
//        if (oReturnCheck != Fapi_Status_Success)
//        {
//            // Check Flash API documentation for possible errors
//            //Error(Fapi_Error_Fail);
//            __asm("    ESTOP0");
//        }
 /*       writeDataLen = 0;
        return 1;
    }*/

    return 1;
}



void bsw_mcal_flash_read(UINT16 *p_u16DestAddr,UINT16 *p_u16SrcAddr, UINT16 u16Len)
{
    UINT16 i = 0;
    for(i = 0; i < u16Len; i ++){
        *p_u16DestAddr++ = *p_u16SrcAddr++;
    }
}


UINT16 bsw_mcal_flash_erase(unsigned short *p_u16Addr, unsigned short u16Len)
{
/*    Fapi_StatusType       oReturnCheck = Fapi_Status_Success;
    Fapi_FlashStatusType oFlashStatus;
    Fapi_FlashStatusWordType  oFlashStatusWord;
    UINT32 u32SecStartAddr = (UINT32)p_u16Addr & 0xFFFFFF00L;
    UINT16 eraseResult = 0;
	UINT32 dTmp = 0;
    //Calculate the p_u32Addr's correspond bank and sector.
    ClearFSMStatus();
    Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, 0xFFFFFFFF);
    Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, 0x000006FF);
    DINT;
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                                        (uint32 *)u32SecStartAddr);
    EINT;
    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    if (oReturnCheck != Fapi_Status_Success)
    {
        //Error(Fapi_Error_Fail);
        //__asm("    ESTOP0"); // Pengyuan 09/09/2024 stop DSP stucking here
                               // Just return 0
        return 0;
    }
    __asm("    NOP");
    __asm("    NOP");
    __asm("    NOP");
    __asm("    NOP");
    // Read FMSTAT register contents to know the status of FSM after program command
    // to see if there are any program operation related errors
    oFlashStatus = Fapi_getFsmStatus();
    dTmp = oFlashStatus & STAT_CMDMASK;

    while((dTmp != STAT_CMDDONE) &&((STAT_CMDDONE | STAT_CMDPASS) != dTmp)){

    }
*/    /**
     * STAT_CMDDONE = done but not pass, then fail
     * STATE_CMDDONE | STATE_CMDPASS = done and pass, then next
     * **/
/*    if(dTmp == STAT_CMDDONE){
        // Check Flash API documentation for FMSTAT and debug accordingly
        // Fapi_getFsmStatus() function gives the FMSTAT register contents.
        // Check to see if any of the EV bit, ESUSP bit, CSTAT bit or
        // VOLTSTAT bit is set (Refer to API documentation for more details).
        //Error(Fapi_Error_Fail);
        //__asm("    ESTOP0");
        return 0;
    }else if((STAT_CMDDONE | STAT_CMDPASS) == dTmp){
        //pass
    }else{
        // should not be here
    }

    // Do blank check
    // Verify that sectAddress[i] is erased.  The Erase command itself does a verify as it goes.
    // Hence erase verify by CPU reads (Fapi_doBlankCheck()) is optional.
    oReturnCheck = Fapi_doBlankCheck((uint32 *) (u32SecStartAddr), SECTDWORD_SIZE, &oFlashStatusWord);
	
    if(oReturnCheck != Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
       // __asm("    ESTOP0");
        eraseResult = 0;
    }
    else
    {
        eraseResult = 1;
    }

    return eraseResult;*/
	return 1;
}

