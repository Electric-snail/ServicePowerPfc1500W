/*****************************************************************************************************************
* File name:       BSW_MCAL_Flash.c 
* Purpose  :       flash 
* 
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
******************************************************************************************************************/
#include "FLASH_API/FlashTech_F280013x_C28x.h"
#include "FLASH_API/Constants/F280013x.h"
#include "MCAL_INC/BSW_MCAL_SYS_CLOCK.h"
#include "MCAL_INC/BSW_MCAL_FLASH.h"

#pragma CODE_SECTION(bsw_mcal_flash_init,   ".TI.ramfunc");
#pragma CODE_SECTION(Flash_powerDown,       ".TI.ramfunc");
#pragma CODE_SECTION(Flash_wakeFromLPM,     ".TI.ramfunc");

#pragma CODE_SECTION(bsw_mcal_flash_erase,  ".TI.ramfunc");
#pragma CODE_SECTION(bsw_mcal_flash_write,  ".TI.ramfunc");
#pragma CODE_SECTION(bsw_mcal_flash_read,   ".TI.ramfunc");

//*****************************************************************************
//
// Flash_powerDown
//
//*****************************************************************************
void Flash_powerDown(uint32_t ctrlBase)
{
    EALLOW;
    EDIS;
}

//*****************************************************************************
//
// Flash_wakeFromLPM
//
//*****************************************************************************
void Flash_wakeFromLPM(void)
{
    EALLOW;
    EDIS;
}


void bsw_mcal_flash_init(void)
{
    // Set the bank fallback power modes to active.
     EALLOW;
     // Disable cache and prefetch mechanism before changing wait states
     Flash0CtrlRegs.FRD_INTF_CTRL.all = 0x00000000;

     // Set waitstates according to frequency.
 #if (SYS_CPU_CLK_FREQ_M == 120)
     Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x02;
 #elif(SYS_CPU_CLK_FREQ_M == 100)
     Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x02; //0x04 before
 #elif(SYS_CPU_CLK_FREQ_M == 80)
     Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x03;
 #else
     Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x05;
 #endif

     // Commit Flash Trims
     // Configure TRIMCTL.ENABLE to be valid
     Flash_writeTrims(FLASH_O_TRIMCTL, FLASH_TRIMCTL_ENABLE_M,
                FLASH_TRIMCTL_ENABLE_S, 1);

     // Configure TRIMLOCKOTHER and TRIMLOCKREAD in TRIMLOCK register
     Flash_writeTrims(FLASH_O_TRIMLOCK, FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_M,
                FLASH_TRIMLOCK_TRIMLOCKREAD_TRIMLOCKOTHER_S, 3);

     // Configure TRIMCOMMITREAD and TRIMCOMMITOTHER in TRIMCOMMIT register
     Flash_writeTrims(FLASH_O_TRIMCOMMIT,
                FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_M,
                FLASH_TRIMCOMMIT_TRIMCOMMITREAD_TRIMCOMMITOTHER_S, 3);
     // Enable cache and prefetch mechanism to improve performance of code
     // executed from flash.
     Flash0CtrlRegs.FRD_INTF_CTRL.all = (unsigned long)0x00000003;
     //
     // At reset, ECC is enabled.  If it is disabled by application software and
     // if application again wants to enable ECC.
     //
     Flash0EccRegs.ECC_ENABLE.all = (Flash0EccRegs.ECC_ENABLE.all & ~(unsigned long)FLASH_ECC_ENABLE_ENABLE_M) \
                                        | 0xAU;
     EDIS;
     // Force a pipeline flush to ensure that the write to
     // the last register configured occurs before returning.
     __asm(" RPT #7 || NOP");
}

unsigned short  bsw_mcal_flash_write(unsigned long u32FlashStartAddr, unsigned short *p_u16SrcAddr, unsigned short  u16Len)
{
     UINT32 u32Index = 0;
     unsigned short i = 0;
     unsigned short u16Cnt = 0;
     unsigned short u16SectorProgramSize;
     unsigned short u16SectorIndex;
     unsigned short u16TempIndex;
     Fapi_StatusType            oReturnCheck;
     Fapi_FlashStatusType       oFlashStatus;

     u32Index = u32FlashStartAddr;

     if(u32Index & 0x00000007) return 0;   //the address is not align 8, the size is not the times of 8

     if(u16Len & 0x00000007)  return 0;  //the size is not times of 8



     for(u16Cnt = 0; u16Cnt < u16Len; u16Cnt += u16SectorProgramSize)
     {
         u16SectorIndex        = (u32Index - FlashBank0StartAddress) >> 10;
         u16SectorProgramSize  = ((u16SectorIndex + 1) << 10) + FlashBank0StartAddress - u32Index;//计算当前地址起始地址距离下一个sector的size,一个完整的sector是1024；如果地址不是sector的起始地址，则少于1024

         if((u16Cnt + u16SectorProgramSize) > u16Len){ //判断编程的size 超过总数的长度
             u16SectorProgramSize = u16Len - u16Cnt;
         }

         for(i = 0; i < u16SectorProgramSize; i+= 8)
         {
                // Wait until FSM is done with the previous flash operation
                while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
                oFlashStatus = Fapi_getFsmStatus();
                if(oFlashStatus != 0)  //isn't in the idel status, so to clear the status.
                {
                     /* Clear the Status register */
                     oReturnCheck = Fapi_issueAsyncCommand(Fapi_ClearStatus);
                     //
                     // Wait until status is cleared
                     //
                     while (Fapi_getFsmStatus() != 0) {}

                     if(oReturnCheck != Fapi_Status_Success)
                     {
                       return 0;
                     }
                }
                if(u16SectorIndex < 32){
                     Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, ~(1UL << u16SectorIndex));
                }else{
                    u16TempIndex = (u16SectorIndex - 32) >> 3;
                    Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, ~(1UL << u16TempIndex));
                }
                oReturnCheck = Fapi_issueProgrammingCommand((UINT32 *)u32Index,(unsigned int *)p_u16SrcAddr,8, 0, 0, Fapi_AutoEccGeneration);
                u32Index += 8;
                p_u16SrcAddr += 8;
                if(oReturnCheck != Fapi_Status_Success)
                  return 0;
         }
     }

     return 1;
}

