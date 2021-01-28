x86_64 Linux Assembly by kupala on Youtube
---------------------------------------------------------
https://www.youtube.com/watch?v=VQAKkuLL31g&list=PLetF-YjXm-sCH6FrTz4AQhfH6INDQvQSn

1. Hello World!
uname -a
Linux primary 5.4.0-62-generic #70-Ubuntu SMP Tue Jan 12 12:45:47 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux

nasm netwide assembler


nasm -f elf64 hello.asm -o hello.o
ld hello.o -o hello
./hello


db define bytes



cirosantilli.com
---------------------------------------------------------
https://cirosantilli.com/elf-hello-world#minimal-elf-file


