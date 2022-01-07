#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

#include <stdio.h>

int sprintf_main(int argc, char **argv)
{
    char str[1000];
    stbsp_snprintf(str, 1000, "omg this is a string thing %f\n", 234.234);
    fputs(str,stdout);
    return 0;
}


#include <stdint.h>
#include <stdio.h>

uint8_t memory[500*1000*1000];

int main(int argc, char **argv)
{

    int i;
    for(i=0;i<500*1000*1000;i++) memory[i] = (uint8_t)(i % 99);
    printf("woo\n");
    for(i=0;i<1000*1000;++i) printf("%d ", (int)memory[i]);
    return 0;
}

