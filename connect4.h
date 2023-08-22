#include "funcs.h"
#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

char order_change(char i);
char get_move(char* moves);
char deeper(long mask, long position, char local_deep, char alpha, char beta, char column);
int connect4(char* game, char len_game, char* best_move);

#endif