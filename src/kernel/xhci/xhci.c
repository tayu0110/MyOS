#include "xhci.h"
#include "../pci.h"

#include <string.h>

// For test
#include "../print.h"

CapabilityRegisters *capability_registers;
OperationalRegisters *operational_registers;
RuntimeRegisters *runtime_registers;

__attribute__((aligned(64))) CommandRing *command_ring;

// Device Context Base Address Array
// For details, Refer to xHCI Specification 6.1.
__attribute__((aligned(64))) DeviceContext *DCBAA[XHCI_MAX_SLOT_ENABLED+1];

// Search a xHC on the PCI device list.
// If a device is a xHC, base class code is 0x0C, sub class code is 0x03 and programming interface is 0x30 in the PCI header.
static pci_device_info_t search_xhc(void) {
  for(uint32_t i = 0; i < pci_device_num; i++) {
    pci_device_info_t info = pci_devices[i];
    if(info.class_code == 0x0C && info.sub_class == 0x03 && info.prog_if == 0x30) return info;
  }
}

// Get the base address of xHC register space.
static uint64_t get_mmio_base(pci_device_info_t *xhc) {
  uint64_t bar0 = (uint64_t)pci_get_BAR0(xhc->bus, xhc->slot, xhc->func);
  uint64_t bar1 = (uint64_t)pci_get_BAR1(xhc->bus, xhc->slot, xhc->func);
  uint64_t align_mask = ~((uint64_t)0xF);

  return bar1 << 32 | bar0 & align_mask;
}

// Set FLADJ field in the PCI Configuration Registers
static void set_FLADJ(void) {
  // As the appropriate setting value are unknown, Implementation is pending.
  // Refer to xHCI Specification 5.2.4. for details.
}

// Initialize the DCBAA and Set the DCBAAP field in the Operational Registers with the base address of DCBAA.
static void init_DCBAA(void) {
  memset(DCBAA, (DeviceContext *)0, sizeof(DCBAA));
  operational_registers->DCBAAP = (uint64_t)DCBAA;
}

// Initialize the Command Ring
static void init_command_ring(void) {
  // TODO : Implement the initialization of Command Ring

  memset(command_ring->trbs, (TRB *)0, sizeof(command_ring->trbs));

  command_ring->cycle_bit = 1;
  command_ring->deq_ptr = command_ring->enq_ptr = command_ring->trbs;

  // Initialize the CRCR in the Operational Registers with the front of the address of the Command Ring.
  operational_registers->CRCR = ((uint64_t)command_ring->trbs & 0xFFFFFFFFFFFFFFC0) | command_ring->cycle_bit;
}

// Initialize the xHC by the following operations.
//    - Get the base address of xHC registar space
//    - Initialize the system I/O memory mapping (if supported)
//    - Chipset Hardware Reset
//    - Set the configuration of some kinds of registers
//    - Initialize each active interrupter
void xhci_init(void) {
  pci_device_info_t xhc = search_xhc();

  // Get the addresses of Capability Registers, Operational Registers and Runtime Registers
  uint64_t mmio_base = get_mmio_base(&xhc);
  capability_registers = (CapabilityRegisters *)mmio_base;
  uint64_t cap_length = (uint64_t)capability_registers->CAPLENGTH;
  operational_registers = (OperationalRegisters *)(mmio_base + cap_length);
  uint64_t rts_off = (uint64_t)capability_registers->RTSOFF;
  runtime_registers = (RuntimeRegisters *)(mmio_base + (rts_off & ~0x1F));

  volatile uint32_t *usbsts = &operational_registers->USBSTS;
  volatile uint32_t *usbcmd = &operational_registers->USBCMD;
  volatile uint32_t *config = &operational_registers->CONFIG;

  // Set the FLADJ register.
  // This register can be set only when the HCH bit in the USBSTS is standing.
  if(*usbsts & 1) {
    set_FLADJ();
  }

  // Chipset Hardware Reset
  // After writing '1' to the HCRST bit in the USBCMD, wait until HCRST bit drops down again.
  // After that, wait for CNR bit in the USBSTS dropping down.
  *usbcmd |= 1 << 1;
  while(*usbcmd & (1 << 1));
  while(*usbsts & (1 << 11));

  printk("Completed to reset a host controller!\n");

  // Set the MaxSlotsEn field in the CONFIG.
  *config &= (XHCI_MAX_SLOT_ENABLED | 0xFFFFFF00);

  // Initialize Command Ring and CRCR register.
  init_command_ring();

  init_DCBAA();
}