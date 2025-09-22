/*
 * BSW_MCAL_CAN.h
 *
 *  Created on: 2022.8.17.
 *      Author: xj8r1j
 */

#ifndef BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_H_
#define BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_H_

#ifndef DLLX64
#include <BSW/MCAL/BSW_MCAL_BASIC.h>
#include <BSW/CHIP_PACK/common/include/F28x_Project.h>
#endif
#include <PUBLIC_INC/AUTO_REGISTER.H>

#include "ENV_CFG/SOFTWARE_ENV_CFG.h"


#define     ERROR_ACTIVE                1
#define     ERROR_BUS_OFF               2
#define     ERROR_PASSIVE               3

//*****************************************************************************
//! This definition is used with the tCANMsgObject ui32Flags value and indicates
//! that transmit interrupts should be enabled, or are enabled.
#define MSG_OBJ_TX_INT_ENABLE           0x00000001
//! This indicates that receive interrupts should be enabled, or are
//! enabled.
#define MSG_OBJ_RX_INT_ENABLE           0x00000002
//! This indicates that a message object will use or is using an extended identifier.
#define MSG_OBJ_EXTENDED_ID             0x00000004
//! This indicates that a message object will use or is using filtering
//! based on the object's message identifier.
#define MSG_OBJ_USE_ID_FILTER           0x00000008
//! This indicates that new data was available in the message object.
#define MSG_OBJ_NEW_DATA                0x00000080

//! This indicates that a message object will use or is using filtering
//! based on the direction of the transfer.  If the direction filtering is
//! used, then ID filtering must also be enabled.
#define MSG_OBJ_USE_DIR_FILTER          (0x00000010 | MSG_OBJ_USE_ID_FILTER)

//! This indicates that a message object will use or is using message
//! identifier filtering based on the extended identifier.  If the extended
//! identifier filtering is used, then ID filtering must also be enabled.
#define MSG_OBJ_USE_EXT_FILTER          (0x00000020 | MSG_OBJ_USE_ID_FILTER)

//! This indicates that a message object is a remote frame.
#define MSG_OBJ_REMOTE_FRAME            0x00000040

//! This indicates that this message object is part of a FIFO structure and
//! not the final message object in a FIFO.
#define MSG_OBJ_FIFO                    0x00000200

//! This indicates that a message object has no flags set.
#define MSG_OBJ_NO_FLAGS                0x00000000

//*****************************************************************************
//! This define is used with the flag values to allow checking only status
//! flags and not configuration flags.
//*****************************************************************************
#define MSG_OBJ_STATUS_MASK             (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)

#ifndef CAN_MSG_OBJ_MACRO
#define CAN_MSG_OBJ_MACRO
typedef struct
{
  UINT32   u32Id;                        // message id
  UINT32   u32Flg;
  UINT8    u8DLC;                        // frame info
  UINT8    u8data[8];                    // message data
}CAN_MSG_OBJ_T;
#endif

enum CAN_BAUD
{
    BAUD_1000000 = 0,
    BAUD_800000  = 1,
    BAUD_500000  = 2,
    BAUD_250000  = 3,
    BAUD_125000  = 4,

};
enum CAN_MSG_DLC
{
     DLC_1BYTE =  1,
     DLC_2BYTE  = 2,
     DLC_3BYTE  = 3,
     DLC_4BYTE  = 4,
     DLC_5BYTE  = 5,
     DLC_6BYTE  = 6,
     DLC_7BYTE  = 7,
     DLC_8BYTE  = 8,
};



enum CAN_OBJ_ID
{
    OBJ_ID1 = 1,
    OBJ_ID2,
    OBJ_ID3,
    OBJ_ID4,
    OBJ_ID5,
    OBJ_ID6,
    OBJ_ID7,
    OBJ_ID8,
    OBJ_ID9,
    OBJ_ID10,
    OBJ_ID11,
    OBJ_ID12,
    OBJ_ID13,
    OBJ_ID14,
    OBJ_ID15,
    OBJ_ID16,
    OBJ_ID17,
    OBJ_ID18,
    OBJ_ID19,
    OBJ_ID20,
    OBJ_ID21,
    OBJ_ID22,
    OBJ_ID23,
    OBJ_ID24,
    OBJ_ID25,
    OBJ_ID26,
    OBJ_ID27,
    OBJ_ID28,
    OBJ_ID29,
    OBJ_ID30,
    OBJ_ID31,
    OBJ_ID32,
    OBJ_ID_MAX
};

