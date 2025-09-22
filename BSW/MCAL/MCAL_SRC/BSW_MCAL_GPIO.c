/*********************************************************************
File name:       BSW_MCAL_GPIO.c 
Purpose :
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
**********************************************************************/
#include "../MCAL/MCAL_INC/BSW_MCAL_GPIO.h"

const struct GPIO_CFG_PARAM gc_stGpioCfgParam[] = GPIO_CFG_PARAM_TAB;

void AIO_SetupPinOption(enum GPIO_NUM emGpioNum,unsigned int flags,unsigned int u16AnDgType,unsigned int u16SampleClk)
{
    unsigned int u16TempData;
    unsigned int u16PinNumOffset;
    unsigned int u16SampleClkTemp = (u16SampleClk >> 1);
    unsigned char u16SampleMode = ((flags & GPIO_ASYNC) / GPIO_QUAL3);

    if(((emGpioNum - PIN_AIO_224) > 23)||(u16SampleClkTemp > 255)||(u16AnDgType > AIO_AI_TYPE)||(u16SampleMode > AI0_ASYN_SAMPLE))
        return;

    u16PinNumOffset   = emGpioNum - PIN_AIO_224;

    u16TempData = u16PinNumOffset >> 3;

    if (u16AnDgType == AIO_DI_TYPE)
    {
        EALLOW;
        GpioCtrlRegs.GPHCTRL.all  &= ~(255UL << (u16TempData << 3));
        GpioCtrlRegs.GPHCTRL.all  |= ((unsigned long)(u16SampleClk << (u16TempData << 3)));

        if(u16TempData < 2)
        {
           GpioCtrlRegs.GPHQSEL1.all &= ~(3UL <<(u16PinNumOffset << 1));   // 6 Sample Points
           GpioCtrlRegs.GPHQSEL1.all |= ((unsigned long)u16SampleMode <<(u16PinNumOffset << 1));
        }
        else
        {
            GpioCtrlRegs.GPHQSEL2.all &= ~(3UL <<((u16PinNumOffset%16) << 1));   // 6 Sample Points
            GpioCtrlRegs.GPHQSEL2.all |= ((unsigned long)u16SampleMode <<((u16PinNumOffset%16) << 1));
        }

        GpioCtrlRegs.GPHAMSEL.all &= (~(1UL << u16TempData));
       // GpioCtrlRegs.GPHAMSEL.all |= ((unsigned long)u16Type << u16TempData);    // Digital Mode

        EDIS;
    }
    else
    {
        EALLOW;
        GpioCtrlRegs.GPHAMSEL.all &= (~(1UL << u16TempData));
        GpioCtrlRegs.GPHAMSEL.all |= ((unsigned long)u16AnDgType << u16TempData);    // Digital Mode
        EDIS;
    }
}

