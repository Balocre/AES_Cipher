/*aes_const.h -- Constants declaration*/

#ifndef AES_CONST_H
#define AES_CONST_H

extern const uint8_t AES_SUB_BOX[16][16];

extern const uint8_t INV_AES_SUB_BOX[16][16];

extern const uint8_t AES_LOG_TABLE[16][16];

extern const uint8_t AES_ALOG_TABLE[16][16];

extern const uint8_t AES_MULT_MAT[4][4];

extern const uint8_t INV_AES_MULT_MAT[4][4];

extern const uint8_t RCON[10];

#endif
