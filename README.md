# C AES Cipher

Disclaimer : I am working on this project to train myself, and it is not safe
(and probably will never be) for encryption usage and can in no way be held
accountable to damages caused by the use of this program.

Feel free to download and share the code as you please but give me credits if
you do so

There is still plenty of work to do and I will update it when I can, any
improvement suggestion (about the algorithm or my code in general), advices or
questions, are welcome, and you can contact me at this address :
antoineaudras[at]gmail[dot]com

### In short :

An encryption program built around an implementation of a FIPS-197 compliant AES
cipher

### Specifications :

Block size : 128 bits
Accepted key length : 128, 192 or 256 bits

Cipher modes : ECB and OFB

### Features

It can cipher/decipher text (or any data) of unspecified length with different
modes of encryption using 128, 192 or 256 bits keys

### Usage :

Compile all the c files (gcc -o aes \*.c)
Will make a make later <3

Options :

- o -> operation : cipher | decipher
- m -> mode : ECB | OFB
- f -> file : path to the file you want to operate on

ex : aes -o cipher -m OFB -f myfile
