#include <elf.h>
#include <efi.h>
#include <efilib.h>

#include "load.h"

extern EFI_SYSTEM_TABLE *sys_table;

void load_program(Elf64_Phdr *phdr, Elf64_Half e_phnum, void *file_buf) {
  for(Elf64_Half i = 0; i < e_phnum; i++) {
    Elf64_Addr phys_addr = phdr->p_paddr;
    Elf64_Off offset = phdr->p_offset;
    Elf64_Xword file_size = phdr->p_filesz;

    gBS->AllocatePages(AllocateAddress, EfiLoaderData, (file_size + 0xfff) / 0x1000, (EFI_PHYSICAL_ADDRESS *)phys_addr);
    sys_table->BootServices->CopyMem((void *)phys_addr, (void *)(file_buf + offset), file_size);

    phdr++;
  }
}