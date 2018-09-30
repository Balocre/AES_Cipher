# AES_Cipher

### about the project :

An implementation of the AES cipher as defined by NIST FIPS 197 that can be found here : https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf

Compile using : gcc -std=c99 -o aes.out aes_ciph_func.c aes_kexp_func.c aes_math.c aes_const.c main.c

The key and the inpu can be changed in the main.c file, if you decide to use a key longer than 128 bit, you have to change nk, 128bit key -> nk = 4, 192bit key -> nk = 6, 256bit key -> nk = 8

This implementation can only encrypt 128 bit at a time for now

### about the files :

- main.c

the main loop and the variables

- aes_ciph_func.c 

the encryption functions

- aes_kexp_func.c

the key expansion routine functions

- aes_math.c

the math operations on gf(2^8) (multiplication, log and exp)

- aes_const

the constants needed for the math operations and the key expansion routine

all the header files only contains the function prototypes of the corresponding modules, think about modifying them if you modify the functions