enum CAN_FRAME_TYPE
{
    //! Set the message ID frame to standard.
    MSG_FRAME_STD,
    //! Set the message ID frame to extended.
    MSG_FRAME_EXT
} ;

enum  CAN_MSG_OBJ_TYPE
{
      //! Transmit message object.
      MSG_OBJ_TYPE_TX,
      //! Transmit remote request message object
      MSG_OBJ_TYPE_TX_REMOTE,
      //! Receive message object.
      MSG_OBJ_TYPE_RX,
      //! Remote frame receive remote, with auto-transmit message object.
      MSG_OBJ_TYPE_RXTX_REMOTE,
};


/*--- The data receive mode, by interrupt or polling method to receive the data ----*/
enum CAN_TX_MODE{
     TX_POLLING   = 0,
     TX_INTERRUP  = 1,
};

/*--- The data receive mode, by interrupt or polling method to receive the data ----*/
enum CAN_RX_MASK_ENA{
    DIS_MASK    = 0,
    ENA_MASK    = 1,
};

enum CAN_MODULE_ID{
    CANA_MODULE_ID      = 0,
    CANB_MODULE_ID,
    CAN_MODULE_MAX_ID,
};


typedef struct
{
    enum CAN_MODULE_ID                   		emCanMoudleId;
    enum CAN_BAUD                        			emCanBaud;
}CAN_ITEM_CFG;

typedef struct{
     enum CAN_OBJ_ID                              	emCanObjId;
     enum CAN_FRAME_TYPE                  	emCanExtSdType;
     enum CAN_MSG_OBJ_TYPE                	emCanTxRxType;
     enum CAN_RX_MASK_ENA                 	emCanMaskEna;
     UINT8                                						u8RxIntEna;
     UINT8                                						u8TxIntEna;
     UINT32                               					u32MsgId;
     UINT32                               					u32MskId;
}CAN_MSG_OBJ_CFG;

#define    DP_TX_CAN_OBJ_ID1      OBJ_ID25
#define    DP_TX_CAN_OBJ_ID2      OBJ_ID26
#define    DP_TX_CAN_OBJ_ID3      OBJ_ID27
#define    DP_TX_CAN_OBJ_ID4      OBJ_ID28
#define    DP_TX_CAN_OBJ_ID5      OBJ_ID29
#define    DP_TX_CAN_OBJ_ID6      OBJ_ID30
#define    DP_TX_CAN_OBJ_ID7      OBJ_ID31
#define    DP_TX_CAN_OBJ_MAX_ID   OBJ_ID32

#define    CYC_TX_CAN_OBJ_ID   OBJ_ID16
#define    DP_RX_CAN_OBJ_ID    OBJ_ID1
#define    CYC_RX_CAN_OBJ_ID   OBJ_ID15

/*---CAN_MODULE-------------BAUD--------*/
#define      REG_CAN_ITEM_CFG_TAB       \
{\
};

//CANA configuration information
/*---emCanObjId-------------emCanExtSdType-----------emCanTxRxType----emCanMaskEna----u8RxIntEna----u8TxIntEna---u32MsgId------u32MskId--*/
#define     REG_CANA_MSG_OBJ_CFG_TAB            \
{\
}

extern unsigned char CANAMessageGet(CAN_MSG_OBJ_T *p_stMsgObj, enum CAN_OBJ_ID emObjId);

extern unsigned char CANBMessageGet(CAN_MSG_OBJ_T*p_stMsgObj, enum CAN_OBJ_ID emObjId);

extern INT16 CANA_Send_Message_UnChageId(CAN_MSG_OBJ_T *p_sTCANMsgObj, enum CAN_OBJ_ID emObjId);

extern INT16 CANA_Send_Message_ChageId(CAN_MSG_OBJ_T *p_sTCANMsgObj, enum CAN_OBJ_ID emObjId);


extern INT16 CANA_Is_Message_Sent(enum CAN_OBJ_ID emObjId);

extern void BSW_MCAL_CanInit(void);
#endif /* BSW_MCAL_MCAL_INC_BSW_MCAL_CAN_H_ */
