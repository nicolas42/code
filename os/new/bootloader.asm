[org 0x7c00]  ; Origin, tells where the program will be loaded

; Set up the data segments
mov ax, 0x07C0
mov ds, ax
mov es, ax

; Jump to the main function assumed to be at 0x7E00
jmp 0x07E0:0000

times 510 - ($ - $$) db 0
dw 0xAA55

