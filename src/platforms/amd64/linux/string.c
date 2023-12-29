#include "string.h"

#include "memory.h"
#include "../../common/types.h"
#include "../../common/string.h"

String createString (const UInt8* data, UInt size)
{
    const UInt stringSize = size + sizeof(UInt);

    UInt8* stringArray = allocate(stringSize);

    UInt* stringIntArray = (UInt*)stringArray;

    stringIntArray[0] = size;

    copy(&stringArray[sizeof(UInt)], data, size);

    return (String)stringArray;
}
