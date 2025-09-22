/*
 * DpStackCfg.h
 *
 *  Created on: 2022/8/19
 *      Author: hongbo.jiang
 */

#ifndef BSW_SVC_COMMSTACK_DPSTACK_DPSTACKCFG_H_
#define BSW_SVC_COMMSTACK_DPSTACK_DPSTACKCFG_H_

#define PC_COMM_INF_MODULE        SCIB_MODULE
#define LLC_COMM_INF_MODULE      SCIB_MODULE
//DP_x_ENABLE        Whether the communication enable
//x_LINK_RX_ROUTE    Whether the recive data need to be route from this communication port
#if(PC_COMM_INF_MODULE == SCIA_MODULE)
#define DP_SCIA_ENABLE             		1
#define SCIA_LINK_RX_ROUTE         1
#elif(PC_COMM_INF_MODULE == SCIB_MODULE)
#define DP_SCIB_ENABLE             		1
#define SCIB_LINK_RX_ROUTE         1
#elif(PC_COMM_INF_MODULE == CANA_MODULE)
#define DP_CANA_ENABLE             		1
#define CANA_LINK_RX_ROUTE         	1
#elif(PC_COMM_INF_MODULE == CANB_MODULE)
#define DP_CANB_ENABLE             		1
#define CANB_LINK_RX_ROUTE         	1
#elif(PC_COMM_INF_MODULE == MCAN_MODULE)
#define DP_MCAN_ENABLE             		1
#define MCAN_LINK_RX_ROUTE         	1
#elif(PC_COMM_INF_MODULE == FSIA_MODULE)
#define DP_FSIA_TX_ENABLE          		1
#define DP_FSIA_RX_ENABLE          		1
#define FSIA_LINK_RX_ROUTE         1
#elif(PC_COMM_INF_MODULE ==PMBUS_MODULE)
#define DP_PMBUS_ENABLE            1
#define PMBUS_LINK_RX_ROUTE        1
#endif

#if(PFC_COMM_INF_MODULE == SCIA_MODULE)
#define DP_SCIA_ENABLE             1
#define ROUTE_SCIA_LINK
#elif(PFC_COMM_INF_MODULE == SCIB_MODULE)
#define DP_SCIB_ENABLE             1
#define ROUTE_SCIB_LINK
#elif(PFC_COMM_INF_MODULE == CANA_MODULE)
#define DP_CANA_ENABLE             1
#define ROUTE_CANA_LINK
#elif(PFC_COMM_INF_MODULE == CANB_MODULE)
#define DP_CANB_ENABLE             1
#define ROUTE_CANB_LINK
#elif(PFC_COMM_INF_MODULE == MCAN_MODULE)
#define DP_MCAN_ENABLE             1
#define ROUTE_MCAN_LINK
#elif(PFC_COMM_INF_MODULE == FSIA_MODULE)
#define DP_FSIA_TX_ENABLE             1
#define DP_FSIA_RX_ENABLE             1
#define ROUTE_FSIA_RX_LINK
#elif(PFC_COMM_INF_MODULE ==PMBUS_MODULE)
#define DP_PMBUS_ENABLE                  1
#define PMBUS_LINK_RX_ROUTE         1
#endif

#if(LLC_COMM_INF_MODULE == SCIA_MODULE)
#define DP_SCIA_ENABLE             1
#define ROUTE_SCIA_LINK
#elif(LLC_COMM_INF_MODULE == SCIB_MODULE)
#define DP_SCIB_ENABLE             1
#define ROUTE_SCIB_LINK
#elif(LLC_COMM_INF_MODULE == CANA_MODULE)
#define DP_CANA_ENABLE             1
#define ROUTE_CANA_LINK
#elif(LLC_COMM_INF_MODULE == CANB_MODULE)
#define DP_CANB_ENABLE             1
#define ROUTE_CANB_LINK
#elif(LLC_COMM_INF_MODULE == MCAN_MODULE)
#define DP_MCAN_ENABLE             1
#define ROUTE_MCAN_LINK
#elif(LLC_COMM_INF_MODULE == FSIA_MODULE)
#define DP_FSIA_TX_ENABLE             1
#define DP_FSIA_RX_ENABLE             1
#define ROUTE_FSIA_LINK
#elif(LLC_COMM_INF_MODULE ==PMBUS_MODULE)
#define DP_PMBUS_ENABLE                  1
#define PMBUS_LINK_RX_ROUTE         1
#endif

