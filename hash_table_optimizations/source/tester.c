#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_table.h"

#define NWORDS 150000
#define NCYCLES 6

char **GetWords(void);
inline int64_t TimeCounter(void) __attribute__((always_inline));

int main(void)
{
    struct HashTable *table = HashTableCtr(1 << 18);
    char **words = GetWords();

    int64_t start = TimeCounter();
    for(size_t i = 0; i < NCYCLES; i++)
    {
        for(size_t j = 0; j < NWORDS; j++)
        {
            volatile bool aboba = HashTableInsert(table, words[j], 0);
        }
    }
    int64_t end = TimeCounter();

    fprintf(stderr, "\n\n<\ttime neasured: %ld>\n\n", end - start);

    for(size_t i = 0; i < NWORDS; i++)
    {
        free(words[i]);
    }
    free(words);
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
        "mov %0, rax\n\t"
        ".att_syntax prefix\n\t"
        : "=r"(result)
        :
        : "%rdx", "%rax"
    );

    return result;
}

char **GetWords(void)
{
    char **words = (char **)calloc(NWORDS, sizeof(char *));
    assert(words);

    char buf[MAX_KEY_LEN] = "";
    for(size_t i = 0; i < NWORDS; i++)
    {
        scanf("%s", buf);
        words[i] = strdup(buf);
        assert(words[i]);
    }

    return words;
}