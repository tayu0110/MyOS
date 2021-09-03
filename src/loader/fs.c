#include <efi.h>
#include <efilib.h>

#include "fs.h"
#include "util.h"

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;

void InitializeFileSystem(EFI_SYSTEM_TABLE *SystemTable) {
  EFI_GUID sfsp_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
  SystemTable->BootServices->LocateProtocol(&sfsp_guid, NULL, (void **)&SFSP);
}

void OpenRootDir(EFI_FILE_PROTOCOL **root_dir) {
  SFSP->OpenVolume(SFSP, root_dir);

  Print(L"Root directory opening...\n");
  if(root_dir == NULL) {
    Print(L"[Failed...] Root directory not opend\n");
    while(1);
  }
  Print(L"[Succeeded!] Root directory open\n");

  return;
}

void OpenFileReadOnly(EFI_FILE_PROTOCOL *dir, EFI_FILE_PROTOCOL **file, CHAR16 *filename) {
  Print(L"FileName: %s\n", filename);
  EFI_STATUS stat = dir->Open(dir, file, filename, EFI_FILE_MODE_READ, 0);

  Print(L"File Reading...\n");
  // If kernel.elf is found and successfully opened, EFI_FILE_PROTOCOL.Open() will return EFI_SUCCESS.
  // So, if stat is not EFI_SUCCESS, it will display a status code, indicating that the file cannot be found or opened.
  if(stat != EFI_SUCCESS) {
    Print(L"[Failed...] File not found or not opened: %s\n", filename);
    Print(L"Status: %s\n", statcode_to_name(stat));
    while(1);
  }
  Print(L"[Succeeded!] File found and opened: %s\n", filename);
}
