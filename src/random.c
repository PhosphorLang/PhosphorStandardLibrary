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
    // TODO: Should we use the unblocking method?
}

Int getRandom (Int range)
{
    seed = (seed * 1103515245 + 12345) % range;

    return seed;
}
