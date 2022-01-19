
C code needs a special linker flag to be used from within c++.  It goes on the type declaration I guess?

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



