#include "mkfile.h"

void makeFile(hashmap_char* map_char)
{   
    char* filename = map_char->value;
    FILE* file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    fclose(file);
    printf("File %s created successfully\n", filename);
}
