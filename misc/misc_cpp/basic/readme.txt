Header only files 
--------------------

#ifdef NAME_IMPLEMENTATION
#ifndef NAME_HEADER_INCLUDED
#define NAME_HEADER_INCLUDED
...
#endif // NAME_HEADER_INCLUDED
#endif // NAME_IMPLEMENTATION


#define NAME_IMPLEMENTATION
#include "name.h"



String.h 
--------------

char *strchr(const char *str, int c)
void *memset(void *str, int c, size_t n)
void *memcpy(void *dest, const void * src, size_t n)



extern "C"
------------------
C code needs a linker flag to be used from within c++
e.g.

extern "C" char* c_function(char* text, int shift);



How to make stuff, shell edition
-----------------------------------

CFLAGS=$(echo "-Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -pthread -Wno-c++11-compat-deprecated-writable-strings")

# compile to object files (.o)
g++ -c $CFLAGS misc.cpp 

# make executable
g++ *.o

# # make dynamically linked standard object (.so)
# gcc -shared -lm -pthread *.o 

# # make statically linked archive object (.a)
# ar rcs lib.a *.o

rm *.o 



