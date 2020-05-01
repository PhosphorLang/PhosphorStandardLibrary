#include "types.h"

/** A string value contains the size of the data as an integer and the data itself as an array. */
typedef struct
{
    const UInt size;
    const UInt8 data[];
} StringValue;

/**
 * The pointer to a string value.
 * A string value contains the size of the data as an integer and the data itself as an array.
 */
typedef const StringValue* String;
