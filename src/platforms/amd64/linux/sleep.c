#include "../../common/types.h"

struct SleepTimeSpec
{
    // TODO: Are the integer types on all platforms correct?
    UInt seconds;
    UInt nanoseconds;
};

/**
 * Waits for the given amount of milliseconds.
 * @param milliseconds The number of milliseconds to wait for.
 */
void sleep (UInt milliseconds)
{
    struct SleepTimeSpec sleepTimeSpec = {
        .seconds = milliseconds / 1000,
        .nanoseconds = milliseconds % 1000 * 1000000
    };

    UInt syscode = 35; // Syscall ID for nanosleep
    Int result;

    asm volatile ("syscall" : "=a" (result)
                            : "D" (&sleepTimeSpec), "S" (&sleepTimeSpec), "a" (syscode)
                            : "rcx", "r11");

    // TODO: Check for the return value and the second struct as this call does not guarantee to wait for the whole time.
    // TODO: We should use sys_clock_nanosleep for more reliability.
}
