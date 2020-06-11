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

Bool stringsAreEqual (const String string1, const String string2);
String createString (const UInt8* data, UInt size);

/**
 * Converts an integer into a string.
 * @return A new string instance, representing the given integer value.
 */
String intToString (Int integer);
