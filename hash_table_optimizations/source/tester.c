#include <inttypes.h>
#include <stdio.h>

#include "../include/hash_table.h"

inline int64_t TimeCounter(void) __attribute__((always_inline));

int main(void)
{
    struct HashTable *table = HashTableCtr(1 << 18);

    char buf[MAX_KEY_LEN] = "";
    while(scanf("%s", buf) != EOF)
    {
        volatile bool aboba = HashTableInsert(table, buf, 0);
    }

    for(size_t i = 0; i < table->size_max; i++)
    {
        printf("%zu\t%zu\n", i, table->data[i].size);
    }

    table = HashTableDtr(table);
}

inline int64_t TimeCounter(void)
{
    int64_t result = 0;

    asm volatile
    (
        ".intel_syntax noprefix\n\t"
        "rdtsc\n\t"
        "shl rdx, 32\n\t"
        "add rax, rdx\n\t"
        ".att_syntax prefix\n\t"
        : "=a"(result)
        :
        : "%rdx", "%rax"
    );

    return result;
}