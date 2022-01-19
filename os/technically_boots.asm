
; fasm technically_boots.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -boot a -fda technically_boots.bin

; fasm technically_boots.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=technically_boots.bin,if=floppy

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
    mov bx, 0x1000              ; load sector to memory address 0x1000 
    mov es, bx                  
    mov bx, 0x0                 ; ES:BX = 0x1000:0x0

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

    ;; reset segment registers for RAM
    mov ax, 0x1000
    mov ds, ax                  ; data segment
    mov es, ax                  ; extra segment
    mov fs, ax                  ; ""
    mov gs, ax                  ; ""
    mov ss, ax                  ; stack segment

    jmp 0x1000:0x0              ; never return from this!



    ;; Boot Sector magic
    times 510-($-$$) db 0       ; pads out 0s until we reach 510th byte
    dw 0xaa55                   ; BIOS magic number; BOOT magic #








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

    ;; print some stuff
    mov bx, str1
    call print_string
    mov bx, str2
    call print_string
    mov bx, str3
    call print_string
    mov dx, 0x12AB
    call print_hex

    jmp $


include "print_string.asm"
include 'print_hex.asm'


str1:          db 'Hello World!', 0xa, 0xd, 0
str2:          db 'You say goodbye but I say hello.  Hello, hello.', 0xa, 0xd, 0
str3:          db "omg it's some hex => ",0





    ;; boot magic
    times 1024-($-$$) db 0

