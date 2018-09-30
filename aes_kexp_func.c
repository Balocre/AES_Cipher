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
		buffer[i] = AES_SUB_BOX[buffer[i] >> 4][buffer[i] & 0x0f];//AES_SUB_BOX is in aes_const.h

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

uint32_t * key_expansion(uint8_t *key, int key_size)
{
	//nk, nombred de mots de la clé 128 -> 4, 19 -> 6, ou 256 -> 8
	//Nr, nombre de rounds 128 -> 10 192 -> 12 256 -> 14 (6 + nk)
	//Nb, nombre de colones du state ici 4

	int i, j;
	int nk = key_size/32;
	uint32_t temp;
  uint32_t *expanded_key = malloc(4*(6+nk+1)*sizeof(uint32_t));

	//extanded_key is filled with the value of the key
	for(i=0; i<nk; i++)
	{
		expanded_key[i]  = key[4*i]   << 24;
    expanded_key[i] |= key[4*i+1] << 16;
    expanded_key[i] |= key[4*i+2] << 8;
    expanded_key[i] |= key[4*i+3];
	}

	//we extand key
	for(i=nk; i<4*(6+nk+1); i++)
	{
		temp = expanded_key[i-1];
		if(i%nk == 0)
		{
			temp = sub_word(rot_word(temp)) ^ RCON[(i/nk)-1] << 24;//RCON is in aes_const.h
		}
		else if (nk > 6 && i%nk == 4)
		{
			temp = sub_word(temp);
		}/*only for 256 bit keys*/

		expanded_key[i] = expanded_key[i-nk] ^ temp;
	}

	return expanded_key;
}
