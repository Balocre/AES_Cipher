/* aes_cyph_func.h -- View aes_cipher_functions.h for detaileld informations */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aes_ctypes.h"
#include "aes_const.h"
#include "aes_math.h"
#include "aes_kexp_func.h"
#include "aes_ciph_func.h"

int sub_bytes(uint8_t *state)
{
	int i;

	for(i=0; i<16; i++)
		state[i] = AES_SUB_BOX[state[i] >> 4][state[i] & 0x0f];

	return 0;
}

int shift_rows(uint32_t *state)
{
  state[1] = (state[1] >> 8)   | (state[1] << 24 );
  state[2] = (state[2] >> 16)  | (state[2] << 16);
  state[3] = (state[3] >> 24 ) | (state[3] << 8);

	return 0;
}

//find a way to only work on 1 column at a time
int mix_columns(uint8_t *state)
{
	int i, j, k;

	uint8_t *state_buffer = calloc(16, sizeof(uint8_t));

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			for(k=0; k<4; k++)
			{
  			state_buffer[4*j+i] ^= gf_mult(AES_MULT_MAT[j][k], state[4*k+i]);
			}

	for(i=0; i<16; i++)
		state[i] = state_buffer[i];

	return 0;
}

int add_round_key(uint8_t *state, uint32_t *extanded_key, int rnd)
{
	int i;

	for(i=0; i<4; i++)
	{
		state[i]    ^= extanded_key[4*rnd+i] >> 24;
		state[4+i]  ^= extanded_key[4*rnd+i] >> 16;
		state[8+i]  ^= extanded_key[4*rnd+i] >> 8;
		state[12+i] ^= extanded_key[4*rnd+i];
	}

	return 0;
}

uint8_t * cipher_block(uint8_t *block, uint8_t *key, int key_size)
{
	int i, j;

	uint32_t *expanded_key;

	State_t state;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			state.by_el[4*j+i] = block[4*i+j];

	expanded_key = key_expansion(key, key_size);

	i=0;

	add_round_key(state.by_el, expanded_key, i);

	for(i=1; i<10; i++)
	{
		sub_bytes(state.by_el);
		shift_rows(state.by_row);
		mix_columns(state.by_el);
		add_round_key(state.by_el, expanded_key, i);
	}

	i = 10;

  sub_bytes(state.by_el);
  shift_rows(state.by_row);
  add_round_key(state.by_el, expanded_key, i);

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
			block[4*i+j] = state.by_el[4*j+i];
		}

	return block;
}
