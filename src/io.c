#include "types.h"
#include "string.h"

/**
 * Print a string to the console.
 * @param text The string to print.
 */
void print (const String text)
{
    Int fileDescriptor = 1; // File descriptor ID for stdout
    UInt syscode = 1; // Syscall ID for writing

    Int result;

    asm volatile ("syscall" : "=a" (result) : "d" (text->size), "S" (text->data), "D" (fileDescriptor), "a" (syscode));

    // TODO: Check if result is an error (-1) or less than the text size.
}
