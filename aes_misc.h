#ifndef AES_MISC_H
#define AES_MISC_H

char * cipher_text(char *plain_text, uint8_t *key, int key_size);

char * decipher_text(char *ciphered_text, uint8_t *key, int key_size);

int cipher_file(char *file_path, uint8_t *key, int key_size);

int decipher_file(char *file_path, uint8_t *key, int key_size);

#endif
