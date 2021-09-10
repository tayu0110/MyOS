#ifndef _PCI_H_INCLUDED_
#define _PCI_H_INCLUDED_

#include <stdint.h>

#define CONFIG_ADDRESS  ((uint16_t)0xCF8)
#define CONFIG_DATA     ((uint16_t)0xCFC)

#define PCI_INVALID_VENDOR_ID 0xFFFF

#define PCI_BUS_NUM_MAX       256
#define PCI_DEVICE_NUM_MAX    32
#define PCI_FUNCTION_NUM_MAX  8

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

char* parse_class_code(uint8_t class_code);

#endif