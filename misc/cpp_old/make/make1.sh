gcc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address -Isrc -c src/*.c 
gcc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address -Isrc -c examples/main.c
gcc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address -Isrc *.o
rm *.o
./a.out $@
