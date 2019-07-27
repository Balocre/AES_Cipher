/* aes_kexp_func.c -- View aes_kexp_func.c for detaileld informations*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aes_const.h"
#include "aes_math.h"
#include "aes_kexp_func.h"

uint32_t sub_word(uint32_t word)
{
	int i;
	uint8_t buffer[4];

	buffer[0] =  word        & 0xff;
	buffer[1] = (word >> 8)  & 0xff;
	buffer[2] = (word >> 16) & 0xff;
	buffer[3] = (word >> 24) & 0xff;

	for(i=0; i<4; i++)
		buffer[i] = AES_SUB_BOX[buffer[i] >> 4][buffer[i] & 0x0f];/* AES_SUB_BOX is in aes_const.h */

	word  = (uint32_t) buffer[3] << 24;
	word |= (uint32_t) buffer[2] << 16;
	word |= (uint32_t) buffer[1] << 8;
	word |= (uint32_t) buffer[0];

	return word;
}

uint32_t rot_word(uint32_t word)
{
	word = (word >> 24) | (word << 8);

	return word;
}

uint32_t* key_expansion(uint8_t *key, int key_size)
{
	/* nk number of 32 bits word of the key 128 -> 4, 19 -> 6, ou 256 -> 8
	 * nr number of rounds 128 -> 10 192 -> 12 256 -> 14 (6 + nk) */

	int i, j, nk, nr;
	uint32_t w_buff, *expanded_key;
	
	nk = key_size/32;
	nr = 6+nk;
	
	expanded_key = malloc(4*(nr+1)*sizeof(uint32_t));

	/* first 32 bits word of the expanded key is initalized */
	for(i=0; i<nk; i++)
	{
		expanded_key[i]  = key[4*i]   << 24;
		expanded_key[i] |= key[4*i+1] << 16;
		expanded_key[i] |= key[4*i+2] << 8;
		expanded_key[i] |= key[4*i+3];
	}

	/* key expansion routine */
	/* TODO: check if there is an issue with endianness an RCON LSHIFT */
	for(i=nk; i<4*(nr+1); i++)
	{
		w_buff = expanded_key[i-1];
	
		if(i%nk == 0)
		{
			w_buff = sub_word(rot_word(w_buff)) ^ RCON[(i/nk)-1] << 24;
		}
		else if (nk>6 && i%nk == 4)
		{
			w_buff = sub_word(w_buff);
		}/* only executed for 256 bit keys */

		expanded_key[i] = expanded_key[i-nk]^w_buff;
	}

	return expanded_key;
}
