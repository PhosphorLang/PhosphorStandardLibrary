; Standard library

[section .text]

    [section .text.print,"ax",@progbits]
    [global exit]
    exit:
        mov rdi, 0 ; Exit code
        mov rax, 60 ; Syscall ID for exit
        syscall
