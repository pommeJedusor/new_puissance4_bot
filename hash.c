#include <stdlib.h>
#include <stdio.h>

#include "funcs.h"

#define HASH_TABLE_SIZE 10000000


typedef struct Input Input;
struct Input
{
    long key;
    char score;
};

Input* hash_table[HASH_TABLE_SIZE];

void init_hash_table()
{
    for (long i=0;i<HASH_TABLE_SIZE;i++)
    {
        hash_table[i] = NULL;
    }
}

long get_hash(long key)
{
    key%=HASH_TABLE_SIZE;
    key*=key;
    key%=HASH_TABLE_SIZE;
    return key;
}

long get_key(long mask, long position)
{
    long key = 1;
    key = key | (key << 1);
    key = key | (key << 2);
    key = key | (key << 3);
    key += mask + position;
    return key;
}

Input* get_input(long mask, long position, char score)
{
    Input* input;
    input = malloc(sizeof(Input));
    input->score = score;
    input->key = get_key(mask, position);
    return input;
}

void make_input(long mask, long position, char score)
{
    Input* input = get_input(mask, position, score);
    long hash = get_hash(input->key);
    if (hash_table[hash]!=NULL)
    {
        free(hash_table[hash]);
    }
    hash_table[hash] = input;
}

char get_score(long mask, long position, char* alpha)
{
    long key = get_key(mask, position);
    long hash = get_hash(key);
    if (hash_table[hash]==NULL)
    {
        return 0;
    }
    if (hash_table[hash]->key == key)
    {
        *alpha = hash_table[hash]->score;
        return 1;
    }
}