void print (const void* address, unsigned long long size)
{
    long long file_descriptor = 1; // File descriptor ID for stdout
    unsigned long long syscode = 1; // Syscall ID for writing

    asm("syscall" : : "d" (size), "S" (address), "D" (file_descriptor), "a" (syscode));

    return;
}
