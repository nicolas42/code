#include <stdio.h>
#include <math.h>
#include <string.h>

#include "lemoda_net/run_command.h"
#include "lemoda_net/list_dir.h"
#include "lemoda_net/fetch_web_page.h"

#include "misc/hello_world.h"
#include "misc/reverse_string.h"

#include "basic.h"

#include "misc/demo_vectors.h"
#include "misc/demo_strtok.h"

#include "multivector.h"


int main(int argc, char **argv)
{
    // char *command = argv[1];

    lemoda::run_command("ls");
    lemoda::list_dir(".");

    const char *host = "www.lemoda.net";
    lemoda::fetch_webpage_main(host);

    basic::string b = basic::read_file("main.cpp");
    puts(b.data);


    misc::hello_world();
    char a[] = "Hello World!";
    misc::reverse_string(a);
    puts(a);
    misc::demo_vectors();
    misc::demo_strtok();


    multivector::main();


    return 0;
}

