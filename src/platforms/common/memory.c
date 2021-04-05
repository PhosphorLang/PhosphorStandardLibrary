#include "types.h"

/**
 * Direct memory to memory copy.
 * @param destination The location to copy the block to.
 * @param source The location to copy the block from.
 * @param size The size of the memory block to copy.
 */
void copy (UInt8* destination, const UInt8* source, UInt size)
{
    for (UInt i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }

    return;
}
