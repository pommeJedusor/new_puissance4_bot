#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

char order_change(char i)
{
    if (i==0)
    {return 3;}
    if (i==1)
    {return 4;}
    if (i==2)
    {return 2;}
    if (i==3)
    {return 5;}
    if (i==4)
    {return 1;}
    if (i==5)
    {return 0;}
    if (i==6)
    {return 6;}

}


void deeper(Grid* grid)
{
    if (is_losing(grid))
    {
        grid->score = -(22 - (grid->local_deep/2.0));
        return;
    }
    //if last move
    if (grid->local_deep==42)
    {
        grid->score = 0;
        return;
    }
    //else
    //make the move
    Grid* child;
    char column;
    char score;
    grid->score = -100;
    for (char i=0;i<7;i++)
    {
        column = order_change(i);
        if (can_play(grid, column))
        {
            child = malloc(sizeof(Grid));
            make_child(grid, column, child);
            deeper(child);
            score = -child->score;
            if (score > grid->score)
            {
                grid->score = score;
            }
            if (score >= grid->beta)
            {
                return;
            }
            if (score > grid->alpha)
            {
                grid->alpha = score;
            }
        }
    }
}

int connect4(Grid* grid)
{
    deeper(grid);
    return grid->score;
}