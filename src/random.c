#include "types.h"

UInt seed = 0;

void randomise ()
{
    UInt syscode = 318; // Syscall ID for getrandom
    UInt byteCount = sizeof(Int);
    UInt flags = 0;

    Int result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (&seed), "S" (byteCount), "d" (flags),  "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check return value.
}

Int getRandom (Int range)
{
    seed = (seed * 1103515245 + 12345) % range;
    // TODO: Is this correct? Shouldn't we only apply the range onto the result and not the seed calculation?

    return seed;
}
