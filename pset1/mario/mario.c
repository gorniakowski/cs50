//towers of mario
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 0;
    do
    {
        n = get_int("Height:");
    }
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++) //line loop
    {
        for (int j = 0; j < n - (i + 1); j++) //space printing
        {
            printf(" ");
        }

        for (int k = 0; k < i + 1; k++) //# printing
        {
            printf("#");
        }

        printf ("  ");

        for (int b = 0; b < i + 1; b++) //# printing
        {
            printf("#");
        }
        printf("\n");
    }

}
