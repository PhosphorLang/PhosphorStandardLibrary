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

String intToString (Int integer)
{
    // The following is a hack.
    // The string length of a number in decimal (including the minus for negative values) is never greater then three times plus one
    // of the number of bytes in binary notation. We need this for the memory allocation of the buffer.
    const UInt maxStringLength = sizeof(Int) * 3 + 1;

    UInt8 characters[maxStringLength];

    UInt stringLength = 0;
    Int rest = integer;

    if (rest < 0)
    {
        rest *= -1;
    }

    do
    {
        UInt8 character = rest % 10 + '0';

        characters[maxStringLength - stringLength - 1] = character;

        stringLength++;

        rest = rest / 10;
    }
    while (rest != 0);

    if (integer < 0)
    {
        characters[maxStringLength - stringLength - 1] = '-';

        stringLength++;
    }

    String result = createString(&characters[maxStringLength - stringLength], stringLength);

    return result;
}

Int stringToInt (const String string)
{
    if (string->size == 0)
    {
        return 0;
    }

    Int result = 0;
    UInt multiplier = 1;

    for (Int i = string->size - 1; i >= 0; i--)
    {
        if ((string->data[i] >= '0') && (string->data[i] <= '9'))
        {
            result += (string->data[i] - '0') * multiplier;

            multiplier *= 10;
        }
        else if (string->data[i] == '-')
        {
            result *= -1;

            break;
        }
    }

    return result;
}
