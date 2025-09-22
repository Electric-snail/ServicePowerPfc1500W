/*****************************************************************************************************************
* File name:       BSW_MCAL_FLASH.h 
*
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
******************************************************************************************************************/
#ifndef BSW_MCAL_FLASH
#define BSW_MCAL_FLASH

#ifdef __cplusplus
extern "C" {
#endif

#include "SOFTWARE_ENV_CFG.H"

typedef enum
{
    FLASH_BANK0 = 0x0, //!< Bank 0
    FLASH_BANK1 = 0x1  //!< Bank 1
} Flash_BankNumber;

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() as the powerMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_BANK_PWR_SLEEP    = 0x0, //!< Sleep fallback mode
    FLASH_BANK_PWR_STANDBY  = 0x1, //!< Standby fallback mode
    FLASH_BANK_PWR_ACTIVE   = 0x3  //!< Active fallback mode
} Flash_BankPowerMode;

//*****************************************************************************
//
//! Values that can be passed to Flash_setPumpPowerMode() as the powerMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    FLASH_PUMP_PWR_SLEEP    = 0x0, //!< Sleep fallback mode
    FLASH_PUMP_PWR_ACTIVE   = 0x1  //!< Active fallback mode
} Flash_PumpPowerMode;

//*****************************************************************************
//
//! Type that correspond to values returned from Flash_getLowErrorStatus() and
//! Flash_getHighErrorStatus() determining the error status code.
//
//*****************************************************************************
typedef enum
{
    FLASH_NO_ERR       = 0x0, //!< No error
    FLASH_FAIL_0       = 0x1, //!< Fail on 0
    FLASH_FAIL_1       = 0x2, //!< Fail on 1
    FLASH_UNC_ERR      = 0x4  //!< Uncorrectable error
} Flash_ErrorStatus;

//*****************************************************************************
//
//! Values that can be returned from Flash_getLowErrorType() and
//! Flash_getHighErrorType() determining the error type.
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_ERR      = 0x0, //!< Data error
    FLASH_ECC_ERR       = 0x1  //!< ECC error
} Flash_ErrorType;

//*****************************************************************************
//
//! Values that can be returned from Flash_getECCTestSingleBitErrorType().
//
//*****************************************************************************
typedef enum
{
    FLASH_DATA_BITS          = 0x0, //!< Data bits
    FLASH_CHECK_BITS         = 0x1  //!< ECC bits
} Flash_SingleBitErrorIndicator;

#define DEVICE_FLASH_WAITSTATES                   4

//*************************************************************************************************
//
// The following are defines for the bit fields in the FRDCNTL register
//
//*************************************************************************************************
#define FLASH_FRDCNTL_RWAIT_S   8U
#define FLASH_FRDCNTL_RWAIT_M   0xF00U   // Random Read Waitstate

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBAC register
//
//*************************************************************************************************
#define FLASH_FBAC_BAGP_S   8U
#define FLASH_FBAC_BAGP_M   0xFF00U   // Bank Active Grace Period

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBFALLBACK register
//
//*************************************************************************************************
#define FLASH_FBFALLBACK_BNKPWR0_S   0U
#define FLASH_FBFALLBACK_BNKPWR0_M   0x3U   // Bank Power Mode of BANK0
#define FLASH_FBFALLBACK_BNKPWR1_S   2U
#define FLASH_FBFALLBACK_BNKPWR1_M   0xCU   // Bank Power Mode of BANK1

//*************************************************************************************************
//
// The following are defines for the bit fields in the FBPRDY register
//
//*************************************************************************************************
#define FLASH_FBPRDY_BANK0RDY   0x1U      // Flash Bank Active Power State
#define FLASH_FBPRDY_BANK1RDY   0x2U      // Flash Bank Active Power State
#define FLASH_FBPRDY_PUMPRDY    0x8000U   // Flash Pump Active Power Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the FPAC1 register
//
//*************************************************************************************************
#define FLASH_FPAC1_PMPPWR     0x1U         // Charge Pump Fallback Power Mode
#define FLASH_FPAC1_PSLEEP_S   16U
#define FLASH_FPAC1_PSLEEP_M   0xFFF0000U   // Pump Sleep Down Count

