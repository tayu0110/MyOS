#ifndef _XHCI_H_INCLUDED_
#define _XHCI_H_INCLUDED_

#include <stdint.h>

#define XHCI_MAX_SLOT_ENABLED   256

typedef struct _CapabilityRegisters {
  uint8_t CAPLENGTH;                 // Base + 00h
  uint8_t Rsvd;                      // Base + 01h
  uint16_t HCIVERSION;               // Base + 02h ~ 03h
  uint32_t HCSPARAMS1;               // Base + 04h ~ 07h
  uint32_t HCSPARAMS2;               // Base + 08h ~ 0Bh
  uint32_t HCSPARAMS3;               // Base + 0Ch ~ 0Fh
  uint32_t HCCPARAMS1;               // Base + 10h ~ 13h
  uint32_t DBOFF;                    // Base + 14h ~ 17h
  uint32_t RTSOFF;                   // Base + 18h ~ 1Bh
  uint32_t HCCPARAMS2;               // Base + 1Ch ~ 1Fh
} CapabilityRegisters;

typedef struct _HCSPARAMS1_Map {
  uint8_t MaxSlots : 8;
  uint16_t MaxIntrs : 11;
  uint8_t Rsvd : 5;
  uint8_t MaxPorts : 8;
} __attribute__((packed)) HCSPARAMS1_Map_t;

typedef struct _HCSPARAMS2_Map {
  uint32_t IST : 4;
  uint32_t ERST_Max : 4;
  uint32_t Rsvd : 13;
  uint32_t MaxScratchpadBufs_Hi : 5;
  uint32_t SPR : 1;
  uint32_t MaxScratchpadBufs_Lo : 5;
} __attribute__((packed)) HCSPARAMS2_Map_t;

typedef struct _HCSPARAMS3_Map {
  uint8_t U1DeviceExitLatency : 8;
  uint8_t Rsvd : 8;
  uint16_t U2DeviceExitLatency : 16;
} __attribute__((packed)) HCSPARAMS3_Map_t;

typedef struct _HCCPARAMS1_Map {
  uint8_t AC64 : 1;
  uint8_t BNC : 1;
  uint8_t CSZ : 1;
  uint8_t PPC : 1;
  uint8_t PIND : 1;
  uint8_t LHRC : 1;
  uint8_t LTC : 1;
  uint8_t NSS : 1;
  uint8_t PAE : 1;
  uint8_t SPC : 1;
  uint8_t SEC : 1;
  uint8_t CFC : 1;
  uint8_t MaxPSASize : 4;
  uint16_t xECP : 16;
} __attribute__((packed)) HCCPARAMS1_Map_t;

typedef struct _DBOFF_Map {
  uint8_t Rsvd : 2;
  uint32_t DoorbellArrayOffset : 30;
} __attribute__((packed)) DBOFF_Map_t;

typedef struct _RTSOFF_Map {
  uint8_t Rsvd : 5;
  uint32_t RuntimeRegisterSpaceOffset : 27;
} __attribute__((packed)) RTSOFF_Map_t;

typedef struct _HCCPARAMS2_Map {
  uint8_t C3C : 1;
  uint8_t CMC : 1;
  uint8_t FSC : 1;
  uint8_t CTC : 1;
  uint8_t LEC : 1;
  uint8_t CIC : 1;
  uint8_t ETC : 1;
  uint8_t ETC_TSC : 1;
  uint8_t GSC : 1;
  uint8_t VTC : 1;
  uint32_t Rsvd : 22;
} __attribute__((packed)) HCCPARAMS2_Map_t;

typedef struct _OperationalRegisters {
  uint32_t USBCMD;                 // Base + 00h ~ 03h
  uint32_t USBSTS;                 // Base + 04h ~ 07h
  uint32_t PAGESIZE;               // Base + 08h ~ 0Bh
  uint32_t RsvdZ1[2];              // Base + 0Ch ~ 13h
  uint32_t DNCTRL;                 // Base + 14h ~ 17h
  uint64_t CRCR;                   // Base + 18h ~ 1Fh
  uint32_t RsvdZ2[4];              // Base + 20h ~ 2Fh
  uint64_t DCBAAP;                 // Base + 30h ~ 37h
  uint32_t CONFIG;                 // Base + 38h ~ 3Bh
} OperationalRegisters;

