#include "rmfile.h"

void removeFile(hashmap_char* map_char)
{
    char* filename = map_char->value;
    int status = remove(filename);
    if (status == 0) 
    {
        printf("File %s removed successfully\n", filename);
    }
    else {
        printf("Error: Could not remove file %s\n", filename);
    }
}