//*************************************************************************************************
//
// The following are defines for the bit fields in the FPAC2 register
//
//*************************************************************************************************
#define FLASH_FPAC2_PAGP_S   0U
#define FLASH_FPAC2_PAGP_M   0xFFFFU   // Pump Active Grace Period

//*************************************************************************************************
//
// The following are defines for the bit fields in the FMSTAT register
//
//*************************************************************************************************
#define FLASH_FMSTAT_VOLTSTAT   0x8U      // Flash Pump Power Status
#define FLASH_FMSTAT_CSTAT      0x10U     // Command Fail Status
#define FLASH_FMSTAT_INVDAT     0x20U     // Invalid Data
#define FLASH_FMSTAT_PGM        0x40U     // Program Operation Status
#define FLASH_FMSTAT_ERS        0x80U     // Erase Operation Status
#define FLASH_FMSTAT_BUSY       0x100U    // Busy Bit
#define FLASH_FMSTAT_EV         0x400U    // Erase Verify Status
#define FLASH_FMSTAT_PGV        0x1000U   // Programming Verify Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the FRD_INTF_CTRL register
//
//*************************************************************************************************
#define FLASH_FRD_INTF_CTRL_PREFETCH_EN     0x1U   // Prefetch Enable
#define FLASH_FRD_INTF_CTRL_DATA_CACHE_EN   0x2U   // Data Cache Enable


//*************************************************************************************************
//
// The following are defines for the bit fields in the ECC_ENABLE register
//
//*************************************************************************************************
#define FLASH_ECC_ENABLE_ENABLE_S   0U
#define FLASH_ECC_ENABLE_ENABLE_M   0xFU   // Enable ECC

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_STATUS register
//
//*************************************************************************************************
#define FLASH_ERR_STATUS_FAIL_0_L    0x1U       // Lower 64bits Single Bit Error Corrected Value 0
#define FLASH_ERR_STATUS_FAIL_1_L    0x2U       // Lower 64bits Single Bit Error Corrected Value 1
#define FLASH_ERR_STATUS_UNC_ERR_L   0x4U       // Lower 64 bits Uncorrectable error occurred
#define FLASH_ERR_STATUS_FAIL_0_H    0x10000U   // Upper 64bits Single Bit Error Corrected Value 0
#define FLASH_ERR_STATUS_FAIL_1_H    0x20000U   // Upper 64bits Single Bit Error Corrected Value 1
#define FLASH_ERR_STATUS_UNC_ERR_H   0x40000U   // Upper 64 bits Uncorrectable error occurred

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_POS register
//
//*************************************************************************************************
#define FLASH_ERR_POS_ERR_POS_L_S   0U
#define FLASH_ERR_POS_ERR_POS_L_M   0x3FU        // Bit Position of Single bit Error in lower 64
                                                 // bits
#define FLASH_ERR_POS_ERR_TYPE_L    0x100U       // Error Type in lower 64 bits
#define FLASH_ERR_POS_ERR_POS_H_S   16U
#define FLASH_ERR_POS_ERR_POS_H_M   0x3F0000U    // Bit Position of Single bit Error in upper 64
                                                 // bits
#define FLASH_ERR_POS_ERR_TYPE_H    0x1000000U   // Error Type in upper 64 bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_STATUS_CLR register
//
//*************************************************************************************************
#define FLASH_ERR_STATUS_CLR_FAIL_0_L_CLR    0x1U       // Lower 64bits Single Bit Error Corrected
                                                        // Value 0 Clear
#define FLASH_ERR_STATUS_CLR_FAIL_1_L_CLR    0x2U       // Lower 64bits Single Bit Error Corrected
                                                        // Value 1 Clear
#define FLASH_ERR_STATUS_CLR_UNC_ERR_L_CLR   0x4U       // Lower 64 bits Uncorrectable error
                                                        // occurred Clear
#define FLASH_ERR_STATUS_CLR_FAIL_0_H_CLR    0x10000U   // Upper 64bits Single Bit Error Corrected
                                                        // Value 0 Clear
