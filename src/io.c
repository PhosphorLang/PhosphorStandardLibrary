#include "types.h"
#include "string.h"

void print (const String text)
{
    Int fileDescriptor = 1; // File descriptor ID for stdout
    UInt syscode = 1; // Syscall ID for writing

    asm("syscall" : : "d" (text->size), "S" (text->data), "D" (fileDescriptor), "a" (syscode));

    return;
}
