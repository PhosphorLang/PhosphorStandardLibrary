#include "types.h"

/**
 * Direct memory to memory copy.
 * @param destination The location to copy the block to.
 * @param source The location to copy the block from.
 * @param size The size of the memory block to copy.
 */
void copy (Cardinal8* destination, const Cardinal8* source, Cardinal size)
{
    for (Cardinal i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }

    return;
}
