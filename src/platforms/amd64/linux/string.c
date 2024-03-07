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
    const Cardinal newSize = string1->size + string2->size;

    Cardinal8* newDataArray = allocate(newSize);

    copy(newDataArray, string1->data, string1->size);
    copy(&newDataArray[string1->size], string2->data, string2->size);

    return createString(newDataArray, newSize);
}

String getIndex (const String string, const Cardinal index) asm ("\"Standard.String~getIndex\"");
String getIndex (const String string, const Cardinal index)
{
    const Cardinal8* indexedArray = string->data + index;

    return createString(indexedArray, 1);
}

void setIndex (const String string, const Cardinal index, const String character) asm ("\"Standard.String~setIndex\"");
void setIndex (const String string, const Cardinal index, const String character)
{
    Cardinal8* newDataArray = string->data;
    newDataArray[index] = character->data[0];
}

Integer getIndexByte (const String string, const Cardinal index) asm ("\"Standard.String~getIndexByte\"");
Integer getIndexByte (const String string, const Cardinal index)
{
    return string->data[index];
}

void setIndexByte (const String string, const Cardinal index, const Integer value) asm ("\"Standard.String~setIndexByte\"");
void setIndexByte (const String string, const Cardinal index, const Integer value)
{
    Cardinal8* newDataArray = string->data;
    newDataArray[index] = value;
}

Cardinal getLength (const String string) asm ("\"Standard.String~getLength\"");
Cardinal getLength (const String string)
{
    return string->size;
}