typedef struct _USBCMD_Map {
  uint32_t RS : 1;
  uint32_t HCRST : 1;
  uint32_t INTE : 1;
  uint32_t HSEE : 1;
  uint32_t RsvdP1 : 3;
  uint32_t LHCRST : 1;
  uint32_t CSS : 1;
  uint32_t CRS : 1;
  uint32_t EWE : 1;
  uint32_t EU3S : 1;
  uint32_t RsvdP2 : 1;
  uint32_t CME : 1;
  uint32_t ETE : 1;
  uint32_t TSCEN : 1;
  uint32_t VTIOEN : 1;
  uint32_t RsvdP3 : 15;
} __attribute__((packed)) USBCMD_Map_t;

typedef struct _USBSTS_Map {
  uint32_t HCH : 1;
  uint32_t RsvdZ1 : 1;
  uint32_t HSE : 1;
  uint32_t EINT : 1;
  uint32_t PCD : 1;
  uint32_t RsvdZ2 : 3;
  uint32_t SSS : 1;
  uint32_t RSS : 1;
  uint32_t SRE : 1;
  uint32_t CNR : 1;
  uint32_t HCE : 1;
  uint32_t RsvdZ3 : 19;
} __attribute__((packed)) USBSTS_Map_t;

typedef struct _CRCR_Map {
  uint64_t RCS : 1;
  uint64_t CS : 1;
  uint64_t CA : 1;
  uint64_t CRR : 1;
  uint64_t RsvdP1 : 2;
  uint64_t CommandRingPointer_Lo : 26;
  uint64_t CommandRingPointer_Hi : 32;
} __attribute__((packed)) CRCR_Map_t;

typedef struct _DCBAAP_Map {
  uint64_t RsvdZ1 : 6;
  uint64_t DeviceContextBaseAddressArrayPointer_Lo : 26;
  uint64_t DeviceContextBaseAddressArrayPointer_Hi : 32;
} __attribute__((packed)) DCBAAP_Map_t;

typedef struct _CONFIG_Map {
  uint32_t MaxSlotsEn : 8;
  uint32_t U3E : 1;
  uint32_t CIE : 1;
  uint32_t RsvdP : 22;
} __attribute__((packed)) CONFIG_Map_t;

typedef struct _RuntimeRegisters {
  uint32_t MFINDEX;               // Base + 00h
  uint8_t RsvdZ[28];              // Base + 04h
  struct {
    uint32_t IMAN;
    uint32_t IMOD;
    uint32_t ERSTSZ;
    uint64_t ERSTBA;
    uint64_t ERDP;
  } __attribute__((packed)) InterruptRegisterSet[1024]; // Base + 20h
} __attribute__((packed)) RuntimeRegisters;

typedef struct _MFINDEX_Map {
  uint16_t MicroframeIndex : 14;
  uint32_t RsvdZ : 18;
} __attribute__((packed)) MFINDEX_Map_t;

typedef struct _IMAN_Map {
  uint8_t IP : 1;
  uint8_t IE : 1;
  uint32_t RsvdP : 30;
} __attribute__((packed)) IMAN_Map_t;

typedef struct _IMOD_Map {
  uint16_t IMODI : 16;
  uint16_t IMODC : 16;
} __attribute__((packed)) IMOD_Map_t;

typedef struct _ERSTSZ_Map {
  uint16_t EventRingSegmentTableSize : 16;
  uint16_t RsvdP : 16;
} __attribute__((packed)) ERSTSZ_Map_t;

typedef struct _ERSTBA_Map {
  uint8_t RsvdP : 6;
  uint64_t EventRingSegmentTableBaseAddressRegister : 58;
} __attribute__((packed)) ERSTBA_Map_t;

typedef struct _ERDP_Map {
  uint8_t DESI : 3;
  uint8_t EHB : 1;
  uint64_t EventRingDequeuePointer : 60;
} __attribute__((packed)) ERDP_Map_t;

