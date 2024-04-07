#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stddef.h>

size_t HashFuncConst(char *key, size_t mod);
size_t HashFuncChar(char *key, size_t mod);
size_t HashFuncCheckSum(char *key, size_t mod);
size_t HashFuncStrLen(char *key, size_t mod);
size_t HashFuncRotL(char *key, size_t mod);
size_t HashFuncRotR(char *key, size_t mod);
size_t HashFuncCRC32(char *key, size_t mod);

#endif //HASH_FUNCTIONS_H