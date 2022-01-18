#define BASIC_IMPLEMENTATION
#include "basic.h"

#define MISC_IMPLEMENTATION
#include "misc.h"

int main(int argc, char **argv)
{

    char string[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    struct list list;
    list = split_string(string,",\n");
    for(int i=0;i<list.length;i+=1) printf("%s\n", (char*)list.data[i]);

    return 0;
}