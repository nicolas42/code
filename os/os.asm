
 ; macos
 ; fasm os.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -boot a -fda os.bin
 ; fasm os.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=os.bin,if=floppy

 ;linux
 ; fasm os.asm && qemu-system-i386 -drive format=raw,file=os.bin,if=floppy


    ;; This demo uses interrupt 0x13 with ah=2 to read a disk sector and then jump to it
;;;  unfortunately this appears to screw up the data segment?
;;;
;;; Simple Boot loader that uses INT13 AH2 to read from disk into memory
;;;

; Note: I did not understood segment:offset addressing fully until later, 
; a segment register (DS, ES, etc.)  implicitly multiply their value by 16, then the offset 
; is added to get an address. So mov AX, 100h; mov ES, AX; would leave ES with 100h, but
;  ES would point to 1000h, 100h*16. 
;  Then if you did something like mov DI, 100h; ES:DI would point to 100h:100h = 1000h + 100h = 1100h;



    org 0x7c00                  ; 'origin' of Boot code; helps make sure addresses don't change


    ;; set up ES:BX memory address/segment:offset to load sector(s) into
    mov bx, 0x7e00              ; load sector to memory address 0x7e00 
    mov es, bx                  
    mov bx, 0x0                 ; ES:BX = 0x7e00:0x0

    ;; Set up disk read
    mov dh, 0x0                 ; head 0
    mov dl, 0x0                 ; drive 0
    mov ch, 0x0                 ; cylinder 0
    mov cl, 0x02                ; starting sector to read from disk

read_disk:
    mov ah, 0x02                ; BIOS int 13h/ah=2 read disk sectors
    mov al, 0x01                ; # of sectors to read
    int 0x13                    ; BIOS interrupts for disk functions

    jc read_disk                ; retry if disk read error (carry flag set/ = 1)


    mov ax, 0x7e00
    mov ds, ax                  ; data segment

    jmp 0x7e00:0x0              ; never return from this!



    ;; Boot Sector magic
    times 510-($-$$) db 0       ; pads out 0s until we reach 510th byte
    dw 0xaa55                   ; BIOS magic number; BOOT magic #



;;; Thing to boot up


    org 0x0000

    ;; Set video mode
    mov ah, 0x00                ; int 0x10/ ah 0x00 = set video mode
    mov al, 0x02
    int 0x10

    ;; Change color/Palette
    mov ah, 0x0B
    mov bh, 0x00
    mov bl, 0x01
    int 0x10

    ;; print something
    mov bx, you_have_booted
    call print_string

    jmp $


include "print_string.asm"
include 'print_hex.asm'


str1:   db 'Hello World!', 0xa, 0xd, 0
str2:   db 'You say goodbye but I say hello.  Hello, hello.', 0xa, 0xd, 0
str3:   db "omg it's some hex => ",0
you_have_booted:   db 'You have loaded a sector from a disk and then run it.', 0xa, 0xd, 0




    ;; boot magic
    times 1024-($-$$) db 0

