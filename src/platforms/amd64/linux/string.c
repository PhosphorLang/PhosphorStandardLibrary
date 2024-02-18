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

String concatenate (const String string1, const String string2) asm ("\"Standard.String~concatenate\"");
String concatenate (const String string1, const String string2)
{
    const UInt newSize = string1->size + string2->size;

    UInt8* newDataArray = allocate(newSize);

    copy(newDataArray, string1->data, string1->size);
    copy(&newDataArray[string1->size], string2->data, string2->size);

    return createString(newDataArray, newSize);
}

String getIndex (const String string, const UInt index) asm ("\"Standard.String~getIndex\"");
String getIndex (const String string, const UInt index)
{
    UInt8* newDataArray = allocate(1);
    newDataArray[0] = string->data[index];

    return createString(newDataArray, 1);
}

String setIndex (const String string, const UInt index, const String character) asm ("\"Standard.String~setIndex\"");
String setIndex (const String string, const UInt index, const String character)
{
    UInt8* newDataArray = allocate(string->size);

    copy(newDataArray, string->data, string->size);

    newDataArray[index] = character->data[0];

    return createString(newDataArray, string->size);
}

UInt getLength (const String string) asm ("\"Standard.String~getLength\"");
UInt getLength (const String string)
{
    return string->size;
}
