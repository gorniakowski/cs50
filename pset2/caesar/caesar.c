#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf ("Usage: ./caesar k\n");
        return 1;
    }
    int k = atoi(argv[1]);
    string p = get_string("plaintext:  ");
    printf ("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++ ) //iterating over string
    {
        if ( isalpha(p[i]) ) //checing if character is in aphabet
        {
            if ( isupper(p[i]) ) //checking uppercase
            {

                printf("%c", 'A' + ((p[i] - 'A' + k) % 26)); /* removing ascii value to get alphabetical order
                                                                and the adding it again to dispaly in ascii*/
            }
            else
            {
                printf("%c", 'a' + ((p[i] - 'a' + k) % 26)); // as above
            }
        }
        else
        {
            printf("%c", p[i]);
        }

    }

    printf("\n");

}