#include <stdlib.h>
#include <stdio.h>

typedef struct Grid Grid;
struct Grid
{
    char grid[42];
    char nb_moves;
    char local_deep;
    //score=100 si indéterminé
    char score;
    char nb_children;
    char player;
    Grid** children;
};

// equation position y*7+x

Grid* grid_init(char* game, char len_game)
{
    char player;
    Grid* grid;
    grid = malloc(sizeof(Grid));
    grid->local_deep = len_game;
    grid->score = 100;
    grid->nb_children = 0;
    char y=0;
    char x=0;
    //feed the grid
    for (char i=0; i<len_game; i++)
    {
        player = (i+1)%2+1;
        x = game[i]-49;
        for (char y=5;y>=0;y--)
        {
            if (grid->grid[y*7+x]==0)
            {
                grid->grid[y*7+x]=player;
                break;
            }
        }
    }
    grid->player = (len_game+1)%2+1;
    return grid;
}

char is_playing_column(char* grid, char column)
{
    if (grid[column]==0)
    {
        return 1;
    }
    return 0;
}

char is_winning_move(char* grid, char col, char player)
{
    char y;
    char score = 0;
    char pos;
    for (char i=5; i>=0; i--)
    {
        if (grid[i*7+col]==0)
        {
            y = i;
            break;
        }
    }
    //down
    for (char i=1; i<4; i++)
    {
        pos = (y+i)*7+col;
        if (pos < 42 && grid[pos]==player)
        {
            score++;
        }
        else 
        {
            break;
        }
    }
    if (score>=3)
    {
        return 1;
    }
    //horizontal
    //left

    return 0;
}