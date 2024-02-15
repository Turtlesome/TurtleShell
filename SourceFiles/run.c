#include "run.h"

void runApp(hashmap_char* map_char)
{
    int status = system(map_char->value);

    if (status == -1) 
    {
        printf("system() method failed\n");
    }
    else 
    {
        printf("External application executed successfully\n");
    }
}