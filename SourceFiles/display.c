#include "display.h"


int isFile(const char* path)
{
    struct _stat path_stat;
    _stat(path, &path_stat);
    return (path_stat.st_mode & _S_IFREG) != 0;
}

void displayFileContents(hashmap_char* map_char)
{
    hashmap_char* current = map_char;
    int head = -1;
    int tail = -1;

    while (current->next != NULL)
    {
        if (strcmp(current->key, "h") == 0)
        {
            head = atoi(current->value);
        }
        else if (strcmp(current->key, "t") == 0)
        {
            tail = atoi(current->value);
        }
        current = current->next;
    }

    const char* fname = current->value;
    if (!isFile(fname))
    {
        printf("%s is not a file or a file does not exist.\n", fname);
        return;
    }

    FILE* file = fopen(fname, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", fname);
        return;
    }

    // Buffer to store each line of the file
    char line[1024];
    int line_number = 0;

    // Create a buffer to store the last 'tail' lines
    char** tail_lines = malloc(sizeof(char*) * tail);
    for (int i = 0; i < tail; i++)
    {
        tail_lines[i] = malloc(sizeof(char) * 1024);
    }

    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        if ((head != -1 && line_number <= head) || (tail == -1 && head == -1))
        {
            printf("%s", line);
        }
        else if (tail != -1)
        {
            // Store the line in the buffer
            strncpy_s(tail_lines[index % tail], sizeof(line), line, _TRUNCATE);
            //tail_lines[index % tail][sizeof(line) - 1] = '\0';
            index++;
        }
    }

    // Print the last 'tail' lines
    if (tail != -1)
    {
        for (int i = index; i <= index + tail; i++)
        {
            printf("%s", tail_lines[i % tail]);
        }
    }

    // Free the buffer
    for (int i = 0; i < tail; i++)
    {
        free(tail_lines[i]);
    }
    free(tail_lines);

    fclose(file);
}