void GPIO_SetupSamplePeriod(enum GPIO_NUM emGpioNum,Uint16 QualiSamplingPeriod)
{
    UINT32 pin32, qualprdx;

    pin32 = emGpioNum % 32;
    qualprdx = pin32 >> 3;

    if (emGpioNum < 32)
    {
        EALLOW;
        GpioCtrlRegs.GPACTRL.all &= ~(255UL << (qualprdx << 3));
        GpioCtrlRegs.GPACTRL.all |= (((unsigned long)QualiSamplingPeriod << (qualprdx << 3)));
        EDIS;
    }
    else
    {
        EALLOW;
        GpioCtrlRegs.GPBCTRL.all &= ~(255UL << (qualprdx << 3));
        GpioCtrlRegs.GPBCTRL.all |= (((unsigned long)QualiSamplingPeriod << (qualprdx << 3)));
        EDIS;
    }

}
void bsw_mcal_gpio_init(void){
    UINT16 i = 0;

    enum GPIO_DIR emGpioDirect = gc_stGpioCfgParam[i].emGpioDirect;
    enum GPIO_NUM emGpioNum   = gc_stGpioCfgParam[i].emGpioNum;
    enum GPIO_CORE emGpioCore = gc_stGpioCfgParam[i].emGpioCore;

    UINT16 u16TempData0;
   // UINT16 u16TempData1;
    UINT16 u16TempData2;

    for(i = 0;i < (sizeof(gc_stGpioCfgParam)/sizeof(struct GPIO_CFG_PARAM)); i++)
    {
        emGpioNum   = gc_stGpioCfgParam[i].emGpioNum;
        if(emGpioNum < GPIO_MAX_NUM){
            emGpioDirect = gc_stGpioCfgParam[i].emGpioDirect;
            emGpioCore 	= gc_stGpioCfgParam[i].emGpioCore;

            u16TempData0 = gc_stGpioCfgParam[i].u16GpioMux;
            GPIO_SetupPinMux(emGpioNum, emGpioCore,u16TempData0);
            u16TempData0 = gc_stGpioCfgParam[i].flag;
            GPIO_SetupPinOptions(emGpioNum,emGpioDirect,u16TempData0);

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == GPIO12_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO12 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == GPIO12_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO12       = 1;
                AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO12 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == GPIO13_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO13 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == GPIO13_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO13       = 1;
                AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO13 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == GPIO20_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO20 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == GPIO20_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO20       = 1;
                AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO20 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == GPIO21_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO21 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == GPIO21_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO21       = 1;
                AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO21 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == GPIO28_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == GPIO28_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPAAMSEL.bit.GPIO28       = 1;
                AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO28 = 1;
                EDIS;
            }

            if(emGpioDirect == GPIO_IN){
                u16TempData2 = gc_stGpioCfgParam[i].u16CtrlValue;
                GPIO_SetupSamplePeriod(emGpioNum,u16TempData2);

                u16TempData0 = gc_stGpioCfgParam[i].u16IntEnable;
                if(u16TempData0 == 1){   // The GPIO XINT enable
                }else{

                }
            }
            else
            {
                u16TempData0 = gc_stGpioCfgParam[i].emOutputDataType;
                GPIO_WritePin(emGpioNum, u16TempData0);
            }

        }else if(emGpioNum < AGPIO224_NUM)
        {

        }
        else if(emGpioNum < AGPIO_MAX_NUM){
            emGpioDirect = gc_stGpioCfgParam[i].emGpioDirect;
           // emGpioNum   = gc_stGpioCfgParam[i].emGpioNum;
            emGpioCore  = gc_stGpioCfgParam[i].emGpioCore;

            u16TempData0 = gc_stGpioCfgParam[i].u16GpioMux;
            GPIO_SetupPinMux(emGpioNum, emGpioCore,u16TempData0);
            u16TempData0 = gc_stGpioCfgParam[i].flag;
            GPIO_SetupPinOptions(emGpioNum,emGpioDirect,u16TempData0);

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO224_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO224_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO224       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO226_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO226 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO226_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO226       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO226 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO227_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO227_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO227       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO228_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO228 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO228_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO228       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO228 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO230_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO230_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO230       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;
                EDIS;
            }

            if((gc_stGpioCfgParam[i].u16AnalogEnable == 0) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO242_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 0;
                EDIS;
            }
            else if((gc_stGpioCfgParam[i].u16AnalogEnable == 1) && (gc_stGpioCfgParam[i].emGpioNum == AGPIO242_NUM))
            {
                EALLOW;
                GpioCtrlRegs.GPHAMSEL.bit.GPIO242       = 1;
                AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;
                EDIS;
            }

            if(emGpioDirect == GPIO_IN){
                u16TempData2 = gc_stGpioCfgParam[i].u16CtrlValue;
                GPIO_SetupSamplePeriod(emGpioNum,u16TempData2);

                u16TempData0 = gc_stGpioCfgParam[i].u16IntEnable;
                if(u16TempData0 == 1){   // The GPIO XINT enable
                }else{

                }
            }
            else
            {
                u16TempData0 = gc_stGpioCfgParam[i].emOutputDataType;
                GPIO_WritePin(emGpioNum, u16TempData0);
            }
        }
    }

}




