#include "ls.h"


void listFiles(hashmap_char* map_char)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    int showHiddenFiles = 0;
    hashmap_char* current = map_char;
    while (current != NULL) {
        if (strcmp(current->key, "a") == 0) {
            showHiddenFiles = 1;
        }
        else {
            printf("Wrong option for ls command: %s\n", current->key);
        }
        current = current->next;
    }

    // Find the first file in the directory.
    hFind = FindFirstFile(TEXT(".\\*"), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("FindFirstFile failed (%d)\n", GetLastError());
        return;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (showHiddenFiles || findFileData.cFileName[0] != '.')
            {
                _tprintf(TEXT("  %s   <DIR>\n"), findFileData.cFileName);
            }
        }
        else {
            if (showHiddenFiles || findFileData.cFileName[0] != '.')
            {
                _tprintf(TEXT("  %s\n"), findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
