/*
 * Parameter_Cfg.c
 *
 *  Created on: 2022-07-18
 *      Author: Hongbo.jiang
 */

#include "DP_STACK/DP_STACK_BASIC.H"
#include "BSW_SVC_BASIC.h"
#include "DEBUG_PLATFORM/PARAMETER_CTRL/PARAMETER_CTRL.H"
#include "DP_STACK/NWM/NWM_STACK.H"
#include "DP_STACK/TPL/TPL_STACK.H"
#include "DEBUG_PLATFORM/DBG_BASIC.H"
#include "string.h"



static param_core_t param_core = {0};

static void reset_param_all(void);

void param_core_init(void)
{

    param_item_t *p_item = NULL;
    UINT32 i = 0;

    INIT_LIST_HEAD(&param_core.param_head);
    while(1)
    {
        p_item = (param_item_t *)auto_reg_get_func_cont_by_index(AUTO_REG_PARAM_CFG, i);
        if(p_item == NULL)
        {
            break;
        }
        INIT_LIST_HEAD(&p_item->param_node);  //The node list point itself.
        LIST_ADD_RAIL(&p_item->param_node, &param_core.param_head);  //Add one node at the rail in the circle list
        i++;
    }
    param_core.u8param_count = (UINT8)i;

    reset_param_all();
}

/*

    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |  num  |       api_func          |              param               |  ret  | SHELL |  PC   |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   1   |    show_all_param       |              NULL                |  tab  |   OK  |       |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   2   |    rd_param_item        |              n                   |  val  |   OK  |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   3   |    wr_param_item        |              n                   |  val  |   OK  |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   4   |    rs_param_item        |              n                   |  val  |   OK  |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   5   |    rs_param_all         |              NULL                | is_ok |   OK  |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   6   |    load_param_item      |              n                   | item  |       |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
    |   7   |    get_param_count      |              NULL                | num   |       |   OK  |
    +-------+-------------------------+----------------------------------+-------+-------+-------+
*/
static UINT8 rd_param_item(UINT16 n_item, UINT16 *p_u16ValAddr)
{
    param_item_t *p_item = NULL;
    const param_item_cfg_u8_t  *p_ParamItemCfgU8  = NULL;
    const param_item_cfg_i8_t  *p_ParamItemCfgI8  = NULL;
    const param_item_cfg_u16_t *p_ParamItemCfgU16 = NULL;
    const param_item_cfg_i16_t *p_ParamItemCfgI16 = NULL;
    const param_item_cfg_u32_t *p_ParamItemCfgU32 = NULL;
    const param_item_cfg_i32_t *p_ParamItemCfgI32 = NULL;
    const param_item_cfg_f32_t *p_ParamItemCfgF32 = NULL;
    UINT32 *p_u32TempAddr = NULL;
    UINT16 i = 0;
    UINT8  u8ByteSize = 0;
    list_t *cur_list = NULL;
    list_t *tag_list_head = &param_core.param_head;

    LIST_FOR_EACH_NEXT(cur_list, tag_list_head)
    {
        if(cur_list == tag_list_head) //Find the whole list.
            break;
        if(i == n_item)
        {
            p_item = LIST_ENTRY(cur_list, param_item_t, param_node);
            switch(p_item->emType){
            case eu_uint8:
                p_ParamItemCfgU8   = (const param_item_cfg_u8_t *)p_item->p_item_cfg;
                *p_u16ValAddr      = *((UINT16 *)(p_ParamItemCfgU8->p_u8Value));
                u8ByteSize         = sizeof(UINT8)*TYPE_8_BYTE_SIZE;
            break;
            case eu_int8:
                p_ParamItemCfgI8   = (const param_item_cfg_i8_t *)p_item->p_item_cfg;
                *p_u16ValAddr       = *((UINT16 *)(p_ParamItemCfgI8->p_i8Value));
                u8ByteSize          = sizeof(UINT8)*TYPE_8_BYTE_SIZE;
            break;
            case eu_uint16:
                p_ParamItemCfgU16   = (const param_item_cfg_u16_t *)p_item->p_item_cfg;
                *p_u16ValAddr       = *(p_ParamItemCfgU16->p_u16Value);
                u8ByteSize          = 2;
            break;
            case eu_int16:
                p_ParamItemCfgI16   = (const param_item_cfg_i16_t *)p_item->p_item_cfg;
                *p_u16ValAddr       = *(p_ParamItemCfgI16->p_i16Value);
                u8ByteSize          = 2;
            break;
            case eu_uint32:
                p_ParamItemCfgU32     = (const param_item_cfg_u32_t *)p_item->p_item_cfg;
                *p_u16ValAddr++     = *(p_ParamItemCfgU32->p_u32Value) & 0x0000ffff;
                *p_u16ValAddr       = *(p_ParamItemCfgU32->p_u32Value) >> 16;
                u8ByteSize          = 4;
            break;
            case eu_int32:
                p_ParamItemCfgI32   = (const param_item_cfg_i32_t *)p_item->p_item_cfg;
                *p_u16ValAddr++     = *(p_ParamItemCfgI32->p_i32Value) & 0x0000ffff;
                *p_u16ValAddr       = *(p_ParamItemCfgI32->p_i32Value) >> 16;
                u8ByteSize          = 4;
            break;
            case eu_fp32:
                p_ParamItemCfgF32   = (const param_item_cfg_f32_t *)p_item->p_item_cfg;
                p_u32TempAddr       = (UINT32 *)p_ParamItemCfgF32->p_f32Value;
                *p_u16ValAddr++     = (*p_u32TempAddr) & 0x0000ffff;
                *p_u16ValAddr       = (*p_u32TempAddr) >> 16;
                u8ByteSize          = 4;
            break;
            default:break;
            }
            break;
        }
        i++;
    }
    return u8ByteSize;
}

