    org 0x7c00

    call main
    jmp end_program

print_string:
    mov ah, 0x0e
    mov al, [bx]
    cmp al, 0
    je print_string_return
    int 0x10
    add bx,1
    jmp print_string 
print_string_return:
    ret


main:

    ;; Set video mode
    mov ah, 0x00                ; int 0x10/ ah 0x00 = set video mode
    mov al, 0x02
    int 0x10

    ;; Change color/Palette
    mov ah, 0x0B
    mov bh, 0x00
    mov bl, 0x01
    int 0x10


    mov bx, str1
    call print_string

    mov bx, newline
    call print_string

    mov bx, str2
    call print_string

    ret


end_program:
    jmp $

str1:          db 'Hello World!', 0
newline:       db 0xA, 0xD, 0
str2:          db 'You say goodbye but I say hello.  Hello, hello.', 0

    times 510-($-$$) db 0
    dw 0xaa55
