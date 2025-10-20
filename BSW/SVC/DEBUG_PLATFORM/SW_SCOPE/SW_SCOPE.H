/*
 * SW_Scope.h
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#ifndef BSW_DEBUGPLATFORM_SW_SCOPE_H_
#define BSW_DEBUGPLATFORM_SW_SCOPE_H_

#include <PUBLIC_INC/RING_ARRAY.H>

#define  SCOPE_VAR_MAX_ITEM_CNT        			6
#define  SCOPE_STOP_CMD                         				0
#define  SCOPE_RUN_CMD                          				1

#if(SCOPE_VAR_MAX_ITEM_CNT > 6)
#error"The SCOPE_VAR_MAX_ITEM_CNT must below 7"
#endif

typedef struct{
    UINT16   ul8VarCnt:        	  8;
    UINT16   uh8NameLen:          8;
}ITEM_NAME_BITS;

typedef union{
	UINT16             u16all;
	ITEM_NAME_BITS     bits;
}SCOPE_ITEM_INFO;

typedef struct{
    UINT16   ul8Index:        	   8;
    UINT16   uh8NameLen:           8;
}SCOPE_VAR_NAME_BITS;

typedef union{
	UINT16                        u16all;
	SCOPE_VAR_NAME_BITS           bits;
}SCOPE_VAR_NAME;

typedef enum
{
      SW_TRIGG 		= 0,
      FALLING_EDGE 	= 1,
      RISING_EDGE  	= 2,
      BELOW_LEVEL 	= 3,
      ABOVE_LEVEL 	= 4,
      EQUAL         = 5,

}SW_SCOPE_TRIGG_METHOD_M;

typedef enum
{
	INVALID_TRIG = 0,
    SINGLE_TRIG  = 1,
    MUL_TRIG     = 2,
}SW_SCOPE_TRIGG_TIMES_MODE_M;

typedef enum
{
	INVALID_ACQ_MODE = 0,
    TASK_FRE = 1,
	CTR_FRE  = 2,
}SW_SCOPE_ACQ_MODE_M;

typedef enum
{
    TRIGG_POINT_FRONT   = 0,
    TRIGG_POINT_MID     = 1,
    TRIGG_POINT_BEHIND  = 2,
}SW_SCOPE_TRIGG_POINT_M;


typedef struct
{
		SW_SCOPE_TRIGG_METHOD_M     			emTrigMethod;     //the trigger mode of SW scope
        SW_SCOPE_TRIGG_POINT_M  					emTrigPoint;      //if the trigger mode is the rising or falling, it defines the trigger point.
        SW_SCOPE_ACQ_MODE_M     					emAcqMode;        //the acquisition mode of sw scope, 0: the acq period basic on the control frequency
                                                    													//1 is the acq period basic on the data record function task's period
        UINT8                  										u8TrigIndex;       //Trigger variable index.
        UINT16  				    									u16AcqInterval;      //it means times of the acq period basic on the em_acq_mode.
        FLOAT32 														f32ThrdValue;      //if the trigger mode is the rising or falling, it is the threshold value.
}SW_SCOPE_GUI_CFG_ITEM;

typedef struct
{
	    UINT8   u8Enable;
	    UINT8   u8RunStopCmd;        //
		UINT8 	u8TrigFlg;           //When using trig capture mode, it indicate whether the trig condition is satisfy.
		UINT8   u8DataMsgTxFlg;
		UINT8   u8VarType[SCOPE_VAR_MAX_ITEM_CNT];  //It indicate the channel variable the type, unsigned int or int, or float and so on
		UINT8 	u8VarChannelNum;    //Variable number.
//    	UINT16  u16MulDelayCnt;      //When using multi capture method, during two data capture, we should at least keep 500ms,  it indicate the delay time.

        INT16   i16RecRefCnt;
        INT16   i16RecCnt;
		float   f32PreData;
		float   f32PreLastData;
}SW_SCOPE_CTRL_OBJ;

#define   SW_SCOPE_ITEM_CMD_ID            0x01
#define   SW_SCOPE_GUI_CFG_ID             0x02
#define   SW_SCOPE_SW_TRIG_ID             0x03
#define   SW_SCOPE_DATA_CMD_ID            0x04
#define   SW_SCOPE_RUN_COMM_ID			  0x05
#define   SW_SCOPE_GET_DATA_ID            0x06
#define   SW_SCOPE_DATA_NOT_READY_ID      0x07
#define   SW_SCOPE_IS_RUNNING_ID          0x08
extern void SwScopeCmdSetLink(void *p_vAplDm);
extern void sw_scope_init(void);
extern void sw_scope_task(void);

#define GEN_SW_SCOPE_VAR_DECLARE
	#include "DEBUG_PLATFORM/SW_SCOPE/SW_Scope_Cfg.h"
#undef GEN_SW_SCOPE_VAR_DECLARE

#define GEN_SW_SCOPE_INIT_DECLARE
	#include "DEBUG_PLATFORM/SW_SCOPE/SW_Scope_Cfg.h"
#undef GEN_SW_SCOPE_INIT_DECLARE

#define GEN_SW_SCOPE_DATA_DECLARE
	#include "DEBUG_PLATFORM/SW_SCOPE/SW_Scope_Cfg.h"
#undef GEN_SW_SCOPE_DATA_DECLARE


#endif /* BSW_DEBUGPLATFORM_SW_SCOPE_H_ */
