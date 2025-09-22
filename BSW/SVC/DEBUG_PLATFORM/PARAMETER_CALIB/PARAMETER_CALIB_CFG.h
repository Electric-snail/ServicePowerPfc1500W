/*
 * SW_Scope_Cfg.h
 *
 *  Created on: 2022.9.15
 *      Author: hongbo
 */
#include "DEBUG_PLATFORM/PARAMETER_CALIB/PARAMETER_CALIB_DEFINE.h"


//X = RVS ��ʾ������趨��ֵΪ��׼��У׼��ϵͳ���������ֵ��
//���� ����PWM����DAC, �趨�ο���ѹ���趨ֵ���趨Ϊ12V, ʵ�����Ϊ11.5V; ��У׼��Ŀ����ʹ��ʵ�����ֵ������趨ֵһ����
//X = ; ��ʾ��ʵ�����ֵΪ��׼��У׼����ϱ���ֵ��ʹ�������ֵ�����ϱ�ֵһ����
//Y��ʾ У׼���������ͣ�����Ǹ�������F32, ������з������ͣ���I16, ��֧����������
//PARAME_CALIB_X_ITEM_Y     (name,              K_MAX,      K_MIN,       B_MAX,     B_MIN)
PARAME_CALIB_START()
PARAME_CALIB_ITEM_F32(VOUT_CALIB,         1.2f,           0.8f,             5.0f,             -5.0f)
PARAME_CALIB_ITEM_I16(IOUT_CALIB,            307,           204,             1280,             -1280)
PARAME_CALIB_RVS_ITEM_F32(VREF_CALIB, 	1.2f, 	        0.8f,             5.0f,  	        -5.0f)
PARAME_CALIB_RVS_ITEM_I16(IREF_CALIB,     307,           204,             1280,             -1280)
PARAME_CALIB_END()

