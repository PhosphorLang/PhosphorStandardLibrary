#include "../../common/types.h"
#include "string.h"

String intToString (Integer integer) asm ("\"Standard.Conversion~intToString\"");
String intToString (Integer integer)
{
    // The following is a hack.
    // The string length of a number in decimal (including the minus for negative values) is never greater then three times plus one
    // of the number of bytes in binary notation. We need this for the memory allocation of the buffer.
    const Cardinal maxStringLength = sizeof(Integer) * 3 + 1;

    Cardinal8 characters[maxStringLength];

    Cardinal stringLength = 0;
    Integer rest = integer;

    if (rest < 0)
    {
        rest *= -1;
    }

    do
    {
        Cardinal8 character = rest % 10 + '0';

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

Integer stringToInt (const String string) asm ("\"Standard.Conversion~stringToInt\"");
Integer stringToInt (const String string)
{
    if (string->size == 0)
    {
        return 0;
    }

    Integer result = 0;
    Cardinal multiplier = 1;

    for (Integer i = string->size - 1; i >= 0; i--)
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
