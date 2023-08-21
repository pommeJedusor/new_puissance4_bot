#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "hash.h"

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


char deeper(long mask, long position, char local_deep, char alpha, char beta, char move)
{
    //check if the deep is still worth it
    char best_possible_score = (22 - ((local_deep+1)/2.0));
    if (best_possible_score < alpha)
    {
        return -100;
    }
    if (alpha >= beta)
    {
        //printf("alpha: %d\nbeta: %d\n",alpha, beta);
        return beta;
    }
    
    play(&position, &mask, move);
    int score = -100;
    if (is_losing(position, mask))
    {
        score = -(22 - (local_deep/2.0));
        return score;
    }
    //if last move
    if (local_deep==42)
    {
        score = 0;
        return score;
    }
    //check the forced move
    int forced_move = get_forced_move(position, mask);
    if (forced_move==3)
    {
        score = -(22 - ((local_deep+2)/2.0));
        return score;
    }
    else if (forced_move!=0)
    {
        for (char i=0;i<7;i++)
        {
            if (forced_move == (1 << i))
            {
                return -deeper(mask, position, local_deep+1, -beta, -alpha, i);
            }
        }
    }
    //check the hash table
    score = -100;
    get_score(mask, position, &alpha);
    //else
    //make the move
    char column;
    int child_score;
    for (char i=0;i<7;i++)
    {
        column = order_change(i);
        if (can_play(mask, column))
        {
            child_score = -deeper(mask, position, local_deep+1, -beta, -alpha, column);
            if (child_score > score)
            {
                score = child_score;
            }
            if (child_score >= beta)
            {
                return child_score;
            }
            if (child_score > alpha)
            {
                alpha = child_score;
                make_input(mask, position, alpha);
            }
        }
    }
    return score;
}

int connect4(char* game, char len_game, char* best_move)
{
    char score = -100;
    char child_score;
    char column;
    long local_deep = len_game;
    //alpha bet
    long alpha = -100;
    long beta = 100;
    //clear the columns
    long mask = 0;
    long position = 0;
    //play the moves
    char move;
    for (char i=0; i<len_game; i++)
    {
        move = game[i]-49;
        play(&position, &mask, move);
    }
    for (char i=0;i<7;i++)
    {
        column = order_change(i);
        if (can_play(mask, column))
        {
            child_score = -deeper(mask, position, local_deep+1, -beta, -alpha, column);
            //printf("-child_score: %d\n",child_score);
            if (child_score > score)
            {
                score = child_score;
                alpha = child_score;
                *best_move = column;
            }
        }
    }
    return score;
}