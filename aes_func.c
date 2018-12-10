/* aes_cyph_func.h -- View aes_cipher_functions.h for detaileld informations */

#include "aes_func.h"

int sub_bytes(uint8_t *state, const uint8_t sub_box[16][16])
{
	int i;

	for(i=0; i<16; i++)
		state[i] = sub_box[state[i] >> 4][state[i] & 0x0f];

	return EXIT_SUCCESS;
}

// direction : -1 gauche, +1 droite
int shift_rows(uint32_t *state, int direction)
{
  int aa = abs(direction*16-8);
  int bb = abs(direction*16+8);

  // sate[0] stays unchanged
  state[1] = (state[1] >> aa) | (state[1] << bb);
  state[2] = (state[2] >> 16) | (state[2] << 16);
  state[3] = (state[3] >> bb) | (state[3] << aa);

	return EXIT_SUCCESS;
}

//find a way to only work on 1 column at a time
int mix_columns(uint8_t *state, const uint8_t aes_mult_mat[4][4])
{
	int i, j, k;

	uint8_t *state_buffer = calloc(16, sizeof(uint8_t));

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			for(k=0; k<4; k++)
  			state_buffer[4*j+i] ^= gf_mult(aes_mult_mat[j][k], state[4*k+i]);

	for(i=0; i<16; i++)
		state[i] = state_buffer[i];

	return EXIT_SUCCESS;
}

int add_round_key(uint8_t *state, uint32_t *extanded_key, int rnd)
{
	int i;

	for(i=0; i<4; i++)
	{
		state[i]    ^= (extanded_key[4*rnd+i] >> 24);
		state[4+i]  ^= (extanded_key[4*rnd+i] >> 16);
		state[8+i]  ^= (extanded_key[4*rnd+i] >> 8);
		state[12+i] ^= (extanded_key[4*rnd+i]);
	}

	return EXIT_SUCCESS;
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
		sub_bytes(state.by_el, AES_SUB_BOX);
		shift_rows(state.by_row, 1);
		mix_columns(state.by_el, AES_MULT_MAT);
		add_round_key(state.by_el, expanded_key, i);
	}

	i = 10;

  sub_bytes(state.by_el, AES_SUB_BOX);
  shift_rows(state.by_row, 1);
  add_round_key(state.by_el, expanded_key, i);

  // Copy state to the returned ciphered data block
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

uint8_t * decipher_block(uint8_t *block, uint8_t *key, int key_size)
{
	int i, j;

	uint32_t *expanded_key;

	State_t state;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			state.by_el[4*j+i] = block[4*i+j];

	expanded_key = key_expansion(key, key_size);

	i = 10;

	add_round_key(state.by_el, expanded_key, i);
	shift_rows(state.by_row, -1);
	sub_bytes(state.by_el, INV_AES_SUB_BOX);

	for(i=9; i>0; i--)
	{
		add_round_key(state.by_el, expanded_key, i);
		mix_columns(state.by_el, INV_AES_MULT_MAT);
		shift_rows(state.by_row, -1);
		sub_bytes(state.by_el, INV_AES_SUB_BOX);
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

	return block;
}
