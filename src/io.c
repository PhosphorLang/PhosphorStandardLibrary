#include "memory.h"
#include "string.h"
#include "types.h"

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

/**
 * Reads a line from the standard input.
 * @return The string that has been read in. Does not include the line break.
 */
String readLine ()
{
    Int fileDescriptor = 0; // File descriptor ID for stdin
    UInt syscode = 0; // Syscall ID for reading

    const UInt bufferSize = 4096;
    UInt8 buffer[bufferSize];

    Int bytesRead = 0;
    UInt resultSize = 0;
    UInt8* result = null;

    while (true)
    {
        asm volatile ("syscall" : "=a" (bytesRead) : "d" (bufferSize), "S" (&buffer[0]), "D" (fileDescriptor), "a" (syscode));

        // TODO: Check for errors (bytesRead is -1).

        if (bytesRead > 0)
        {
            // Allocate memory for the new total result size:
            UInt newSize = resultSize + bytesRead;
            UInt8* newResult = alloc(newSize);

            // Copy the old result and the buffer to the new result:
            copy(newResult, result, resultSize);
            copy(&newResult[resultSize], buffer, bytesRead);

            // Don't forget: Free the old result!
            free(result, resultSize);

            result = newResult;
            resultSize = newSize;

            // We end reading as soon as the last character is a line break:
            if (buffer[bytesRead - 1] == '\n') // TODO: Replace the hard coded line break with a system dependent constant.
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    UInt stringSize = resultSize;

    // Remove the line break at the end if there is one:
    if (result[stringSize - 1] == '\n') // TODO: Replace the hard coded line break with a system dependent constant.
    {
        stringSize--;
    }

    String readString = createString(result, stringSize);

    // Free the full result, including the potentially ignored line break:
    free(result, resultSize);

    return readString;
}
