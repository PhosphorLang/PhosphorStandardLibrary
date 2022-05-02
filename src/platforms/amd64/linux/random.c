#include "../../common/types.h"

static Int seed = 0;

void randomise ()
{
    UInt syscode = 318; // Syscall ID for getrandom
    UInt byteCount = sizeof(Int);
    UInt flags = 0;

    Int newSeed;
    Int result;

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

Int getRandom (UInt range)
{
    seed = (seed * 1103515245 + 12345);

    Int result = seed % range;

    return result;
}