#if(DCDC_COMM_INF_MODULE == SCIA_MODULE)
#define DP_SCIA_ENABLE             1
#define ROUTE_SCIA_LINK
#elif(DCDC_COMM_INF_MODULE == SCIB_MODULE)
#define DP_SCIB_ENABLE             1
#define ROUTE_SCIB_LINK
#elif(DCDC_COMM_INF_MODULE == CANA_MODULE)
#define DP_CANA_ENABLE             1
#define ROUTE_CANA_LINK
#elif(DCDC_COMM_INF_MODULE == CANB_MODULE)
#define DP_CANB_ENABLE             1
#define ROUTE_CANB_LINK
#elif(DCDC_COMM_INF_MODULE == MCAN_MODULE)
#define DP_MCAN_ENABLE             1
#define ROUTE_MCAN_LINK
#elif(DCDC_COMM_INF_MODULE == FSIA_MODULE)
#define DP_FSIA_TX_ENABLE             1
#define DP_FSIA_RX_ENABLE             1
#define ROUTE_FSIA_LINK
#elif(DCDC_COMM_INF_MODULE ==PMBUS_MODULE)
#define DP_PMBUS_ENABLE                  1
#define PMBUS_LINK_RX_ROUTE         1
#endif

#define     NODE_ROUTE_ENABLE                                         0
#define     DLL_TX_RING_BYTE_LEN                                    2048
#define     DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN         512

#if(NODE_ROUTE_ENABLE == 1)
#define     DP_APP_SIG_FRAME_RX_MAX_BYTE_LEN         DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN
#else
#define     DP_APP_SIG_FRAME_RX_MAX_BYTE_LEN         64
#endif

#if(DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN < 128)
#error "The Maximum App data length is little,should be >= 128"
#elif(DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN > 1024)
#error "The Maximum App data length is large,should be <= 1024"
#endif
#if(DP_APP_SIG_FRAME_RX_MAX_BYTE_LEN < 64)
#error "The Maximum App data length is little,should be >= 64"
#elif(DP_APP_SIG_FRAME_RX_MAX_BYTE_LEN > 512)
#error "The Maximum App data length is large,should be <= 512"
#endif

#define     DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN       (DP_APP_SIG_FRAME_RX_MAX_BYTE_LEN + sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE)
#define     DP_APL_SIG_FRAME_TX_MAX_BYTE_LEN       (DP_APP_SIG_FRAME_TX_MAX_BYTE_LEN + sizeof(APL_DOMAIN)*TYPE_8_BYTE_SIZE)

#define     DP_TPL_SIG_FRAME_RX_MAX_BYTE_LEN       (DP_APL_SIG_FRAME_RX_MAX_BYTE_LEN + sizeof(TPL_DOMAIN)*TYPE_8_BYTE_SIZE)
#define     DP_TPL_SIG_FRAME_TX_MAX_BYTE_LEN       (DP_APL_SIG_FRAME_TX_MAX_BYTE_LEN + sizeof(TPL_DOMAIN)*TYPE_8_BYTE_SIZE)

#define     DP_NWM_SIG_FRAME_RX_MAX_BYTE_LEN       (DP_TPL_SIG_FRAME_RX_MAX_BYTE_LEN + sizeof(NWM_DOMAIN)*TYPE_8_BYTE_SIZE)
#define     DP_NWM_SIG_FRAME_TX_MAX_BYTE_LEN       (DP_TPL_SIG_FRAME_TX_MAX_BYTE_LEN + sizeof(NWM_DOMAIN)*TYPE_8_BYTE_SIZE)


#endif /* BSW_SVC_COMMSTACK_DPSTACK_DPSTACKCFG_H_ */
