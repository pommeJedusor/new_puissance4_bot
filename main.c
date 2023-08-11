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
        see_tree(grid->children[i]);
    }
}

char get_move(Grid* grid)
{
    char column;
    for (char i=0;i<7;i++)
    {
        column = order_change(i);
        if (grid->children[column]!=NULL && grid->children[column]->score==-grid->score)
        {
            return column+1;
        }
    }
    return 10;
}

void get_moves(Grid* grid)
{
    for (char i=0;i<7;i++)
    {
        if (grid->children[i]==NULL)
        {
            printf("move: %d null\n",i);
        }
        else
        {
            printf("move: %d score: %d\n", i, grid->children[i]->score);
        }
    }
}

void main()
{
    /*char len_game = 17;
    char* game_1 = "44444432655555367";
    Grid* grid;
    grid = grid_init(game_1, len_game);
    printf("score: %d\n",connect4(grid));
    see_grid(grid);
    printf("move: %d\n",get_move(grid));
    get_moves(grid);
    /*
    char result = connect4(grid);
    printf("local deep: %d\nfinal result: %d\n",grid->local_deep, result);
    printf("the move: %d\n",get_move(grid));
    */
    test_1();
    test_3();
}