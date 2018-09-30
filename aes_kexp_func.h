/* aes_kexp_func.c -- Function prototypes declarations */

#ifndef AES_KEXP_FUNC_H
#define AES_KEXP_FUNC_H

uint32_t sub_word(uint32_t word);

uint32_t rot_word(uint32_t word);

uint32_t * key_expansion(uint8_t *key, int key_size);

#endif
