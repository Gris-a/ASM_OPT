#include <stdio.h>

#include "../include/hash_table.h"

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