#define FLASH_ERR_STATUS_CLR_FAIL_1_H_CLR    0x20000U   // Upper 64bits Single Bit Error Corrected
                                                        // Value 1 Clear
#define FLASH_ERR_STATUS_CLR_UNC_ERR_H_CLR   0x40000U   // Upper 64 bits Uncorrectable error
                                                        // occurred Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_CNT register
//
//*************************************************************************************************
#define FLASH_ERR_CNT_ERR_CNT_S   0U
#define FLASH_ERR_CNT_ERR_CNT_M   0xFFFFU   // Error counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_THRESHOLD register
//
//*************************************************************************************************
#define FLASH_ERR_THRESHOLD_ERR_THRESHOLD_S   0U
#define FLASH_ERR_THRESHOLD_ERR_THRESHOLD_M   0xFFFFU   // Error Threshold

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_INTFLG register
//
//*************************************************************************************************
#define FLASH_ERR_INTFLG_SINGLE_ERR_INTFLG   0x1U   // Single Error Interrupt Flag
#define FLASH_ERR_INTFLG_UNC_ERR_INTFLG      0x2U   // Uncorrectable Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ERR_INTCLR register
//
//*************************************************************************************************
#define FLASH_ERR_INTCLR_SINGLE_ERR_INTCLR   0x1U   // Single Error Interrupt Flag Clear
#define FLASH_ERR_INTCLR_UNC_ERR_INTCLR      0x2U   // Uncorrectable Interrupt Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the FADDR_TEST register
//
//*************************************************************************************************
#define FLASH_FADDR_TEST_ADDRL_S   3U
#define FLASH_FADDR_TEST_ADDRL_M   0xFFF8U     // ECC Address Low
#define FLASH_FADDR_TEST_ADDRH_S   16U
#define FLASH_FADDR_TEST_ADDRH_M   0x3F0000U   // ECC Address High

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_TEST register
//
//*************************************************************************************************
#define FLASH_FECC_TEST_ECC_S   0U
#define FLASH_FECC_TEST_ECC_M   0xFFU   // ECC Control Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_CTRL register
//
//*************************************************************************************************
#define FLASH_FECC_CTRL_ECC_TEST_EN   0x1U   // Enable ECC Test Logic
#define FLASH_FECC_CTRL_ECC_SELECT    0x2U   // ECC Bit Select
#define FLASH_FECC_CTRL_DO_ECC_CALC   0x4U   // Enable ECC Calculation

//*************************************************************************************************
//
// The following are defines for the bit fields in the FECC_STATUS register
//
//*************************************************************************************************
#define FLASH_FECC_STATUS_SINGLE_ERR       0x1U     // Test Result is Single Bit Error
#define FLASH_FECC_STATUS_UNC_ERR          0x2U     // Test Result is Uncorrectable Error
#define FLASH_FECC_STATUS_DATA_ERR_POS_S   2U
#define FLASH_FECC_STATUS_DATA_ERR_POS_M   0xFCU    // Holds Bit Position of Error
#define FLASH_FECC_STATUS_ERR_TYPE         0x100U   // Holds Bit Position of 8 Check Bits of Error


//************************************************************************************************
// Sector Size
//************************************************************************************************
#define SECTDWORD_SIZE              0x200

//************************************************************************************************
// The following are defines for the bit fields in the (FMS)STATCMD register 
//************************************************************************************************

#define STAT_CMDDONE                    0x0001u
#define STAT_CMDPASS                    0x0002u
#define STAT_CMDMASK                    0x0003u

extern void   	 	bsw_mcal_flash_init(void);
extern void    		bsw_mcal_flash_read(UINT16 *p_u16DestAddr,UINT16 *p_u16SrcAddr, UINT16 u16Len);
extern UINT16  	bsw_mcal_flash_erase(unsigned short *p_u16Addr, unsigned short u16Len);
extern UINT16  	bsw_mcal_flash_write(UINT16 *p_u16FlashStartAddr, UINT16 *p_u16SrcAddr, UINT16 u16Len);
#ifdef __cplusplus
}
#endif // extern "C"

#endif // end #ifndef BSW_MCAL_FLASH
//===========================================================================
// End of file.
//===========================================================================
