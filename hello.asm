section .bss
    ; variables

section .data
    ; constants
    hello_world: db "Hello, world!", 10 ; string to print
    hw_len: equ $-hello_world

section .text
    global _start ; entry point for linker

    _start: ; start
        mov rax,1 ; sys_write
        mov rdi,1 ; stdout
        mov rsi,hello_world ; message to write
        mov rdx,hw_len ; message length
        syscall ; call kernel

        mov rax,60 ; sys_exit
        mov rdi,0 ; error code
        syscall
