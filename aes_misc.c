#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aes_ciph_func.h"

int cipher_text(char *text, uint8_t *key, int key_size){

  int i, j, block_count;
  char *ciphered_block;

  block_count = (int)((strlen(text)-1)/16)+1;

  char **block_arr = malloc(block_count*sizeof(char *));
  for(i=0; i<block_count; i++)
    block_arr[i] = malloc(16*sizeof(char));

  //cutting down the text into blocks of 128 bits
  for(i=0; i<block_count; i++)
    for(j=0; j<16; j++)
      block_arr[i][j] = text[16*i+j];

  for(i=0; i<block_count; i++)
  {
    ciphered_block = cipher_block(block_arr[i], key, key_size);
    for(j=0; j<16; j++)
        block_arr[i][j] = ciphered_block[j];
  }

  for(i=0; i<block_count; i++)
  {
    for(j=0; j<16; j++)
      printf("%02x", (uint8_t)block_arr[i][j]);
  }
  printf("\n");

}