typedef struct _SlotContext {
  uint32_t RouteString : 20;      // Base + 00h ~ 03h
  uint16_t Speed : 4;
  uint8_t RsvdZ1 : 1;
  uint8_t MTT : 1;
  uint8_t Hub : 1;
  uint8_t ContextEntries : 5;

  uint16_t MaxExitLatency : 16;   // Base + 04h ~ 07h
  uint8_t RootHubPortNumber : 8;
  uint8_t NumberofPorts : 8;

  uint8_t ParentHubSlotID : 8;    // Base + 08h ~ 0Bh
  uint8_t ParentPortNumber : 8;
  uint8_t TTT : 2;
  uint8_t RsvdZ2 : 4;
  uint16_t InterrupterTarget : 10;

  uint8_t USBDeviceAddress : 8;   // Base + 0C ~ 0Fh
  uint32_t RsvdZ3 : 19;
  uint8_t SlotState : 5;

  uint32_t RsvdO[4];              // Base + 10h ~ 1Fh
} SlotContext;

typedef struct _EndpointContext {
  uint8_t EPState : 3;            // Base + 00h ~ 03h
  uint8_t RsvdZ1 : 5;
  uint8_t Mult : 2;
  uint8_t MaxPStreams : 5;
  uint8_t LSA : 1;
  uint8_t Interval : 8;
  uint8_t MaxESITPayload_Hi : 8;

  uint8_t RsvdZ2 : 1;             // Base + 04h ~ 07h
  uint8_t CErr : 2;
  uint8_t EPType : 3;
  uint8_t RsvdZ3 : 1;
  uint8_t HID : 1;
  uint8_t MaxBurstSize : 8;
  uint16_t MaxPacketSize : 16;

  uint8_t DCS : 1;                // Base + 08h ~ 0Fh
  uint8_t RsvdZ4 : 3;
  uint64_t TRDequeuePointer : 60;

  uint16_t AverageTRBLength : 16; // Base + 10h ~ 13h
  uint16_t MaxESITPayload_Lo : 16;

  uint32_t RsvdO[3];              // Base + 14h ~ 1Fh
} EndpointContext;

typedef struct _StreamContext {
  uint8_t DCS : 1;                // Base + 00h ~ 07h
  uint8_t SCT : 3;
  uint64_t TRDequeuePointer : 60;

  uint32_t StoppedEDTLA : 24;     // Base + 08 ~ 0Fh
  uint64_t RsvdO : 40;
} StreamContext;

typedef struct _DeviceContext {
  SlotContext slot_context;             // Base + 000h ~ 01Fh
  EndpointContext endpoint_context[31]; // Base + 020h ~ 3FFh
} DeviceContext;

typedef enum {
  TRB_INVALID = 0,
  TRB_SUCCESS,
  TRB_DATA_BUFFER_ERROR,
  TRB_BABBLE_DETECTED_ERROR,
  TRB_USB_TRANSACTION_ERROR,
  TRB_TRB_ERROR,
  TRB_STALL_ERROR,
  TRB_RESOURCE_ERROR,
  TRB_BANDWIDTH_ERROR,
  TRB_NO_SLOTS_AVAILABLE_ERROR,
  TRB_INVALID_STREAM_TYPE_ERROR,
  TRB_SLOT_NOT_ENABLED_ERROR,
  TRB_ENDPOINT_NOT_ENABLED_ERROR,
  TRB_SHORT_PACKET,
  TRB_RING_UNDERRUN,
  TRB_RING_OVERRUN,
  TRB_VF_EVENT_RING_FULL_ERROR,
  TRB_PARAMETER_ERROR,
  TRB_BANDWIDTH_OVERRUN_ERROR,
  TRB_CONTEXT_STATE_ERROR,
  TRB_NO_PING_RESPONSE_ERROR,
  TRB_EVENT_RING_FULL_ERROR,
  TRB_INCOMPATIBLE_DEVICE_ERROR,
  TRB_MISSED_SERVICE_ERROR,
  TRB_COMMAND_RING_STOPPED,
  TRB_COMMAND_ABORTED,
  TRB_STOPPED,
  TRB_STOPPED_LENGTH_INVALID,
  TBR_STOPPED_SHORT_PACKET,
  TRB_MAX_EXIT_LATENCY_TOO_LARGE_ERROR,
  TRB_ISOCH_BUFFER_OVERRUN = 31,
  TRB_EVENT_LOST_ERROR,
  TRB_UNDEFINED_ERROR,
  TRB_INVALID_STREAM_ID_ERROR,
  TRB_SECONDARY_BANDWIDTH_ERROR,
  TRB_SPLIT_TRANSACTION_ERROR,
  TRB_VENDOR_DEFINED_ERROR = 192,
  TRB_VENDOR_DEFINED_INFO = 224
} TRBCompletionCodes;

