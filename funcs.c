#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

char* get_moves(long mask, long position)
{
    unsigned long edit_position;
    unsigned long edit_mask;
    unsigned long temp_position;
    char* moves = NULL;
    moves = malloc(sizeof(char)*7);

    for (char i=0;i<7;i++)
    {
        moves[i]=0;
        if (!can_play(mask,i))
        {
            moves[i]=-2;
            continue;
        }
        edit_position = position;
        edit_mask = mask;
        play(&edit_position, &edit_mask, i);
        edit_position ^= edit_mask;
        edit_mask = ~edit_mask;
        //delete the one outside the grid
        edit_mask <<=15;
        edit_mask >>=15;
        /*
        3 décalages comme pour trouver les lignes complêtes
        puis un décalage xor avex le mask
        */
        //vertical
        temp_position = edit_position;
        temp_position &= temp_position << 1;
        temp_position &= temp_position << 1;
        temp_position = (temp_position << 1) & edit_mask;
        //count the number of lines
        for (char j=0;temp_position;moves[i]++)
        {
            temp_position &= temp_position-1;
        }
        //horizontal
        temp_position = edit_position;
        temp_position &= temp_position << 7;
        temp_position &= temp_position << 7;
        temp_position = (temp_position << 7) & edit_mask;
        //count the number of lines
        for (char j=0;temp_position;moves[i]++)
        {
            temp_position &= temp_position-1;
        }
        //diagonal down right -> up left
        temp_position = edit_position;
        temp_position &= temp_position >> 6;
        temp_position &= temp_position >> 6;
        temp_position = (temp_position >> 6) & edit_mask;
        //count the number of lines
        for (char j=0;temp_position;moves[i]++)
        {
            temp_position &= temp_position-1;
        }
        //down left -> up right
        temp_position = edit_position;
        temp_position &= temp_position << 8;
        temp_position &= temp_position << 8;
        temp_position = (temp_position << 8) & edit_mask;
        //count the number of lines
        for (char j=0;temp_position;moves[i]++)
        {
            temp_position &= temp_position-1;
        }
    }
    return moves;
}

void see_pos(long mask, long position)
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
            if ((mask_pos & mask) == 0)
            {
                printf("0");
            }
            else if ((mask_pos & position) == 0)
            {
                copy_mask_grid = position;
                //printf("\npos: %d\nmask pos: %ld\ngridpos: %ld\n",(x*7+6-y),mask_pos,copy_mask_grid);
                copy_mask_grid = mask;
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

char can_play(long mask, char column)
{
    long top_mask = 1;
    top_mask = mask & top_mask << (column*7+5);
    return top_mask == 0;
}

void play(long* position, long* mask, char column)
{
    //update position
    *position ^= *mask;
    //update the mask
    long mask_bottom = 1;
    mask_bottom = mask_bottom << (column*7);
    *mask |= *mask + mask_bottom;
}

char is_losing(long position, long mask)
{
    position ^= mask;
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

int get_forced_move(long position, long mask)
{
   long temp_position;
   long temp_mask;
   long columns = 0;
   //check if winning moves
   for (char i=0;i<7;i++)
   {
        temp_position = position;
        temp_mask = mask;
        if (can_play(temp_mask, i))
        {
            play(&temp_position, &temp_mask, i);
            if (is_losing(temp_position, temp_mask))
            {
                columns = 1 << i;
                return columns;
            }
        }
   }
   //check loosing moves
   for (char i=0;i<7;i++)
   {
        temp_position = position ^ mask;
        temp_mask = mask;
        if (can_play(temp_mask, i))
        {
            play(&temp_position, &temp_mask, i);
            if (is_losing(temp_position, temp_mask) && columns==0)
            {
                columns = 1 << i;
            }
            else if (is_losing(temp_position, temp_mask))
            {
                return 3;
            }
        }
   }
   //return 0 if no forced move else return the forced move
   return columns;
}