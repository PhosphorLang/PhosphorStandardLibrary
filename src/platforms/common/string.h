#pragma once

#include "types.h"

/** A string value contains the size of the data as an integer and the data itself as an array. */
typedef struct
{
    const UInt size;
    const UInt8 data[];
} __attribute__((__packed__)) StringValue;

/**
 * The pointer to a string value.
 * A string value contains the size of the data as an integer and the data itself as an array.
 */
typedef const StringValue* String;

Bool stringsAreEqual (const String string1, const String string2) asm ("Standard.String.stringsAreEqual");
