/* aes_math.c - View aes_math.h for detailed informations*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aes_const.h"
#include "aes_math.h"

uint8_t gf_log(uint8_t a)
{
	a = AES_LOG_TABLE[a >> 4][a & 0x0f];

	return a;
}

uint8_t gf_alog(uint8_t a)
{
	a = AES_ALOG_TABLE[a >> 4][a & 0x0f];

	return a;
}

uint8_t gf_mult(uint8_t a, uint8_t b)
{
    if(a!=0 && b!=0) return gf_alog((gf_log(a) + gf_log(b)) % 0xff);

    else return 0x00;
}
