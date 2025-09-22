/*
 * line_buff.h
 *
 *  Created on: 2022-07-21
 *      Author: Hongbo.jiang
 */

#ifndef BSW_BASIC_LINE_BUFF_H_
#define BSW_BASIC_LINE_BUFF_H_

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"

typedef enum{
  BUFF_EMPTY        = 0,
  BUFF_FULL         = 1,
}LINE_BUFF_STATUS;

typedef enum{
    BUFF_UNLOCK       = 0,
    BUFF_READ_LOCK    = 1,
    BUFF_WRITE_LOCK   = 2,
}LINE_BUFF_CMD;
typedef struct
{
    UINT16              *p_u16HeadBuf;
    INT16                i16IdSize;
    INT16                i16TotalSize;
    UINT16               u16R_Index;
    UINT16               u16W_Index;
    LINE_BUFF_STATUS     enState;
    LINE_BUFF_CMD        enCmd;
}LINE_BUF_OBJ;

#endif /* BSW_BASIC_LINE_BUFF_H_ */
