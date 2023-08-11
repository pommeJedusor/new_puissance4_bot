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

long get_key(Grid* grid)
{
    long key = 1;
    key = key | (key << 1);
    key = key | (key << 2);
    key = key | (key << 3);
    key += grid->mask + grid->position;
    return key;
}

Input* get_input(Grid* grid)
{
    Input* input;
    input = malloc(sizeof(Input));
    input->score = grid->score;
    input->key = get_key(grid);
    return input;
}

void make_input(Grid* grid)
{
    Input* input = get_input(grid);
    long hash = get_hash(input->key);
    if (hash_table[hash]!=NULL)
    {
        free(hash_table[hash]);
    }
    hash_table[hash] = input;
}

char get_score(Grid* grid)
{
    Input* input = get_input(grid);
    long hash = get_hash(input->key);
    if (hash_table[hash]==NULL)
    {
        free(input);
        return 0;
    }
    if (hash_table[hash]->key == input->key)
    {
        grid->score = hash_table[hash]->score;
        grid->alpha = hash_table[hash]->score;
        free(input);
        return 1;
    }
    free(input);
}