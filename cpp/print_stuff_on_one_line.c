#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;
    for (i=0;i<100;++i) { fprintf(stdout, "omg I'm printing stuff on one line [%d%%] \r", i ); fflush(stdout); usleep(1e5); } 
    printf("\n");
}