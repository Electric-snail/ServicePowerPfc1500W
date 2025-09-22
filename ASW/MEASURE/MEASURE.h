/*
 * measure.h
 *
 *  Created on: 2022/11/24
 *      Author: rjgslg
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#include "MEASURE/MEASURE_INF.h"

/******macros definition region**************/
#define VDC_BUSAVG_FC_HZ            10.0f
#define VDC_OUTAVG_FC_HZ            10.0f
#define IDC_OUTAVG_FC_HZ            10.0f

#define TEMP_OUTAVG_FC_HZ           1.0f
#define TASK_10MS_TS                0.01f

#define B2B_DIFF_OUTAVG_FC_HZ       1.0f
#define OUT_DIFF_OUTAVG_FC_HZ       1.0f


/*****data type definition region ***************/



/********* function declaration region *********************************/
extern void measure_1ms_task(void);
extern void measure_10ms_task(void);
extern void measure_init(void);

#endif /* MEASURE_H_ */
