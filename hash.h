#ifndef HASH_H
#define HASH_H

typedef struct Input Input;
struct Input
{
    long key;
    char score;
};

void init_hash_table();
long get_hash(long key);
long get_key(Grid* grid);
Input* get_input(Grid* grid);
void make_input(Grid* grid);
char get_score(Grid* grid);

#endif