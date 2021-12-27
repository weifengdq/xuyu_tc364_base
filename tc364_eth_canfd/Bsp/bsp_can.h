#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "IfxCan_Can.h"
#include "IfxCan.h"
#include <stdint.h>

//can frame's max data length, unit: words
//#define MAXIMUM_CAN_DATA_PAYLOAD                  2    //CAN
#define MAXIMUM_CAN_DATA_PAYLOAD                    16   //CANFD

//can node struct
typedef struct
{
    IfxCan_Can_Config canConfig;                /* CAN module configuration structure   */
    IfxCan_Can canModule;                       /* CAN module handle                    */
    IfxCan_Can_Node canNode;                    /* CAN source node handle data structure*/
    IfxCan_Can_NodeConfig canNodeConfig;        /* CAN node configuration structure     */
    IfxCan_Filter canFilter;                    /* CAN filter configuration structure   */
    IfxCan_Message txMsg;                       /* Transmitted CAN message structure    */
    IfxCan_Message rxMsg;                       /* Received CAN message structure       */
    uint32_t busoff_state;
    uint32_t txData[MAXIMUM_CAN_DATA_PAYLOAD];  /* Transmitted CAN data array           */
    uint32_t rxData[MAXIMUM_CAN_DATA_PAYLOAD];  /* Received CAN data array              */
} McmcanType;

#endif // !BSP_CAN_H