static INT8 wr_param_item(UINT16 n_item, UINT16 *p_u16DataBuf)
{
    const param_item_cfg_u8_t  *p_ParamItemCfgU8 = NULL;
    const param_item_cfg_i8_t  *p_ParamItemCfgI8 = NULL;
    const param_item_cfg_u16_t *p_ParamItemCfgU16 = NULL;
    const param_item_cfg_i16_t *p_ParamItemCfgI16 = NULL;
    const param_item_cfg_u32_t *p_ParamItemCfgU32 = NULL;
    const param_item_cfg_i32_t *p_ParamItemCfgI32 = NULL;
    const param_item_cfg_f32_t *p_ParamItemCfgF32 = NULL;
    UINT8   u8CurVal = 0;
    INT8    i8CurVal = 0;
    UINT16  u16CurVal = 0;
    INT16   i16CurVal = 0;
    UINT32  u32CurVal = 0;
    INT32   i32CurVal = 0;
    FLOAT32 f32CurVal = 0;
    UINT32  *p_u32TempData = NULL;
    param_item_t *p_item = NULL;
    UINT16 i = 0;
    list_t *cur_list = NULL;
    list_t *tag_list_head = &param_core.param_head;
    LIST_FOR_EACH_NEXT(cur_list, tag_list_head)
    {
        if(cur_list == tag_list_head) //Find the whole list.
            return 0;                 //Write fail
        if(i == n_item)
        {
            p_item = LIST_ENTRY(cur_list, param_item_t, param_node);
            switch(p_item->emType){
            case  eu_uint8:
                    u8CurVal = *p_u16DataBuf;
                    p_ParamItemCfgU8 = (const param_item_cfg_u8_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(UINT8)){ //Register variable size is right
                        if((u8CurVal >= p_ParamItemCfgU8->u8min_val)     \
                                &&(u16CurVal <= p_ParamItemCfgU8->u8max_val)){ //Over the min and max value range
                            *(p_ParamItemCfgU8->p_u8Value) = u8CurVal;
                            return 1;
                        }
                    }
            break;
            case  eu_int8:
                    u16CurVal = *p_u16DataBuf;
                    if(u16CurVal > 127) i8CurVal = (INT8)(u16CurVal | 0xff00U);
                    else i8CurVal = (INT8)u16CurVal;
                    p_ParamItemCfgI8 = (const param_item_cfg_i8_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(INT8)){ //Register variable size is right
                        if((i8CurVal >= p_ParamItemCfgI8->i8min_val)     \
                        &&(i8CurVal <= p_ParamItemCfgI8->i8max_val)){ //Over the min and max value range
                           *(p_ParamItemCfgI8->p_i8Value) = i8CurVal;
                           return 1;
                        }
                    }
            break;
            case  eu_uint16:
                    u16CurVal = *p_u16DataBuf;
                    p_ParamItemCfgU16 = (const param_item_cfg_u16_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(UINT16)){ //Register variable size is right
                        if((u16CurVal >= p_ParamItemCfgU16->u16min_val)     \
                                &&(u16CurVal <= p_ParamItemCfgU16->u16max_val)){ //Over the min and max value range
                            *(p_ParamItemCfgU16->p_u16Value) = u16CurVal;
                            return 1;
                        }
                    }
            break;
            case  eu_int16:
                    i16CurVal = *((INT16 *)p_u16DataBuf);
                    p_ParamItemCfgI16 = (const param_item_cfg_i16_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(INT16)){ //Register variable size is right
                        if((i16CurVal >= p_ParamItemCfgI16->i16min_val)     \
                        &&(i16CurVal <= p_ParamItemCfgI16->i16max_val)){ //Over the min and max value range
                           *(p_ParamItemCfgI16->p_i16Value) = i16CurVal;
                           return 1;
                        }
                    }
            break;
            case  eu_uint32:
                    u32CurVal = *p_u16DataBuf++;
                    u32CurVal |= ((UINT32)(*p_u16DataBuf) << 16);
                    p_ParamItemCfgU32 = (const param_item_cfg_u32_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(UINT32)){ //Register variable size is right
                        if((u32CurVal >= p_ParamItemCfgU32->u32min_val)     \
                        &&(u32CurVal <= p_ParamItemCfgU32->u32max_val)){ //Over the min and max value range
                            *(p_ParamItemCfgU32->p_u32Value) = u32CurVal;
                            return 1;
                        }
                    }
            break;
            case  eu_int32:
                    i32CurVal = *p_u16DataBuf++;
                    i32CurVal |= ((INT32)(*p_u16DataBuf) << 16);
                    p_ParamItemCfgI32 = (const param_item_cfg_i32_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(INT32)){ //Register variable size is right
                        if((i32CurVal >= p_ParamItemCfgI32->i32min_val)     \
                        &&(i32CurVal <= p_ParamItemCfgI32->i32max_val)){ //Over the min and max value range
                            *(p_ParamItemCfgI32->p_i32Value) = i32CurVal;
                            return 1;
                        }
                    }
            break;
            case  eu_fp32:
                    p_u32TempData = (UINT32 *)&f32CurVal;
                    *p_u32TempData = *p_u16DataBuf++;
                    *p_u32TempData |= ((UINT32)(*p_u16DataBuf) << 16);
                    p_ParamItemCfgF32 = (const param_item_cfg_f32_t *)p_item->p_item_cfg;
                    if(p_item->u16VarSize == sizeof(FLOAT32)){ //Register variable size is right
                        if((f32CurVal >= p_ParamItemCfgF32->f32min_val)     \
                        &&(f32CurVal <= p_ParamItemCfgF32->f32max_val)){ //Over the min and max value range
                            *(p_ParamItemCfgF32->p_f32Value) = f32CurVal;
                            return 1;
                        }
                    }
            break;
            default:break;
            }
            break;
        }
        i++;
    }
   return 0;                 //Write fail
}

