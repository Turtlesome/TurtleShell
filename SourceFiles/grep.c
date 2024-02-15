#include "grep.h"

void grep(hashmap_char* map_char)
{
    if (map_char == NULL || map_char->value == NULL || map_char->next == NULL)
    {
        printf("At least two arguments must be present and the last argument must be a filename.\n");
        return;
    }

    hashmap_char* current = map_char;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // The last value in the linked list is the filename
    const char* fname = current->value;

    FILE* file = fopen(fname, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", fname);
        return;
    }

    // Buffer to store each line of the file
    char line[1024];
    int line_number = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        line[strcspn(line, "\n")] = 0; // Remove the newline character

        hashmap_char* current = map_char;
        while (current != NULL)
        {
            if (current->value != NULL && strstr(line, current->value) != NULL)
            {
                printf("%d: %s\n", line_number, line);
                break;
            }
            current = current->next;
        }
    }

    fclose(file);
}