typedef enum {
  Normal = 1,
  SetupStage,
  DataStage,
  StatusStage,
  Isoch,
  Link,
  EventData,
  NoOp,
  EnableSlotCommand,
  DisableSlotCommand,
  AddressDeviceCommand,
  ConfigureEndpointCommand,
  EvaluateContextCommand,
  ResetEndpointCommand,
  StopEndpointCommand,
  SetTRDequeuePointerCommand,
  ResetTRDequeueCommand,
  ForceEventCommand,
  NegotiateBandwidthCommand,
  SetLTVCommand,
  GetPortBandwidthCommand,
  ForceHeaderCommand,
  NoOpCommand,
  GetExtendedPropertyCommand,
  SetExtendedPropertyCommand,
  TransferEvent = 32,
  CommandCompletionEvent,
  PortStatusChangeEvent,
  BandwidthRequestEvent,
  DoorbellEvent,
  HostControllerEvent,
  DeviceNorificationEvent,
  MFINDEXWrapEvent
} TRBTypes;

typedef struct _TRB {
  uint64_t address : 64;
  uint32_t status : 32;
  uint32_t flag : 32;
} TRB;

#define XHCI_TRB_R_CYCLE_BIT(trb_flag)  ((trb_flag >> 00) & 0x01)
#define XHCI_TRB_R_ENT(trb_flag)        ((trb_flag >> 01) & 0x01)
#define XHCI_TRB_R_TRB_TYPE(trb_flag)   ((trb_flag >> 10) & 0x3F)

#define XHCI_TRB_W_CYCLE_BIT(trb_flag)  ((trb_flag & 0x01) << 00)
#define XHCI_TRB_W_ENT(trb_flag)        ((trb_flag & 0x01) << 01)
#define XHCI_TRB_W_TRB_TYPE(trb_flag)   ((trb_flag & 0x3F) << 10)

typedef struct _NormalTRB {
  uint32_t DataBufferPointer_Lo : 32;   // Base + 00h ~ 03h
  uint32_t DataBufferPointer_Hi : 32;   // Base + 04h ~ 07h
  uint32_t TRBTransferLength : 17;      // Base + 08h ~ 0Bh
  uint8_t TDSize : 5;
  uint16_t InterrupterTarget : 10;
  uint8_t C : 1;                        // Base + 0Ch ~ 0Fh
  uint8_t ENT : 1;
  uint8_t ISP : 1;
  uint8_t NS : 1;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t IDT : 1;
  uint8_t RsvdZ1 : 2;
  uint8_t BEI : 1;
  uint8_t TRBType : 6;
  uint16_t RsvdZ2 : 16;
} NormalTRB;

typedef struct _SetupStageTRB {
  uint8_t bmRequestType : 8;
  uint8_t bRequest : 8;
  uint16_t wValue : 16;

  uint16_t wIndex : 16;
  uint16_t wLength : 16;

  uint32_t TRBTransferLength : 17;
  uint8_t RsvdZ : 5;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t RsvdZ2 : 4;
  uint8_t IOC : 1;
  uint8_t IDT : 1;
  uint8_t RsvdZ3 : 3;
  uint8_t TRBType : 6;
  uint8_t TRT : 2;
  uint16_t RsvdZ4 : 14;
} SetupStageTRB;

