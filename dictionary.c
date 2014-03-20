/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"


int words_loaded = 0;


// global variable for start of list
node* root = NULL;

// count the words we have
int wordcounter = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* current = root;
    int i = 0;https://github.com/Erocdotusa/pset6.git
    while (word[i] != '\0')
    {
        // assembles word
        char trie = word[i];
        if (word[i] == '\'')
        {
            trie = 'z' + 1;
        }   
        // Set up for reading children elements
        int buffer = tolower(trie) - 'a';
        
        if(current->children[buffer] != NULL)
        {
            current = current->children[buffer];
            i++;
        }
        else
        {
            return false;
        }
     }
     if(current->is_word == true)
     {
        return true;
     }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    
    // open dictionary
    FILE* file = fopen(dictionary, "r");
    if ( file == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }
    
     // declare starting node
    root = malloc(sizeof(node));
    node* current = NULL;
    // variable for keeping track of children[i]     
    int c = 0;  
     

    while (fgetc(file) != EOF)
    {
        fseek(file, 1, SEEK_CUR);
        // set up cursor to point to the root of our trie
        current = root;
    
        // Iterate through trie
        for(c=fgetc(file); c != '\n'; c=fgetc(file))
        {
            if (c == '\'')
            {
                // change value of apostrophe to one past letter z
                c = 'z' + 1;
            }   
                // check if chararacter exists in trie
            if (current->children[c - 'a'] == NULL)
            {
                // if not, malloc a new node
                current->children[c - 'a'] = malloc(sizeof(node));
            
                // and then go to the node
                current = current->children[c - 'a'];
            }
            else
            {
                // If char exists, go to the node we already have
                current = current->children[c - 'a'];
            }
        }
                // reaching a '\n' char must mean we have completed loading a word
            current->is_word = true;  
            wordcounter++;
                // We move on to the next letter
            c = fgetc(file);
    }
     
    fclose(file);
    return true;     
        
   
}

 
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return wordcounter;
}

/**
 * Recursive helper function to unload
 */
bool NodeUnload(node* buffer)
{
    // free each child if not null
    for (int i = 0; i < 27; i++)
    {
        if(buffer->children[i] != NULL)
        {
            free(buffer->children[i]);
        }
    }
    free(buffer);
    return true;
} 
 
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return NodeUnload(root);
}
