#include <stdlib.h>
#include <stdio.h>

typedef struct Grid Grid;
struct Grid
{
    char* grid;
    char local_deep;
    //score=100 si indéterminé
    char score;
    char nb_children;
    char player;
    Grid* children;
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
    grid->grid = malloc(sizeof(char)*42);
    for (char i=0; i<len_game; i++)
    {
        player = (i)%2+1;
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
    //the player of a pos is the player that'll make the next move
    grid->player = (len_game)%2+1;
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
        if ( y+i < 7 && grid[pos]==player)
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
    score = 0;
    //left
    for (char i=1; i<4; i++)
    {
        pos = (y)*7+col-i;
        //check if no line change
        if ((pos+1)%7!=0 && grid[pos]==player)
        {
            score++;
        }
        else
        {
            break;
        }
    }
    //right
    for (char i=1; i<4; i++)
    {
        pos = (y)*7+col+i;
        //check if no line change
        if ((pos+1)%7!=1 && grid[pos]==player)
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
    printf("check\n");
    //diagonal
    //up left -> down right
    score = 0;
    //up left
    for (char i=1; i<4; i++)
    {
        pos = (y-i)*7+col-i;
        //check if always in the diagonal
        if ((y-i) >= 0 && (col-i) >= 0 && grid[pos]==player)
        {
            printf("up left\n");
            score++;
        }
        else
        {
            break;
        }
    }
    //down right
    for (char i=1; i<4; i++)
    {
        pos = (y+i)*7+col+i;
        //check if always in the diagonal
        if ((y+i) <= 5 && (col+i) <= 6 && grid[pos]==player)
        {
            printf("down right\n");
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
    //up right -> down left
    printf("check\n");
    score = 0;
    //up right
    for (char i=1; i<4; i++)
    {
        pos = (y-i)*7+col+i;
        //check if always in the diagonal
        if ((y-i) >= 0 && (col+i) < 7 && grid[pos]==player)
        {
            score++;
        }
        else
        {
            break;
        }
    }
    //down left
    for (char i=1; i<4; i++)
    {
        pos = (y+i)*7+col-i;
        //check if always in the diagonal
        if ((y+i) < 6 && (col-i) >= 0 && grid[pos]==player)
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

    return 0;
}

void make_child(Grid* grid, char move, Grid* child)
{
    //copy the grid
    //printf("check\n");
    child->grid = malloc(sizeof(char)*42);
    //printf("check\n");
    for (char i=0; i<42;i++)
    {
        //printf("parent: %d\n",grid->grid[i]);
        //printf("child: %d\n",child->grid[i]);
        child->grid[i]=grid->grid[i];
    }
    child->local_deep = grid->local_deep+1;
    child->score = 100;
    child->nb_children = 0;
    //get the opposite player of the parent
    child->player = grid->player%2+1;
    //make the move
    for (char i=5;i>=0;i--)
    {
        if (child->grid[i*7+move]==0)
        {
            child->grid[i*7+move]=grid->player;
            printf("move fait\n");
            break;
        }
        else
        {
            printf("case %d: %d\n",i*7+move,child->grid[i*7+move]);
        }
    }
}