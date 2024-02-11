#include "mv.h"

void moveFile(hashmap_char* map_char)
{
    char src_dir[MAX_PATH];
    char dst_dir[MAX_PATH];
    const char* src = map_char->value;
    const char* dst = map_char->next->value;

    // Find the last backslash in the source path
    const char* src_last_backslash = strrchr(src, '\\');
    if (src_last_backslash == NULL)
    {
        printf("Invalid source path.\n");
        return;
    }

    // Copy the source path up to the last backslash into src_dir
    strncpy_s(src_dir, sizeof(src_dir), src, src_last_backslash - src);
    src_dir[src_last_backslash - src] = '\0';

    const char* dst_last_backslash = strrchr(dst, '\\');
    if (dst_last_backslash == NULL)
    {
        printf("Invalid destination path.\n");
        return;
    }

    strncpy_s(dst_dir, sizeof(dst_dir), dst, dst_last_backslash - dst);
    dst_dir[dst_last_backslash - dst] = '\0';

    printf("Moving %s to %s\n", src_dir, dst_dir);

    // Convert src and dst to LPCWSTR
    // Determine the size of the wide character string for src
    int src_size_w = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
    wchar_t* src_w = (wchar_t*)malloc(src_size_w * sizeof(wchar_t));
    if (src_w == NULL)
    {
        printf("Failed to allocate memory for src_w.\n");
        return;
    }
    MultiByteToWideChar(CP_UTF8, 0, src, -1, src_w, src_size_w);

    int dst_size_w = MultiByteToWideChar(CP_UTF8, 0, dst, -1, NULL, 0);
    wchar_t* dst_w = (wchar_t*)malloc(dst_size_w * sizeof(wchar_t));
    if (dst_w == NULL)
    {
        printf("Failed to allocate memory for dst_w.\n");
        return;
    }
    MultiByteToWideChar(CP_UTF8, 0, dst, -1, dst_w, dst_size_w);

    if (!MoveFile(src_w, dst_w))
    {
        printf("Error moving file: %d\n", GetLastError());
    }
    else
    {
        printf("File moved successfully.\n");
    }

    free(src_w);
    free(dst_w);
}
