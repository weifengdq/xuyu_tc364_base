#include "bsp_can.h"
#include "IfxCan_Can.h"
#include "IfxCan.h"
#include <string.h>

McmcanType mcmcan[8];

IfxCan_Can_Pins mcmcan_pins[8] = {
    {   //CAN00
        &IfxCan_TXD00_P02_0_OUT,   IfxPort_OutputMode_pushPull, 
        &IfxCan_RXD00A_P02_1_IN,   IfxPort_InputMode_pullUp,
        IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN01
       &IfxCan_TXD01_P14_0_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD01B_P14_1_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN02
       &IfxCan_TXD02_P10_3_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD02E_P10_2_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN03
       &IfxCan_TXD03_P00_2_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD03A_P00_3_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN10
       &IfxCan_TXD10_P00_0_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD10A_P00_1_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN11
       &IfxCan_TXD11_P00_4_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD11B_P00_5_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    },
    {   //CAN12
       &IfxCan_TXD12_P20_7_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD12A_P20_6_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4        
    },
    {   //CAN13
       &IfxCan_TXD13_P11_4_OUT,   IfxPort_OutputMode_pushPull, 
       &IfxCan_RXD13D_P11_13_IN,   IfxPort_InputMode_pullUp,
       IfxPort_PadDriver_cmosAutomotiveSpeed4
    }
};

IfxCan_Filter mcmcan_std_default_filter = {
    .number = 0,
    .elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxFifo0,
    .type = IfxCan_FilterType_classic,
    .id1 = 0,
    .id2 = 0,
    .rxBufferOffset = IfxCan_RxBufferId_0
};

IfxCan_Filter mcmcan_ext_default_filter = {
    .number = 0,
    .elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxFifo0,
    .type = IfxCan_FilterType_classic,
    .id1 = 0,
    .id2 = 0,
    .rxBufferOffset = IfxCan_RxBufferId_0
};

/********************************
 * USER NEED CONFIG
 * - cpu, 0~1
 * - module, 0~1
 * - node, 0~3
 * - baud, 250000, 500000, 1000000
 * - sample_point, 8000
 * - fast_baud, 2000000, 4000000, 5000000
 * - fast_sample_point, 8000
 * - tx_priority
 * - rx_priority
 * - busoff_priority
 * *****************************/



