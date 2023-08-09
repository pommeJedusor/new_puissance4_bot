#ifndef FUNCS_H
#define FUNCS_H

typedef struct Grid Grid;
struct Grid
{
    long position: 49;
    long mask: 49;
    char local_deep;
    //score=100 si indéterminé
    char score;
    char nb_children;
    Grid* children;
};

char can_play(Grid* grid, char column);
void play(Grid* grid, char column);
void see_grid(Grid* grid);
char is_losing(Grid* grid);
Grid* grid_init(char* game, char len_game);
void make_child(Grid* grid, char move, Grid* child);

#endif