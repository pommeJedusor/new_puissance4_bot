#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "test.h"
#include "connect4.h"

void see_tree(Grid* grid)
{
    printf("profondeur %d\nscore: %d\n",grid->local_deep, grid->score);
    for (char i=0;i<42;i++)
    {
        if (i%7==0)
        {
            printf("\n");
        }
        printf("%d",grid->grid[i]);
    }
    printf("\n");
    for (int i=0;i<grid->nb_children;i++)
    {
        see_tree(&grid->children[i]);
    }
}

void main()
{
    char len_game = 6;
    char* game_1 = "444444";
    Grid* grid;
    grid = grid_init(game_1, len_game);
    printf("player: %d\n",grid->player);
    printf("gagnant: %d\n",is_winning_move(grid->grid, 6 , grid->player));
    char result = connect4(grid);
    printf("local deep: %d\nfinal result: %d\n",grid->local_deep, result);
    see_tree(grid);
    printf("result: %d\nlocal deep: %d\n",result,grid->local_deep);
    
    //test_1();
}