/*********************************************************************
File name:       BSW_MCAL_INT_CTRL.c
Purpose :
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/
#include "MCAL_INC/BSW_MCAL_INT_CTRL.h"
#include "MCAL_INC/BSW_MCAL_MEMCFG.h"
#include "ISR_INC/BSW_ISR_CPUTIMER.H"
#include "ISR_INC/BSW_ISR_ADC.H"

const INT_PARAM_CFG gc_stIntParamCfg[] = REG_INT_PARAM_CFG_TAB;

void InitUserInt(void)
{
    unsigned int i;
    const INT_PARAM_CFG *p_stIntParamCfg = gc_stIntParamCfg;
    PINT *p_IntFunc;
    UINT16 *p_u16All = NULL;
    unsigned int u16VectOffset = 0;
    enum INT_VECT_X emINTx;
    enum INT_VECT_Y emINTy;
    /**** configure the User Interrupt vector **************/
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;
    EALLOW;
    for(i = 0; i < (sizeof(gc_stIntParamCfg)/sizeof(INT_PARAM_CFG)); i++){
        emINTx = p_stIntParamCfg->emINTx;
        emINTy = p_stIntParamCfg->emINTy;
        if(emINTx < INT_X_MAX){
           if(emINTx > INT_X12){
               if(p_stIntParamCfg->fp_isr != NULL){
                   u16VectOffset = (emINTx << 1);
                   p_IntFunc  = (PINT *)((UINT16 *)&PieVectTable + u16VectOffset);
                   *p_IntFunc = p_stIntParamCfg->fp_isr;
                }
           }else{
                if((p_stIntParamCfg->fp_isr != NULL)&&(emINTy > 0)&&(emINTy < INT_Y_MAX)){
                    if (emINTy < INT_Y9){
                        u16VectOffset = (emINTx + 3) * 16 + ((emINTy -1)<< 1);
                    }
                    else{
                        u16VectOffset = (emINTx + 15) * 16 + ((emINTy -INT_Y9) << 1);
                    }
                   p_IntFunc = (PINT *)((UINT16 *)&PieVectTable + u16VectOffset);
                   *p_IntFunc = p_stIntParamCfg->fp_isr;
                }
           }
        }
		p_stIntParamCfg++;
    }
    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEACK.all        = 0xFFFF;
    p_stIntParamCfg = gc_stIntParamCfg;
    /****Peripheral stage interrupt ***********/
    for(i = 0; i < (sizeof(gc_stIntParamCfg)/sizeof(INT_PARAM_CFG)); i++){
        emINTx = p_stIntParamCfg->emINTx;
        emINTy = p_stIntParamCfg->emINTy;
        if((emINTx <= INT_X12)&&(emINTy > 0)&&(emINTy <= 16)){
            p_u16All = ((UINT16 *)&PieCtrlRegs + (emINTx << 1));
            *p_u16All = (*p_u16All) | (1 << (emINTy - 1));
            PieCtrlRegs.PIEACK.all = (1U <<(emINTx - 1));
        }
		p_stIntParamCfg++;
    }
    /****Enable CPU interrupt and Clear flag ********/
    IFR  = 0x0000;                      //Clear all interrupt flag
	p_stIntParamCfg = gc_stIntParamCfg;
    for(i = 0; i < (sizeof(gc_stIntParamCfg)/sizeof(INT_PARAM_CFG)); i++){
          emINTx = p_stIntParamCfg->emINTx;
          if(emINTx <= INT_X_MAX){
              IER |= (1U <<(emINTx - 1));
          }
	 	  p_stIntParamCfg++;
    }
}

void bsw_mcal_pie_ctrl_init(void)
{
    /* Disable CPU interrupts and clear all CPU interrupt flags*/
    DINT;
    //unlock the access Dx register;
    EALLOW;
    MemCfgRegs.DxLOCK.all               = 0x00000000;
    //allow write the vector ram.
    MemCfgRegs.DxACCPROT1.all           = 0x00000000;

    EDIS;

    InitPieVectTable();

    InitPieCtrl();

    InitUserInt();

    EALLOW;
    //block write the vector ram.
    MemCfgRegs.DxACCPROT1.all           = (1U << CPUWRPROT_PIEVECT_BIT);
    //lock the access Dx register;
    MemCfgRegs.DxLOCK.bit.LOCK_PIEVECT  = 1;
    EDIS;
}


