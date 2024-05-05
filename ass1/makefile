# clang -Wall -Wpedantic -Wextra -Wno-missing-prototypes -Wno-old-style-cast -std=c++11 new.cpp && ./a.out

CC=gcc
CFLAGS = -Wall -Wpedantic -Wextra -Wno-missing-prototypes -Wno-old-style-cast
# Everyone!!!

all: new

clean:
	rm -f *.o new

new: new.o
	$(CC) $(CFLAGS) -o new new.o

new.o: new.cpp
	$(CC) $(CFLAGS) -c new.cpp


