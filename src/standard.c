extern __attribute__((noreturn)) void exit ();
    // The following trick of having a full Assembly function is necessary because otherwise gcc adds a return statement at the end.
    asm(".globl exit");
    asm(".type exit, @function");
    asm("exit:");
    asm("mov rdi, 0");
    asm("mov rax, 60"); // Syscall ID for exit
    asm("syscall");

void print (const void* address, unsigned long long size)
{
    long long file_descriptor = 1; // File descriptor ID for stdout
    unsigned long long syscode = 1; // Syscall ID for writing

    asm("syscall" : : "d" (size), "S" (address), "D" (file_descriptor), "a" (syscode));

    return;
}

void* new (unsigned long long size)
{
    void* address = 0;
    unsigned long long prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register unsigned long long flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register long long file_descriptor asm("r8") = -1;
    register unsigned long long offset asm("r9") = 0;
    unsigned long long syscode = 9; // Syscall ID for mmap
    void * result;

    asm("syscall" : "=a" (result) : "S" (size), "D" (address), "d" (prot), "r" (flags), "r" (file_descriptor), "r" (offset), "a" (syscode));

    return result;
}