typedef struct _DataStageTRB {
  uint32_t DataBufferPointer_Lo : 32;
  
  uint32_t DataBufferPointer_Hi : 32;

  uint32_t TRBTransferLength : 17;
  uint8_t TDSize : 5;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t ENT : 1;
  uint8_t ISP : 1;
  uint8_t NS : 1;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t IDT : 1;
  uint8_t RsvdZ1 : 3;
  uint8_t TRBType : 6;
  uint8_t DIR : 1;
  uint16_t RsvdZ2 : 15;
} DataStageTRB;

typedef struct _StatusStageTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 22;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t ENT : 1;
  uint8_t RsvdZ4 : 2;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t RsvdZ5 : 4;
  uint8_t TRBType : 6;
  uint8_t DIR : 1;
  uint16_t RsvdZ6 : 15;
} StatusStageTRB;

typedef struct _IsochTRB {
  uint32_t DataBufferPointer_Lo : 32;
  uint32_t DataBufferPointer_Hi : 32;

  uint32_t TRBTransferLength : 17;
  uint8_t TBC : 5;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t ENT : 1;
  uint8_t ISP : 1;
  uint8_t NS : 1;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t IDT : 1;
  uint8_t TBCSts : 2;
  uint8_t BEI : 1;
  uint8_t TRBType : 6;
  uint8_t TLBPC : 4;
  uint16_t FrameID : 11;
  uint8_t SIA : 1;
} IsochTRB;

typedef struct _NoOpTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 22;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t ENT : 1;
  uint8_t RsvdZ4 : 2;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t RsvdZ5 : 4;
  uint8_t TRBType : 6;
  uint16_t RsvdZ6 : 16;
} NoOpTRB;

typedef struct _TransferEventTRB {
  uint32_t TRBPointer_Lo : 32;
  uint32_t TRBPointer_Hi : 32;

  uint32_t TRBTransferLength : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint8_t RsvdZ1 : 1;
  uint8_t ED : 1;
  uint8_t RsvdZ2 : 7;
  uint8_t TRBType : 6;
  uint8_t EndpointID : 5;
  uint8_t RsvdZ3 : 3;
  uint8_t SlotID : 8;
} TransferEventTRB;

typedef struct _CommandCompletionEventTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t CommandTRBPointer_Lo : 28;
  uint32_t CommandTRBPointer_Hi : 32;

  uint32_t CommandCompletionParameter : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ2 : 9;
  uint8_t TRBType : 6;
  uint8_t VFID : 8;
  uint8_t SlotID : 8;
} CommandCompletionEventTRB;

typedef struct _PortStatusChangeEventTRB {
  uint32_t RsvdZ1 : 24;
  uint8_t PortID : 8;

  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint16_t RsvdZ5 : 16;
} PortStatusChangeEventTRB;

typedef struct _BandwidthRequestEventTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t RsvdZ5 : 8;
  uint8_t SlotID : 8;
} BandwidthRequestEventTRB;

typedef struct _DoorbellEventTRB {
  uint8_t DBReason : 5;
  uint32_t RsvdZ1 : 27;
  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t VFID : 8;
  uint8_t SlotID : 8;
} DoorbellEventTRB;

typedef struct _HostControllerEventTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  
  uint32_t RsvdZ3 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint16_t RsvdZ5 : 16;
} HostControllerEventTRB;

typedef struct _DeviceNotificationEventTRB {
  uint8_t RsvdZ1 : 4;
  uint8_t NotificationType : 4;
  uint32_t DeviceNotificationData_Lo : 24;
  uint32_t DeviceNotificationData_Hi : 32;

  uint32_t RsvdZ2 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ3 : 9;
  uint8_t TRBType : 6;
  uint8_t RsvdZ4 : 8;
  uint8_t SlotID : 8;
} DeviceNotificationEventTRB;

typedef struct _MFINDEXWrapEventTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;

  uint32_t RsvdZ3 : 24;
  uint8_t CompletionCode : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint16_t RsvdZ5 : 16;
} MFINDEXWrapEventTRB;

