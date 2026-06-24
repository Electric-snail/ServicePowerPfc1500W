/*
 * LED_CTRL.C
 *
 *  Created on: 2026.1.6
 *      Author: Administrator
 */
#include "HAL_INC/BSW_HAL_GPIO.H"
#include "SYS_FSM/SYS_FSM.H"
#include "LED_CTRL/LED_CTRL.H"

void led_ctrl_500ms_task(void){
	static unsigned short   s_u16Cnt = 0;
    s_u16Cnt++;
    if(s_u16Cnt & 0x0001)
        BSW_HAL_YELLOW_ON();
    else
        BSW_HAL_YELLOW_OFF();
}

