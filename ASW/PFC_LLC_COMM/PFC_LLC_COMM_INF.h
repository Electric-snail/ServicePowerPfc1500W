/*
 * PFC_LLC_COMM_INF.h
 *
 *  Created on: 2022.11.24.
 *      Author: xj8r1j
 */
#ifndef _PFC_LLC_COMM_INF_H_
#define _PFC_LLC_COMM_INF_H_
#include "../PFC_LLC_COMM/pfc_llc_comm.h"

extern INT8 g_i8PfcPowerStatusTest;


/* signal status */
typedef enum {
    WORK_MODE_STANDBY = 0,
    WORK_MODE_PFC_3PH3W,
    WORK_MODE_PFC_3PH4W,
    WORK_MODE_PFC_1PH1,
    WORK_MODE_PFC_1PH2,
    WORK_MODE_PFC_1PH3,
    WORK_MODE_INV_3PH3W,
    WORK_MODE_INV_1PH1,
    WORK_MODE_INV_1PH2,
    WORK_MODE_INV_1PH3,
    WORK_MODE_INV_ERR,
}WORK_MODE_t;

typedef enum {
    PSM_STANDBY = 0,
    PSM_RUNNING,
    PSM_ERR,
}PSM_STATE_t;

typedef struct{
	//BYTE0
    UINT16 rolling_counter            :8;   //0
    //BYTE1
    UINT16 b4WorkMode                 :4;
    UINT16 b4PsmState                 :4;   //1
    //BYTE2
    UINT16 fault_level1_event0L       :8;   //2
    //BYTE3
    UINT16 fault_level1_event0H       :8;   //3
    //BYTE4
    UINT16 fault_level1_event1L       :8;   //4
    //BYTE5
    UINT16 fault_level1_event1H       :8;   //5
    //BYTE6
    UINT16 fault_level2_event0L       :8;   //6
    //BYTE7
    UINT16 fault_level2_event0H       :8;   //7
    //BYTE8
    UINT16 fault_level2_event1L       :8;   //8
    //BYTE9
    UINT16 fault_level2_event1H       :8;   //9
    //BYTE10
    UINT16 fault_level3_event0L       :8;   //10
    //BYTE11
    UINT16 fault_level3_event0H       :8;   //11
    //BYTE12
    UINT16 fault_level3_event1L       :8;   //12
    //BYTE13
    UINT16 fault_level3_event1H       :8;   //13
    //BYTE14
    UINT16 PhaseAVacRmsL              :8;   //14
    //BYTE15
    UINT16 PhaseAVacRmsH              :8;   //15
    //BYTE16
    UINT16 PhaseBVacRmsL              :8;   //16
    //BYTE17
    UINT16 PhaseBVacRmsH              :8;   //17
    //BYTE18
    UINT16 PhaseCVacRmsL              :8;   //18
    //BYTE19
    UINT16 PhaseCVacRmsH              :8;   //19
    //BYTE20
    UINT16 PhaseAIacRmsL              :8;   //20
    //BYTE21
    UINT16 PhaseAIacRmsH              :8;   //21
    //BYTE22
    UINT16 PhaseBIacRmsL              :8;   //22
    //BYTE23
    UINT16 PhaseBIacRmsH              :8;   //23
    //BYTE24
    UINT16 PhaseCIacRmsL              :8;   //24
    //BYTE25
    UINT16 PhaseCIacRmsH              :8;   //25
    //BYTE26
    UINT16 InvOutputPwrL              :8;   //26
    //BYTE27
    UINT16 InvOutputPwrH              :8;   //27
    //BYTE28
    UINT16 AcFreqHzL                  :8;   //28
    //BYTE29
    UINT16 AcFreqHzH                  :8;   //29
    //BYTE30
    UINT16 VbusAvgL                   :8;   //30
    //BYTE31
    UINT16 VbusAvgH                   :8;   //31
    //BYTE32
    UINT16 IbusAvgL                   :8;   //32
    //BYTE33
    UINT16 IbusAvgH                   :8;   //33
    //BYTE34
    UINT16 pfcMosfetTemp              :8;   //34
    //BYTE35
    UINT16 llcPMosfetTemp             :8;   //35
    //BYTE36
    UINT16 Test0ValueL                :8;   //36
    //BYTE37
    UINT16 Test0ValueH                :8;   //37
    //BYTE38
    UINT16 Test1ValueL                :8;   //38
    //BYTE39
    UINT16 Test1ValueH                :8;   //39
    //BYTE40
    UINT16 Test2ValueL                :8;  //40
    //BYTE41
    UINT16 Test2ValueH                :8;  //41
    //BYTE42
    UINT16 Test3ValueL                :8;  //42
    //BYTE43
    UINT16 Test3ValueH                :8;  //43
}PFC_LLC_COMM_MATRIX_BYTES;

