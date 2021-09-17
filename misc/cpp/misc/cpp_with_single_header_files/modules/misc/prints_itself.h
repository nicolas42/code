/* 
https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
*/
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

namespace misc {

int prints_itself(void)
{
    FILE *file = fopen("./"__FILE__, "r");
    uint16_t tick = UINT16_MAX;

    for (;;) {
        while (!feof(file)) {
            usleep(tick -= ftell(file));
            fputc(fgetc(file), stderr);
        }
        rewind(file);
    }
}

}