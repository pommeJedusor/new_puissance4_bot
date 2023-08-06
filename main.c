#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

void main()
{
    char game_1[38] = "22525762534622441115633653436713514417";
    Grid* grid;
    grid = grid_init(game_1, 38);
    char wm = is_playing_column(grid->grid, 5);
    if (wm)
    {wm = is_winning_move(grid->grid, 6, 1);}
    printf("is_winning_move : %d\n",wm);
    /*
    Grid* grid;
    grid = malloc(sizeof(Grid));
    grid->local_deep = 0;
    grid->score = 100;
    grid->nb_children = 0;
    */
    for (int i=0;i<42;i++)
    {
        printf("%d",grid->grid[i]);
        if (i%7==6)
        {
            printf("\n");
        }
    }
}