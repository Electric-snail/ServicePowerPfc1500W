#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_TYPES_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_TYPES_H_
/*===========================================================================*/
/**
 * @file BSW_MCAL_CAN_TYPES.h
 *
 * Type definitions of the CAN and MCAN
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
 * @todo Add full description here
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
#include <BSW/ENV_CFG/SOFTWARE_ENV_CFG.h>
#if 0
/* Standard header files:
Header files that are common across an entire program or project and ANSI C standard library header files. */
#include "std_data_types.h" 
#endif /* #if 0 */

/*===========================================================================*
 * Other Header Files
 *===========================================================================*/
#ifdef __cplusplus
extern "C" {	/* ! Inclusion of header files should NOT be inside the extern "C" block */
#endif	/* __cplusplus */


#if 0
/* Other header files:
Header files that are required by a particular file (all header files that are not "standard header files"). */
#include "BSW_MCAL_CAN_TYPES_cfg.h"
#endif /* #if 0 */


enum MCAN_MODULE_ID_T{
   MCAN_MODULE_ID       = 0,
   MCAN_MODULE_MAX_ID,
};

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */


#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_TYPES_H_ */

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
