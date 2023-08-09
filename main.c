#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "test.h"
#include "connect4.h"

void see_tree(Grid* grid)
{
    printf("profondeur %d\nscore: %d\n",grid->local_deep, grid->score);
    //show the grid
    see_grid(grid);
    for (int i=0;i<grid->nb_children;i++)
    {
        see_tree(&grid->children[i]);
    }
}

char get_move(Grid* grid)
{
    long move;
    Grid* child;
    char child_score = grid->score;
    if (child_score > 0)
    {
        child_score -=1;
        child_score *=-1;
    }
    else if (child_score < 0)
    {
        child_score +=1;
        child_score *=-1;
    }
    for (int i=0;i<grid->nb_children;i++)
    {
        //printf("child score %d\nthe other child score: %d\n",grid->children[i].score,child_score);
        if (child_score==grid->children[i].score)
        {
            move = grid->mask ^ grid->children[i].mask;
            printf("i: %d\nmove: %ld\n",i,move);
            if (move <= 64)
            {return 0;}
            if (move <= 8192)
            {return 1;}
            if (move <= 1048576)
            {return 2;}
            if (move <= 134217728)
            {return 3;}
            if (move <= 17179869184)
            {return 4;}
            if (move <= 2199023255552)
            {return 5;}
            if (move <= 281474976710656)
            {return 6;}
            return 7;
        }
    }
    return 7;
}

void main()
{
    char len_game = 26;
    char* game_1 = "46612371375417426432243354";
    Grid* grid;
    grid = grid_init(game_1, len_game);
    char result = connect4(grid);
    printf("local deep: %d\nfinal result: %d\n",grid->local_deep, result);
    //see_tree(grid);
    //printf("result: %d\nlocal deep: %d\n",result,grid->local_deep);
    printf("the move: %d\n",get_move(grid));
    
    //test_1();
}