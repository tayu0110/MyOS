#ifndef _PORTIO_H_INCLUDED_
#define _PORTIO_H_INCLUDED_

#include <stdint.h>

// Writes the data indicated by "src" to the port with the address indicated by "dest".
void out_port(uint16_t dest, uint32_t src);
// Reads 32-bit data from a port with the address indicated by "src".
uint32_t in_port(uint16_t src);

#endif