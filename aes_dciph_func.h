#ifndef AES_DCIPH_FUNC_H
#define AES_DCIPH_FUNC_H

int inv_sub_bytes(uint8_t *state);

int inv_shift_rows(uint32_t *state);

int inv_mix_columns(uint8_t *state);

uint8_t * decipher_block(uint8_t *block, uint8_t *key, int key_size);

#endif
