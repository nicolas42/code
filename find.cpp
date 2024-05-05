// gcc find.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>

#define PATH_MAX 1000

void find_files(const char* directory, const char* pattern, uintmax_t min_size) {
    DIR* dir;
    struct dirent* entry;
    struct stat info;
    
    dir = opendir(directory);
    if (dir == NULL) {
        printf("%s", directory);
	perror("Error opening directory");
	return;
        // exit(EXIT_FAILURE);
    }
    
    while ((entry = readdir(dir)) != NULL) {
      char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

        if (lstat(path, &info) == -1) {
            perror("Error getting file information");
            continue;
        }

        if (S_ISREG(info.st_mode)) {
            if (pattern == NULL || strstr(entry->d_name, pattern) != NULL) {
                if ((uintmax_t)info.st_size >= min_size) {
		  if (strstr(path, pattern) != NULL){
                    printf("%s\n", path);
		  }
                }
            }
        } else if (S_ISDIR(info.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            find_files(path, pattern, min_size);
        }
    }
    
    closedir(dir);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory> [pattern] [min_size]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* directory = argv[1];
    const char* pattern = (argc > 2) ? argv[2] : "";
    uintmax_t min_size = (argc > 3) ? strtoull(argv[3], NULL, 10) : 0;

    find_files(directory, pattern, min_size);
    return 0;
}


