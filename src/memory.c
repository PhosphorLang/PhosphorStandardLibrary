#include "types.h"

void* new (UInt size)
{
    void* address = 0;
    UInt prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register UInt flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register Int file_descriptor asm("r8") = -1;
    register UInt offset asm("r9") = 0;
    Int syscode = 9; // Syscall ID for mmap
    void* result;

    asm("syscall" : "=a" (result) : "S" (size), "D" (address), "d" (prot), "r" (flags), "r" (file_descriptor), "r" (offset), "a" (syscode));

    return result;
}

void delete (void* address, UInt size)
{
    UInt syscode = 11; // Syscall ID for munmap

    asm("syscall" : : "D" (address), "S" (size), "a" (syscode));

    return;
}

void copy (UInt8* destination, UInt8* source, UInt size)
{
    for (UInt i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }

    return;
}
