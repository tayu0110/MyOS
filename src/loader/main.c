#include <efi.h>
#include <efilib.h>
#include <elf.h>

#include "util.h"
#include "frame_buffer.h"
#include "fs.h"
#include "load.h"

EFI_SYSTEM_TABLE *sys_table;

static EFI_STATUS elf_check(const CHAR8 *magic) {
  const CHAR8 *elf_magic = (const CHAR8 *)"\x7f" "ELF";
  if(strncmpa(magic, elf_magic, 4)) {
    Print(L"[Fatal] This file is not ELF format file...\n");
    while(1);
  }
  Print(L"[Succeeded!] File format checked!\n");

  return EFI_SUCCESS;
}

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(ImageHandle, SystemTable);
  sys_table = SystemTable;
  SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
  Print(L"OS Loading...\n");
  
  // Get the address of the top of EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.
  InitializeFileSystem(SystemTable);

  // Open root directory.
  // If opening failed, root_dir is NULL.
  EFI_FILE_PROTOCOL *root_dir = (EFI_FILE_PROTOCOL *)NULL;
  OpenRootDir(&root_dir);

  // Search kernel.elf in root directory.
  EFI_FILE_PROTOCOL *kernel_elf = (EFI_FILE_PROTOCOL *)NULL;
  OpenFileReadOnly(root_dir, &kernel_elf, L"\\kernel.elf");

  // Allocate a buffer to store the contents of kernel.elf temporarily.
  // Before allocating, get the size of kernel file.
  UINTN kernel_elf_info_size = 2 * sizeof(EFI_FILE_INFO);
  CHAR8 kernel_elf_info_buf[kernel_elf_info_size];
  EFI_GUID lfp_guid = EFI_FILE_INFO_ID;
  EFI_STATUS stat = kernel_elf->GetInfo(kernel_elf, &lfp_guid, &kernel_elf_info_size, (void *)kernel_elf_info_buf);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to get the infomation of kernel.elf...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  EFI_FILE_INFO *kernel_elf_info = (EFI_FILE_INFO *)kernel_elf_info_buf;
  // Execute to allocate with getting file size.
  UINTN kernel_elf_temp_buf_size = kernel_elf_info->FileSize;
  CHAR8 kernel_elf_temp_buf[kernel_elf_temp_buf_size];
  stat = gBS->AllocatePool(EfiLoaderData, kernel_elf_temp_buf_size, (void **)&kernel_elf_temp_buf);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to allocated memories for the kernel file content temprarily...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to allocated memories for the kernel file content temporarily!\n");

  // Store the contents of kernel.elf in the allocated temporary buffer.
  stat = kernel_elf->Read(kernel_elf, &kernel_elf_temp_buf_size, (void *)kernel_elf_temp_buf);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to read the content of kernel.elf...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to read the content of kernel.elf!\n");

  // Check the format of kernel.elf
  // If kernel.elf is not ELF format file, display an error message and stop this program.
  Elf64_Ehdr *elf_header = (Elf64_Ehdr *)kernel_elf_temp_buf;
  elf_check(elf_header->e_ident);

  Elf64_Phdr *elf_phdr = (Elf64_Phdr *)(kernel_elf_temp_buf + elf_header->e_phoff);
  load_program(elf_phdr, elf_header->e_phnum, kernel_elf_temp_buf);

  kernel_elf->Close(kernel_elf);
  root_dir->Close(root_dir);

  // Get the address of the top of EFI_GRAPHICS_OUTPUT_PROTOCOL.
  EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
  stat = gBS->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to get the address of the top of grahics protocol.\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to get the address of the top of graphics protocol.\n");
  
  // Get the current mode and other infomations.
  // If the mode is set abnormally, set the graphic mode once more by self with GOP->SetMode().
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
  UINTN SizeOfInfo = 0;
  stat = GOP->QueryMode(GOP, (GOP->Mode==NULL ? 0 : GOP->Mode->Mode), &SizeOfInfo, &info);
  if(stat == EFI_NOT_STARTED) {
    stat = GOP->SetMode(GOP, 3);
  }
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to get the current graphic mode.\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }

  // Configure frame_buffer which is the argument of the kernel_main.
  frame_buffer_info_t frame_buffer;
  frame_buffer.horizontal_resolution = GOP->Mode->Info->HorizontalResolution;
  frame_buffer.vertical_resolution = GOP->Mode->Info->VerticalResolution;
  frame_buffer.pixel_format = GOP->Mode->Info->PixelFormat;
  frame_buffer.pixels_per_scanline = GOP->Mode->Info->PixelsPerScanLine;
  frame_buffer.frame_buffer_base = GOP->Mode->FrameBufferBase;
  frame_buffer.frame_buffer_size = GOP->Mode->FrameBufferSize;

  // Get the current memory map.
  // The memory map which is got by gBS->GetMemoryMap needs for exitting boot services.
  CHAR8 memmap_buf[4096 * 4];
  UINTN memmap_buf_size = sizeof(memmap_buf);
  UINTN descriptor_size = 0;
  UINTN map_key = 0;
  UINT32 descriptor_version = 0;
  stat = gBS->GetMemoryMap(&memmap_buf_size, (EFI_MEMORY_DESCRIPTOR *)memmap_buf, &map_key, &descriptor_size, &descriptor_version);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to get the current memmory map...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to get the current memory map!\n");

  // Exit the boot services.
  stat = gBS->ExitBootServices(ImageHandle, map_key);
  if(stat != EFI_SUCCESS) {
    memmap_buf_size = sizeof(memmap_buf);
    stat = gBS->GetMemoryMap(&memmap_buf_size, (EFI_MEMORY_DESCRIPTOR *)memmap_buf, &map_key, &descriptor_size, &descriptor_version);
    if(stat != EFI_SUCCESS) {
      Print(L"Failed to get the current memmory map...\n");
      Print(L"Status: %s\n", statcode_to_name(stat));
      while(1);
      return EFI_SUCCESS;
    }
    stat = gBS->ExitBootServices(ImageHandle, map_key);
    if(stat != EFI_SUCCESS) {
      Print(L"Failed to exit the boot services...\n");
      Print(L"Status: %s\n", statcode_to_name(stat));
      while(1);
      return EFI_SUCCESS;
    }
  }

  // Define the variable type for calling kernel's main function.
  // After that, get the address of kernel's main function and call kernel's main function.
  typedef INT32 kernel_entry_point_type_t(frame_buffer_info_t);
  kernel_entry_point_type_t *kernel_main = (kernel_entry_point_type_t *)elf_header->e_entry;
  // Print(L"Entry Point: %x\n", elf_header->e_entry);
  kernel_main(frame_buffer);

  // Print(L"Return value: 0x%x\n", ret);

  // Print(L"Success!\n");
  while(1);
  return EFI_SUCCESS;
}
