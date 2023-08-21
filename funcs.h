#ifndef FUNCS_H
#define FUNCS_H

void see_pos(long mask, long position);
char can_play(long mask, char column);
void play(long* position, long* mask, char column);
char is_losing(long position, long mask);
int get_forced_move(long position, long mask);

#endif