void IfxCan_Can_ReinitNodeConfig(IfxCan_Can_NodeConfig *config, IfxCan_Can *can)
{
    const IfxCan_Can_NodeConfig defaultConfig = {
        .can         = NULL_PTR,
        .nodeId      = IfxCan_NodeId_0,
        .clockSource = IfxCan_ClockSource_both,
        .frame       = {
            .type = IfxCan_FrameType_transmitAndReceive,
            .mode = IfxCan_FrameMode_fdLongAndFast
        },
        .baudRate                                    = {
            .baudrate      = 500000,
            .samplePoint   = 8000,
            .syncJumpWidth = 2000,
            .prescaler     = 0,
            .timeSegment1  = 3,
            .timeSegment2  = 10
        },
        .fastBaudRate                                = {
            .baudrate              = 2000000,
            .samplePoint           = 8000,
            .syncJumpWidth         = 2000,
            .prescaler             = 1,
            .timeSegment1          = 3,
            .timeSegment2          = 10,
            .tranceiverDelayOffset = 28
        },
        .txConfig                                    = {
            .txMode                   = IfxCan_TxMode_fifo,
            .dedicatedTxBuffersNumber = 0,
            .txFifoQueueSize          = 32,
            .txBufferDataFieldSize    = IfxCan_DataFieldSize_64,
            .txEventFifoSize          = 0
        },
        .filterConfig                                = {
            .messageIdLength                    = IfxCan_MessageIdLength_both,
            .standardListSize                   = 64,
            .extendedListSize                   = 32,
            .rejectRemoteFramesWithStandardId   = TRUE,
            .rejectRemoteFramesWithExtendedId   = TRUE,
            .standardFilterForNonMatchingFrames = IfxCan_NonMatchingFrame_reject,
            .extendedFilterForNonMatchingFrames = IfxCan_NonMatchingFrame_reject
        },
        .rxConfig                                    = {
            .rxMode                = IfxCan_RxMode_fifo0,
            .rxBufferDataFieldSize = IfxCan_DataFieldSize_64,
            .rxFifo0DataFieldSize  = IfxCan_DataFieldSize_64,
            .rxFifo1DataFieldSize  = IfxCan_DataFieldSize_64,
            .rxFifo0OperatingMode  = IfxCan_RxFifoMode_overwrite,
            .rxFifo1OperatingMode  = IfxCan_RxFifoMode_overwrite,
            .rxFifo0WatermarkLevel = 0,
            .rxFifo1WatermarkLevel = 0,
            .rxFifo0Size           = 16,
            .rxFifo1Size           = 0
        },
        .messageRAM                                  = {
            .baseAddress                    = (uint32)&MODULE_CAN0,
            .standardFilterListStartAddress = 0x0,
            .extendedFilterListStartAddress = 0x100,
            .rxFifo0StartAddress            = 0x200,
            .rxFifo1StartAddress            = 0x0,
            .rxBuffersStartAddress          = 0x0,
            .txEventFifoStartAddress        = 0x0,
            .txBuffersStartAddress          = 0x700
        },
        .interruptConfig                             = {
            .rxFifo0NewMessageEnabled                = TRUE,
            .rxFifo0WatermarkEnabled                 = FALSE,
            .rxFifo0FullEnabled                      = FALSE,
            .rxFifo0MessageLostEnabled               = FALSE,
            .rxFifo1NewMessageEnabled                = FALSE,
            .rxFifo1WatermarkEnabled                 = FALSE,
            .rxFifo1FullEnabled                      = FALSE,
            .rxFifo1MessageLostEnabled               = FALSE,
            .highPriorityMessageEnabled              = FALSE,
            .transmissionCompletedEnabled            = FALSE,
            .transmissionCancellationFinishedEnabled = FALSE,
            .txFifoEmptyEnabled                      = FALSE,
            .txEventFifoNewEntryEnabled              = FALSE,
            .txEventFifoWatermarkEnabled             = FALSE,
            .txEventFifoFullEnabled                  = FALSE,
            .txEventFifoEventLostEnabled             = FALSE,
            .timestampWraparoundEnabled              = FALSE,
            .messageRAMAccessFailureEnabled          = FALSE,
            .timeoutOccurredEnabled                  = FALSE,
            .messageStoredToDedicatedRxBufferEnabled = FALSE,
            .errorLoggingOverflowEnabled             = FALSE,
            .errorPassiveEnabled                     = FALSE,
            .warningStatusEnabled                    = FALSE,
            .busOffStatusEnabled                     = TRUE,
            .watchdogEnabled                         = FALSE,
            .protocolErrorArbitrationEnabled         = FALSE,
            .protocolErrorDataEnabled                = FALSE,
            .tefifo                                  = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .hpe                                     = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .wati                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .alrt                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .moer                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .safe                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .boff                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .loi                                     = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .reint                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .rxf1f                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .rxf0f                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .rxf1n                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .rxf0n                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .reti                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .traq                                    = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            },
            .traco                                   = {
                .interruptLine = IfxCan_InterruptLine_0,
                .priority      = 0,
                .typeOfService = IfxSrc_Tos_cpu0
            }
        },
        .pins                     = NULL_PTR,
        .busLoopbackEnabled       = FALSE,
        .calculateBitTimingValues = TRUE
    };

    /* Default Configuration */
    *config = defaultConfig;

    /* take over module pointer */
    config->can = can->can;
}

