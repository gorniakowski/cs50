// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
#define array_size 150000
typedef struct node
{
    char word [LENGTH + 1];
    struct node *next;

} node;

node *array[array_size] = {NULL};

unsigned long hash(char *str); //prototype of a hash function djb2 algorithm http://www.cse.yorku.ca/~oz/hash.html

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char low_word[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        low_word[i] = tolower(word[i]);
    }
    low_word[strlen(word)] = '\0';
    node *cursor = array[hash(low_word)];
    while (cursor != NULL)
    {
        if (strcasecmp(low_word, cursor -> word) == 0)
        {
            return true;
        }

        cursor = cursor -> next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("could not open disctionary\n");
        return false;
    }
    char word_temp[LENGTH + 1];
    unsigned long hash_value;
    while (fscanf(dict, "%s", word_temp) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        new_node ->next = NULL;
        strcpy(new_node -> word, word_temp);
        hash_value = hash((new_node->word));
        if (array[hash_value] == NULL)
        {
            array[hash_value] = new_node;
        }
        else
        {
            new_node -> next = array[hash_value];
            array[hash_value] = new_node;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < array_size; i++)
    {

        node *cursor = array[i];
        while (cursor != NULL)
        {
            counter++;

            cursor = cursor->next;
        }


    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int counter = 0;
    node *cursor;
    for (int i = 0; i < array_size; i++)
    {
        cursor = array[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
            counter++;

        }
    }

    return true;
}

unsigned long hash(char *str) //djb2 algorithm http://www.cse.yorku.ca/~oz/hash.html
{


    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = (((hash << 5) + hash) + c) ;/* hash * 33 + c */
    }
    return hash % array_size;
}