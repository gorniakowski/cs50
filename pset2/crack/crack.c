#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (int argc, string argv[])
{
    if ( argc != 2 )
    {
        printf ("Usage ./crack hash\n");
        return 1;
    }

    string hash = argv[1];
    char key[5];
    char alphabet[52];
    for (int i = 0; i < 5; i++) //incialization of key array
    {
        key[i] = '\0';
    }
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = 65 + i;

    }
    for (int i = 0; i < 26; i++)
    {
        alphabet[i + 26] = 97 + i;
    }
//   printf("%s\n",crypt("bacdz","51"));// - you can generate your own hashes with this
    //one character password
    for (int i = 0; i < 52; i++)

    {
        key[0] = alphabet[i];
        if (strcmp(crypt(key, "51"), hash) == 0)
        {
            printf("%s\n", key);
            return 0;
        }


    }
    //two characters password
    for (int j = 0; j < 52; j++)
    {
        key[1] = alphabet[j];
        for (int i = 0; i < 52; i++)

        {
            key[0] = alphabet[i];
            if (strcmp(crypt(key, "51"), hash) == 0)
            {
                printf("%s\n", key);
                return 0;
            }


        }

    }
    //this is for 3 characters password
    for (int k = 0; k < 52; k++)
    {
        key[2] = alphabet[k];
        for (int j = 0; j < 52; j++)
        {
            key[1] = alphabet[j];
            for (int i = 0; i < 52; i++)

            {
                key[0] = alphabet[i];
                if (strcmp(crypt(key, "51"), hash) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }


            }

        }

    }
    //this is for 4 characters password
    for (int l = 0; l < 52; l++)
    {
        key[3] = alphabet[l];
        for (int k = 0; k < 52; k++)
        {
            key[2] = alphabet[k];
            for (int j = 0; j < 52; j++)
            {
                key[1] = alphabet[j];
                for (int i = 0; i < 52; i++)

                {
                    key[0] = alphabet[i];
                    if (strcmp(crypt(key, "51"), hash) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }


                }

            }

        }

    }
    //this is for 5 characters password
    for (int m = 0; m < 52; m++)
    {
        key[4] = alphabet[m];
        for (int l = 0; l < 52; l++)
        {
            key[3] = alphabet[l];
            for (int k = 0; k < 52; k++)
            {
                key[2] = alphabet[k];
                for (int j = 0; j < 52; j++)
                {
                    key[1] = alphabet[j];
                    for (int i = 0; i < 52; i++)

                    {
                        key[0] = alphabet[i];
                        if (strcmp(crypt(key, "51"), hash) == 0)
                        {
                            printf("%s\n", key);
                            return 0;
                        }


                    }

                }

            }

        }

    }
}