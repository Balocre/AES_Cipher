#ifndef AES_MISC_H
#define AES_MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "aes_func.h"

char * cipher_text(char *plain_text, uint8_t *key, int key_size);

char * decipher_text(char *ciphered_text, uint8_t *key, int key_size);

int ecb_cipher(char *file_path, uint8_t *key, int key_size);

int ecb_decipher_file(char *file_path, uint8_t *key, int key_size);

int ofb_cipher(char *file_path, uint8_t *key, int key_size);

#endif
