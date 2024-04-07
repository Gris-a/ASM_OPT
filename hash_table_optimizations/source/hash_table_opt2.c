#include <assert.h>
#include <inttypes.h>
#include <immintrin.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_table.h"

extern size_t CRC32(char *key, size_t mod);

static inline struct HashNode *HashNodeCtr(char *key, size_t val) __attribute__((always_inline));
static inline void HashNodeDtr(struct HashNode *node) __attribute__((always_inline));

static inline int StrCmp(const char *s1, const char *s2) __attribute__((always_inline));

static inline int StrCmp(const char *s1, const char *s2)
{
    return !strcmp(s1, s2);
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
        if(StrCmp(curr->key, key))
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
        if(StrCmp(curr->key, key) == 0)
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
        if(StrCmp(curr->key, key) == 0) return curr;
    }

    return NULL;
}

size_t HashTableGet(struct HashTable *table, char *key)
{
    struct HashNode *node = HashTableFind(table, key);
    return (node == NULL) ? ~0 : node->val;
}