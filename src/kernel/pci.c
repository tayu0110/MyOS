#include "pci.h"
#include "portio.h"

uint32_t pci_device_num;
pci_device_info_t pci_devices[PCI_BUS_NUM_MAX * PCI_DEVICE_NUM_MAX * PCI_FUNCTION_NUM_MAX];

// Add the informations of pci devices into pci_devices[].
static void pci_add_device(uint8_t bus, uint8_t slot, uint8_t func, uint8_t class_code, uint8_t sub_class, uint8_t prog_if) {
  pci_device_info_t *info = pci_devices + pci_device_num;
  info->bus = bus;
  info->slot = slot;
  info->func = func;
  info->class_code = class_code;
  info->sub_class = sub_class;
  info->prog_if = prog_if;
  pci_device_num++;
}

// Declare a function prototype for using pci_scan_bus() in pci_scan_func().
static void pci_scan_bus(uint8_t bus);
// If a passed device is PCI to PCI bridge, take out the secondary bus number and search that bus by pci_scan_bus().
// Otherwise, add it into pci_devices[] with pci_add_device().
static void pci_scan_func(uint8_t bus, uint8_t device, uint8_t func) {
  uint8_t class_code = pci_get_class_code(bus, device, func);
  uint8_t sub_class = pci_get_sub_class(bus, device, func);
  if(class_code != 0x06 || sub_class != 0x04) {
    uint8_t prog_if = (uint8_t)((pci_read_config_word(bus, device, func, 0x08) >> 8) & 0xFF);
    pci_add_device(bus, device, func, class_code, sub_class, prog_if);
    return;
  }

  uint8_t secondary_bus_number = (uint8_t)((pci_read_config_word(bus, device, func, 0x18) >> 8) & 0xFF);

  pci_scan_bus(secondary_bus_number);
}

// Check whether the device is a multi-function device or not.
// If that is a single-function device, only scan function 0 of that.
// Otherwise, check function numbers that have a device and scan it.
static void pci_scan_device(uint8_t bus, uint8_t device) {
  uint16_t vendor_id = pci_get_vendor_id(bus, device, 0);
  if(vendor_id == PCI_INVALID_VENDOR_ID) return;

  pci_scan_func(bus, device, 0);

  uint8_t header_type = pci_get_header_type(bus, device, 0);
  if(~header_type & (1 << 7)) return;

  for(uint8_t func = 1; func < PCI_FUNCTION_NUM_MAX; func++) {
    vendor_id = pci_get_vendor_id(bus, device, func);
    if(vendor_id == PCI_INVALID_VENDOR_ID) continue;

    pci_scan_func(bus, device, func);
  }
}

// Scan the bus that has a bus number passed as the argument.
static void pci_scan_bus(uint8_t bus) {
  for(uint16_t device = 0; device < PCI_DEVICE_NUM_MAX; device++) {
    pci_scan_device(bus, device);
  }
}

// Scan all PCI buses.
// If the devices are found, they are added into pci_devices[].
static void pci_scan_all_buses() {
  uint8_t header_type = pci_get_header_type(0, 0, 0);
  if(~header_type & (1 << 7)) {
    pci_scan_bus(0);
    return;
  }

  for(uint8_t func = 0; func < PCI_FUNCTION_NUM_MAX; func++) {
    uint16_t vendor_id = pci_get_vendor_id(0, 0, func);
    if(vendor_id == PCI_INVALID_VENDOR_ID) continue;
  
    pci_scan_bus(func);
  }
}

// Explore and expose available PCI devices so that the kernel can find them.
void pci_init() {
  pci_device_num = 0;
  pci_scan_all_buses();
}

// Extract the contents of the header in 32-bit width.
// The offset of the data to be retrieved must be separated by 4 bytes.
uint32_t pci_read_config_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t lbus = (uint32_t)bus;
  uint32_t lslot = (uint32_t)slot;
  uint32_t lfunc = (uint32_t)func;

  uint32_t address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

  out_port(CONFIG_ADDRESS, address);

  return in_port(CONFIG_DATA);
}

// Extract the contents of the header in 16-bit width.
// The offset of the data to be retrieved must be separated by 2 bytes.
uint16_t pci_read_config_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t conf_dw = pci_read_config_dword(bus, slot, func, offset);

  uint16_t res = (uint16_t)((conf_dw >> ((offset & 2) * 8)) & 0xFFFF);

  return res;
}

// Extract the Vendor ID of the specified device.
uint16_t pci_get_vendor_id(uint8_t bus, uint8_t slot, uint8_t func) {
  return pci_read_config_word(bus, slot, func, 0x00);
}

// Extract the Device ID of the specified device.
uint16_t pci_get_device_id(uint8_t bus, uint8_t slot, uint8_t func) {
  return pci_read_config_word(bus, slot, func, 0x02);
}

// Extract the Sub Class of the specified device.
uint8_t pci_get_sub_class(uint8_t bus, uint8_t slot, uint8_t func) {
  return (uint8_t)pci_read_config_word(bus, slot, func, 0x0A);
}

// Extract the Class Code of the specified device.
uint8_t pci_get_class_code(uint8_t bus, uint8_t slot, uint8_t func) {
  uint16_t class = pci_read_config_word(bus, slot, func, 0x0A);
  return (uint8_t)(class >> 8);
}

// Extract the Header Type of the specified device.
uint8_t pci_get_header_type(uint8_t bus, uint8_t slot, uint8_t func) {
  return (uint8_t)pci_read_config_word(bus, slot, func, 0x0E);
}

// Converts a Class Code from a number to a string.
char* parse_class_code(uint8_t class_code) {
  switch(class_code) {
    case 0x00: return "Unclassified";
    case 0x01: return "Mass Storage Controller";
    case 0x02: return "Network Controller";
    case 0x03: return "Display Controller";
    case 0x04: return "Multimedia Controller";
    case 0x05: return "Memory Controller";
    case 0x06: return "Bridge";
    case 0x07: return "Simple Communication Controller";
    case 0x08: return "Base System Peripheral";
    case 0x09: return "Input Device Controller";
    case 0x0A: return "Docking Station";
    case 0x0B: return "Processor";
    case 0x0C: return "Serial Bus Controller";
    case 0x0D: return "Wireless Controller";
    case 0x0E: return "Intelligent Controller";
    case 0x0F: return "Satellite Communication Controller";
    case 0x10: return "Encryption Controller";
    case 0x11: return "Signal Processing Controller";
    case 0x12: return "Processing Accelarator";
    case 0x13: return "Non-Essential Instrumentation";
    case 0x40: return "Co-Processor";
    case 0xFF: return "Unassigned Class(Vendor specific";
    default: return "Reserved";
  }
}
