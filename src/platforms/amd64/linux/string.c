#include "string.h"

#include "memory.h"
#include "../../common/types.h"
#include "../../common/string.h"

String createString (const Cardinal8* data, Cardinal size)
{
    const Cardinal stringSize = size + sizeof(Cardinal);

    Cardinal8* stringArray = allocate(stringSize);

    Cardinal* stringIntArray = (Cardinal*)stringArray;

    stringIntArray[0] = size;

    copy(&stringArray[sizeof(Cardinal)], data, size);

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
    const UInt8* indexedArray = string->data + index;

    return createString(indexedArray, 1);
}

void setIndex (const String string, const UInt index, const String character) asm ("\"Standard.String~setIndex\"");
void setIndex (const String string, const UInt index, const String character)
{
    UInt8* newDataArray = string->data;
    newDataArray[index] = character->data[0];
}

Int getIndexByte (const String string, const UInt index) asm ("\"Standard.String~getIndexByte\"");
Int getIndexByte (const String string, const UInt index)
{
    return string->data[index];
}

void setIndexByte (const String string, const UInt index, const Int value) asm ("\"Standard.String~setIndexByte\"");
void setIndexByte (const String string, const UInt index, const Int value)
{
    UInt8* newDataArray = string->data;
    newDataArray[index] = value;
}

UInt getLength (const String string) asm ("\"Standard.String~getLength\"");
UInt getLength (const String string)
{
    return string->size;
}
