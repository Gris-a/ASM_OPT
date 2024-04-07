#include <assert.h>
#include <inttypes.h>
#include <immintrin.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_table.h"

static inline size_t CRC32(char *key, uint64_t mod);

static inline struct HashNode *HashNodeCtr(char *key, size_t val);
static inline void HashNodeDtr(struct HashNode *node);


static inline size_t CRC32(char *key, uint64_t mod)
{
    uint64_t crc = 0;

    size_t key_len    = strlen(key);
    size_t first_take = key_len & 3; // key_len % 4

    for(size_t i = 0; i < first_take; i++)
    {
        crc <<= 8;
        crc |= key[i];
    }
    crc <<= 32;

    uint32_t *word_ptr = (uint32_t *)(key + first_take);
    for(size_t i = first_take; i < key_len; i += 4, word_ptr++)
    {
        crc |= (uint64_t)*word_ptr;

        for(size_t j = 0; j < 32; j++)
        {
            bool xor_cond = crc & ((uint64_t)1 << 63);
            crc <<= 1;
            if(xor_cond) crc ^= ((uint64_t)0x04C11DB7 << 32);
        }
    }

    return (size_t)((crc >> 32) & (mod - 1));
}


static inline struct HashNode *HashNodeCtr(char *key, size_t val)
{
    struct HashNode *node = (struct HashNode *)malloc(sizeof(struct HashNode));
    assert(node);

    char *key_cpy = strdup(key);
    assert(key_cpy);

    node->key  = key_cpy;
    node->val  = val;
    node->next = NULL;

    return node;
}

static inline void HashNodeDtr(struct HashNode *node)
{
    free(node->key);
    free(node);
}


struct HashTable *HashTableCtr(size_t table_sz)
{
    struct HashTable *table = (struct HashTable *)malloc(sizeof(struct HashTable));
    assert(table);

    struct HashList *data = (struct HashList *)calloc(table_sz, sizeof(struct HashList));
    assert(data);
    table->data = data;

    struct HashNode *lists = (struct HashNode *)calloc(table_sz, sizeof(struct HashNode));
    assert(lists);
    table->lists = lists;

    for(size_t i = 0; i < table_sz; i++) (data++)->head = lists++;

    table->size     = 0;
    table->size_max = table_sz;

    return table;
}

struct HashTable *HashTableDtr(struct HashTable *table)
{
    size_t n_lists = table->size_max;
    struct HashNode *lists = table->lists;

    for(size_t i = 0; i < n_lists; i++)
    {
        struct HashNode *curr = (lists++)->next;
        while(curr != NULL)
        {
            struct HashNode *next = curr->next;
            HashNodeDtr(curr);
            curr = next;
        }
    }

    free(table->data);
    free(table->lists);

    free(table);
    return NULL;
}


bool HashTableInsert(struct HashTable *table, char *key, size_t val)
{
    size_t hash = CRC32(key, table->size_max);
    struct HashList *lst = table->data + hash;

    struct HashNode *prev = lst->head;
    for(struct HashNode *curr = prev->next; curr != NULL; prev = curr, curr = curr->next)
    {
        if(strcmp(curr->key, key) == 0)
        {
            curr->val = val;
            return false;
        }
    }
    prev->next = HashNodeCtr(key, val);

    lst->size++;
    table->size++;

    return true;
}

bool HashTableDelete(struct HashTable *table, char *key)
{
    size_t hash = CRC32(key, table->size_max);
    struct HashList *lst = table->data + hash;

    if(lst->size == 0) return false;

    for(struct HashNode *prev = lst->head, *curr = prev->next; curr != NULL; prev = curr, curr = curr->next)
    {
        if(strcmp(curr->key, key) == 0)
        {
            prev->next = curr->next;
            HashNodeDtr(curr);

            lst->size--;
            table->size--;

            return true;
        }
    }

    return false;
}


struct HashNode *HashTableFind(struct HashTable *table, char *key)
{
    size_t hash = CRC32(key, table->size_max);
    struct HashList *lst = table->data + hash;

    for(struct HashNode *curr = lst->head->next; curr != NULL; curr = curr->next)
    {
        if(strcmp(curr->key, key) == 0) return curr;
    }

    return NULL;
}

size_t HashTableGet(struct HashTable *table, char *key)
{
    struct HashNode *node = HashTableFind(table, key);
    return (node == NULL) ? ~0 : node->val;
}

