// cl find.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>

void find_files(const char* directory, const char* pattern, uintmax_t min_size) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    char dirToSearch[MAX_PATH];
    snprintf(dirToSearch, MAX_PATH, "%s\\*.*", directory);

    hFind = FindFirstFile(dirToSearch, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to access directory: %s\n", directory);
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
            char fullPath[MAX_PATH];
            snprintf(fullPath, MAX_PATH, "%s\\%s", directory, findData.cFileName);

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                find_files(fullPath, pattern, min_size); // Recurse into subdirectories
            } else {
                if (pattern == NULL || strstr(findData.cFileName, pattern) != NULL) {
                    LARGE_INTEGER size;
                    size.HighPart = findData.nFileSizeHigh;
                    size.LowPart = findData.nFileSizeLow;

                    if (size.QuadPart >= min_size) {
                        printf("%s\n", fullPath);
                    }
                }
            }
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory> [pattern] [min_size]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* directory = argv[1];
    const char* pattern = (argc > 2) ? argv[2] : NULL;
    uintmax_t min_size = (argc > 3) ? strtoull(argv[3], NULL, 10) : 0;

    find_files(directory, pattern, min_size);
    return 0;
}
