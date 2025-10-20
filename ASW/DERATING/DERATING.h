/*
 * derate.h
 *
 *  Created on: 2022/12/5
 *      Author: fjf897
 */

#ifndef ASW_DERATING_DERATING_H_
#define ASW_DERATING_DERATING_H_

void  derating_init(void);
void  derating_task_20ms(void);
float GetPowerDeratingPower(void);

#endif /* ASW_DERATING_DERATING_H_ */
