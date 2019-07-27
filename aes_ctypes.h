/* aes_ctypes.h -- Custom types declaratiosn*/

#ifndef AES_CTYPES_H
#define AES_CTYPES_H

#include <stdint.h>

typedef union{
	uint8_t by_el[16];
	uint32_t by_row[4];
} State_t;

#endif
