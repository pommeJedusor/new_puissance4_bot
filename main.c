#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcs.h"
#include "test.h"
#include "connect4.h"
#include "hash.h"


void main()
{
    
    init_hash_table();
    char* game_1 = "44444432655555";
    char move;
    int score = connect4(game_1, strlen(game_1), &move);
    printf("score: %d\nmove: %d\n", score, move);
    /*
    char result = connect4(grid);
    printf("local deep: %d\nfinal result: %d\n",grid->local_deep, result);
    printf("the move: %d\n",get_move(grid));
    */
    //test_1();
    //test_3();
}