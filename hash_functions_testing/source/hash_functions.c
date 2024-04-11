#include <inttypes.h>
#include <string.h>

#include "../include/hash_functions.h"

#define ROL64(num, shift) ((num) << shift) | ((num) >> (sizeof(uint64_t) * 8 - shift))
#define ROR64(num, shift) ((num) >> shift) | ((num) << (sizeof(uint64_t) * 8 - shift))

#define ROL32(num, shift) ((num) << shift) | ((num) >> (sizeof(uint32_t) * 8 - shift))
#define ROR32(num, shift) ((num) >> shift) | ((num) << (sizeof(uint32_t) * 8 - shift))


size_t HashFuncConst(char *key, size_t mod)
{
    return 0;
}

size_t HashFuncChar(char *key, size_t mod)
{
    return key[0] % mod;
}

size_t HashFuncCheckSum(char *key, size_t mod)
{
    size_t hash = 0;
    for(char c = *key; c != '\0'; c = *(++key))
    {
        hash += c;
        hash %= mod;
    }
    return hash % mod;
}

size_t HashFuncStrLen(char *key, size_t mod)
{
    return strlen(key) % mod;
}

size_t HashFuncRotL(char *key, size_t mod)
{
    uint64_t hash = 0;
    while(*key != '\0')
    {
        hash = ROL64(hash, 1);
        hash ^= *(key++);
    }
    return (size_t)(hash % mod);
}

size_t HashFuncRotR(char *key, size_t mod)
{
    uint64_t hash = 0;
    while(*key != '\0')
    {
        hash = ROR64(hash, 1);
        hash ^= *(key++);
    }
    return (size_t)(hash % mod);
}

size_t HashFuncCRC32(char *key, size_t mod)
{
    uint64_t crc = 0;

    size_t key_len    = strlen(key);
    size_t first_take = key_len % 4;

    for(size_t i = 0; i < first_take; i++)
    {
        crc <<= 8;
        crc |= key[i];
    }
    crc <<= 32;

    for(size_t i = first_take; i < key_len; i += 4)
    {
        crc |= (uint64_t)(*(uint32_t *)(key + i));

        for(size_t j = 0; j < 32; j++)
        {
            if(crc & ((uint64_t)1 << 63))
            {
                crc <<= 1;
                crc  ^= ((uint64_t)0x04C11DB7 << 32);
            }
            else crc <<= 1;
        }
    }

    return (size_t)((crc >> 32) % mod);
}