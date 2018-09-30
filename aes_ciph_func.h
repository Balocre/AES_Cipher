/* aes_cypher_functions.h -- Function prototypes */

#ifndef AES_CIPH_FUNC_H
#define AES_CIPH_FUNC_H

int sub_bytes(uint8_t *state);

int shift_rows(uint32_t *state);

int mix_columns(uint8_t *state);

int add_round_key(uint8_t *state, uint32_t *extanded_key, int rnd);

uint8_t * cipher_block(uint8_t *block, uint8_t *key, int key_size);

#endif