UINT16 bsw_mcal_flash_read(UINT16 *p_u16DestAddr,UINT16 *p_u16SrcAddr, UINT16 u16Len)
{
    unsigned short i = 0;
    for(i = 0; i < u16Len; i++){
        *p_u16DestAddr++ = *p_u16SrcAddr++;
    }
    return 1;
}

UINT16 bsw_mcal_flash_fsm_init(void){
    Fapi_StatusType  oReturnCheck;

    oReturnCheck = Fapi_initializeAPI(FlashTech_CPU0_BASE_ADDRESS,  SYS_CPU_CLK_FREQ_M);

    if(oReturnCheck != Fapi_Status_Success)
    {
          return 0;
    }
//    EALLOW;
//    // Clear the prefetch enable bit.
//    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;
//    EDIS;
//    __asm(" RPT #7 || NOP");

    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    if(oReturnCheck != Fapi_Status_Success){
       // Check Flash API documentation for possible errors
       return 0;
    }

//    EALLOW;
//    // Set the prefetch enable bit.
//    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;
//    EDIS;
//    __asm(" RPT #7 || NOP");
    return 1;
}

UINT16  bsw_mcal_flash_erase(UINT32 u32SectorStartAddr, UINT16 u16SectorCnt){
       Fapi_StatusType          oReturnCheck;
       Fapi_FlashStatusType     oFlashStatus;
       UINT16 i = 0;
       UINT16 u16SectorIndex, u16TempIndex;

       u32SectorStartAddr = u32SectorStartAddr & 0xfffff000;

       u16SectorIndex     = (u32SectorStartAddr - FlashBank0StartAddress) >> 10;
       // Issue ClearMore command
       while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

       oFlashStatus = Fapi_getFsmStatus();
       if(oFlashStatus != 0){
                 /* Clear the Status register */
             oReturnCheck = Fapi_issueAsyncCommand(Fapi_ClearStatus);
             //
             // Wait until status is cleared
             //
             while (Fapi_getFsmStatus() != 0) {}

             if(oReturnCheck != Fapi_Status_Success)
                return 0;
       }

       // Wait until FSM is done with erase sector operation
       //
       while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

       for(i = 0; i < u16SectorCnt; i ++){
            if(u16SectorIndex < 32){
              Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTA, ~(1UL << u16SectorIndex));
            }else{
              u16TempIndex = (u16SectorIndex - 32) >> 3;
              Fapi_setupBankSectorEnable(FLASH_WRAPPER_PROGRAM_BASE+FLASH_O_CMDWEPROTB, ~(1UL << u16TempIndex));
            }
            oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                                                            (UINT32 *)u32SectorStartAddr);
            // Wait until FSM is done with erase sector operation
            //
            while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

            if(oReturnCheck != Fapi_Status_Success)
            {
               return 0;
            }

            u32SectorStartAddr += FLASH_SECTOR_SIZE;
            u16SectorIndex++;

            oFlashStatus = Fapi_getFsmStatus();
            if(oFlashStatus != 3)
            {
                __asm("    ESTOP0");
            }
       }
       return 1;
}


UINT16  bsw_mcal_flash_verify(UINT32 u32FlashStartAddr, UINT16 *p_u16DataBuff, UINT16 u16Len){
    Fapi_FlashStatusWordType    oFlashStatusWord;
    Fapi_StatusType             oReturnCheck;
    oReturnCheck = Fapi_doVerify((UINT32 *)u32FlashStartAddr,\
                                 (u16Len >> 1), (UINT32 *)p_u16DataBuff,\
                                 &oFlashStatusWord);
    if(oReturnCheck != Fapi_Status_Success) return 0;
    return 1;
}

