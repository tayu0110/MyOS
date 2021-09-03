#ifndef _FS_H_INCLUDED_
#define _FS_H_INCLUDED_

#include <efi.h>
#include <efilib.h>

void InitializeFileSystem(EFI_SYSTEM_TABLE *SystemTable);
void OpenRootDir(EFI_FILE_PROTOCOL **root_dir);
void OpenFileReadOnly(EFI_FILE_PROTOCOL *dir, EFI_FILE_PROTOCOL **file, CHAR16 *filename);

#endif