static param_item_t *reset_param_item(UINT8 u8ItemNum)
{
    param_item_t *p_item = NULL;
    const param_item_cfg_u8_t *p_ParamItemCfgU8 = NULL;
    const param_item_cfg_i8_t *p_ParamItemCfgI8 = NULL;
    const param_item_cfg_u16_t *p_ParamItemCfgU16 = NULL;
    const param_item_cfg_i16_t *p_ParamItemCfgI16 = NULL;
    const param_item_cfg_u32_t *p_ParamItemCfgU32 = NULL;
    const param_item_cfg_i32_t *p_ParamItemCfgI32 = NULL;
    const param_item_cfg_f32_t *p_ParamItemCfgF32 = NULL;

    UINT8   u8CurDefVal = 0;
    INT8    i8CurDefVal = 0;
    UINT16  u16CurDefVal = 0;
    INT16   i16CurDefVal = 0;
    UINT32  u32CurDefVal = 0;
    INT32   i32CurDefVal = 0;
    FLOAT32 f32CurDefVal = 0;
    UINT8   i = 0;
    list_t  *cur_list = NULL;
    list_t  *tag_list_head = &param_core.param_head;

    LIST_FOR_EACH_NEXT(cur_list, tag_list_head)
    {
        if(cur_list == tag_list_head) //Find the whole list.
            break;
        if(i == u8ItemNum)  //Find the item
        {
            p_item = LIST_ENTRY(cur_list, param_item_t, param_node);
            switch(p_item->emType){
                case eu_uint8:
                    p_ParamItemCfgU8 = (const param_item_cfg_u8_t *)p_item->p_item_cfg;
                    u8CurDefVal = p_ParamItemCfgU8->u8def_val <= p_ParamItemCfgU8->u8max_val?p_ParamItemCfgU8->u8def_val:p_ParamItemCfgU8->u8max_val;
                    u8CurDefVal = (u8CurDefVal >= p_ParamItemCfgU8->u8min_val)?u8CurDefVal:p_ParamItemCfgU8->u8min_val;
                    *(p_ParamItemCfgU8->p_u8Value) = u8CurDefVal;
                break;
                case eu_int8:
                    p_ParamItemCfgI8 = (const param_item_cfg_i8_t *)p_item->p_item_cfg;
                    i8CurDefVal = p_ParamItemCfgI8->i8def_val <= p_ParamItemCfgI8->i8max_val?p_ParamItemCfgI8->i8def_val:p_ParamItemCfgI8->i8max_val;
                    i8CurDefVal = (i8CurDefVal >= p_ParamItemCfgI8->i8min_val)?i8CurDefVal:p_ParamItemCfgI8->i8min_val;
                    *(p_ParamItemCfgI8->p_i8Value) = i8CurDefVal;
                break;
                case eu_uint16:
                    p_ParamItemCfgU16 = (const param_item_cfg_u16_t *)p_item->p_item_cfg;
                    u16CurDefVal = p_ParamItemCfgU16->u16def_val <= p_ParamItemCfgU16->u16max_val?p_ParamItemCfgU16->u16def_val:p_ParamItemCfgU16->u16max_val;
                    u16CurDefVal = (u16CurDefVal >= p_ParamItemCfgU16->u16min_val)?u16CurDefVal:p_ParamItemCfgU16->u16min_val;
                    *(p_ParamItemCfgU16->p_u16Value) = u16CurDefVal;
                break;
                case eu_int16:
                    p_ParamItemCfgI16 = (const param_item_cfg_i16_t *)p_item->p_item_cfg;
                    i16CurDefVal = p_ParamItemCfgI16->i16def_val <= p_ParamItemCfgI16->i16max_val?p_ParamItemCfgI16->i16def_val:p_ParamItemCfgI16->i16max_val;
                    i16CurDefVal = (i16CurDefVal >= p_ParamItemCfgI16->i16min_val)?i16CurDefVal:p_ParamItemCfgI16->i16min_val;
                    *(p_ParamItemCfgI16->p_i16Value) = i16CurDefVal;
                break;
                case eu_uint32:
                    p_ParamItemCfgU32 = (const param_item_cfg_u32_t *)p_item->p_item_cfg;
                    u32CurDefVal = p_ParamItemCfgU32->u32def_val <= p_ParamItemCfgU32->u32max_val?p_ParamItemCfgU32->u32def_val:p_ParamItemCfgU32->u32max_val;
                    u32CurDefVal = (u32CurDefVal >= p_ParamItemCfgU32->u32min_val)?u32CurDefVal:p_ParamItemCfgU32->u32min_val;
                    *(p_ParamItemCfgU32->p_u32Value) = u32CurDefVal;
                break;
                case eu_int32:
                    p_ParamItemCfgI32 = (const param_item_cfg_i32_t *)p_item->p_item_cfg;
                    i32CurDefVal = p_ParamItemCfgI32->i32def_val <= p_ParamItemCfgI32->i32max_val?p_ParamItemCfgI32->i32def_val:p_ParamItemCfgI32->i32max_val;
                    i32CurDefVal = (i32CurDefVal >= p_ParamItemCfgI32->i32min_val)?i32CurDefVal:p_ParamItemCfgI32->i32min_val;
                    *(p_ParamItemCfgI32->p_i32Value) = i32CurDefVal;
                break;
                case eu_fp32:
                    p_ParamItemCfgF32 = (const param_item_cfg_f32_t *)p_item->p_item_cfg;
                    f32CurDefVal = p_ParamItemCfgF32->f32def_val <= p_ParamItemCfgF32->f32max_val?p_ParamItemCfgF32->f32def_val:p_ParamItemCfgF32->f32max_val;
                    f32CurDefVal = (f32CurDefVal >= p_ParamItemCfgF32->f32min_val)?f32CurDefVal:p_ParamItemCfgF32->f32min_val;
                    *(p_ParamItemCfgF32->p_f32Value) = f32CurDefVal;
                break;
                default:break;
               }
          break;
        }
        i++;
    }
    return p_item;
}

