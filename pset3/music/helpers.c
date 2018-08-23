// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = atoi ( &fraction[0] );
    int y = atoi ( &fraction[2] );
    if (y == 8)
    {
        return x;
    }
    else if (y < 8)
    {
        while (y != 8)
        {
            y = y * 2;
            x = x * 2;
        }
        return x;

    }
    else
    {
        while (y != 8)
        {
            y = y / 2;
            x = x / 2;
        }
        return  x;
    }

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int octave, n;
    double semitone, letter;
    if ( strlen(note) == 2 )
    {
        octave = atoi (&note[1]);
        semitone = 0;
    }
    else
    {
        octave = atoi (&note[2]);
        if ( note[1] == '#')
        {
            semitone = 1.00 / 12.00;
        }
        else
        {
            semitone = -1.00 / 12.00;
        }

    }

    if ( octave == 4 )
    {
        n = 0;
    }
    else if ( octave < 4)
    {
        n = (-1 * ( 4 - octave));
    }
    else
    {
        n = octave - 4;

    }

    switch (note[0])
    {
        case 'C':
            letter = -9.00 / 12.00;
            break;
        case 'D':
            letter = -7.00 / 12.00;
            break;
        case 'E':
            letter = -5.00 / 12.00;
            break;
        case 'F':
            letter = -4.00 / 12.00;
            break;
        case 'G':
            letter = -2.00 / 12.00;
            break;
        case 'B':
            letter = 2.00 / 12.00;
            break;

    }
    return  round (( pow( 2, (n + semitone + letter) ) ) * 440 );
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
