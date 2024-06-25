# as -o hello.o hello.s
# ld -o hello -e _start hello.o


    .data
hello_message:
    .asciz "Hello, World!\n"

    .text
    .globl _start
_start:
    # write(1, message, length)
    movl $4, %eax             # system call number for sys_write
    movl $1, %ebx             # file descriptor 1 is stdout
    movl $hello_message, %ecx # pointer to the string
    movl $14, %edx            # length of the message
    int $0x80                 # make the system call

    # exit(0)
    movl $1, %eax             # system call number for sys_exit
    xorl %ebx, %ebx           # exit code 0
    int $0x80                 # make the system call