typedef union
{
    UINT16  						ua16Buff[sizeof(PFC_LLC_COMM_MATRIX_BYTES)/sizeof(UINT16)];
    PFC_LLC_COMM_MATRIX_BYTES       bits;
}MSG_PFC_LLC_SLOW_U;

typedef struct{
    float f32PfcVolt;
}PFC_LLC_COMM_FAST_MATRIX_T;

typedef union
{
    UINT16                           ua16Buff[sizeof(PFC_LLC_COMM_FAST_MATRIX_T)/sizeof(UINT16)];
    PFC_LLC_COMM_FAST_MATRIX_T       stPfcLlcFastData;
}MSG_PFC_LLC_FAST_U;

extern MSG_PFC_LLC_SLOW_U g_unPfcSlowRxMsg;
extern MSG_PFC_LLC_FAST_U g_unPfcFastRxMsg;

extern void pfc_llc_comm_rx_hander(void *p_stAplDmTemp);

#define u8_get_rolling_counter()         (g_unPfcSlowRxMsg.bits.rolling_counter)
#define em_get_workMode()                (g_unPfcSlowRxMsg.bits.b4WorkMode)
#define em_get_psmState()                (g_unPfcSlowRxMsg.bits.b4PsmState)
#define set_em_get_psmState(VALUE)       (g_unPfcSlowRxMsg.bits.b4PsmState = VALUE)
#define u16_get_pfc_fault_L1E0_l()       (g_unPfcSlowRxMsg.bits.fault_level1_event0L)
#define u16_get_pfc_fault_L1E0_h()       (g_unPfcSlowRxMsg.bits.fault_level1_event0H)
#define u16_get_pfc_fault_L1E1_l()       (g_unPfcSlowRxMsg.bits.fault_level1_event1L)
#define u16_get_pfc_fault_L1E1_h()       (g_unPfcSlowRxMsg.bits.fault_level1_event1H)

#define u16_get_pfc_fault_L2E0_l()       (g_unPfcSlowRxMsg.bits.fault_level2_event0L)
#define u16_get_pfc_fault_L2E0_h()       (g_unPfcSlowRxMsg.bits.fault_level2_event0H)
#define u16_get_pfc_fault_L2E1_l()       (g_unPfcSlowRxMsg.bits.fault_level2_event1L)
#define u16_get_pfc_fault_L2E1_h()       (g_unPfcSlowRxMsg.bits.fault_level2_event1H)

#define u16_get_pfc_fault_L3E0_l()       (g_unPfcSlowRxMsg.bits.fault_level3_event0L)
#define u16_get_pfc_fault_L3E0_h()       (g_unPfcSlowRxMsg.bits.fault_level3_event0H)
#define u16_get_pfc_fault_L3E1_l()       (g_unPfcSlowRxMsg.bits.fault_level3_event1L)
#define u16_get_pfc_fault_L3E1_h()       (g_unPfcSlowRxMsg.bits.fault_level3_event1H)

#define u8_get_phaseA_Vac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseAVacRmsH)
#define u8_get_phaseA_Vac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseAVacRmsL)

#define u8_get_phaseB_Vac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseBVacRmsH)
#define u8_get_phaseB_Vac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseBVacRmsL)

