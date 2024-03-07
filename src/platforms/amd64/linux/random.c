#include "syscodes.h"
#include "../../common/types.h"

static Integer seed = 0;

void randomise () asm ("\"Standard.Random~randomise\"");
void randomise ()
{
    Cardinal syscode = SYSCODE_GET_RANDOM;
    Cardinal byteCount = sizeof(Integer);
    Cardinal flags = 0;

    Integer newSeed;
    Integer result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (&newSeed), "S" (byteCount), "d" (flags),  "a" (syscode)
                            : "rcx", "r11");

    if (newSeed < 0)
    {
        seed = -newSeed;
    }
    else
    {
        seed = newSeed;
    }

    // TODO: Check return value.
}

Integer getRandom (Integer range) asm ("\"Standard.Random~getRandom\"");
Integer getRandom (Integer range)
{
    seed = (seed * 1103515245 + 12345);

    Integer result = seed % range;

    return result;
}
