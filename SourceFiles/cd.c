#include "cd.h"

void change_directory(hashmap_char* map_char)
{
    if (map_char == NULL)
    {
        printf("Error: map_char is NULL.\n");
        return;
    }

    if (map_char->value == NULL)
    {
        printf("Error: No directory path provided.\n");
        return;
    }

    const char* path = map_char->value;

    // Check if path is a null-terminated string
    if (path[strlen(path)] != '\0')
    {
        printf("Error: Path is not a null-terminated string.\n");
        return;
    }

    int result = _chdir(path);

    if (result == 0)
    {
        print_working_directory();
    }
    else
    {
        perror("Failed to change directory");
    }
    return;
}