#define u8_get_phaseC_Vac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseCVacRmsH)
#define u8_get_phaseC_Vac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseCVacRmsL)

#define u8_get_phaseA_Iac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseAIacRmsH)
#define u8_get_phaseA_Iac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseAIacRmsL)
#define u8_get_phaseA_Iac_rms()         ((g_unPfcSlowRxMsg.bits.PhaseAIacRmsH<<8)|g_stPfc_llc_commMsg.bits.PhaseAIacRmsL)

#define u8_get_phaseB_Iac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseBIacRmsH)
#define u8_get_phaseB_Iac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseBIacRmsL)
#define u8_get_phaseB_Iac_rms()         ((g_unPfcSlowRxMsg.bits.PhaseBIacRmsH<<8) | g_stPfc_llc_commMsg.bits.PhaseBIacRmsL)

#define u8_get_phaseC_Iac_rmsH()         (g_unPfcSlowRxMsg.bits.PhaseCIacRmsH)
#define u8_get_phaseC_Iac_rmsL()         (g_unPfcSlowRxMsg.bits.PhaseCIacRmsL)
#define u8_get_phaseC_Iac_rms()         ((g_unPfcSlowRxMsg.bits.PhaseCIacRmsH<<8)|g_stPfc_llc_commMsg.bits.PhaseCIacRmsL)

#define u8_get_acFrequency_hzL()         (g_unPfcSlowRxMsg.bits.AcFreqHzL)
#define u8_get_acFrequency_hzH()         (g_unPfcSlowRxMsg.bits.AcFreqHzH)

#define u8_get_Vbus_avgL()               (g_unPfcSlowRxMsg.bits.VbusAvgL)
#define u8_get_Vbus_avgH()               (g_unPfcSlowRxMsg.bits.VbusAvgH)
#define u8_get_Vbus_avg()                ((g_unPfcSlowRxMsg.bits.VbusAvgH<<8)|g_stPfc_llc_commMsg.bits.VbusAvgL)

#define u8_get_Ibus_avgL()               (g_unPfcSlowRxMsg.bits.IbusAvgL)
#define u8_get_Ibus_avgH()               (g_unPfcSlowRxMsg.bits.IbusAvgH)
#define u8_get_Ibus_avg()                ((g_unPfcSlowRxMsg.bits.IbusAvgH<<8)|g_stPfc_llc_commMsg.bits.IbusAvgL)

#define u8_get_pfcMosfetTemp()           (g_unPfcSlowRxMsg.bits.pfcMosfetTemp)
#define u8_get_llcPMosfetTemp()          (g_unPfcSlowRxMsg.bits.llcPMosfetTemp)
#define u16_get_test_val0L()             (g_unPfcSlowRxMsg.bits.Test0ValueL)
#define u16_get_test_val0H()             (g_unPfcSlowRxMsg.bits.Test0ValueH)
#define u16_get_test_val1L()             (g_unPfcSlowRxMsg.bits.Test1ValueL)
#define u16_get_test_val1H()             (g_unPfcSlowRxMsg.bits.Test1ValueH)
#define u16_get_test_val2L()             (g_unPfcSlowRxMsg.bits.Test2ValueL)
#define u16_get_test_val2H()             (g_unPfcSlowRxMsg.bits.Test2ValueH)
#define u16_get_test_val3L()             (g_unPfcSlowRxMsg.bits.Test3ValueL)
#define u16_get_test_val3H()             (g_unPfcSlowRxMsg.bits.Test3ValueH)

#define u16_get_acFrequency_hz()         (g_unPfcSlowRxMsg.bits.AcFreqHzL + (g_unPfcSlowRxMsg.bits.AcFreqHzH << 8))
#define u16_get_Vbus_avg()                   (g_unPfcSlowRxMsg.bits.VbusAvgL + (g_unPfcSlowRxMsg.bits.IbusAvgH << 8))

#define    u16_loop_work_mode()         0

#endif /* _PFC_LLC_COMM_INF_H_ */
