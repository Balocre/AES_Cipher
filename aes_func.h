#ifndef AES_FUNC_H
#define AES_FUNC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "aes_ctypes.h"
#include "aes_const.h"
#include "aes_math.h"
#include "aes_kexp_func.h"

int sub_bytes(uint8_t *state, const uint8_t sub_box[16][16]);

int shift_rows(uint32_t *state, int direction);

int mix_columns(uint8_t *state, const uint8_t mult_mat[4][4]);

int add_round_key(uint8_t *state, uint32_t *extanded_key, int rnd);

uint8_t * cipher_block(uint8_t *block, uint8_t *key, int key_size);

uint8_t * decipher_block(uint8_t *block, uint8_t *key, int key_size);

#endif
