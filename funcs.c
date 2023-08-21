#include <stdlib.h>
#include <stdio.h>


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