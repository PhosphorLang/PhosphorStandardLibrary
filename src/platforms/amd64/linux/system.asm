[section .text]
    [section .text.exit,"ax",@progbits]
    [global Standard.System.exit]
    Standard.System.exit:
        mov rdi, 0 ; Exit code
        mov rax, 60 ; Syscall ID for exit
        syscall