uint8_t can_init(void)
{
    for(uint8_t i = 0; i < 8; i++) {
        switch(i/4) {
            case 0: IfxCan_Can_initModuleConfig(&mcmcan[i].canConfig, &MODULE_CAN0); break;
            case 1: IfxCan_Can_initModuleConfig(&mcmcan[i].canConfig, &MODULE_CAN1); break;
            default: return 1;
        }
        
        IfxCan_Can_initModule(&mcmcan[i].canModule, &mcmcan[i].canConfig);
        IfxCan_Can_ReinitNodeConfig(&mcmcan[i].canNodeConfig, &mcmcan[i].canModule);

        //message ram offset
        mcmcan[i].canNodeConfig.nodeId = IfxCan_NodeId_0 + i % 4;
        switch(i/4) {
            case 0: mcmcan[i].canNodeConfig.messageRAM.baseAddress = (uint32)&MODULE_CAN0; break;
            case 1: mcmcan[i].canNodeConfig.messageRAM.baseAddress = (uint32)&MODULE_CAN1; break;
            default: return 1;
        }
        mcmcan[i].canNodeConfig.messageRAM.standardFilterListStartAddress = 0x0   + 0x1000 * (i%4);
        mcmcan[i].canNodeConfig.messageRAM.extendedFilterListStartAddress = 0x100 + 0x1000 * (i%4);
        mcmcan[i].canNodeConfig.messageRAM.rxFifo0StartAddress = 0x200 + 0x1000 * (i%4);
        mcmcan[i].canNodeConfig.messageRAM.txBuffersStartAddress = 0x700 + 0x1000 * (i%4);

        //tx isr, default close
        mcmcan[i].canNodeConfig.interruptConfig.traco.priority = 110 + i;
        mcmcan[i].canNodeConfig.interruptConfig.traco.interruptLine = IfxCan_InterruptLine_0 + i%4;
        mcmcan[i].canNodeConfig.interruptConfig.traco.typeOfService = IfxSrc_Tos_cpu0;

        //rx isr
        mcmcan[i].canNodeConfig.interruptConfig.rxf0n.priority = 130 + i;
        mcmcan[i].canNodeConfig.interruptConfig.rxf0n.interruptLine = IfxCan_InterruptLine_4 + i%4;
        mcmcan[i].canNodeConfig.interruptConfig.rxf0n.typeOfService = IfxSrc_Tos_cpu0;

        //busoff isr
        mcmcan[i].canNodeConfig.interruptConfig.boff.priority = 150 + i;
        mcmcan[i].canNodeConfig.interruptConfig.boff.interruptLine = IfxCan_InterruptLine_8 + i%4;
        mcmcan[i].canNodeConfig.interruptConfig.boff.typeOfService = IfxSrc_Tos_cpu0;

        //pins
        mcmcan[i].canNodeConfig.pins = &mcmcan_pins[i];

        IfxCan_Can_initNode(&mcmcan[i].canNode, &mcmcan[i].canNodeConfig);

        //std filter
        for(uint8_t j = 0; j < 64; j++) {
            memcpy(&mcmcan[i].canFilter, &mcmcan_std_default_filter, sizeof(IfxCan_Filter));
            mcmcan[i].canFilter.number = i;
            IfxCan_Can_setStandardFilter(&mcmcan[i].canNode, &mcmcan[i].canFilter);
        }

        //ext filter
        for(uint8_t k = 0; k < 32; k++) {
            memcpy(&mcmcan[i].canFilter, &mcmcan_ext_default_filter, sizeof(IfxCan_Filter));
            mcmcan[i].canFilter.number = i;
            IfxCan_Can_setExtendedFilter(&mcmcan[i].canNode, &mcmcan[i].canFilter);
        }
    }

    return 0;
}

#define MCMCAN_RX_ISR(rx_handler, vectabNum, prio, mcmcan) \
IFX_INTERRUPT(rx_handler, vectabNum, prio); \
void rx_handler(void) \
{ \
    IfxCan_Node_clearInterruptFlag(mcmcan.canNode.node, IfxCan_Interrupt_rxFifo0NewMessage); \
    IfxCan_Can_readMessage(&mcmcan.canNode, &mcmcan.rxMsg, mcmcan.rxData); \
}

MCMCAN_RX_ISR(mcmcan00_rx_handler, 0, 130, mcmcan[0]);
MCMCAN_RX_ISR(mcmcan01_rx_handler, 0, 131, mcmcan[1]);
MCMCAN_RX_ISR(mcmcan02_rx_handler, 0, 132, mcmcan[2]);
MCMCAN_RX_ISR(mcmcan03_rx_handler, 0, 133, mcmcan[3]);
MCMCAN_RX_ISR(mcmcan10_rx_handler, 0, 134, mcmcan[4]);
MCMCAN_RX_ISR(mcmcan11_rx_handler, 0, 135, mcmcan[5]);
MCMCAN_RX_ISR(mcmcan12_rx_handler, 0, 136, mcmcan[6]);
MCMCAN_RX_ISR(mcmcan13_rx_handler, 0, 137, mcmcan[7]);
