#include "mkdir.h"

void make_directory(hashmap_char* map_char)
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
    int result = _mkdir(path);

    if (result == 0)
    {
        printf("Successfully created directory %s\n", path);
    }
    else
    {
        perror("Failed to create directory");
    }
}
