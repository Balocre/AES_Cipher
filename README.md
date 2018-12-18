# C AES Cipher

Disclaimer : I am working on this project to train myself, and it is not safe
(and probably will never be) for encryption usage and I can in no way be held
accountable to damages caused by the use of this program

Feel free to download and share the code as you please but credit me if
you do so

There is still plenty of work to do and I will update it when I can, any
improvements suggestions (about the cipher or my code in general), advices or
questions, are welcome, and you can contact me at this address :
antoineaudras[at]gmail[dot]com

### In short :

A lightweight portable file encryption program for UNIX systems built around an
implementation of a FIPS-197 compliant AES cipher

### Specifications :

The AES has been implemented following the [FIPS-197](https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf)
specifications

State size : 128 bits

Accepted key length : 128, 192 or 256 bits

Available cipher modes : OFB

### Features

It can cipher/decipher any file of unspecified length (as long as you have
enough memory space available ) with different modes of encryption using 128,
192 or 256 bits keys

### Usage :

Compile all the c files (gcc -o aes \*.c)
Will make a make later <3

Options :

- o -> operation : cipher | decipher
- m -> mode : ECB | OFB
- f -> file : path to the file you want to operate on

ex : ./aes -o cipher -m OFB -f myfile
