#include "graphics.h"
#include "pci.h"
#include "print.h"
#include "xhci/xhci.h"

int main(frame_buffer_info_t frame_buffer) {
  init_graphics(frame_buffer);
  set_cursor(0, 0);
  pci_init();
  xhci_init();

  put_char('\n');

  uint8_t *cap_length = &capability_registers->CAPLENGTH;
  uint8_t *Rsvd = &capability_registers->Rsvd;
  uint8_t *hci_version = &capability_registers->HCIVERSION;
  uint8_t *hcs_params1 = &capability_registers->HCSPARAMS1;
  uint8_t *hcs_params2 = &capability_registers->HCSPARAMS2;
  uint8_t *hcs_params3 = &capability_registers->HCSPARAMS3;
  uint8_t *hcc_params1 = &capability_registers->HCCPARAMS1;
  uint8_t *db_off = &capability_registers->DBOFF;
  uint8_t *rts_off = &capability_registers->RTSOFF;
  uint8_t *hcc_params2 = &capability_registers->HCCPARAMS2;

  printk("Offset CAPLENGTH  : 0x%04x\n", cap_length - (uint8_t *)capability_registers);
  printk("Offset Rsvd       : 0x%04x\n", Rsvd - (uint8_t *)capability_registers);
  printk("Offset HCIVERSION : 0x%04x\n", hci_version - (uint8_t *)capability_registers);
  printk("Offset HCSPARAMS1 : 0x%04x\n", hcs_params1 - (uint8_t *)capability_registers);
  printk("Offset HCSPARAMS2 : 0x%04x\n", hcs_params2 - (uint8_t *)capability_registers);
  printk("Offset HCSPARAMS3 : 0x%04x\n", hcs_params3 - (uint8_t *)capability_registers);
  printk("Offset HCCPARAMS1 : 0x%04x\n", hcc_params1 - (uint8_t *)capability_registers);
  printk("Offset DBOFF      : 0x%04x\n", db_off - (uint8_t *)capability_registers);
  printk("Offset RTSOFF     : 0x%04x\n", rts_off - (uint8_t *)capability_registers);
  printk("Offset HCCPARAMS2 : 0x%04x\n", hcc_params2 - (uint8_t *)capability_registers);

  put_char('\n');

  printk("CAPLENGTH  : 0x%08x\n", *cap_length);
  printk("Rsvd       : 0x%08x\n", *Rsvd);
  printk("HCIVERSION : 0x%08x\n", *hci_version);
  printk("HCSPARAMS1 : 0x%08x\n", *hcs_params1);
  printk("HCSPARAMS2 : 0x%08x\n", *hcs_params2);
  printk("HCSPARAMS3 : 0x%08x\n", *hcs_params3);
  printk("HCCPARAMS1 : 0x%08x\n", *hcc_params1);
  printk("DBOFF      : 0x%08x\n", *db_off);
  printk("RTSOFF     : 0x%08x\n", *rts_off);
  printk("HCCPARAMS2 : 0x%08x\n", *hcc_params2);

  put_char('\n');

  // uint8_t *usb_cmd = &operational_registers->USBCMD;
  // uint8_t *usb_sts = &operational_registers->USBSTS;
  // uint8_t *pagesize = &operational_registers->PAGESIZE;
  // uint8_t *rsvdz1 = &operational_registers->RsvdZ1;
  // uint8_t *dnctrl = &operational_registers->DNCTRL;
  // uint8_t *crcr = &operational_registers->CRCR;
  // uint8_t *rsvdz2 = &operational_registers->RsvdZ2;
  // uint8_t *dcbaap = &operational_registers->DCBAAP;
  // uint8_t *config = &operational_registers->CONFIG;

  // printk("Offset USBCMD   : 0x%04x\n", usb_cmd - (uint8_t *)operational_registers);
  // printk("Offset USBSTS   : 0x%04x\n", usb_sts - (uint8_t *)operational_registers);
  // printk("Offset PAGESIZE : 0x%04x\n", pagesize - (uint8_t *)operational_registers);
  // printk("Offset RsvdZ1   : 0x%04x\n", rsvdz1 - (uint8_t *)operational_registers);
  // printk("Offset DNCTRL   : 0x%04x\n", dnctrl - (uint8_t *)operational_registers);
  // printk("Offset CRCR     : 0x%04x\n", crcr - (uint8_t *)operational_registers);
  // printk("Offset RsvdZ2   : 0x%04x\n", rsvdz2 - (uint8_t *)operational_registers);
  // printk("Offset DCBAAP   : 0x%04x\n", dcbaap - (uint8_t *)operational_registers);
  // printk("Offset CONFIG   : 0x%04x\n", config - (uint8_t *)operational_registers);

  // printk("USBSMD  : 0x%08x\n", operational_registers->USBCMD);
  // printk("USBSTS  : 0x%08x\n", operational_registers->USBSTS);
  // printk("PAGESIZE: 0x%08x\n", operational_registers->PAGESIZE);
  // printk("RsvdZ1  : 0x%016lx\n", operational_registers->RsvdZ1);
  // printk("DNCTRL  : 0x%08x\n", operational_registers->DNCTRL);
  // printk("CRCR    : 0x%016lx\n", operational_registers->CRCR);
  // printk("RsvdZ2  : 0x%016lx\n", operational_registers->RsvdZ2);
  // printk("DCBAAP  : 0x%016lx\n", operational_registers->DCBAAP);
  // printk("CONFIG  : 0x%08x\n", operational_registers->CONFIG);
  // put_char('\n');

  return 0;
}
