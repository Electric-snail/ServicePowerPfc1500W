/*
 * BSW_MCAL_PERIP_CLOCK.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_CLOCK_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_CLOCK_H_

#include "PUBLIC_INC/AUTO_REGISTER.H"
#include "HARDWARE_ENV_CFG.h"
#include "BSW_MCAL_BASIC.h"

enum SYS_CLK_SRC
{
    INT_OSC2_SRC    = 0,  // Internal oscillator 2
    XTAL_OSC_SRC    = 1,  // External oscillator, crystal mode
    INT_OSC1_SRC    = 2,  // Internal oscillator 1
    XTAL_OSC_SE_SRC = 5,  // External oscillator, single-ended mode
};

enum SysCtl_LSPCLK_PRESCALE
{
    SYSCTL_LSPCLK_PRESCALE_1    = 0,    //!< LSPCLK = SYSCLK / 1
    SYSCTL_LSPCLK_PRESCALE_2    = 1,    //!< LSPCLK = SYSCLK / 2
    SYSCTL_LSPCLK_PRESCALE_4    = 2,    //!< LSPCLK = SYSCLK / 4 (default)
    SYSCTL_LSPCLK_PRESCALE_6    = 3,    //!< LSPCLK = SYSCLK / 6
    SYSCTL_LSPCLK_PRESCALE_8    = 4,    //!< LSPCLK = SYSCLK / 8
    SYSCTL_LSPCLK_PRESCALE_10   = 5,    //!< LSPCLK = SYSCLK / 10
    SYSCTL_LSPCLK_PRESCALE_12   = 6,    //!< LSPCLK = SYSCLK / 12
    SYSCTL_LSPCLK_PRESCALE_14   = 7     //!< LSPCLK = SYSCLK / 14
};

//*****************************************************************************
//
//! The following are values that can be passed to
//! SysCtl_setMCANClk() as \e divider parameter.
//
//*****************************************************************************
enum SysCtl_MCANCLK_DIV
{
    SYSCTL_MCANCLK_DIV_1  = 0x0,   //!<  MCAN clock =  MCAN clock / 1
    SYSCTL_MCANCLK_DIV_2  = 0x1,   //!<  MCAN clock =  MCAN clock / 2
    SYSCTL_MCANCLK_DIV_3  = 0x2,   //!<  MCAN clock =  MCAN clock / 3
    SYSCTL_MCANCLK_DIV_4  = 0x3,   //!<  MCAN clock =  MCAN clock / 4
    SYSCTL_MCANCLK_DIV_5  = 0x4,   //!<  MCAN clock =  MCAN clock / 5
    SYSCTL_MCANCLK_DIV_6  = 0x5,   //!<  MCAN clock =  MCAN clock / 6
    SYSCTL_MCANCLK_DIV_7  = 0x6,   //!<  MCAN clock =  MCAN clock / 7
    SYSCTL_MCANCLK_DIV_8  = 0x7,   //!<  MCAN clock =  MCAN clock / 8
    SYSCTL_MCANCLK_DIV_9  = 0x8,   //!<  MCAN clock =  MCAN clock / 9
    SYSCTL_MCANCLK_DIV_10 = 0x9,   //!<  MCAN clock =  MCAN clock / 10
    SYSCTL_MCANCLK_DIV_11 = 0xA,   //!<  MCAN clock =  MCAN clock / 11
    SYSCTL_MCANCLK_DIV_12 = 0xB,   //!<  MCAN clock =  MCAN clock / 12
    SYSCTL_MCANCLK_DIV_13 = 0xC,   //!<  MCAN clock =  MCAN clock / 13
    SYSCTL_MCANCLK_DIV_14 = 0xD,   //!<  MCAN clock =  MCAN clock / 14
    SYSCTL_MCANCLK_DIV_15 = 0xE,   //!<  MCAN clock =  MCAN clock / 15
    SYSCTL_MCANCLK_DIV_16 = 0xF,   //!<  MCAN clock =  MCAN clock / 16
    SYSCTL_MCANCLK_DIV_17 = 0x10,  //!<  MCAN clock =  MCAN clock / 17
    SYSCTL_MCANCLK_DIV_18 = 0x11,  //!<  MCAN clock =  MCAN clock / 18
    SYSCTL_MCANCLK_DIV_19 = 0x12,  //!<  MCAN clock =  MCAN clock / 19
    SYSCTL_MCANCLK_DIV_20 = 0x13   //!<  MCAN clock =  MCAN clock / 20
};

#define        SYS_CLK_OUT_FREQ_60M_INDEX     		0
#define        SYS_CLK_OUT_FREQ_80M_INDEX     		1
#define        SYS_CLK_OUT_FREQ_100M_INDEX    		2
#define        SYS_CLK_OUT_FREQ_120M_INDEX    		3

//the clock configure zoon
#define         SRC_CLK_FREQ_M                            	10.0f
#define         SYS_CLK_SRC_IN 									INT_OSC2_SRC
#define         SYS_CLK_OUT_FREQ_INDEX               SYS_CLK_OUT_FREQ_120M_INDEX
#define         SYSCTL_LSPCLK_PRESCALE         		SYSCTL_LSPCLK_PRESCALE_4
#define         SYSCTL_MCANCLK_PRESCALE        	SYSCTL_MCANCLK_DIV_3
//end of the clock configuration


#if(SYS_CLK_OUT_FREQ_INDEX == SYS_CLK_OUT_FREQ_120M_INDEX)
#define SYS_CPU_CLK_FREQ_M             120
#elif(SYS_CLK_OUT_FREQ_INDEX == SYS_CLK_OUT_FREQ_100M_INDEX)
#define SYS_CPU_CLK_FREQ_M             100
#elif(SYS_CLK_OUT_FREQ_INDEX == SYS_CLK_OUT_FREQ_80M_INDEX)
#define SYS_CPU_CLK_FREQ_M             80
#elif(SYS_CLK_OUT_FREQ_INDEX == SYS_CLK_OUT_FREQ_60M_INDEX)
#define SYS_CPU_CLK_FREQ_M             60
#else
#error("The cpu system clock configure error")
#endif

#define  		LSP_CLK_FREQ_M           				SYS_CPU_CLK_FREQ_M/(2*SYSCTL_LSPCLK_PRESCALE)
//jackey
#define  		MCAN_CLK_FREQ_M           	  		SYS_CPU_CLK_FREQ_M/(2*SYSCTL_MCANCLK_PRESCALE)

typedef struct{
    float            													f32ClkSrcFreq;
    enum             SYS_CLK_SRC             			emSysClkSrc;
    unsigned short   											u16SysClkOutFreqIndex;
    enum             SysCtl_LSPCLK_PRESCALE  emLspClkPrec;
    enum             SysCtl_MCANCLK_DIV      	emMcanClkDiv;
}SYS_CLK_CFG;

/*To ensure the independence of the WDG clock source, disable INTOSC1 if the internal watchdog is enabled*/
/* don't configure the parameter in the table.please configure it in the configure zoon ******/
/***---f32ClkSrcFreq-----------------emSysClkSrc-----------------------u16SysClkOutFreq----------------------emLspClkPrec-----------------------------emMcanClkDiv--***/
#define SYS_CLK_CFG_TAB   \
{\
	SRC_CLK_FREQ_M, 				SYS_CLK_SRC_IN,    			SYS_CLK_OUT_FREQ_INDEX,   		SYSCTL_LSPCLK_PRESCALE, 			SYSCTL_MCANCLK_PRESCALE  \
}


extern float SYS_CLK_GetSysClkFreq(void);
extern float SYS_CLK_GetLpsClkFreq(void);
extern float SYS_CLK_GetMcanClkFreq(void);
extern float SYS_CLK_GetPllRawClkFreq(void);

extern void bsw_mcal_sys_clock_init(void);


#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_CLOCK_H_ */
