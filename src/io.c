#include "types.h"
#include "string.h"

/**
 * Writes a string to the standard output, followed by a line break.
 * @param text The string to write.
 */
void writeLine (const String text)
{
    Int fileDescriptor = 1; // File descriptor ID for stdout
    UInt syscode = 1; // Syscall ID for writing

    Int result;

    asm volatile ("syscall" : "=a" (result) : "d" (text->size), "S" (text->data), "D" (fileDescriptor), "a" (syscode));

    // TODO: Check if result is an error (-1) or less than the text size.

    // Print line break:
    asm volatile ("syscall" : "=a" (result) : "d" (1), "S" ("\n"), "D" (fileDescriptor), "a" (syscode));

    // TODO: Check result.
    // TODO: Replace hardcoded line break with a system dependent constant.
}