typedef struct _NoOpCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint16_t RsvdZ5 : 16;
} NoOpCommandTRB;

typedef struct _EnableSlotCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;
  
  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t SlotType : 5;
  uint16_t RsvdZ5 : 11;
} EnableSlotCommandTRB;

typedef struct _DisableSlotCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;
  
  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t RsvdZ5 : 8;
  uint16_t SlotID : 8;
} DisableSlotCommandTRB;

typedef struct _AddressDeviceCommandTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t InputContextPointer_Lo : 28;
  uint32_t InputContextPointer_Hi : 32;

  uint32_t RsvdZ2 : 32;

  uint8_t C : 1;
  uint8_t RsvdZ3 : 8;
  uint8_t BSR : 1;
  uint8_t TRBType : 6;
  uint8_t RsvdZ4 : 8;
  uint8_t SlotID : 8;
} AddressDeviceCommandTRB;

typedef struct _ConfigureEndpointCommandTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t InputContextPointer_Lo : 28;
  uint32_t InputContextPointer_Hi : 32;

  uint32_t RsvdZ2 : 32;

  uint8_t C : 1;
  uint8_t RsvdZ3 : 8;
  uint8_t DC : 1;
  uint8_t TRBType : 6;
  uint8_t RsvdZ4 : 8;
  uint8_t SlotID : 8;
} ConfigureEndpointCommandTRB;

typedef AddressDeviceCommandTRB EvaluateContextCommandTRB;

typedef struct _ResetEndpointCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;
  
  uint8_t C : 1;
  uint16_t RsvdZ4 : 8;
  uint8_t TSP : 1;
  uint8_t TRBType : 6;
  uint8_t EndpointID : 5;
  uint8_t RsvdZ5 : 3;
  uint16_t SlotID : 8;
} ResetEndpointCommandTRB;

typedef struct _StopEndpointCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;
  
  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t EndpointID : 5;
  uint8_t RsvdZ5 : 2;
  uint8_t SP : 1;
  uint16_t SlotID : 8;
} StopEndpointCommandTRB;

typedef struct _SetTRDequeuePointerCommandTRB {
  uint8_t DCS : 1;
  uint8_t SCT : 3;
  uint32_t NewTRDequeuePointer_Lo : 28;
  uint32_t NewTRDequeuePointer_Hi : 32;

  uint16_t RsvdZ1 : 16;
  uint16_t StreamID : 16;

  uint8_t C : 1;
  uint16_t RsvdZ2 : 9;
  uint8_t TRBType : 6;
  uint8_t EndpointID : 5;
  uint8_t RsvdZ3 : 3;
  uint8_t SlotID : 8;
} SetTRDequeuePointerCommandTRB;

typedef struct _ResetDeviceCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;
  
  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t RsvdZ5 : 8;
  uint16_t SlotID : 8;
} ResetDeviceCommandTRB;

typedef struct _ForceEventCommandTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t EventTRBPointer_Lo : 28;
  uint32_t EventTRBPointer_Hi : 32;

  uint32_t RsvdZ2 : 22;
  uint16_t VFInterrupterTarget : 10;

  uint8_t C : 1;
  uint16_t RsvdZ3 : 9;
  uint8_t TRBType : 6;
  uint8_t VFID : 8;
  uint8_t RsvdZ4 : 8;
} ForceEventCommandTRB;

typedef DisableSlotCommandTRB NegotiateBandwidthCommandTRB;

typedef struct _SetLTVCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;
  uint32_t RsvdZ3 : 32;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint16_t BELT : 12;
  uint8_t RsvdZ5 : 4;
} SetLTVCommandTRB;

typedef struct _GetPortBandwidthCommandTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t PortBandwidthContextPointer_Lo : 28;
  uint32_t PortBandwidthContextPointer_Hi : 32;

  uint32_t RsvdZ2 : 32;

  uint8_t C : 1;
  uint16_t RsvdZ3 : 9;
  uint8_t TRBType : 6;
  uint8_t DevSpeed : 4;
  uint8_t RsvdZ4 : 4;
  uint8_t HubSlotID : 8;
} GetPortBandwidthCommandTRB;

