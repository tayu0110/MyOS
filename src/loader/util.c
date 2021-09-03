#include <efi.h>
#include <efilib.h>
#include <efistdarg.h>
#include <elf.h>

#include "lib.h"

UINTN AsciiSPrint(CHAR8 *Str, IN UINTN StrSize, IN CONST CHAR8 *fmt, ...) {
  va_list ap;
  UINTN len;

  va_start(ap, fmt);
  AsciiVSPrint(Str, StrSize, fmt, ap);
  len = strlena(Str);
  va_end(ap);

  return len;
}

CHAR16 *statcode_to_name(EFI_STATUS stat) {
  switch(stat) {
    case EFI_SUCCESS: return L"EFI_SUCCESS";
    case EFI_ACCESS_DENIED: return L"EFI_ACCESS_DENIED";
    case EFI_BUFFER_TOO_SMALL: return L"EFI_BUFFER_TOO_SMALL";
    case EFI_DEVICE_ERROR: return L"EFI_DEVICE_ERROR";
    case EFI_INVALID_PARAMETER: return L"EFI_INVALID_PARAMETER";
    case EFI_MEDIA_CHANGED: return L"EFI_MEDIA_CHANGED";
    case EFI_NO_MEDIA: return L"EFI_NO_MEDIA";
    case EFI_NOT_FOUND: return L"EFI_NOT_FOUND";
    case EFI_OUT_OF_RESOURCES: return L"EFI_OUT_OF_RESOURCES";
    case EFI_UNSUPPORTED: return L"EFI_UNSUPPORTED";
    case EFI_VOLUME_CORRUPTED: return L"EFI_VOLUME_CORRUPTED";
    case EFI_VOLUME_FULL: return L"EFI_VOLUME_FULL";
    case EFI_WRITE_PROTECTED: return L"EFI_WRITE_PROTECTED";
    default: return L"UNKNOWN ERROR";
  }
}

CHAR16 *elf_file_type_to_code(Elf64_Half e_type) {
  switch(e_type) {
    case ET_NONE: return L"ET_NONE";      // File type not found
    case ET_REL: return L"ET_REL";        // Relocationable
    case ET_EXEC: return L"ET_EXEC";      // Executable
    case ET_DYN: return L"ET_DYN";        // Dynamic shared
    case ET_CORE: return L"ET_CORE";      // Core file
    case ET_LOPROC: return L"ET_LOPROC";
    case ET_HIPROC: return L"ET_HIPROC";
    default: return L"FATAL";
  }
}

CHAR16 *elf_machine_type_to_code(Elf64_Half e_machine) {
  switch(e_machine) {
    case EM_NONE: return L"EM_NONE";
    case EM_SPARC: return L"EM_SPARC";
    case EM_386: return L"EM_386";
    case EM_SPARC32PLUS: return L"EM_SPARC32PLUS";
    case EM_SPARCV9: return L"EM_SPARCV9";
    case EM_X86_64: return L"EM_X86_64";
    default: return L"FATAL";
  }
}

CHAR16 *pixel_format_to_name(EFI_GRAPHICS_PIXEL_FORMAT format) {
  switch(format) {
    case PixelRedGreenBlueReserved8BitPerColor: return L"PixelRedGreenBlueReserved8BitPerColor";
    case PixelBlueGreenRedReserved8BitPerColor: return L"PixelBlueGreenRedReserved8BitPerColor";
    case PixelBitMask: return L"PixelBitMask";
    case PixelBltOnly: return L"PixelBltOnly";
    case PixelFormatMax: return L"PixelFormatMax";
    default: return L"Unknown format";
  }
}
