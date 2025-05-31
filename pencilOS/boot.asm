; 引导扇区代码
bits 16
org 0x7C00

start:
    cli
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    sti

    ; 设置栈指针
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFF

    ; 加载内核到内存
    mov ah, 0x02
    mov al, 10      ; 读取10个扇区
    mov ch, 0       ; 柱面0
    mov cl, 2       ; 从第2个扇区开始
    mov dh, 0       ; 磁头0
    mov bx, 0x1000  ; 加载到0x1000:0000
    mov es, bx
    mov bx, 0
    int 0x13
    jc disk_error

    ; 跳转到保护模式
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp 0x08:protected_mode

bits 32
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; 设置栈指针
    mov esp, 0x90000

    ; 跳转到内核
    jmp 0x10000

disk_error:
    mov si, error_msg
    call print_string
    hlt

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

error_msg db "Disk read error!", 0

; GDT
gdt_start:
    dq 0x0
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

times 510-($-$$) db 0
dw 0xAA55
