/*
 * aes_misc.c
 *
 * This file contains the implementations of the files used for the encryption
 * process
 */

#include "aes_misc.h"

int encrypt_file(uint8_t* key, int key_size, int encryption_mode, char* filepath) {

  switch (encryption_mode) {
    case 0 /*ECB*/:
      printf("Not implemented yet\n");
      break;
    case 1 /*OFB*/:
      ofb_encrypt(key, key_size, filepath);
      break;
    default:
      printf("Please specify an encryption mode\n");
      break;
  }

  return EXIT_SUCCESS;
}

int decrypt_file(uint8_t* key, int key_size, int encryption_mode, char* filepath) {

  FILE* file;

  file = fopen(filepath, "rb");

  switch (encryption_mode) {
    case 0 /*ECB*/:
      printf("Not implemented yet\n");
      break;
    case 1 /*OFB*/:
      ofb_decrypt(key, key_size, filepath);
      break;
    default:
      printf("Please specify a decryption mode\n");
      break;
  }

  fclose(file);

  return EXIT_SUCCESS;
}

int ofb_round(uint8_t* key, int key_size, uint8_t* iv, uint8_t* data_block) {
  int i;
  cipher_block(iv, key, key_size);
  for (i=0; i<16; i++) data_block[i] ^= iv[i];
}

int ofb_encrypt(uint8_t* key, int key_size, char* filepath) {

  int rcc, p;
  uint8_t *data_block, *iv;
  FILE *file, *wfile;

  /* TODO: add safety checks */
  file = fopen(filepath, "rb");
  wfile = fopen(".wfile", "wb+");

  iv = malloc(16*sizeof(uint8_t));
  data_block = malloc(16*sizeof(uint8_t));

  getrandom(iv, 16, 0);

  /* Write the header */
  fwrite(iv, (size_t)1, (size_t)16, wfile);

  while ( (rcc = fread(data_block, (size_t)1, (size_t)16, file)) == 16) {
    ofb_round(key, key_size, iv, data_block);
    fwrite(data_block, (size_t)1, (size_t)16, wfile);
  }

  /* add PKCS#7 compliant padding to the last data block */
  if (rcc != 0) {
    p = 16-rcc;
    memset(data_block+rcc, p, p);
    ofb_round(key, key_size, iv, data_block);
    fwrite(data_block, (size_t)1, (size_t)16, wfile);
  }
  else {
    memset(data_block, 16, 16);
    ofb_round(key, key_size, iv, data_block);
    fwrite(data_block, (size_t)1, (size_t)16, wfile);
  }

  /* Replace the unencrypted file with its encrypted counterpart */
  fclose(file);
  remove(filepath);
  fclose(wfile);
  rename(".wfile", filepath);

  return EXIT_SUCCESS;
}

int ofb_decrypt(uint8_t* key, int key_size, char* filepath) {

  int rcc, p;
  uint8_t *data_block, *iv;
  FILE *file, *wfile;
  fpos_t* position;

  file = fopen(filepath, "rb");
  wfile = fopen(".wfile", "wb+");

  iv = malloc(16*sizeof(uint8_t));
  data_block = malloc(16*sizeof(uint8_t));
  position = malloc(sizeof(fpos_t));

  getrandom(iv, 16, 0);

  /* Read the header and assign the IV value */
  fread(iv, (size_t)1, (size_t)16, file);

  while ( (rcc = fread(data_block, (size_t)1, (size_t)16, file)) == 16) {
    ofb_round(key, key_size, iv, data_block);

    /* If next byte is EOF break */
    fgetpos(file, position);
    getc(file);
    if ( feof(file) ) break;
    fsetpos(file, position);

    fwrite(data_block, (size_t)1, (size_t)16, wfile);
  }

  /* Write the block minus the padding */
  p = 16 - data_block[15];
  fwrite(data_block, (size_t)1, (size_t)p, wfile);

  fclose(file);
  remove(filepath);
  fclose(wfile);
  rename(".wfile", filepath);

  return EXIT_SUCCESS;
}
