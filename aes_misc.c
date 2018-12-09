#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "aes_ciph_func.h"
#include "aes_dciph_func.h"

char * cipher_text(char *plain_text, uint8_t *key, int key_size){

  int i, j, block_count;
  char *ciphered_block;
  char *ciphered_text;

  // defines the number of block of 16 chars the text contains
  block_count = (int)((strlen(plain_text)-1)/16)+1;

  ciphered_text = malloc(16*block_count*sizeof(char));

  // allocates the memory for the arry of blocks
  char **block_arr = malloc(block_count*sizeof(char *));
  for(i=0; i<block_count; i++)
    block_arr[i] = malloc(16*sizeof(char));

  //cuts down the text into blocks of 128 bits and fills the block array
  for(i=0; i<block_count; i++)
    for(j=0; j<16; j++)
      block_arr[i][j] = plain_text[16*i+j];

  for(i=0; i<block_count; i++)
  {
    ciphered_block = cipher_block(block_arr[i], key, key_size);
    for(j=0; j<16; j++)
        block_arr[i][j] = ciphered_block[j];
  }

  for(i=0; i<block_count; i++)
  {
    for(j=0; j<16; j++)
        ciphered_text[16*i+j] = block_arr[i][j];
  }

  printf("ciphered text : ");
  for(i=0; i<16*block_count; i++) printf("%c", (char)ciphered_text[i]);
  // Spacing only 1 line results in an unknown character being added to the end of the following line
  printf("\n\n");

  return ciphered_text;
}

char * decipher_text(char *ciphered_text, uint8_t *key, int key_size){

  int i, j, block_count;
  char *deciphered_block;
  char *plain_text;

  block_count = (int)((strlen(ciphered_text)-1)/16)+1;

  plain_text = malloc(16*block_count*sizeof(char));

  char **block_arr = malloc(block_count*sizeof(char *));
  for(i=0; i<block_count; i++)
    block_arr[i] = malloc(16*sizeof(char));

  for(i=0; i<block_count; i++)
    for(j=0; j<16; j++)
      block_arr[i][j] = ciphered_text[16*i+j];

  for(i=0; i<block_count; i++)
  {
    deciphered_block = decipher_block(block_arr[i], key, key_size);
    for(j=0; j<16; j++)
        block_arr[i][j] = deciphered_block[j];
  }

  for(i=0; i<block_count; i++)
  {
    for(j=0; j<16; j++)
        plain_text[16*i+j] = block_arr[i][j];
  }

  printf("plain text : ");
  for(i=0; i<16*block_count; i++) printf("%c", (char)plain_text[i]);
  printf("\n\n");

  return plain_text;
}

int cipher_file(char *file_path, uint8_t *key, int key_size){

    FILE *file;
    size_t read_char_count, wrote_char_count;

    fpos_t *pos = malloc(sizeof(fpos_t));
    char *block = malloc(16*sizeof(uint8_t));

    if ( !(file = fopen(file_path, "r+b")) ) {
      return EXIT_FAILURE;
    }

    while(!feof(file)){

      while( ( read_char_count = fread(block, 1, 16*sizeof(uint8_t), file) ) > 0 ) {
        block = cipher_block(block, key, key_size);
        fseek(file, -16, SEEK_CUR);
        wrote_char_count = fwrite(block , 1, read_char_count*sizeof(uint8_t), file);
        printf("%d\n", wrote_char_count);
        fseek(file, +16, SEEK_CUR);
      }

    }
    fclose(file);
    return EXIT_SUCCESS;
}

int decipher_file(char *file_path, uint8_t *key, int key_size){

    FILE *file;
    size_t read_char_count, wrote_char_count;

    fpos_t *pos = malloc(sizeof(fpos_t));
    uint8_t *block = malloc(16*sizeof(uint8_t));

    if ( !(file = fopen(file_path, "rb+")) ) {
      return EXIT_FAILURE;
    }

    while(!feof(file)){

      while( ( read_char_count = fread(block, 1, 16*sizeof(uint8_t), file) ) > 0 ) {
        block = decipher_block(block, key, key_size);
        fseek(file, -16, SEEK_CUR);
        wrote_char_count = fwrite(block , 1, read_char_count*sizeof(uint8_t), file);
        fseek(file, +16, SEEK_CUR);
      }

    }
    fclose(file);
    return EXIT_SUCCESS;
}
