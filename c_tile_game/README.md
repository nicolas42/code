Block game "fitz" from university
--------------------------------------

Make and run demos with GCC or Visual Studio

GCC

    gcc main.c -g -fsanitize=address,undefined -Ofast -Wall -Wpedantic -Wextra -Wno-missing-prototypes -Wno-old-style-cast
    ./a.out tilefile 1 2 10 10

Visual Studio

    "c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 
    cl main.c 
    main.exe tilefile 1 2 10 10



Read code for explanation of terminal arguments

BUG: Currently windows throws an error when reading the tilefile