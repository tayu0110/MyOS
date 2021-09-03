#ifndef _UTIL_H_INCLUDED_
#define _UTIL_H_INCLUDED_

#include <efi.h>
#include <efilib.h>
#include <efistdarg.h>
#include <elf.h>

UINTN AsciiSPrint(CHAR8 *Str, IN UINTN StrSize, IN CONST CHAR8 *fmt, ...);
CHAR16 *statcode_to_name(EFI_STATUS stat);
CHAR16 *elf_file_type_to_code(Elf64_Half e_type);
CHAR16 *elf_machine_type_to_code(Elf64_Half e_machine);
CHAR16 *pixel_format_to_name(EFI_GRAPHICS_PIXEL_FORMAT format);

#endif