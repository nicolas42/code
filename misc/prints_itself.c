/* 
https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
*/
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main(void)
{
    FILE *file = fopen("./"__FILE__, "r");
    // uint16_t tick = UINT16_MAX;

    for (;;) {
        while (!feof(file)) {
            usleep(1e4);
            fputc(fgetc(file), stderr);
        }
        rewind(file);
    }
}

