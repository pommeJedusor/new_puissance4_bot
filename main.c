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
    //char* game_1 = "2275634273633217117526375347415";
    char* game_1 = "444444562";
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
    //test_2();
    //test_4();
    //test_5();
    //test_6();
}