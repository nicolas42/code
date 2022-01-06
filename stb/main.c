#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    char str[1000];
    stbsp_snprintf(str, 1000, "omg this is a string thing %f\n", 234.234);
    fputs(str,stdout);
    return 0;
}

