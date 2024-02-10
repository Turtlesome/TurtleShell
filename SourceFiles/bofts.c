#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bofts.h"

#define BUFSIZE 1024


char* turtleReadLine(void)
{
    int bufsize = BUFSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char) * bufsize);

    if (!buffer)
    {
        fprintf(stderr, "turtleReadLine: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        int c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position++] = c;

        if (position >= bufsize)
        {
            bufsize += BUFSIZE;
            char* temp = realloc(buffer, bufsize);
            if (!temp)
            {
                fprintf(stderr, "turtleReadLine: reallocation error\n");
                free(buffer);
                exit(EXIT_FAILURE);
            }
            buffer = temp;
        }
    }
}

char* getCommand(const char* command_line)
{
    // Assign first occurence of space
    const char* end = strchr(command_line, ' ');

    // If space was found
    if (end)
    {
        // Subtracting addresses
        size_t first_word_len = end - command_line;
        // Allocate memory for a new string that will hold the first word
        char* first_word = (char*)malloc(first_word_len + 1);

        if (first_word == NULL)
        {
            return NULL;
        }

        strncpy_s(first_word, first_word_len + 1, command_line, first_word_len);
        first_word[first_word_len] = '\0';
        return first_word;
    }
    else
    {
        return _strdup(command_line);
    }
}


hashmap_char* parseCommandLine(char* command_line)
{
    char* token;
    char* next_token = NULL;
    hashmap_char* head = NULL;
    hashmap_char* current = NULL;
    int isFirstArg = 1;

    // Get first token which is the command
    token = strtok_s(command_line, " ", &next_token);
    while (token != NULL)
    {
        if (token[0] == '-')
        {
            // For options to get a from -a and b from -ab, etc.
            for (int i = 1; i < strlen(token); i++)
            {
                hashmap_char* map_char = malloc(sizeof(hashmap_char));
                if (map_char == NULL)
                {
                    printf("Error: malloc failed\n");
                    return NULL;
                }

                char key[2] = { token[i], '\0' };
                map_char->key = _strdup(key);
                map_char->value = NULL;
                map_char->next = NULL;

                if (head == NULL)
                {
                    head = map_char;
                    current = map_char;
                }
                else
                {
                    current->next = map_char;
                    current = map_char;
                }
            }
        }
        else
        {
            // If it's the first argument after the command, skip it
            if (isFirstArg)
            {
                isFirstArg = 0;
            }
            else
            {
                // If there is no current option, create a new one with an empty key
                if (current == NULL || current->value != NULL)
                {
                    hashmap_char* map_char = malloc(sizeof(hashmap_char));
                    if (map_char == NULL)
                    {
                        printf("Error: malloc failed\n");
                        return NULL;
                    }

                    map_char->key = _strdup("");
                    map_char->value = _strdup(token);
                    map_char->next = NULL;

                    if (head == NULL)
                    {
                        head = map_char;
                    }
                    else
                    {
                        current->next = map_char;
                    }
                    current = map_char;
                }
                else
                {
                    // Assign the argument to the value of the last option
                    current->value = _strdup(token);
                }
            }
        }

        // Get the next token
        token = strtok_s(NULL, " ", &next_token);
    }
    return head;
}

