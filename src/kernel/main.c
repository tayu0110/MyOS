#include "graphics.h"
#include "pci.h"
#include "print.h"

int main(frame_buffer_info_t frame_buffer) {
  init_graphics(frame_buffer);

  clear_srceen();

  set_cursor(0, 0);
  put_string("Hello, World!\n");
  
  pci_init();

  put_char('\n');

  for(int i = 0; i < pci_device_num; i++) {
    pci_device_info_t info = pci_devices[i];
    printk("Bus: %d, Device: %d, Func: %d, Class: %s, Sub Class: %x, Prog IF: %x\n", 
        info.bus, info.slot, info.func, parse_class_code(info.class_code), info.sub_class, info.prog_if);
  }

  return 0;
}
