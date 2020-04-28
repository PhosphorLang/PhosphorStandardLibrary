#include "types.h"

void print (const void* address, const UInt size)
{
    Int file_descriptor = 1; // File descriptor ID for stdout
    UInt syscode = 1; // Syscall ID for writing

    asm("syscall" : : "d" (size), "S" (address), "D" (file_descriptor), "a" (syscode));

    return;
}
