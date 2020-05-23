#include "memory.h"
#include "string.h"
#include "types.h"

Bool stringsAreEqual (const String string1, const String string2)
{
    if (string1->size != string2->size)
    {
        return false;
    }

    for (UInt i = 0; i < string1->size; i++)
    {
        if (string1->data[i] != string2->data[i])
        {
            return false;
        }
    }

    return true;
}

String createString (const UInt8* data, UInt size)
{
    const UInt stringSize = size + sizeof(UInt);

    UInt8* stringArray = alloc(stringSize);

    UInt* stringIntArray = (UInt*)stringArray;

    stringIntArray[0] = size;

    copy(&stringArray[sizeof(UInt)], data, size);

    return (String)stringArray;
}
