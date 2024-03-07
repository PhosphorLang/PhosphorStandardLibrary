#include "syscodes.h"
#include "../../common/types.h"

/**
 * Allocate memory on the heap.
 * @param size The size of the memory block to allocate.
 * @return The pointer to the allocated memory.
 */
void* allocate (Cardinal size) asm ("\"Standard.Memory~allocate\"");
void* allocate (Cardinal size)
{
    void* address = 0;
    Cardinal prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register Cardinal flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register Integer fileDescriptor asm("r8") = -1;
    register Cardinal offset asm("r9") = 0;
    Cardinal syscode = SYSCODE_MEMORY_MAP;
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
void free (const void* address, Cardinal size)
{
    Cardinal syscode = SYSCODE_MEMORY_UNMAP;

    Integer result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (address), "S" (size), "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check result (0 on success, -1 on failure).

    return;
}
