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
    unsigned long long file_descriptor = 1; // File descriptor ID for stdout
    unsigned long long syscode = 1; // Syscall ID for writing

    asm("syscall" : : "d" (size), "S" (address), "D" (file_descriptor), "a" (syscode));

    return;
}
