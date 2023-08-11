#include <stdlib.h>
#include <stdio.h>

typedef struct Grid Grid;
struct Grid
{
    long position: 49;
    long mask: 49;
    char local_deep;
    //score=22 - nombre de coups joué par le joueur
    char score;
    char nb_children;
    char alpha;
    char beta;
    Grid** children;
};


char can_play(Grid* grid, char column)
{
    long top_mask = 1;
    top_mask = grid->mask & top_mask << (column*7+5);
    return top_mask == 0;
}

void play(Grid* grid, char column)
{
    //update position
    grid->position ^= grid->mask;
    //update the mask
    long mask_bottom = 1;
    mask_bottom = mask_bottom << (column*7);
    grid->mask |= grid->mask + mask_bottom;
}

void see_grid(Grid* grid)
{
    long mask_pos;
    long copy_mask_grid = 0;
    //not optimal
    for (int y=1;y<7;y++)
    {
        for (int x=0;x<7;x++)
        {
            mask_pos = 1;
            mask_pos = (mask_pos << (x*7+6-y));
            //printf("mask: %ld\npos: %d\ntent: %d\n",mask_pos,(x*7+6-y),(1 << (x*7+6-y)));
            //if case is empty
            if ((mask_pos & grid->mask) == 0)
            {
                printf("0");
            }
            else if ((mask_pos & grid->position) == 0)
            {
                copy_mask_grid = grid->position;
                //printf("\npos: %d\nmask pos: %ld\ngridpos: %ld\n",(x*7+6-y),mask_pos,copy_mask_grid);
                copy_mask_grid = grid->mask;
                //printf("gridmask: %ld\n",copy_mask_grid);
                printf("2");
            }
            else
            {
                printf("1");
            }
        }
        printf("\n");
    }
}

char is_losing(Grid* grid)
{
    grid->position ;
    long position = grid->position ^ grid->mask;
    long temp;
    //horizontal
    temp = position & (position << 7);
    if (temp & (temp << 14))
    {
        return 1;
    }
    //vertical
    temp = position & (position << 1);
    if (temp & (temp << 2))
    {
        return 1;
    }
    //diagonal up left -> down right
    temp = position & (position << 6);
    if (temp & (temp << 12))
    {
        return 1;
    }
    //diagonal down left -> up right
    temp = position & (position << 8);
    if (temp & (temp << 16))
    {
        return 1;
    }

    return 0;
}

Grid* grid_init(char* game, char len_game)
{
    Grid* grid;
    grid = malloc(sizeof(Grid));
    grid->local_deep = len_game;
    grid->nb_children = 0;
    //alpha bet
    grid->alpha = -100;
    grid->beta = 100;
    //children
    grid->children = malloc(sizeof(Grid*)*7);
    for (char i=0;i<7;i++)
    {
        grid->children[i]=NULL;
    }
    //clear the columns
    grid->mask = 0;
    grid->position = 0;
    //play the moves
    char move;
    for (char i=0; i<len_game; i++)
    {
        move = game[i]-49;
        play(grid, move);
    }
    return grid;
}

void make_child(Grid* grid, char move, Grid* child)
{
    grid->children[move] = child;
    //alpha beta
    child->alpha = -grid->beta;
    child->beta = -grid->alpha;
    //copy the grid
    child->mask = grid->mask;
    child->position = grid->position;

    child->children = malloc(sizeof(Grid*)*7);
    for (char i=0;i<7;i++)
    {
        child->children[i]=NULL;
    }

    child->local_deep = grid->local_deep+1;
    child->nb_children = 0;
    //make the move
    play(child, move);
}