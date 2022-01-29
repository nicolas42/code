// https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/dirent.h

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int bash_ls(const char *path) 
{
  struct dirent *entry;

  DIR *dir = opendir(path);
  if ( !dir ) {
    printf("ERROR %s %d couldn't open dir\n", __FILE__,__LINE__);
    return -1;
  }

  while(( entry = readdir(dir) )) printf("%s\n", entry->d_name ); // puts(entry->d_name);

  closedir(dir);

  return 0;
}


int bash_find(const char *path) 
{
    struct dirent *entry;

    DIR *dir = opendir(path);
    if ( !dir ) {
        printf("ERROR %s %d couldn't open dir\n", __FILE__,__LINE__);
        return -1;
    }

    while(( entry = readdir(dir) )) {

        if ( !strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") ) {
            continue;
        }

        printf("%s/%s\n", path, entry->d_name );

        // if ( entry->d_type == DT_REG ) { 
        //     // regular file
        // }
        if ( entry->d_type == DT_DIR ) {

            char newpath[1000];
            snprintf(newpath, 1000, "%s/%s", path, entry->d_name);
            bash_find(newpath);
        }

    }

    closedir(dir);

    return 0;
}


int main(int argc, char **argv) {

    // printf("%s", argv[1]);
    // bash_ls(argv[1]);

    bash_find(argv[1]);

  return 0;
}



// d_type
// #define DT_UNKNOWN 0
// #define DT_REG S_IFREG
// #define DT_DIR S_IFDIR
// #define DT_FIFO S_IFIFO
// #define DT_SOCK S_IFSOCK
// #define DT_CHR S_IFCHR
// #define DT_BLK S_IFBLK
// #define DT_LNK S_IFLNK

