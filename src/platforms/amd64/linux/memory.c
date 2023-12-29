#include "syscodes.h"
#include "../../common/types.h"

/**
 * Allocate memory on the heap.
 * @param size The size of the memory block to allocate.
 * @return The pointer to the allocated memory.
 */
void* allocate (UInt size) asm ("Standard.Memory.allocate");
void* allocate (UInt size)
{
    void* address = 0;
    UInt prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register UInt flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register Int fileDescriptor asm("r8") = -1;
    register UInt offset asm("r9") = 0;
    UInt syscode = SYSCODE_MEMORY_MAP;
    void* result;

    asm volatile ("syscall" : "=a" (result)
                            : "S" (size), "D" (address), "d" (prot), "r" (flags), "r" (fileDescriptor), "r" (offset), "a" (syscode)
                            : "rcx", "r11");

    return result;
}

/**
 * Free allocated heap memory.
 * @param address The pointer to the memory to free.
 * @param size The size of the memory block.
 */
void free (const void* address, UInt size)
{
    UInt syscode = SYSCODE_MEMORY_UNMAP;

    Int result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (address), "S" (size), "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check result (0 on success, -1 on failure).

    return;
}
