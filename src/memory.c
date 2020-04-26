void* new (unsigned long long size)
{
    void* address = 0;
    unsigned long long prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register unsigned long long flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register long long file_descriptor asm("r8") = -1;
    register unsigned long long offset asm("r9") = 0;
    unsigned long long syscode = 9; // Syscall ID for mmap
    void* result;

    asm("syscall" : "=a" (result) : "S" (size), "D" (address), "d" (prot), "r" (flags), "r" (file_descriptor), "r" (offset), "a" (syscode));

    return result;
}

void delete (void* address, unsigned long long size)
{
    unsigned long long syscode = 11; // Syscall ID for munmap

    asm("syscall" : : "D" (address), "S" (size), "a" (syscode));

    return;
}

void copy (char* destination, char* source, unsigned long long size)
{
    for (unsigned long long i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }

    return;
}
