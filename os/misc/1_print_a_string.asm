org 0x7c00

; print
mov ah, 0x0e
mov al, "o"
int 0x10
mov ah, 0x0e
mov al, "m"
int 0x10
mov ah, 0x0e
mov al, "g"
int 0x10

mov ah, 0x0e
mov bx, a_string
jmp print_string

; print a string
a_string: db 'hello',0

print_string:
mov al, [bx]
cmp al, 0
je infinite_loop
int 0x10
add bx,1
jmp print_string 


infinite_loop:
jmp $

times 510-($-$$) db 0
dw 0xaa55
