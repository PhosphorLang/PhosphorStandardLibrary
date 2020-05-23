#include "types.h"

/**
 * Allocate memory on the heap.
 * @param size The size of the memory block to allocate.
 * @return The pointer to the allocated memory.
 */
void* alloc (UInt size)
{
    void* address = 0;
    UInt prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register UInt flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register Int fileDescriptor asm("r8") = -1;
    register UInt offset asm("r9") = 0;
    Int syscode = 9; // Syscall ID for mmap
    void* result;

    asm("syscall" : "=a" (result) : "S" (size), "D" (address), "d" (prot), "r" (flags), "r" (fileDescriptor), "r" (offset), "a" (syscode));

    return result;
}

/**
 * Free allocated heap memory.
 * @param address The pointer to the memory to free.
 * @param size The size of the memory block.
 */
void free (void* address, UInt size)
{
    UInt syscode = 11; // Syscall ID for munmap

    asm("syscall" : : "D" (address), "S" (size), "a" (syscode));

    return;
}

/**
 * Direct memory to memory copy.
 * @param destination The location to copy the block to.
 * @param source The location to copy the block from.
 * @param size The size of the memory block to copy.
 */
void copy (UInt8* destination, UInt8* source, UInt size)
{
    for (UInt i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }

    return;
}
