#include <stdio.h>
#include <stdlib.h>

#include "bofts.h"
#include "Hashmap.h"
#include "Tree.h"
#include "pwd.h"
#include "cd.h"
#include "mkdir.h"
#include "rmdir.h"
#include "mkfile.h"
#include "rmfile.h"
#include "ls.h"
#include "cp.h"
#include "mv.h"

int main()
{
    char* command_line;
    char* command;
    int status = 1;

    Node* root = NULL;
    char* map_commands[] = { "pwd", "cd", "mkdir", "rmdir", "mkfile", "rmfile", "ls", "cp", "mv"};
    void (*commands_functions[])(hashmap_char*) = { print_working_directory, change_directory, make_directory, remove_directory, makeFile, removeFile, listFiles, copyFile, moveFile};

    for (int i = 0; i < sizeof(map_commands) / sizeof(map_commands[0]); i++)
    {
        root = insert(root, map_commands[i], commands_functions[i]);
    }

    do {
        printf("TurtleShell> ");
        command_line = turtleReadLine();
        command = getCommand(command_line);
        hashmap_char* map_char = parseCommandLine(command_line);

        //printf("%s\n", command);
        // printHashMap(map_char);

        Node* command_node = search(root, command);
        if (command_node != NULL)
        {
            command_node->command_function(map_char);
        }
        else if (strcmp(command, "exit") == 0)
        {
            status = 0;
        }
        else
        {
            printf("Command not found\n");
        }

        free(command_line);
        free_hashmap(map_char);

    } while (status);

    return 0;
}

