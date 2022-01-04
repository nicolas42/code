# echo $0

CFLAGS=$(echo "-Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC -pthread -Wno-c++11-compat-deprecated-writable-strings")

# compile to object files (.o)
g++ -c $CFLAGS misc.cpp main.cpp


# make executable
g++ *.o

# # make dynamically linked standard object (.so)
# gcc -shared -lm -pthread *.o 

# # make statically linked archive object (.a)
# ar rcs lib.a *.o

rm *.o 



