#include <stdio.h>

#include "../include/hash_table.h"

int main(void)
{
    struct HashTable *table = HashTableCtr(1 << 18);

    char buf[MAX_KEY_LEN] = "";
    while(scanf("%s", buf) != EOF)
    {
        HashTableInsert(table, buf, 0);
    }

    table = HashTableDtr(table);
}