/*********************************************************************
File name:       BSW_MCAL_ADC.c 
Purpose :
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang

**********************************************************************/
#include <BSW/MCAL/MCAL_INC/BSW_MCAL_ADC.h>
#include <BSW/ENV_CFG/HARDWARE_ENV_CFG.h>
#include <BSW/MCAL/MCAL_INC/BSW_MCAL_SYS_CLOCK.h>
#include <BSW/CHIP_PACK/common/include/F28x_Project.h>
//#include <BSW/ENV_CFG/HARDWARE_ENV_CFG.h>

const ADC_MODULE_CFG gc_stAdcSysCfg[] = REG_ADC_MODULE_CFG_TAB;
const struct ADCx_CFG_SOC gc_stAdcSocCfgParam[] =  ADC_CFG_SOC_TAB;

extern float g_f32SysClkFreq;
static void InitAdcSoc(struct ADCx_CFG_SOC stAdcSocCfgParam)
{
    unsigned int u16TempData = stAdcSocCfgParam.u16AqcPs;

    if (u16TempData < ADC_SOC_ACQPS_MIN)
    {
        u16TempData = ADC_SOC_ACQPS_MIN;
    }
    else if (u16TempData > ADC_SOC_ACQPS_MAX)
    {
        u16TempData = ADC_SOC_ACQPS_MAX;
    }
    EALLOW;
    switch (stAdcSocCfgParam.emAdcx_modele)
    {
        case ADC_ADCA_MODULE:
        {
            switch(stAdcSocCfgParam.emAdcx_socNum)
            {
                case ADC_SOC_NUMBER0:
                {
                    AdcaRegs.ADCSOC0CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC0CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER1:
                {
                    AdcaRegs.ADCSOC1CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC1CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER2:
                {
                    AdcaRegs.ADCSOC2CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC2CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER3:
                {
                    AdcaRegs.ADCSOC3CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC3CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER4:
                {
                    AdcaRegs.ADCSOC4CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC4CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER5:
                {
                    AdcaRegs.ADCSOC5CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC5CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER6:
                {
                    AdcaRegs.ADCSOC6CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC6CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER7:
                {
                    AdcaRegs.ADCSOC7CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC7CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC7CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER8:
                {
                    AdcaRegs.ADCSOC8CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC8CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC8CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER9:
                {
                    AdcaRegs.ADCSOC9CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC9CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC9CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER10:
                {
                    AdcaRegs.ADCSOC10CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC10CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC10CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER11:
                {
                    AdcaRegs.ADCSOC11CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC11CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC11CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER12:
                {
                    AdcaRegs.ADCSOC12CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC12CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC12CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER13:
                {
                    AdcaRegs.ADCSOC13CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC13CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC13CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER14:
                {
                    AdcaRegs.ADCSOC14CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC14CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER15:
                {
                    AdcaRegs.ADCSOC15CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdcaRegs.ADCSOC15CTL.bit.ACQPS = u16TempData;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case ADC_ADCC_MODULE:
        {
            switch(stAdcSocCfgParam.emAdcx_socNum)
            {
                case ADC_SOC_NUMBER0:
                {
                    AdccRegs.ADCSOC0CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC0CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER1:
                {
                    AdccRegs.ADCSOC1CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC1CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER2:
                {
                    AdccRegs.ADCSOC2CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC2CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER3:
                {
                    AdccRegs.ADCSOC3CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC3CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER4:
                {
                    AdccRegs.ADCSOC4CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC4CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC4CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER5:
                {
                    AdccRegs.ADCSOC5CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC5CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC5CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER6:
                {
                    AdccRegs.ADCSOC6CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC6CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC6CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER7:
                {
                    AdccRegs.ADCSOC7CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC7CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC7CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER8:
                {
                    AdccRegs.ADCSOC8CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC8CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC8CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER9:
                {
                    AdccRegs.ADCSOC9CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC9CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC9CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER10:
                {
                    AdccRegs.ADCSOC10CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC10CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC10CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER11:
                {
                    AdccRegs.ADCSOC11CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC11CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC11CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER12:
                {
                    AdccRegs.ADCSOC12CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC12CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC12CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER13:
                {
                    AdccRegs.ADCSOC13CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC13CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC13CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER14:
                {
                    AdccRegs.ADCSOC14CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC14CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC14CTL.bit.ACQPS = u16TempData;
                    break;
                }
                case ADC_SOC_NUMBER15:
                {
                    AdccRegs.ADCSOC15CTL.bit.CHSEL = stAdcSocCfgParam.emAdcx_chSel;
                    AdccRegs.ADCSOC15CTL.bit.TRIGSEL = stAdcSocCfgParam.emAdcx_trigSel;
                    AdccRegs.ADCSOC15CTL.bit.ACQPS = u16TempData;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    EDIS;
}
UINT16 u16AdcPrescale = 0;
void AdcModuleInit(enum ADC_MODULE emAdcModule, UINT16 u16IntEnable, UINT16 u16IntSrc, float f32AdcClkFreq){

    float  f32SysClkFreq  = SYS_CLK_GetSysClkFreq();

    if(f32AdcClkFreq <= 0.0f)
        return;
    u16AdcPrescale = (UINT16)(f32SysClkFreq/f32AdcClkFreq);

    if(u16AdcPrescale > 8)  u16AdcPrescale = (8U - 1U) << 1;

    else if(u16AdcPrescale == 0) u16AdcPrescale = 0;
    else u16AdcPrescale = (u16AdcPrescale - 1U) << 1;

    EALLOW;
    switch(emAdcModule){
       case ADC_ADCA_MODULE:
           AdcaRegs.ADCCTL2.bit.PRESCALE    = u16AdcPrescale;
           AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
           AdcaRegs.ADCCTL1.bit.ADCPWDNZ    = 1;
           if(u16IntEnable == 1)
           {
              AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = u16IntSrc;/* End of SOC9 will set INT1 flag */
              AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;/* Enable INT1 flag */
              AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;/* continuous mode */
              AdcaRegs.ADCINTFLGCLR.bit.ADCINT1  = 1;/* make sure INT1 flag is cleared */
           }
           break;
       case ADC_ADCC_MODULE:
           AdccRegs.ADCCTL2.bit.PRESCALE    = u16AdcPrescale;
           AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
           AdccRegs.ADCCTL1.bit.ADCPWDNZ    = 1;
           if(u16IntEnable == 1)
           {
              AdccRegs.ADCINTSEL1N2.bit.INT1SEL  = u16IntSrc;   /* End of SOC9 will set INT1 flag */
              AdccRegs.ADCINTSEL1N2.bit.INT1E    = 1;           /* Enable INT1 flag */
              AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;           /* continuous mode */
              AdccRegs.ADCINTFLGCLR.bit.ADCINT1  = 1;           /* make sure INT1 flag is cleared */
           }
           break;
       default:break;
    }
    EDIS;
    DELAY_US(ADC_USDELAY);//ADC_USDELAY
}

void bsw_mcal_sf_adc_init(void)
{
     unsigned int i = 0;
     const ADC_MODULE_CFG *p_stAdcSysCfg = gc_stAdcSysCfg;

     for(i = 0; i < sizeof(gc_stAdcSysCfg)/sizeof(ADC_MODULE_CFG); i++)
     {
         SetVREF(p_stAdcSysCfg->emAdcModule,p_stAdcSysCfg->emAdcRefMode, p_stAdcSysCfg->emAdcRefVolt);
         AdcModuleInit(p_stAdcSysCfg->emAdcModule,p_stAdcSysCfg->u16IntEnable,\
                       p_stAdcSysCfg->u16IntSrc,p_stAdcSysCfg->f32AdcClkFreq);
         p_stAdcSysCfg++;
     }

     for(i = 0;i < (sizeof(gc_stAdcSocCfgParam)/sizeof(struct ADCx_CFG_SOC)); i++)
     {
         InitAdcSoc(gc_stAdcSocCfgParam[i]);
     }

}









