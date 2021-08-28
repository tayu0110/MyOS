#include <efi.h>
#include <efilib.h>
#include <elf.h>

#include "util.h"
#include "frame_buffer.h"

static CHAR16 *pixel_format_to_name(EFI_GRAPHICS_PIXEL_FORMAT format) {
  switch(format) {
    case PixelRedGreenBlueReserved8BitPerColor: return L"PixelRedGreenBlueReserved8BitPerColor";
    case PixelBlueGreenRedReserved8BitPerColor: return L"PixelBlueGreenRedReserved8BitPerColor";
    case PixelBitMask: return L"PixelBitMask";
    case PixelBltOnly: return L"PixelBltOnly";
    case PixelFormatMax: return L"PixelFormatMax";
    default: return L"Unknown format";
  }
}

EFI_STATUS
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(ImageHandle, SystemTable);
  SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
  Print(L"OS Loading...\n");
  
  // Get the address of the top of EFI_SIMPLE_FILE_SYSTEM_PROTOCOL.
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
  EFI_GUID sfsp_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
  SystemTable->BootServices->LocateProtocol(&sfsp_guid, NULL, (void **)&SFSP);

  // Open root directory.
  // If opening failed, root_dir is NULL.
  EFI_FILE_PROTOCOL *root_dir;
  SFSP->OpenVolume(SFSP, &root_dir);
  if(root_dir == NULL) {
    Print(L"Failed to open root directory...\n");
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to open root directory!\n");

  // Search kernel.elf in root directory.
  EFI_FILE_PROTOCOL *kernel_elf;
  EFI_STATUS stat = root_dir->Open(root_dir, &kernel_elf, L"\\kernel.elf", EFI_FILE_MODE_READ, 0);
  // If kernel.elf is found and successfully opened, EFI_FILE_PROTOCOL.Open() will return EFI_SUCCESS.
  // So, if stat is not EFI_SUCCESS, it will display a status code, indicating that the file cannot be found or opened.
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to open or search kernel.elf...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to find and open kernel.elf!\n");

  // Allocate a buffer to store the contents of kernel.elf.
  // Before allocating, get the size of kernel file.
  UINTN kernel_elf_info_size = 2 * sizeof(EFI_FILE_INFO);
  CHAR8 kernel_elf_info_buffer[kernel_elf_info_size];
  EFI_GUID lfp_guid = EFI_FILE_INFO_ID;
  stat = kernel_elf->GetInfo(kernel_elf, &lfp_guid, &kernel_elf_info_size, (void *)kernel_elf_info_buffer);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to get the infomation of kernel.elf...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  EFI_FILE_INFO *kernel_elf_info = (EFI_FILE_INFO *)kernel_elf_info_buffer;
  // Execute to allocate with getting file size.
  EFI_PHYSICAL_ADDRESS file_content_buf = (EFI_PHYSICAL_ADDRESS)0x100000;
  stat = gBS->AllocatePages(AllocateAddress, EfiLoaderData, (kernel_elf_info->FileSize + 0xfff) / 0x1000, &file_content_buf);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to allocated memories for the kernel file content...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
  }

  // Store the contents of kernel.elf in the allocated buffer.
  UINTN file_content_buf_size = (UINTN)kernel_elf_info->FileSize;
  stat = kernel_elf->Read(kernel_elf, &file_content_buf_size, (void *)file_content_buf);
  if(stat != EFI_SUCCESS) {
    Print(L"Failed to read the content of kernel.elf...\n");
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to read the content of kernel.elf!\n");

  // Check the format of kernel.elf
  // If kernel.elf is not ELF format file, display an error message and stop this program.
  Elf64_Ehdr *elf_header = (Elf64_Ehdr *)file_content_buf;
  const CHAR8 *elf_magic = (const CHAR8 *)"\x7f" "ELF";
  if(strncmpa(elf_header->e_ident, elf_magic, 4)) {
    Print(L"Fatal: kernel.elf is not ELF format file.\n");
    while(1);
    return EFI_SUCCESS;
  }
  Print(L"Succeeded to check file format!\n");
  Print(L"File Size: %x\n", kernel_elf_info->FileSize);
  Print(L"Machine: %s\n", elf_machine_type_to_code(elf_header->e_machine));
  Print(L"Type: %s\n", elf_file_type_to_code(elf_header->e_type));

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
  Print(L"HorizontalResolution: %d\n", frame_buffer.horizontal_resolution);
  Print(L"VerticalResolution: %d\n", frame_buffer.vertical_resolution);
  Print(L"Pixel Fromat: %s\n", pixel_format_to_name(frame_buffer.pixel_format));
  Print(L"Frame Buffer Scanline: %d\n", frame_buffer.pixels_per_scanline);
  Print(L"Frame Buffer Base: %ld\n", frame_buffer.frame_buffer_base);


  // Define the variable type for calling kernel's main function.
  // After that, get the address of kernel's main function and call kernel's main function.
  typedef INT32 kernel_entry_point_type_t(frame_buffer_info_t);
  kernel_entry_point_type_t *kernel_main = (kernel_entry_point_type_t *)elf_header->e_entry;
  Print(L"Entry Point: %x\n", elf_header->e_entry);
  INT32 ret = kernel_main(frame_buffer);

  Print(L"Return value: %x\n", ret);

  Print(L"Success!\n");
  while(1);
  return EFI_SUCCESS;
}
