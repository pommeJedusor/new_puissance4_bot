#ifndef FUNCS_H
#define FUNCS_H

char can_play(long mask, char column);
void play(long* position, long* mask, char column);
char is_losing(long position, long mask);

#endif