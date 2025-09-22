/*
 * BSW_MCAL_GPIO_MUX_DEFINE.h
 *
 *  Created on: 2022-07-13
 *      Author: Hongbo.jiang
 */

#ifndef BSW_MCAL_GPIO_DEF_H_
#define BSW_MCAL_GPIO_DEF_H_

enum GPIO_NUM
{
    GPIO00_NUM = 0,
    GPIO01_NUM = 1,
    GPIO02_NUM = 2,
    GPIO03_NUM = 3,
    GPIO04_NUM = 4,
    GPIO05_NUM = 5,
    GPIO06_NUM = 6,
    GPIO07_NUM = 7,
    GPIO08_NUM = 8,
    GPIO09_NUM = 9,
    GPIO10_NUM = 10,
    GPIO11_NUM = 11,
    GPIO12_NUM = 12,
    GPIO13_NUM = 13,
    GPIO14_NUM = 14,
    GPIO15_NUM = 15,
    GPIO16_NUM = 16,
    GPIO17_NUM = 17,
    GPIO18_NUM = 18,
    GPIO19_NUM = 19,
    GPIO20_NUM = 20,
    GPIO21_NUM = 21,
    GPIO22_NUM = 22,
    GPIO23_NUM = 23,
    GPIO24_NUM = 24,
    GPIO25_NUM = 25,
    GPIO26_NUM = 26,
    GPIO27_NUM = 27,
    GPIO28_NUM = 28,
    GPIO29_NUM = 29,
    GPIO30_NUM = 30,
    GPIO31_NUM = 31,
    GPIO32_NUM = 32,
    GPIO33_NUM = 33,
    GPIO34_NUM = 34,
    GPIO35_NUM = 35,
    rsvd1      = 36,
    GPIO37_NUM = 37,
    rsvd2      = 38,
    GPIO39_NUM = 39,
    GPIO40_NUM = 40,
    GPIO41_NUM = 41,
    GPIO42_NUM = 42,
    GPIO43_NUM = 43,
    GPIO44_NUM = 44,
    GPIO45_NUM = 45,
    GPIO46_NUM = 46,
    rsvd3      = 47,
    GPIO48_NUM = 48,
    GPIO49_NUM = 49,
    GPIO_MAX_NUM,
    AGPIO224_NUM = 224,
    AGPIO225_NUM = 225,
    AGPIO226_NUM = 226,
    AGPIO227_NUM = 227,
    AGPIO228_NUM = 228,
    rsvd4        = 229,
    AGPIO230_NUM = 230,
    AGPIO231_NUM = 231,
    AGPIO232_NUM = 232,
    AGPIO233_NUM = 233,
    rsvd5      = 234,
    rsvd6      = 235,
    rsvd7      = 236,
    AGPIO237_NUM = 237,
    AGPIO238_NUM = 238,
    AGPIO239_NUM = 239,
    rsvd8      = 240,
    AGPIO241_NUM = 241,
    AGPIO242_NUM = 242,
    rsvd9      = 243,
    AGPIO244_NUM = 244,
    AGPIO245_NUM = 245,
    AGPIO_MAX_NUM,
};

#define    GPIO_IO                         0
#define    GPIO227_MUX_EPWM                3
#define    GPIO230_MUX_EPWM                3

#define    GPIO00_MUX_MCAN_RX              10
#define    GPIO01_MUX_MCAN_TX              10

#define    GPIO04_MUX_MCAN_TX              3
#define    GPIO04_MUX_CANA_TX              6

#define    GPIO05_MUX_MCAN_RX              5
#define    GPIO05_MUX_CANA_RX              6


#define    GPIO08_MUX_SCI_RX               6
#define    GPIO09_MUX_SCI_TX               6

#define    GPIO11_MUX_SCIB_RX              6

#define    GPIO12_MUX_MCAN_RX              3
#define    GPIO12_MUX_SCIB_TX                6
#define    GPIO12_MUX_FSIRXA_D0            9

#define    GPIO13_MUX_MCAN_TX              3
#define    GPIO13_MUX_SCIB_RX                6

#define    GPIO20_MUX_CANA_TX              3
#define    GPIO20_MUX_MCAN_TX              9

#define    GPIO21_MUX_CANA_RX              3
#define    GPIO21_MUX_MCAN_RX              9

#define    GPIO30_MUX_CANA_RX              1
#define    GPIO30_MUX_SPIB_SIMO            3
#define    GPIO30_MUX_MCAN_RX              10
#define    GPIO30_MUX_MCAN_RX              10

#define    GPIO31_MUX_MCAN_TX              10
#define    GPIO31_MUX_CANA_TX              1
#define    GPIO31_MUX_SPIB_SOMI            3
#define    GPIO31_MUX_MCAN_TX              10

#define    GPIO32_MUX_SPIB_CLK             3
#define    GPIO32_MUX_CANA_TX              10

#define    GPIO33_MUX_SPIB_STE             3

#define    GPIO33_MUX_FSIRXA_CLK           9
#define    GPIO33_MUX_CANA_RX              10

#define    GPIO39_MUX_MCAN_RX              6

#define    GPIO46_MUX_MCAN_TX              5
#define    GPIO47_MUX_MCAN_RX              5

#define    GPIO51_MUX_MCAN_RX              5
#define    GPIO50_MUX_MCAN_TX              5

#define    GPIO57_MUX_MCAN_RX              3
#define    GPIO56_MUX_MCAN_TX              3

#define    GPIO61_MUX_MCAN_RX              3
#define    GPIO60_MUX_MCAN_TX              3

#define    GPIO11_MUX_SPIA_STE             7
#define    GPIO12_MUX_SPIA_CLK             11
#define    GPIO16_MUX_SPIA_SIMO            1
#define    GPIO17_MUX_SPIA_SOMI            1

#define    GpioNum(A)                       GPIO##A##_NUM

#define    GpioMux(A,B)				        GPIO##A##_MUX_##B

#define    GpioSet(GROUP,NUM)               GpioDataRegs.GP##GROUP##SET.bit.GPIO##NUM 	= 1
#define    GpioClear(GROUP,NUM)             GpioDataRegs.GP##GROUP##CLEAR.bit.GPIO##NUM = 1

#endif /* BSW_MCAL_GPIO_DEF_H_ */
