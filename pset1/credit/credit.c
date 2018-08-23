//This is poor implemenation
#include <stdio.h>
#include <cs50.h>

int main (void)
{
    long  every_second = 0, every = 0, leftover, every_second_sum = 0;
    long number = 0;
    int card_type = 0;
    do
    {
        number = get_long_long("Number:");
    }
    while (number <= 0);
    leftover = number;
    do                                          //this is a mess
    {
        if (leftover > 9 && leftover < 100)         //getting card type
        {
            card_type = leftover;
        }
        every = every + leftover % 10;
        leftover = (leftover - leftover % 10) / 10;
        every_second = (leftover % 10) * 2;
        if (every_second >= 10)
        {
            do
            {
                every_second_sum = every_second_sum + every_second % 10;
                every_second = (every_second - every_second % 10) / 10;
            }
            while (every_second > 0);

        }
        else
        {
            every_second_sum = every_second_sum + every_second % 10;
        }

        if (leftover > 9 && leftover < 100) //getting card type
        {
            card_type = leftover;
        }

        leftover = (leftover - leftover % 10) / 10;


    }
    while (leftover > 0);

//checking card type

    if (card_type == 34 || card_type == 37)
    {
        printf("AMEX\n");

    }
    else if (card_type >= 51 && card_type <= 55)
    {
        printf("MASTERCARD\n");

    }
    else if (card_type >= 40 && card_type <= 49)
    {
        printf ("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

