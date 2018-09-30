/* aes_cyph_func.h -- View aes_cipher_functions.h for detaileld informations */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aes_ctypes.h"
#include "aes_const.h"
#include "aes_math.h"
#include "aes_kexp_func.h"
#include "aes_ciph_func.h"
#include "aes_dciph_func.h"

int inv_sub_bytes(uint8_t *state)
{
	int i;

	for(i=0; i<16; i++)
		state[i] = INV_AES_SUB_BOX[state[i] >> 4][state[i] & 0x0f];

	return 0;
}

int inv_shift_rows(uint32_t *state)
{
  state[1] = (state[1] << 8)   | (state[1] >> 24);
  state[2] = (state[2] << 16)  | (state[2] >> 16);
  state[3] = (state[3] << 24 ) | (state[3] >> 8);

	return 0;
}

//find a way to only work on 1 column at a time
int inv_mix_columns(uint8_t *state)
{
	int i, j, k;

	uint8_t *state_buffer = calloc(16, sizeof(uint8_t));

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			for(k=0; k<4; k++)
			{
  			state_buffer[4*j+i] ^= gf_mult(INV_AES_MULT_MAT[j][k], state[4*k+i]);
			}

	for(i=0; i<16; i++)
		state[i] = state_buffer[i];

	return 0;
}

uint8_t * decipher_block(uint8_t *block, uint8_t *key, int key_size)
{
	int i, j;

	uint32_t *expanded_key;

	State_t state;

	printf("input block : ");
	for(j=0; j<16; j++)
		printf("%x", block[j]);
	printf("\n");


	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			state.by_el[4*j+i] = block[4*i+j];

	expanded_key = key_expansion(key, key_size);

	i = 10;

	add_round_key(state.by_el, expanded_key, i);
	inv_shift_rows(state.by_row);
	inv_sub_bytes(state.by_el);

	for(i=9; i>0; i--)
	{
		add_round_key(state.by_el, expanded_key, i);
		inv_mix_columns(state.by_el);
		inv_shift_rows(state.by_row);
		inv_sub_bytes(state.by_el);
	}

	i=0;

	add_round_key(state.by_el, expanded_key, i);

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
		}

	printf("output block : ");
	for(j=0; j<16; j++)
		printf("%x", block[j]);
	printf("\n");

	return block;
}
