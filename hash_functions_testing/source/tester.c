#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash_table.h"
#include "../include/hash_functions.h"

int main(int argc, char **argv)
{
    size_t (*Func)(char *, size_t) = NULL;

    if((argc != 3) || argv[1][1] != '\0') abort();

    switch(argv[1][0])
    {
        case '1':
            Func = HashFuncConst;
            break;
        case '2':
            Func = HashFuncChar;
            break;
        case '3':
            Func = HashFuncStrLen;
            break;
        case '4':
            Func = HashFuncCheckSum;
            break;
        case '5':
            Func = HashFuncRotL;
            break;
        case '6':
            Func = HashFuncRotR;
            break;
        case '7':
            Func = HashFuncCRC32;
            break;
        default: abort();
    }

    size_t table_sz = 0;
    if(strcmp(argv[2], "small") == 0)    table_sz = 1 << 9;
    else if(strcmp(argv[2], "big") == 0) table_sz = 1 << 16;
    else abort();

    struct HashTable *table = HashTableCtr(Func, table_sz);

    char buf[MAX_KEY_LEN] = "";
    while(scanf("%s", buf) != EOF)
    {
        HashTableInsert(table, buf, 0);
    }

    for(size_t i = 0; i < table->size_max; i++)
    {
        printf("%zu\t%zu\n", i, table->data[i].size);
    }

    table = HashTableDtr(table);
}