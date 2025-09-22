/*
 * BSW_MCAL_BASIC.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */
#ifndef BSW_MCAL_BASIC_H_
#define BSW_MCAL_BASIC_H_

#include "HARDWARE_ENV_CFG.h"
#include "SOFTWARE_ENV_CFG.h"


typedef void  (*pf_mcal_init)   (void);
typedef INT16 (*pf_mcal_write)  (UINT8 *,  UINT16);
typedef INT16 (*pf_mcal_read)   (UINT8 *,  UINT8 *, UINT16);
typedef INT16 (*pf_mcal_ctrl)   (void *, UINT16);

typedef struct
{
    UINT16          mcal_id;
    UINT8           is_auto_init;
    pf_mcal_init    mcal_init;
}MCAL_DRIVE_OBJ;

/****The initial sequence of each Mcal module basic on the sequence of MCAL_DRV_REG_TAB
 * NOTE: the sequence is also keep the same with the enum id definition ****/

enum MCAL_ID
{
    MCAL_RAM = 0,        		 // 0
    MCAL_FLASH,           		// 1
    MCAL_SYS,             			// 2
	MCAL_SP,                 		//
    MCAL_SYS_CLOCK,       //
    MCAL_INT_CTR,         //
    MCAL_CPU_TIMER,       //
    MCAL_CLA,             //
    MCAL_DMA,             //
    MCAL_XBAR,            //
    MCAL_ADC,             //
    MCAL_ePWM,            //
    MCAL_GPIO,            //
    MCAL_SPI,             //
    MCAL_SCI,             //
	MCAL_I2C,
	MCAL_CAN,             //
    MCAL_MCAN,            //
	MCAL_FSI,                //
    MCAL_WDG,             //
};
/****mcal_id******is_auto_init*****mcal_init***********/
#define MCAL_DRV_REG_TAB          \
{\
    {MCAL_RAM,    		            	1,    bsw_mcal_ram_init},  		\
    {MCAL_FLASH,  		        	1,    bsw_mcal_flash_init},  		\
    {MCAL_SYS,  		            		1,    bsw_mcal_sys_init},  		\
    {MCAL_SP,  		               	 	1,    bsw_mcal_sp_init},  		\
    {MCAL_SYS_CLOCK,  	    	1,    bsw_mcal_sys_clock_init},  	\
    {MCAL_INT_CTR,  	        	1,    bsw_mcal_pie_ctrl_init},  	\
    {MCAL_CPU_TIMER,  	    	1,    bsw_mcal_cpu_timer_init},	\
    {MCAL_CLA,  		            		0,    NULL},  		\
    {MCAL_DMA,  		            	0,    NULL},  					\
    {MCAL_XBAR,  		            	0,    NULL},  		\
	{MCAL_ADC,    		            	0,    NULL},  		\
	{MCAL_ePWM,   		        	0,    NULL}, 		\
    {MCAL_GPIO,   		            	1,   bsw_mcal_gpio_init}, 		\
    {MCAL_SPI,   		            		0,    NULL}, 		\
    {MCAL_SCI,   		            		1,    bsw_mcal_sci_init}, 		\
    {MCAL_I2C,   		            		0,    NULL}, 		\
    {MCAL_CAN,   		            	0,    NULL}, 		\
    {MCAL_MCAN,                   	0,    NULL},      \
	{MCAL_FSI,                      		0,    NULL},       \
    {MCAL_WDG,   		            	0,    NULL} 		\
}
extern void bsw_mcal_init(void);


#endif /* BSW_MCAL_BASIC_H_ */
