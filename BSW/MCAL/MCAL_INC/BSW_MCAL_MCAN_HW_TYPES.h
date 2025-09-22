#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_MCAN_HW_TYPES_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_MCAN_HW_TYPES_H_
/*===========================================================================*/
/**
 * @file BSW_MCAL_MCAN_HW_TYPES.h
 *
 * This file contains the in-line functions required to read/write
 * values from/to the hardware registers. This file also contains field
 * manipulation macros to get and set field values.
 *
 *------------------------------------------------------------------------------
 *
 * Copyright (C) 2022 Aptiv. All rights reserved. 
 * Aptiv Sensitve Business ¡§C Restricted Aptiv information. Do not disclose
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * This file is migrated from TI's driverlib file "hw_types_mcan.h".
 * Original data types are replaced.
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 * Add Polarion Work Item Link to the intended line (if using Resource Link  
 * for traceability)
 * Syntax: 
 * @wi.<LinkRoleAsSingleWord> <PolarionProjectID>/<workitemID>
 * example:
 * @wi.implemented PDP2.0_playground/WI-5001
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - ESGW_4-2_PE-SWx_00-01-A02_EN - C Coding Standards [20120506]
 *     - @todo Update list of other applicable standards
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - @todo List of deviations from standards in this file, or "None".
 *
 * @ updates to areas outside the scope of procedures:
 *   - Refer to module footer comment block.
 *
 * @defgroup template Provide API description and define/delete next line
 * @ingroup <parent_API> (OPTIONAL USE if part of another API, else delete)
 * @{
 */
/*==========================================================================*/

/*===========================================================================*
 * Standard Header Files
 *===========================================================================*/

/*===========================================================================*
 * Other Header Files
 *===========================================================================*/
