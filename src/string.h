#include "types.h"

typedef struct
{
    const UInt size;
    const UInt8 data[];
} StringValue;

typedef const StringValue* String;