typedef struct _ForceHeaderCommandTRB {
  uint8_t Type : 5;
  uint32_t HeaderInfo_Lo : 27;
  uint32_t HeaderInfo_Mid : 32;
  uint32_t HeaderInfo_Hi : 32;

  uint8_t C : 1;
  uint16_t RsvdZ1 : 9;
  uint8_t TRBType : 6;
  uint8_t RsvdZ2 : 8;
  uint8_t RootHubPortNumber : 8;
} ForceHeaderCommandTRB;

typedef struct _GetExtendedPropertyCommandTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t ExtendedPropertyContextPointer_Lo : 28;
  uint32_t ExtendedPropertyContextPointer_Hi : 32;

  uint16_t ECI : 16;
  uint16_t RsvdZ2 : 16;

  uint8_t C : 1;
  uint16_t RsvdZ3 : 9;
  uint8_t TRBType : 6;
  uint8_t CommandSubType : 3;
  uint8_t EndpointID : 5;
  uint8_t SlotID : 8;
} GetExtendedPropertyCommandTRB;

typedef struct _SetExtendedPropertyCommandTRB {
  uint32_t RsvdZ1 : 32;
  uint32_t RsvdZ2 : 32;

  uint16_t ECI : 16;
  uint8_t CapabilityParameter : 8;
  uint8_t RsvdZ3 : 8;

  uint8_t C : 1;
  uint16_t RsvdZ4 : 9;
  uint8_t TRBType : 6;
  uint8_t CommandSubType : 3;
  uint8_t EndpointID : 5;
  uint8_t SlotID : 8;
} SetExtendedPropertyCommandTRB;

typedef struct _LinkTRB {
  uint8_t RsvdZ1 : 4;
  uint32_t RingSegmentPointer_Lo : 28;
  uint32_t RingSegmentPointer_Hi : 32;

  uint32_t RsvdZ2 : 22;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t TC : 1;
  uint8_t RsvdZ3 : 2;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t RsvdZ4 : 4;
  uint8_t TRBType : 6;
  uint16_t RsvdZ5 : 16;
} LinkTRB;

typedef struct _EventDataTRB {
  uint32_t EventData_Lo : 32;
  uint32_t EventData_Hi : 32;

  uint32_t RsvdZ1 : 22;
  uint16_t InterrupterTarget : 10;

  uint8_t C : 1;
  uint8_t ENT : 1;
  uint8_t RsvdZ2 : 2;
  uint8_t CH : 1;
  uint8_t IOC : 1;
  uint8_t RsvdZ3 : 3;
  uint8_t BEI : 1;
  uint8_t TRBType : 6;
  uint16_t RsvdZ4 : 16;
} EventDataTRB;

#define XHCI_COMMAND_RING_SIZE 32
typedef struct {
  TRB trbs[XHCI_COMMAND_RING_SIZE];
  TRB *enq_ptr;
  TRB *deq_ptr;
  uint8_t cycle_bit;
} CommandRing;

extern CapabilityRegisters *capability_registers;
extern OperationalRegisters *operational_registers;
extern RuntimeRegisters *runtime_registers;

extern __attribute__((aligned(64))) CommandRing *command_ring;

// Device Context Base Address Array
// 0 : If the Max Scratchpad Buffers field of the HCSPARAMS2 register is
//       ... > 0, then this entry shall contain a pointer to the Scratchpad Buffer Array.
//       ... = 0, then this entry is reserved and shall be cleared to '0' by software.
// 1-XHCI_MAX_SLOT_ENABLED : These entries shall contain a 64-bit pointer to the base of associated Device Context.
// Bit5-0 : Reserved.
// Bit63-6 : Contain a pointer to a Device Context data structure. Device Context data structure is aligned on a 64 byte boundary,
//            hence the low order 6 bits are reserved and always cleared to '0' when initialized by software.
extern __attribute__((aligned(64))) DeviceContext *DCBAA[XHCI_MAX_SLOT_ENABLED+1];

void xhci_init();
#endif