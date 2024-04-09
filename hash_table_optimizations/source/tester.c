#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_table.h"

#define NWORDS 150000
#define NCYCLES 100

#define TABLE_SZ (1 << 18)

char **GetWords(void);
inline int64_t TimeCounter(void) __attribute__((always_inline));

int main(void)
{
    char **words = GetWords();

    struct HashTable *table = HashTableCtr(TABLE_SZ);
    int64_t start = TimeCounter();
    for(size_t i = 0; i < NCYCLES; i++)
    {
        for(size_t j = 0; j < NWORDS; j++)
        {
            volatile bool is_inserted = HashTableInsert(table, words[j], 0);
        }
    }
    int64_t end = TimeCounter();
    table = HashTableDtr(table);


    for(size_t i = 0; i < NWORDS; i++) free(words[i]);
    free(words);

    fprintf(stderr, "\n\n<time measured: %ld>\n\n", end - start);
}

inline int64_t TimeCounter(void)
{
    int64_t result = 0;

    asm
    (
        ".intel_syntax noprefix\n\t"
        "rdtsc\n\t"
        "shl rdx, 32\n\t"
        "add rax, rdx\n\t"
        ".att_syntax prefix\n\t"
        : "=a"(result)
        :
        : "%rdx"
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
        char *temp = calloc(MAX_KEY_LEN, sizeof(char));
        assert(temp);
        strcpy(temp, buf);
        words[i] = temp;
    }

    return words;
}