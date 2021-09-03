#ifndef _LOAD_H_INCLUDED_
#define _LOAD_H_INCLUDED_

#include <elf.h>

void load_program(Elf64_Phdr *phdr, Elf64_Half e_phnum, void *file_buf);

#endif