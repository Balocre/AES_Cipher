#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "aes_func.h"
#include "aes_misc.h"

int main(int argc, char *argv[])
{
//----------------------------------------------------------------------------//
	// This part is just for testing purposes, if all is right, deciphered content should be equal to input string else this means the aes is badly broken

	uint8_t *output;

	uint8_t input[16] = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0X70};
	//uint8_t input[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	//uint8_t input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

	// 128 bits key
	//int key_size = 128;
  //uint8_t key[16]   = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

	// 192 bits key
	//int key_size = 192;
	//uint8_t key[24]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

	// 256 bit key
	int key_size = 256;
	uint8_t key[32]  = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

	printf("key : %s\n"
				 "key size : %d\n",
				  key, key_size);
	printf("sample input : %s\n", input);
	output = cipher_block(input, key, key_size);
	printf("ciphered     : %s\n", output);
	output = decipher_block(output, key, key_size);
	printf("deciphered   : %s\n", output);

//----------------------------------------------------------------------------//

	int opt;

	FILE* file;

	char *operation = NULL;
	char *filepath = NULL;

	enum EncryptionMode {ECB, OFB} emode;

	// Get options
	while( (opt = getopt(argc, argv, "o:m:f:")) != -1)
	{
		switch (opt) {
		case 'o' :
			operation = optarg;
			break;
		case 'm' :
			if (strcmp(optarg, "OFB") == 0) {emode = OFB; break;}
			else if (strcmp(optarg, "ECB") == 0) {emode = ECB; break;}
			break;
		case 'f':
			filepath = optarg;
			break;
		default :
			break;
		}
	}

	if (strcmp(operation, "cipher") == 0) {
		encrypt_file(key, key_size, emode, filepath);
	}
	else if (strcmp(operation, "decipher") == 0) {
		decrypt_file(key, key_size, emode, filepath);
	}
	else {
		printf("Unknow operation\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
