; 简单的引导加载程序
bits 16
org 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    
    ; 加载内核到内存
    mov ah, 0x02
    mov al, 10       ; 读取10个扇区
    mov ch, 0        ; 柱面0
    mov dh, 0        ; 磁头0
    mov cl, 2        ; 从第2个扇区开始
    mov bx, 0x7E00   ; 加载到0x7E00
    int 0x13
    
    ; 切换到保护模式
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:protected_mode

bits 32
protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; 跳转到内核
    jmp 0x7E00

; GDT定义
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xAA55