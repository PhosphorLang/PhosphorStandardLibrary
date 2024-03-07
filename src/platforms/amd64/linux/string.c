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
