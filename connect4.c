#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

void deeper(Grid* grid,char deep)
{
    if (grid->score != 100)
    {
        return;
    }
    else if (grid->local_deep < deep)
    {
        char all_child_noted;
        for (int i=0; i<grid->nb_children; i++)
        {
            printf("lance deeper récursive\n");
            printf("test: %d\n",grid->children[i].score);
            deeper(&grid->children[i], deep);
            printf("test: %d\n",grid->children[i].score);
            printf("fin deeper récursive\n");
        }
        //try to find the score of the grid
        char max_negatif = -100;
        char max = -100;
        all_child_noted = 1;
        for (int i=0; i<grid->nb_children; i++)
        {
            if (grid->children[i].score == 100)
            {
                all_child_noted = 0;
            }
            else if (grid->children[i].score > max)
            {
                max = grid->children[i].score;
            }
            if (grid->children[i].score > max_negatif && grid->children[i].score<0)
            {
                max_negatif = grid->children[i].score;
            }
        }
        if (all_child_noted==1 || max_negatif!=-100)
        {
            if (max_negatif!=-100)
            {
                grid->score = max_negatif;
            }
            else
            {
                grid->score = max;
            }
            grid->score *= -1;
            if (grid->score>0)
            {
                grid->score++;
            }
            else if (grid->score<0)
            {
                grid->score--;
            }
        }
    }
    else if (grid->local_deep == deep)
    {
        char child_number = 0;
        for (char i=0; i<7; i++)
        {
            if (is_playing_column(grid->grid, i) == 0)
            {
                continue;
            }
            else if (is_winning_move(grid->grid, i, grid->player) == 1)
            {
                printf("win!!! %d\nplayer: %d\n",i,grid->player);
                if (grid->player == 1)
                {
                    grid->score = 1;
                    for (char i=0;i<42;i++)
                    {
                        if (i%7==0)
                        {
                            printf("\n");
                        }
                        printf("%d",grid->grid[i]);
                    }
                    printf("\nlocal deep: %d, score: %d\n",grid->local_deep, grid->score);
                }
                else
                {
                    grid->score = 1;
                    for (char i=0;i<42;i++)
                    {
                        if (i%7==0)
                        {
                            printf("\n");
                        }
                        printf("%d",grid->grid[i]);
                    }
                    printf("\n");
                }
                printf("move: %d\n",i);
                grid->nb_children=0;
                return;
            }
            else
            {
                grid->nb_children++;
            }
        }
        grid->children = malloc(sizeof(Grid)*grid->nb_children);
        for (char i=0; i<7; i++)
        {
            if (is_playing_column(grid->grid, i) == 1)
            {
                //printf("lancement make_child\n");
                make_child(grid, i, &grid->children[child_number]);
                //printf("fin make_child\n");
                child_number++;
            }
        }
    }
}

int connect4(Grid* grid)
{
    //printf("score: %d\n",grid->score);
    for (int i=grid->local_deep; i<=42; i++)
    {
        //printf("lance fonction deeper ld: %d\n",i);
        printf("lance deeper: n°%d\n",i);
        deeper(grid, i);
        //printf("fin fonction deeper\n");
        //if grid solved
        if (grid->score != 100)
        {
            break;
        }
    }
    if (grid->score==100)
    {
        return 0;
    }
    return grid->score;
}