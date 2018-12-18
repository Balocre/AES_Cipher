#ifndef AES_MISC_H
#define AES_MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/random.h>

#include "aes_func.h"

int encrypt_file(uint8_t* key, int key_size, int encryption_mode, char* filepath);

int decrypt_file(uint8_t* key, int key_size, int encryption_mode, char* filepath);

int ofb_round(uint8_t* key, int key_size, uint8_t* iv, uint8_t* data_block);

int ofb_encrypt(uint8_t* key, int key_size, char* filepath);

int ofb_decrypt(uint8_t* key, int key_size, char* filepath);

#endif
