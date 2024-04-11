#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OPT3
#include "../include/hash_table.h"
#else
#include "../include/hash_table_opt3.h"
#endif

#define NWORDS 150000
#define NCYCLES 100

#define TABLE_SZ (1 << 18)

char **GetWords(void);
inline int64_t TimeCounter(void) __attribute__((always_inline));

int main(void)
{
    struct HashTable *table = HashTableCtr(TABLE_SZ);

    char **words = GetWords();
    for(size_t j = 0; j < NWORDS; j++)
    {
        volatile bool is_inserted = HashTableInsert(table, words[j], 0);
    }

    int64_t start = TimeCounter();
    for(size_t i = 0; i < NCYCLES; i++)
    {
        for(size_t j = 0; j < NWORDS; j++)
        {
            volatile struct HashNode *finded = HashTableFind(table, words[j]);
        }
    }
    int64_t end = TimeCounter();

    fprintf(stderr, "\n\n<time measured: %ld>\n\n", end - start);

    for(size_t i = 0; i < NWORDS; i++) free(words[i]);
    free(words);


    for(size_t i = 0; i < table->size_max; i++)
    {
        printf("%zu\n", table->data[i].size);
    }
    table = HashTableDtr(table);
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