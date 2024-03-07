#pragma once

#include "types.h"

/** A string value contains the size of the data as an integer and the data itself as an array. */
typedef struct
{
    const Cardinal size;
    const Cardinal8 data[];
} __attribute__((__packed__)) StringValue;

/**
 * The pointer to a string value.
 * A string value contains the size of the data as an integer and the data itself as an array.
 */
typedef const StringValue* String;

Boolean stringsAreEqual (const String string1, const String string2) asm ("\"Standard.String~stringsAreEqual\"");
