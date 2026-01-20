#include "syscodes.h"
#include "../../common/types.h"

typedef struct
{
    Cardinal size;
} __attribute__((__packed__, __aligned__(16))) MemoryHeader;

/**
 * Allocate memory on the heap.
 * @param size The size of the memory block to allocate.
 * @return The pointer to the allocated memory.
 */
void* allocate (Cardinal size) asm ("\"Standard.Memory~allocate\"");
void* allocate (Cardinal size)
{
    Cardinal totalSize = size + sizeof(MemoryHeader);

    void* address = 0;
    Cardinal prot = 0x3; // 0x3 = PROT_READ|PROT_WRITE
    register Cardinal flags asm("r10") = 0x22; // 0x22 = MAP_PRIVATE|MAP_ANONYMOUS
    register Integer fileDescriptor asm("r8") = -1;
    register Cardinal offset asm("r9") = 0;
    Cardinal syscode = SYSCODE_MEMORY_MAP;
    void* memoryRegion;

    asm volatile ("syscall" : "=a" (memoryRegion)
                            : "S" (totalSize), "D" (address), "d" (prot), "r" (flags), "r" (fileDescriptor), "r" (offset), "a" (syscode)
                            : "rcx", "r11");

    if (memoryRegion == (void*)-1)
    {
        // TODO: What to do here?

        return null;
    }

    MemoryHeader* header = (MemoryHeader*)memoryRegion;
    header->size = totalSize;

    void* userMemory = (void*)(header + 1);
    return userMemory;
}

/**
 * Free allocated heap memory.
 * @param address The pointer to the memory to free.
 */
void free (const void* address) asm ("\"Standard.Memory~free\"");
void free (const void* address)
{
    if (address == 0)
    {
        return;
    }

    MemoryHeader* header = (MemoryHeader*)address - 1;
    Cardinal size = header->size;

    Cardinal syscode = SYSCODE_MEMORY_UNMAP;
    Integer result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (header), "S" (size), "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check result (0 on success, -1 on failure).

    return;
}
