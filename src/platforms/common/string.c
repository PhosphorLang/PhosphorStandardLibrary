#include "types.h"
#include "string.h"

Bool stringsAreEqual (const String string1, const String string2) asm ("\"Standard.String~stringsAreEqual\"");
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
