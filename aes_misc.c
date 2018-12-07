#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aes_ciph_func.h"

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

  printf("ciphered text:");

  for(i=0; i<block_count; i++)
  {
    for(j=0; j<16; j++)
      // Have the printf rely on the ciĥered_text legnth instead of block count
      printf("%c", (char)ciphered_text[16*i+j]);
  }
  printf("\n");

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

  for(i=0; i<block_count; i++)
  {
    for(j=0; j<16; j++)
      printf("%c", (char)plain_text[16*i+j]);
  }
  printf("\n");

  return plain_text;
}