static void reset_param_all(void)
{
    param_item_t *p_item = NULL;
    const param_item_cfg_u16_t *p_ParamItemCfgU16 = NULL;
    const param_item_cfg_i16_t *p_ParamItemCfgI16 = NULL;
    const param_item_cfg_u32_t *p_ParamItemCfgU32 = NULL;
    const param_item_cfg_i32_t *p_ParamItemCfgI32 = NULL;
    const param_item_cfg_f32_t *p_ParamItemCfgF32 = NULL;

    UINT16  u16CurDefVal = 0;
    INT16   i16CurDefVal = 0;
    UINT32  u32CurDefVal = 0;
    INT32   i32CurDefVal = 0;
    FLOAT32 f32CurDefVal = 0;

    list_t *cur_list = NULL;
    list_t *tag_list_head = &param_core.param_head;
    LIST_FOR_EACH_NEXT(cur_list, tag_list_head)
    {
        p_item = LIST_ENTRY(cur_list, param_item_t, param_node); //Get the struct object address, which includes the param_node
        switch(p_item->emType){
            case eu_uint16:
            p_ParamItemCfgU16 = (const param_item_cfg_u16_t *)p_item->p_item_cfg;
            u16CurDefVal = p_ParamItemCfgU16->u16def_val <= p_ParamItemCfgU16->u16max_val?p_ParamItemCfgU16->u16def_val:p_ParamItemCfgU16->u16max_val;
            u16CurDefVal = (u16CurDefVal >= p_ParamItemCfgU16->u16min_val)?u16CurDefVal:p_ParamItemCfgU16->u16min_val;
            *(p_ParamItemCfgU16->p_u16Value) = u16CurDefVal;
            break;
            case eu_int16:
            p_ParamItemCfgI16 = (const param_item_cfg_i16_t *)p_item->p_item_cfg;
            i16CurDefVal = p_ParamItemCfgI16->i16def_val <= p_ParamItemCfgI16->i16max_val?p_ParamItemCfgI16->i16def_val:p_ParamItemCfgI16->i16max_val;
            i16CurDefVal = (i16CurDefVal >= p_ParamItemCfgI16->i16min_val)?i16CurDefVal:p_ParamItemCfgI16->i16min_val;
            *(p_ParamItemCfgI16->p_i16Value) = i16CurDefVal;
            break;
            case eu_uint32:
            p_ParamItemCfgU32 = (const param_item_cfg_u32_t *)p_item->p_item_cfg;
            u32CurDefVal = p_ParamItemCfgU32->u32def_val <= p_ParamItemCfgU32->u32max_val?p_ParamItemCfgU32->u32def_val:p_ParamItemCfgU32->u32max_val;
            u32CurDefVal = (u32CurDefVal >= p_ParamItemCfgU32->u32min_val)?u32CurDefVal:p_ParamItemCfgU32->u32min_val;
            *(p_ParamItemCfgU32->p_u32Value) = u32CurDefVal;
            break;
            case eu_int32:
            p_ParamItemCfgI32 = (const param_item_cfg_i32_t *)p_item->p_item_cfg;
            i32CurDefVal = p_ParamItemCfgI32->i32def_val <= p_ParamItemCfgI32->i32max_val?p_ParamItemCfgI32->i32def_val:p_ParamItemCfgI32->i32max_val;
            i32CurDefVal = (i32CurDefVal >= p_ParamItemCfgI32->i32min_val)?i32CurDefVal:p_ParamItemCfgI32->i32min_val;
            *(p_ParamItemCfgI32->p_i32Value) = i32CurDefVal;
            break;
            case eu_fp32:
            p_ParamItemCfgF32 = (const param_item_cfg_f32_t *)p_item->p_item_cfg;
            f32CurDefVal = p_ParamItemCfgF32->f32def_val <= p_ParamItemCfgF32->f32max_val?p_ParamItemCfgF32->f32def_val:p_ParamItemCfgF32->f32max_val;
            f32CurDefVal = (f32CurDefVal >= p_ParamItemCfgF32->f32min_val)?f32CurDefVal:p_ParamItemCfgF32->f32min_val;
            *(p_ParamItemCfgF32->p_f32Value) = f32CurDefVal;
            break;
            default:
            break;
        }
    }
}

