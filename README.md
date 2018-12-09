# AES_Cipher

### about the project :

An implementation of the AES cipher as defined by NIST FIPS 197 that can be found here : https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf

Compile using : gcc -std=c99 -o aes.out aes_ciph_func.c aes_dciph_func.c aes_kexp_func.c aes_math.c aes_const.c main.c

Will make a make later <3

It can cipher/decipher text (or any data) of unspecified length block by block (very unsafe) as well as single blocks of 128bits using 128, 192 or 256 bits keys

The key can be changed in the main.c file, remember to specify the correct key length, you have to change key_size, 128bit key -> key_size = 128, 192bit key -> key_size = 192, 256bit key -> key_size = 256

