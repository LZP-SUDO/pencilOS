; bootloader/boot.asm
bits 16
org 0x7C00

start:
    ; 设置段寄存器
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; 加载内核到内存
    mov ah, 0x02    ; 读取扇区功能
    mov al, 10      ; 读取扇区数
    mov ch, 0       ; 柱面号
    mov cl, 2       ; 起始扇区号
    mov dh, 0       ; 磁头号
    mov bx, 0x7E00  ; 加载地址
    int 0x13

    ; 检查是否成功加载
    jc disk_error

    ; 跳转到内核
    jmp 0x0000:0x7E00

disk_error:
    mov si, error_msg
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

error_msg db "Disk error!", 0

times 510-($-$$) db 0
dw 0xAA55