#ifdef __cplusplus
extern "C" {	/* ! Inclusion of header files should NOT be inside the extern "C" block */
#endif	/* __cplusplus */



/*===========================================================================*
 * Exported Preprocessor #define Constants
 *===========================================================================*/

   /* None */

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

    /* None */

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/

    /* None */

/*===========================================================================*
 * Exported Const Object Declarations
 *===========================================================================*/

    /* None */

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/

    /* None */

/*===========================================================================*
 * Exported Inline Function Definitions and #define Function-Like Macros
 *===========================================================================*/
/**
 *  \brief   This function reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
static inline UINT32 HW_RD_REG32_RAW(UINT32 addr);
static inline UINT32 HW_RD_REG32_RAW(UINT32 addr)
{
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT32 regVal = *(volatile UINT32 *) addr;
    return (regVal);
}
/**
 *  \brief   This function writes a 32-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 32-bit value which has to be written to the
 *                   register.
 */
static inline void HW_WR_REG32_RAW(UINT32 addr, UINT32 value);
static inline void HW_WR_REG32_RAW(UINT32 addr, UINT32 value)
{
/*TI_INSPECTED 18 D : MISRAC_2012_R.5.3
 * "Tool Issue - argument 'value' used here is in same scope " */
    *(volatile UINT32 *) addr = value;
    return;
}

/**
 *  \brief   This function reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
static inline UINT16 HW_RD_REG16_RAW(UINT32 addr);
static inline UINT16 HW_RD_REG16_RAW(UINT32 addr)
{
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT16 regVal = *(volatile UINT16 *) addr;
    return (regVal);
}

/**
 *  \brief   This function writes a 16-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 16-bit value which has to be written to the
 *                   register.
 */
static inline void HW_WR_REG16_RAW(UINT32 addr, UINT16 value);
static inline void HW_WR_REG16_RAW(UINT32 addr, UINT16 value)
{
/*TI_INSPECTED 18 D : MISRAC_2012_R.5.3
 * "Tool Issue - argument 'value' used here is in same scope " */
    *(volatile UINT16 *) addr = value;
    return;
}

/**
 *  \brief   This function reads a 32 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *  \param   value   Value to be written to bit-field.
 */
static inline void HW_WR_FIELD32_RAW(UINT32 addr,
                                     UINT32 mask,
                                     UINT32 shift,
                                     UINT32 value);
static inline void HW_WR_FIELD32_RAW(UINT32 addr,
                                     UINT32 mask,
                                     UINT32 shift,
                                     UINT32 value)
{
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT32 regVal = *(volatile UINT32 *) addr;
    regVal &= (~mask);
    regVal |= (value << shift) & mask;
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    *(volatile UINT32 *) addr = regVal;
    return;
}

/**
 *  \brief   This function reads a 16 bit register, modifies specific set of
 *           bits and writes back to the register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *  \param   value   Value to be written to bit-field.
 */
static inline void HW_WR_FIELD16_RAW(UINT32 addr,
                                     UINT16 mask,
                                     UINT32 shift,
                                     UINT16 value);
static inline void HW_WR_FIELD16_RAW(UINT32 addr,
                                     UINT16 mask,
                                     UINT32 shift,
                                     UINT16 value)
{
    UINT32 tempVal;
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT16 regVal = *(volatile UINT16 *) addr;
    tempVal = ((UINT32) regVal);
    tempVal &=  (~((UINT32) mask));
    tempVal |= (((UINT32) value) << shift) & ((UINT32) mask);
    regVal = (UINT16) tempVal;
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    *(volatile UINT16 *) addr = regVal;
    return;
}

/**
 *  \brief   This function reads a 32 bit register, masks specific set of bits
 *           and the left shifted value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline UINT32 HW_RD_FIELD32_RAW(UINT32 addr,
                                         UINT32 mask,
                                         UINT32 shift);
static inline UINT32 HW_RD_FIELD32_RAW(UINT32 addr,
                                         UINT32 mask,
                                         UINT32 shift)
{
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT32 regVal = *(volatile UINT32 *) addr;
    regVal = (regVal & mask) >> shift;
    return (regVal);
}

/**
 *  \brief   This function reads a 16 bit register, masks specific set of bits
 *           and the left shifted value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   mask    Mask for the bit field.
 *  \param   shift   Bit field shift from LSB.
 *
 *  \return  Bit-field value (absolute value - shifted to LSB position)
 */
static inline UINT16 HW_RD_FIELD16_RAW(UINT32 addr,
                                         UINT16 mask,
                                         UINT32 shift);
static inline UINT16 HW_RD_FIELD16_RAW(UINT32 addr,
                                         UINT16 mask,
                                         UINT32 shift)
{
    UINT32 tempVal;
/*TI_INSPECTED 440 S : MISRAC_2012_R.11.4
 * "Reason - Pointer typecast required here since addr variable holds
 * required register value" */
    UINT16 regVal = *(volatile UINT16 *) addr;
    tempVal = (((UINT32) regVal & (UINT32) mask) >> shift);
    regVal = (UINT16) tempVal;
    return (regVal);
}

/**
 *  \brief   This macro reads a 32-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 32-bit value read from a register.
 */
#define HW_RD_REG32(addr) (UINT32)(HW_RD_REG32_RAW((UINT32) (addr)))

/**
 *  \brief   This macro writes a 32-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 32-bit value which has to be written to the
 *                   register.
 */
#define HW_WR_REG32(addr, value)                                               \
    (HW_WR_REG32_RAW((UINT32) (addr), (UINT32) (value)))

/**
 *  \brief   This macro reads a 16-bit value from a hardware register
 *           and returns the value.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *
 *  \return  Unsigned 16-bit value read from a register.
 */
#define HW_RD_REG16(addr) (HW_RD_REG16_RAW((UINT32) (addr)))

/**
 *  \brief   This macro writes a 16-bit value to a hardware register.
 *
 *  \param   addr    Address of the memory mapped hardware register.
 *  \param   value   unsigned 16-bit value which has to be written to the
 *                   register.
 */
#define HW_WR_REG16(addr, value)                                               \
    (HW_WR_REG16_RAW((UINT32) (addr), (UINT16) (value)))


/**
 *  \brief Macro to extract a field value. This macro extracts the field value
 *         from a 32-bit variable (which contains the register value).
 *         This macro does not read from actual register address, and only
 *         extracts the field from a variable.
 *
 *  \param regVal         32-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, whose value has to
 *                        be extracted.
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_GET_FIELD(regVal, REG_FIELD)                                        \
    (((regVal) & (UINT32) REG_FIELD##_MASK) >> (UINT32) REG_FIELD##_SHIFT)

/**
 *  \brief Macro to write a specific field value. This macro first clears the
 *         specified field value and then performs "OR" of the field value which
 *         is shifted and masked. This will set the field value at its
 *         desired position.
 *
 *  \param regVal         32-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_SET_FIELD32(regVal, REG_FIELD, fieldVal)                            \
    ((regVal) = ((regVal) & (UINT32) (~(UINT32) REG_FIELD##_MASK)) |       \
                    ((((UINT32) (fieldVal)) << (UINT32) REG_FIELD##_SHIFT) \
                        & (UINT32) REG_FIELD##_MASK))

/**
 *  \brief Macro to write a specific field value. This macro first clears the
 *         specified field value and then performs "OR" of the field value which
 *         is shifted and masked. This will set the field value at its
 *         desired position.
 *
 *  \param regVal         16-bit variable containing the register value.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_SET_FIELD16(regVal, REG_FIELD, fieldVal)                            \
    ((regVal) = ((regVal) & (UINT16) (~(UINT16) REG_FIELD##_MASK)) |       \
                    ((((UINT16) (fieldVal)) << (UINT16) REG_FIELD##_SHIFT) \
                        & (UINT16) REG_FIELD##_MASK))

/**
 *  \brief This macro calls read-modify-write API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_WR_FIELD32(regAddr, REG_FIELD, fieldVal)                            \
    (HW_WR_FIELD32_RAW((UINT32) (regAddr), (UINT32) REG_FIELD##_MASK,      \
                          (UINT32) REG_FIELD##_SHIFT, (UINT32) (fieldVal)))

/**
 *  \brief This macro calls read-modify-write API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, to which specified
 *                        value has to be set.
 *  \param fieldVal       Value of the field which has to be set.
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_WR_FIELD16(regAddr, REG_FIELD, fieldVal)                            \
    (HW_WR_FIELD16_RAW((UINT32) (regAddr), (UINT16) REG_FIELD##_MASK,      \
                          (UINT32) REG_FIELD##_SHIFT, (UINT16) (fieldVal)))

/**
 *  \brief This macro calls read field API for 32 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, from which
 *                        specified bit-field value has to be read.
 *  \return Value of the bit-field
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_RD_FIELD32(regAddr, REG_FIELD)                                      \
    (HW_RD_FIELD32_RAW((UINT32) (regAddr), (UINT32) REG_FIELD##_MASK,      \
                          (UINT32) REG_FIELD##_SHIFT))

/**
 *  \brief This macro calls read field API for 16 bit register. It also
 *         frames the mask and shift from register field macro.
 *
 *  \param regAddr        Register Address.
 *  \param REG_FIELD      Peripheral register bit field name, from which
 *                        specified bit-field value has to be read.
 *  \return Value of the bit-field
 */
/*TI_INSPECTED 76 S : MISRAC_2012_R.20.11
 * "The places in which order of evaluation has no side effects could be a
    waiver. This used in SHIFT and MASK to extract specified field value " */
/*TI_INSPECTED 125 S : MISRAC_2012_R.20.12
 * "The places in which order of evaluation has no side effects could be a
    waiver. ## operator here used in SHIFT and MASK to extract specified field
    value " */
#define HW_RD_FIELD16(regAddr, REG_FIELD)                                      \
    (HW_RD_FIELD16_RAW((UINT32) (regAddr), (UINT16) REG_FIELD##_MASK,      \
                          (UINT32) REG_FIELD##_SHIFT))


#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */


#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_MCAN_HW_TYPES_H_ */

/*============================================================================*\
 * AUTHOR(S) IDENTITY (AID)                                                     
 *-----------------------------------------------------------------------------  
 *                                     
 *  AID         NAME                 User ID
 *  ---------------------------------------------------------------------------
 *  XG          Xianzhi Gong         njp4bz
 *  HL          Herbert Langley                        
\*============================================================================*/

/*============================================================================*\
 * FILE REVISION HISTORY - To be filled by the project team                                               
 *-----------------------------------------------------------------------------  
 *                                     
 *  DATE               REVISION    AID          JIRA Ticket ID/SUMMARY OF CHANGES                                 
 *  ---------------------------------------------------------------------------
 *  Oct 24, 2022       1.00        XG           12345 First revision
 *                                           
 *  ---------------------------------------------------------------------------
\*============================================================================*/

/* END OF FILE -------------------------------------------------------------- */
