; boot.asm - 引导加载程序
bits 32
section .multiboot
    align 4
    dd 0x1BADB002              ; 魔数
    dd 0x00                    ; 标志
    dd - (0x1BADB002 + 0x00)   ; 校验和

section .text
global start
extern kernel_main             ; 声明C++入口点

start:
    cli                        ; 禁用中断
    mov esp, stack_space       ; 设置栈指针
    
    call kernel_main           ; 调用C++内核主函数
    
    hlt                        ; 停机

section .bss
resb 8192                      ; 8KB栈空间
stack_space:
