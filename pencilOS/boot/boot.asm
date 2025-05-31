; 多引导头 - GRUB需要这个来识别我们的内核
section .multiboot
align 4
    dd 0x1BADB002              ; 魔数
    dd 0x00                    ; 标志
    dd - (0x1BADB002 + 0x00)   ; 校验和

section .text
global _start
extern kernel_main             ; 在C++代码中定义

_start:
    ; 设置栈指针
    mov esp, stack_top
    
    ; 调用C++内核
    call kernel_main
    
    ; 如果内核返回，进入无限循环
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384 ; 16KB栈空间
stack_top: