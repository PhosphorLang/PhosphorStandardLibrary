#include "memory.h"
#include "string.h"
#include "types.h"

String createString (const UInt8* data, UInt size)
{
    const UInt stringSize = size + sizeof(UInt);

    UInt8* stringArray = alloc(stringSize);

    UInt* stringIntArray = (UInt*)stringArray;

    stringIntArray[0] = size;

    copy(&stringArray[sizeof(UInt)], data, size);

    return (String)stringArray;
}
