#ifndef FUNCS_H
#define FUNCS_H

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
Grid* grid_init(char* game, char len_game);
char is_playing_column(char* grid, char column);
char is_winning_move(char* grid, char col, char player);
void make_child(Grid* grid, char move, Grid* child);

#endif