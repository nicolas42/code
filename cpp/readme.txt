
C code needs a special linker flag to be used from within c++.  It goes on the type declaration I guess?

extern "C" char* c_function(char* text, int shift);