static INT8  LoadParamItem(UINT8 u8ItemIndex, UINT16 *p_u16DataLen, PARAM_GET_ITEM_ACK_OBJ *p_ParamGetItem)
{
    param_item_t *p_item = NULL;
    const param_item_cfg_u8_t  *p_ParamItemCfgU8 = NULL;
    const param_item_cfg_i8_t  *p_ParamItemCfgI8 = NULL;
    const param_item_cfg_u16_t *p_ParamItemCfgU16 = NULL;
    const param_item_cfg_i16_t *p_ParamItemCfgI16 = NULL;
    const param_item_cfg_u32_t *p_ParamItemCfgU32 = NULL;
    const param_item_cfg_i32_t *p_ParamItemCfgI32 = NULL;
    const param_item_cfg_f32_t *p_ParamItemCfgF32 = NULL;
    UINT32 *p_u32Addr = NULL;
    UINT8         i = 0;
    list_t *cur_list = NULL;
    list_t *tag_list_head = &param_core.param_head;
    UINT8        u8CharNum = 0;
    const char  *p_u8char = NULL;
    LIST_FOR_EACH_NEXT(cur_list, tag_list_head)
    {
        if(cur_list == tag_list_head)
            return 0;
        if(i == u8ItemIndex)
        {
            p_item = LIST_ENTRY(cur_list, param_item_t, param_node);
            p_ParamGetItem->unParamAttr.bits.uh8VarType =  p_item->emType;
             switch(p_item->emType){
                 case  eu_uint8:
                     p_ParamItemCfgU8 = (const param_item_cfg_u8_t *)p_item->p_item_cfg;
                     p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgU8->u8def_val;
                     p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgU8->u8min_val;
                     p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgU8->u8max_val;
                     p_ParamGetItem->ua16CurValue[0] = *p_ParamItemCfgU8->p_u8Value;
                     p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgU8->emAttr;
                     p_u8char                        = p_ParamItemCfgU8->pchar_name;
                     for(u8CharNum = 0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum += 2){
                         p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
                         if(*p_u8char == '\0'){
                             break;
                         }
                         p_u8char++;
                         p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
                         if(*p_u8char == '\0'){
                             break;
                         }
                         p_u8char++;
                     }
                     if(*p_u8char != '\0')
                         return 0;
                 break;
                 case  eu_int8:
                     p_ParamItemCfgI8 = (const param_item_cfg_i8_t *)p_item->p_item_cfg;
                     p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgI8->i8def_val;
                     p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgI8->i8min_val;
                     p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgI8->i8max_val;
                     p_ParamGetItem->ua16CurValue[0] = *p_ParamItemCfgI8->p_i8Value;
                     p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgI8->emAttr;
                     p_u8char                        = p_ParamItemCfgI8->pchar_name;
                     for(u8CharNum =0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum +=2){
                         p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
                         if(*p_u8char == '\0'){
                             break;
                         }
                         p_u8char++;
                         p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
                         if(*p_u8char == '\0'){
                             break;
                         }
                         p_u8char++;
                     }
                     if(*p_u8char != '\0')
                         return 0;
                 break;
                case  eu_uint16:
                    p_ParamItemCfgU16 = (const param_item_cfg_u16_t *)p_item->p_item_cfg;
                    p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgU16->u16def_val;
                    p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgU16->u16min_val;
                    p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgU16->u16max_val;
                    p_ParamGetItem->ua16CurValue[0] = *p_ParamItemCfgU16->p_u16Value;
                    p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgU16->emAttr;
                    p_u8char 						= p_ParamItemCfgU16->pchar_name;
                    for(u8CharNum = 0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum += 2){
                        p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
                        if(*p_u8char == '\0'){
                            break;
                        }
                        p_u8char++;
                        p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
                        if(*p_u8char == '\0'){
                            break;
                        }
                        p_u8char++;
                    }
                    if(*p_u8char != '\0')
                        return 0;
                break;
                case  eu_int16:
					p_ParamItemCfgI16 = (const param_item_cfg_i16_t *)p_item->p_item_cfg;
					p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgI16->i16def_val;
					p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgI16->i16min_val;
					p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgI16->i16max_val;
					p_ParamGetItem->ua16CurValue[0] = *p_ParamItemCfgI16->p_i16Value;
                    p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgI16->emAttr;
					p_u8char 						= p_ParamItemCfgI16->pchar_name;
					for(u8CharNum =0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum +=2){
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
					}
					if(*p_u8char != '\0')
						return 0;
				break;
                case  eu_uint32:
					p_ParamItemCfgU32 = (const param_item_cfg_u32_t *)p_item->p_item_cfg;
					p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgU32->u32def_val & 0x0000FFFF;
					p_ParamGetItem->ua16DefValue[1] = (p_ParamItemCfgU32->u32def_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgU32->u32min_val & 0x0000FFFF;
					p_ParamGetItem->ua16MinValue[1] = (p_ParamItemCfgU32->u32min_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgU32->u32max_val & 0x0000FFFF;
					p_ParamGetItem->ua16MaxValue[1] = (p_ParamItemCfgU32->u32max_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16CurValue[0] = (*(p_ParamItemCfgU32->p_u32Value)) & 0x0000FFFF;
					p_ParamGetItem->ua16CurValue[1] = (*(p_ParamItemCfgU32->p_u32Value) >> 16) & 0x0000FFFF;
                    p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgU32->emAttr;
					p_u8char 						= p_ParamItemCfgU32->pchar_name;
					for(u8CharNum =0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum +=2){
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
					}
					if(*p_u8char != '\0')
						return 0;
				break;
                case  eu_int32:
					p_ParamItemCfgI32 = (const param_item_cfg_i32_t *)p_item->p_item_cfg;
					p_ParamGetItem->ua16DefValue[0] = p_ParamItemCfgI32->i32def_val & 0x0000FFFF;
					p_ParamGetItem->ua16DefValue[1] = (p_ParamItemCfgI32->i32def_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16MinValue[0] = p_ParamItemCfgI32->i32min_val & 0x0000FFFF;
					p_ParamGetItem->ua16MinValue[1] = (p_ParamItemCfgI32->i32min_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16MaxValue[0] = p_ParamItemCfgI32->i32max_val & 0x0000FFFF;
					p_ParamGetItem->ua16MaxValue[1] = (p_ParamItemCfgI32->i32max_val >> 16) & 0x0000FFFF;
					p_ParamGetItem->ua16CurValue[0] = (*(p_ParamItemCfgI32->p_i32Value)) & 0x0000FFFF;
					p_ParamGetItem->ua16CurValue[1] = (*(p_ParamItemCfgI32->p_i32Value) >> 16) & 0x0000FFFF;
                    p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgI32->emAttr;
					p_u8char 						= p_ParamItemCfgI32->pchar_name;
					for(u8CharNum =0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum +=2){
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
					}
					if(*p_u8char != '\0')
						return 0;
				break;
                case  eu_fp32:
					p_ParamItemCfgF32 = (const param_item_cfg_f32_t *)p_item->p_item_cfg;
					p_u32Addr         = (UINT32 *)&(p_ParamItemCfgF32->f32def_val);
					p_ParamGetItem->ua16DefValue[0] = *p_u32Addr & 0x0000FFFF;
					p_ParamGetItem->ua16DefValue[1] = (*p_u32Addr >> 16) & 0x0000FFFF;
					p_u32Addr         = (UINT32 *)&(p_ParamItemCfgF32->f32min_val);
					p_ParamGetItem->ua16MinValue[0] = *p_u32Addr & 0x0000FFFF;
					p_ParamGetItem->ua16MinValue[1] = (*p_u32Addr >> 16) & 0x0000FFFF;
					p_u32Addr         = (UINT32 *)&(p_ParamItemCfgF32->f32max_val);
					p_ParamGetItem->ua16MaxValue[0] = *p_u32Addr & 0x0000FFFF;
					p_ParamGetItem->ua16MaxValue[1] = (*p_u32Addr >> 16) & 0x0000FFFF;
					p_u32Addr         = (UINT32 *)p_ParamItemCfgF32->p_f32Value;
					p_ParamGetItem->ua16CurValue[0] = *p_u32Addr & 0x0000FFFF;
					p_ParamGetItem->ua16CurValue[1] = (*p_u32Addr >> 16) & 0x0000FFFF;
                    p_ParamGetItem->unParamAttr.bits.ul8VarAttr = p_ParamItemCfgF32->emAttr;
					p_u8char 						= p_ParamItemCfgF32->pchar_name;
					for(u8CharNum =0; u8CharNum < PARAM_VAR_NAME_MAX_LEN;u8CharNum +=2){
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] = *p_u8char;
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
						p_ParamGetItem->ua16VarName[u8CharNum >> 1] |= ((UINT16)(*p_u8char) << 8);
						if(*p_u8char == '\0'){
							break;
						}
						p_u8char++;
					}
					if(*p_u8char != '\0')
						return 0;
				break;
                default:break;
             }
             break;
        }
        i++;
    }
    *p_u16DataLen = sizeof(PARAM_GET_ITEM_ACK_OBJ)*TYPE_8_BYTE_SIZE \
    				- (PARAM_VAR_NAME_MAX_LEN >> 1)*TYPE_8_BYTE_SIZE       \
					+ u8CharNum + 2;
    return 1;
}


//--------------protocol-api interface
void ParamGetCntAction(APL_DOMAIN *p_stAplDm)
{
    PARAM_ITEM_CNT_ACK_OBJ  unParamAck = {0};
    FRAME_PROTOCOL_FORMAT   stFrame_info = {0};

    unParamAck.bits.uh8ItemNum                       = param_core.u8param_count;
    unParamAck.bits.ul8status                        = 1;
    stFrame_info.stAplDm.unAplCmd.u16all             = p_stAplDm->unAplCmd.u16all;
    stFrame_info.stNwmDm.unNwmAddr.bits.ul8DestAddr  = PC_NODE_ADDR;
    stFrame_info.stAplDm.u16AplDLC                   = sizeof(PARAM_ITEM_CNT_ACK_OBJ) * TYPE_8_BYTE_SIZE;
    stFrame_info.p_u16AppData                        = (UINT16 *)&unParamAck;

    Tpl_Single_Frame_Send(&stFrame_info);
}


void ParamGetItemAction(APL_DOMAIN *p_stAplDm)
{
    UINT8    u8ItemNum                      = 0;
    INT8     i8Status                       = 0;
    UINT16   *p_u16AplData                  = NULL;
    UINT16   u16AplDataSize                 = 0;
    PARAM_GET_ITEM_ACK_OBJ    stParamGetItemAck   = {0};
    FRAME_PROTOCOL_FORMAT     stParamGetItemFrame = {0};
    p_u16AplData   = (unsigned short *)p_stAplDm + sizeof(APL_DOMAIN);
    u8ItemNum      =  (UINT8)(*p_u16AplData);
    if(p_stAplDm -> u16AplDLC != 2) //if the request frame DLC is wrong, we donot require to ack.
    	return;

    if(u8ItemNum < param_core.u8param_count){
         i8Status = LoadParamItem(u8ItemNum, &u16AplDataSize ,&stParamGetItemAck);
    }else{
    	i8Status  = 0;
    }
    stParamGetItemAck.unParamItemCtrl.bits.ul8status     	= i8Status;
    stParamGetItemAck.unParamItemCtrl.bits.uh8ItemIndex  	= u8ItemNum;
    stParamGetItemFrame.p_u16AppData 						= (UINT16 *)&stParamGetItemAck;
    stParamGetItemFrame.stAplDm.unAplCmd.u16all          	= p_stAplDm->unAplCmd.u16all;
    stParamGetItemFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr 	= PC_NODE_ADDR;
    if(i8Status == 1){
    	stParamGetItemFrame.stAplDm.u16AplDLC = u16AplDataSize;  //Response the get item information.
    }else{
    	stParamGetItemFrame.stAplDm.u16AplDLC = 2;  //Only feedback the PARAM_ACK_WORD to PC.
    }
    Tpl_Single_Frame_Send(&stParamGetItemFrame);
}

void ParamWtItemAction(APL_DOMAIN *p_stAplDm)
{
    UINT8    u8ItemNum                      = 0;
    UINT16   *p_u16AplData                  = NULL;
    if(p_stAplDm -> u16AplDLC >= 4){
        p_u16AplData   = (unsigned short *)p_stAplDm + sizeof(APL_DOMAIN);
        u8ItemNum  =  (UINT8)*p_u16AplData;
        p_u16AplData++;
        wr_param_item(u8ItemNum, p_u16AplData);
    }
}


void ParamRdItemAction(APL_DOMAIN *p_stAplDm)
{
    PARAM_WR_ACK_OBJ        stAckWrInfo     = {0};
    UINT8    u8ItemNum                      = 0;
    UINT16   u16DataLen                     = 0;
    UINT16   *p_u16AplData                  = NULL;
    UINT8    u8DataByteNum                  = 0;
    FRAME_PROTOCOL_FORMAT   stParamRstFrame = {0};
    //Check the data length is coordinate with the APL protocol
    u16DataLen      =  p_stAplDm->u16AplDLC;
    if(u16DataLen ==  (sizeof(UINT16)*TYPE_8_BYTE_SIZE))
    {
        p_u16AplData   = (unsigned short *)p_stAplDm + sizeof(APL_DOMAIN);
        u8ItemNum  =  (UINT8)*p_u16AplData;
    }
    u8DataByteNum   = rd_param_item(u8ItemNum, stAckWrInfo.ua16ValueBuff);

    if(u8DataByteNum == 0)  stAckWrInfo.unParamItemCtrl.bits.ul8status = 0;
    else stAckWrInfo.unParamItemCtrl.bits.ul8status = 1;

    stAckWrInfo.unParamItemCtrl.bits.uh8ItemIndex           = u8ItemNum;

    stParamRstFrame.stAplDm.u16AplDLC                       = sizeof(PARAM_WR_ACK_OBJ)* TYPE_8_BYTE_SIZE - PARAM_WR_ACK_DATA_MAX_LEN*sizeof(UINT16)* TYPE_8_BYTE_SIZE \
                                                               + u8DataByteNum;
    stParamRstFrame.stAplDm.unAplCmd.u16all                 = p_stAplDm->unAplCmd.u16all;
    stParamRstFrame.p_u16AppData                            = (UINT16 *)&stAckWrInfo;
    stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

    Tpl_Single_Frame_Send(&stParamRstFrame);
}

void ParamRstItemAction(APL_DOMAIN *p_stAplDm)
{
//    param_item_t            *param_item = NULL;
    UINT8    u8ItemNum       = 0;
    UINT16   u16DataLen      = 0;
    UINT16   *p_u16AplData   = NULL;
    //Check the data length is coordinate with the APL protocol
    #if(MCU_MEM_STORE_MODE == BIG_END)
        u8TempData      = p_stAplDm->u16AplDLC >> 8;
        u16DataLen      = u8TempData;
        u16DataLen      = (p_stAplDm->u16AplDLC << 8)|(u16DataLen);
    #else
        u16DataLen      =  p_stAplDm->u16AplDLC;
    #endif
    if(u16DataLen ==  (sizeof(UINT16)*TYPE_8_BYTE_SIZE))
    {
        p_u16AplData   = (unsigned short *)p_stAplDm + sizeof(APL_DOMAIN);
#if(MCU_MEM_STORE_MODE == BIG_END)
        u8TempData  =  (*p_u16AplData) >> 8;
        u16nItem    = u8TempData;
        u16nItem    = ((*p_u16AplData) << 8)|(u16ItemNum);
#else
        u8ItemNum  =  (UINT8)*p_u16AplData;
#endif
    }
    //param_item      = reset_param_item(u8ItemNum);
    reset_param_item(u8ItemNum);
}

void ParamRstAllItemAction(APL_DOMAIN *p_stAplDm)
{
    FRAME_PROTOCOL_FORMAT   stParamRstFrame = {0};

    reset_param_all();
        stParamRstFrame.stAplDm.u16AplDLC                       = 0;
        stParamRstFrame.stAplDm.unAplCmd.u16all                 = p_stAplDm->unAplCmd.u16all;
        stParamRstFrame.p_u16AppData                            = NULL;
        stParamRstFrame.stNwmDm.unNwmAddr.bits.ul8DestAddr      = PC_NODE_ADDR;

        Tpl_Single_Frame_Send(&stParamRstFrame);
}

void ParamCfgCmdSetLink(void *p_stAplDmTemp){
    APL_DOMAIN *p_stAplDm =(APL_DOMAIN *)p_stAplDmTemp;
    UINT8 u8CmdId;
    u8CmdId = p_stAplDm->unAplCmd.bits.uh8CmdId;
    switch(u8CmdId){
        case CMD_ID_GET_PARAM_CNT:
            ParamGetCntAction(p_stAplDm);
        break;
        case CMD_ID_GET_PARAM_ITEM:
            ParamGetItemAction(p_stAplDm);
        break;
        case CMD_ID_WR_PARAM_ITEM:
            ParamWtItemAction(p_stAplDm);
        break;
        case CMD_ID_RD_PARAM_ITEM:
            ParamRdItemAction(p_stAplDm);
        break;
        case CMD_ID_RS_PARAM_ITEM:
            ParamRstItemAction(p_stAplDm);
        break;
        case CMD_ID_RS_ALL_PARAM_ITEM:
            ParamRstAllItemAction(p_stAplDm);
        break;
        default:break;
    }
}

