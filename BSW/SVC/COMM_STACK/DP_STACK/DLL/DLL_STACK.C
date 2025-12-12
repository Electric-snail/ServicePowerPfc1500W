/*
 * DLL_Stack.c
 *
 *  Created on: 2022-8-21.
 *      Author: xj8r1j
 */

#include "DP_STACK/DLL/DLL_SCI.H"

void DLL_Handle(void){
    #if(DP_SCIA_ENABLE == 1)
    scia_send_from_ring();
//    scia_err_handler();
    #endif
    #if(DP_SCIB_ENABLE == 1)
    scib_send_from_ring();
//    scib_err_handler();
    #endif
    #if(DP_CANA_ENABLE == 1)
    Cana_Send_From_Ring();
    #endif
    #if(DP_CANB_ENABLE == 1)
    Canb_Send_From_Ring();
    #endif
    #if(DP_MCAN_ENABLE == 1)
    Mcan_Send_From_Ring();
    #endif
    #if(DP_FSIA_TX_ENABLE == 1)
    Fsi_Send_From_Ring();
    #endif
}

