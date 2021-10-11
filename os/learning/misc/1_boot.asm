;;; Basic Boot sector that will jump continuously
;;;

; fasm bootSect.asm
; qemu-system-i386 -drive format=raw,file=bootSect.bin,if=ide,index=0,media=disk


here:
    jmp here                ; jump repeatedly to label 'loop'; neverending

    times 510-($-$$) db 0   ; pads out 0s until we reach 510th byte

    dw 0xaa55               ; BIOS magic number; BOOT magic #


; $ = value of current offset
; $$ = base address of current addressing space

