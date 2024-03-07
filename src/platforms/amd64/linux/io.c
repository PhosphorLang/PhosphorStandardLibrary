#include "memory.h"
#include "string.h"
#include "syscodes.h"
#include "../../common/types.h"

/**
 * Writes a string to the standard output.
 * @param text The string to write.
 */
void write (const String text) asm ("\"Standard.Io~write\"");
void write (const String text)
{
    Integer fileDescriptor = 1; // File descriptor ID for stdout
    Cardinal syscode = SYSCODE_WRITE;

    Integer result;

    asm volatile ("syscall" : "=a" (result)
                            : "d" (text->size), "S" (text->data), "D" (fileDescriptor), "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check if result is an error (-1) or less than the text size.
}

/**
 * Writes a string to the standard output, followed by a line break.
 * @param text The string to write.
 */
void writeLine (const String text) asm ("\"Standard.Io~writeLine\"");
void writeLine (const String text)
{
    Cardinal8* lineBreakLiteralChar = { "\n" };

    String lineBreak = createString(lineBreakLiteralChar, 1);

    write(text);
    write(lineBreak);

    free(lineBreak, sizeof (StringValue) + 1);

    // TODO: Replace the hard coded line break with a system dependent constant.
}

/**
 * Reads a line from the standard input.
 * @return The string that has been read in. Does not include the line break.
 */
String readLine () asm ("\"Standard.Io~readLine\"");
String readLine ()
{
    Integer fileDescriptor = 0; // File descriptor ID for stdin
    Cardinal syscode = SYSCODE_READ;

    const Cardinal bufferSize = 4096;
    Cardinal8 buffer[bufferSize];

    Integer bytesRead = 0;
    Cardinal resultSize = 0;
    Cardinal8* result = null;

    while (true)
    {
        asm volatile ("syscall" : "=a" (bytesRead)
                                : "d" (bufferSize), "S" (&buffer[0]), "D" (fileDescriptor), "a" (syscode)
                                : "rcx", "r11");

        // TODO: Check for errors (bytesRead is -1).

        if (bytesRead > 0)
        {
            // Allocate memory for the new total result size:
            Cardinal newSize = resultSize + bytesRead;
            Cardinal8* newResult = allocate(newSize);

            // Copy the old result and the buffer to the new result:
            copy(newResult, result, resultSize);
            copy(&newResult[resultSize], buffer, bytesRead);

            // Don't forget: Free the old result!
            if (result != null)
            {
                free(result, resultSize);
            }

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

    Cardinal stringSize = resultSize;

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
