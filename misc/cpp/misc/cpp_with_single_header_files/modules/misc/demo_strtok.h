#include <stdio.h>
#include <string.h>

namespace misc {


void demo_strtok(void)
{

    printf(
        "\n\nSTRTOK DEMO\n"
        "--------------------------\n"
    );

    char str[] = 
    "Return Value\n"
    "This function returns a pointer to the first token found in the string. \n"
    "A null pointer is returned if there are no tokens left to retrieve.\n"
    "\n"
    "Example\n"
    "The following example shows the usage of strtok() function.\n"
    "\n";


    // strtok uses a static for the string after it's initialized
    for (char *p = strtok(str,"\n"); p != NULL; p = strtok(NULL, "\n")){
        printf("{%s}\n", p);
    }

}

}
