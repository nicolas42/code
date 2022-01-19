Read disk sectors into memory 
-------------------------------------
Load past the first 512 bytes in our file.

Cylinder head sector addressing 

bios interrupt 13  ah2, ah3 
ah2 read into memory 
ah3 write 

Interrupts https://stanislavs.org/helppc/int_table.html


Spinning Disk 
https://en.wikipedia.org/wiki/Cylinder-head-sector

A (original) floppy disk has two sides, each with 40 cylinders or tracks, 
and each track has 9 sectors (start from 1) like pie slices, which each have 512 bytes.

2*40*9*512 = 360KB

platter (disk)
several thousand tracks 
hard drive heads 

cylinder (several tracks)

https://www.youtube.com/watch?v=gd5vKobmZ3Q

;  reading sectors with a CHS address  
; https://wiki.osdev.org/Disk_access_using_the_BIOS_(INT_13h)



Pixel OS
--------------

Aim: Boot directly to an arbitrary high resolution graphical program, written in c, with dynamic memory allocation.


tired amateur 
https://www.youtube.com/watch?v=5FnrtmJXsdM&list=PLT7NbkyNWaqajsw8Xh7SP9KJwjfpP8TNX&index=1
https://git.sr.ht/~queso_fuego/amateur_os_video_sources/tree/master

https://wiki.osdev.org
https://flatassembler.net
https://github.com/arjun024/mkernel



Mac OS 10.12 
-----------------
I'm using mac os 10.12 because I hate myself.  

QEMU

An old version of qemu has to be compiled.  I chose 2.9.1 because it was released a year 
after this operating system.  

It's available here
https://github.com/qemu/qemu/tree/359c41abe32638adad503e386969fa428cecff52

The program we're interested in will be output to a directory like this
qemu-2.9.1/i386-softmmu/qemu-system-i386

A raw hard drive image binary can be booted with this kind of command.

qemu-system-i386 -drive format=raw,file=OS.bin,if=ide,index=0,media=disk


I modified qemu so it doesn't ask for confirmation on exit by changing the verifyQuit function to this.

- (BOOL)verifyQuit
{
    return YES;
}


GCC and NASM 

The code that uses nasm and gcc needs to use the linux versions of gcc and ld, 
which can be installed using macports (brew doesn't work on old macos).

sudo port install i386-elf-gcc

So just replace gcc and ld with their elf equivalents and the code should work.

gcc => i386-elf-gcc
ld => i386-elf-ld


---------------------------------------------------------
Old Notes on Assembly and Booting 
---------------------------------------------------------

Booting
-------------------
source: wiki.osdev.org/Boot_Sequence

To boot from a drive, bytes 510 and 511 in sector 0 should be 10101010 01010101 .
So the first 512 bytes should look like this [ ... aa 55 ]

This code will boot.

here:
jmp here
times 510-($-$$) db 0
dw 0xaa55

The line "times 510-($-$$) db 0" pads the program with zeros until the 510th byte.
$ = value of current offset
$$ = base address of current addressing space


The boot sector is loaded into memory segment 0 at address 0x7c00.  




org directive 
-------------------------
Reaching a org directive, FASM will assembly addresses from that place on taking the new origin as base. It will not physically put padding.

org 0x7c00

This directive tells the assembler that addresses should be calculated as if the 
beginning of the file has been loaded into memory address 0x7c00. 
cause that is where it's usually loaded for some reason.
So addresses need to keep that in mind.



Print a character 
--------------------
To print a character we can use a BIOS interrupt, which is a bit like a crappy function call.
Apparently printing is a BIOS video interrupt.  Video interrupts are called with the command
int 0x10.  This command then looks in the a register for some arguments.
The high bytef of a is the function name, and the low byte of a is the character.
I guess that the function for print a character is called 0x0e.
The computer starts in 16 bit mode for backwards compatibility.

; print a character
mov ah, 0x0e
mov al, "c"
int 0x10



Print a string 
--------------------

To print a string we put some characters into memory, then we load 
each character into al and fire the interrupt.  If the character byte 
is zero then we terminate the proceedure.


a_string: db 'hello',0       ; 0/null to null terminate 

mov bx, a_string            ; move the test_string address into b 
; jmp print_string

print_string:
mov ah, 0x0e                ; int 10 / ah 0x0e for BIO teletype output 
mov al, [bx]                ; get character AT bx
cmp al, 0                   ; sets zero flag
je here                     ; jump if equal. (al == 0)
int 0x10                    ; print character
add bx,1                    ; move forward 
jmp print_string 

here:
jmp here


These two lines perform a jump if equals operation.
cmp al, 0                   ; sets zero flag
je here                     ; jump if equal. (al == 0)



a_string: db 'Hello World!',0

mov bx, a_string

mov ah, 0x0e
mov al, [bx]
int 0x10
mov al, [bx+1]
int 0x10
mov al, [bx+2]
int 0x10
mov al, [bx+3]
int 0x10

