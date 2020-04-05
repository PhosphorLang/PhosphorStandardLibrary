void print (void* address, unsigned long long int size)
{
    void* address_param;
    unsigned long int file_descriptor, syscode;
    unsigned long long int size_param;

    asm("mov rdx, rsi" : "=d" (size_param) : "S" (size));
    asm("mov rsi, rdi" : "=S" (address_param) : "D" (address));
    asm("mov rdi, 1" : "=D" (file_descriptor)); // File descriptor ID for stdout
    asm("mov rax, 1" : "=a" (syscode)); // Syscall ID for writing

    asm("syscall" : : "D" (file_descriptor), "S" (address_param), "d" (size_param), "a" (syscode));

    return;
}
