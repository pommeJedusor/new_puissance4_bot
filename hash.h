#ifndef HASH_H
#define HASH_H

typedef struct Input Input;
struct Input
{
    long key:32;
    char score:8;
};

void init_hash_table();
long get_hash(long key);
long get_key(long mask, long position);
Input* get_input(long mask, long position, char score);
void make_input(long mask, long position, char score);
char get_score(long mask, long position, char* alpha);

#endif