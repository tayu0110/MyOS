#ifndef _PCI_H_INCLUDED_
#define _PCI_H_INCLUDED_

#include <stdint.h>

#define CONFIG_ADDRESS  ((uint16_t)0xCF8)
#define CONFIG_DATA     ((uint16_t)0xCFC)

#define PCI_INVALID_VENDOR_ID 0xFFFF

#define PCI_BUS_NUM_MAX       ((uint32_t)256)
#define PCI_DEVICE_NUM_MAX    ((uint32_t)32)
#define PCI_FUNCTION_NUM_MAX  ((uint32_t)8)

typedef struct _pci_device_info_t {
  uint8_t bus;
  uint8_t slot;
  uint8_t func;
  uint8_t class_code;
  uint8_t sub_class;
  uint8_t prog_if;
} pci_device_info_t;

// When the dynamic memory allocation mechanism is implemented,
// this array should be changed so that it is not statically allocated by linked list or the like.
extern pci_device_info_t pci_devices[PCI_BUS_NUM_MAX * PCI_DEVICE_NUM_MAX * PCI_FUNCTION_NUM_MAX];
extern uint32_t pci_device_num;

void pci_init();
uint32_t pci_read_config_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pci_read_config_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pci_get_vendor_id(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_device_id(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t pci_get_sub_class(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t pci_get_class_code(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t pci_get_header_type(uint8_t bus, uint8_t slot, uint8_t func);
uint32_t pci_get_BAR0(uint8_t bus, uint8_t slot, uint8_t func);
uint32_t pci_get_BAR1(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_system_vendor_id(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_subsystem_id(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t pci_get_capabilities_pointer(uint8_t bus, uint8_t slot, uint8_t func);

char* parse_class_code(uint8_t class_code);

typedef struct {
  uint8_t cap_id : 8;
  uint8_t nxt_ptr : 8;
  uint16_t msi_msg_ctrl : 16;
  uint32_t msg_address : 32;
  uint32_t msg_upper_address : 32;
  uint16_t msg_data : 16;
  uint16_t RsvdP : 16;
} msi_conf_cap;

typedef struct {
  uint8_t cap_id : 8;
  uint8_t nxt_ptr : 8;
  uint16_t msix_msg_ctrl : 16;
  uint8_t table_BIR : 3;
  uint32_t table_offset : 29;
  uint8_t PBA_BIR : 3;
  uint32_t PBA_offset : 29;
} msix_conf_cap;

msi_conf_cap pci_get_msi_conf_cap(uint8_t bus, uint8_t slot, uint8_t func);
msix_conf_cap pci_get_msix_conf_cap(uint8_t bus, uint8_t slot, uint8_t func);

#endif