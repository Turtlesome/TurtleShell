#include "pwd.h"

void print_working_directory() 
{
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("Current working directory: %s\n", cwd);
    }
    else 
    {
        perror("_getcwd() error");
    }
}
