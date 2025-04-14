[BITS 16]
[ORG 0x7C00]

start:
    xor ax, ax
    mov ds, ax
    mov si, msg

print_loop:
    lodsb              
    or al, al          
    jz hang           

    mov ah, 0x0E     
    int 0x10          
    jmp print_loop

hang:
    jmp hang

msg db "Hello World from Bios!", 0

times 510 - ($ - $$) db 0
dw 0xAA55