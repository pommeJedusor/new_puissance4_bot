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

void deeper(Grid* grid,char deep)
{
    //if already evaluated
    if (grid->score != 100)
    {
        return;
    }
    //if already have children
    else if (grid->local_deep < deep)
    {
        for (int i=0; i<grid->nb_children; i++)
        {
            deeper(&grid->children[i], deep);
        }
        //try to find the score of the grid
        char max_negatif = -100;
        char max = -100;
        char all_child_noted = 1;
        char null_atleast = 0;
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
            if (grid->children[i].score == 0)
            {
                null_atleast=1;
            }
        }
        if (all_child_noted==1 || max_negatif!=-100)
        {
            //if a child_score under 0
            if (max_negatif!=-100)
            {
                grid->score = max_negatif;
            }
            //else if a child_score == 0
            else if (null_atleast)
            {
                grid->score = 0;
            }
            else
            {
                grid->score = max;
            }
            //change the score to give to the parent
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
    //if doeasn't have any child
    else if (grid->local_deep == deep)
    {
        //if the position of the grid is losing
        if (is_losing(grid))
        {
            grid->score = -1;
            return;
        }
        //count the number of possible moves
        for (char i=0; i<7; i++)
        {
            if (can_play(grid, i))
            {
                grid->nb_children++;;
            }
        }
        //make the children of the grid
        char better_i;
        char child_number = 0;
        grid->children = malloc(sizeof(Grid)*grid->nb_children);
        for (char i=0; i<7; i++)
        {
            better_i = order_change(i);
            if (can_play(grid, better_i))
            {
                make_child(grid, better_i, &grid->children[child_number]);
                child_number++;
            }
        }
        if (child_number!=grid->nb_children)
        {
            printf("wtf\n");
        }
    }
}

int connect4(Grid* grid)
{
    for (int i=grid->local_deep; i<=42; i++)
    {
        deeper(grid, i);
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