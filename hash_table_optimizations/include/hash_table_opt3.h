#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <stddef.h>
#include <stdbool.h>

#define MAX_KEY_LEN 32

struct HashNode;
struct HashList;
struct HashTable;

struct HashNode
{
    char *key;
    size_t val;

    struct HashNode *next;
};

struct HashList
{
    size_t size;
    struct HashNode *head;
};

struct HashTable
{
    size_t size;
    size_t size_max;

    struct HashList *data;
    struct HashNode *lists;
};


struct HashTable *HashTableCtr(size_t table_sz);
struct HashTable *HashTableDtr(struct HashTable *table);


bool HashTableInsert(struct HashTable *table, char *key, size_t val);
bool HashTableDelete(struct HashTable *table, char *key);


extern struct HashNode *HashTableFind(struct HashTable *table, char *key);
size_t HashTableGet(struct HashTable *table, char *key);

#endif //HASH_TABLE_HPP