; kernel/start.asm
bits 32
global _start

section .text
_start:
    ; 设置栈指针
    mov esp, 0x90000
    
    ; 调用内核主函数
    extern kernel_main
    call kernel_main
    
    ; 如果返回则挂起
    cli
    hlt