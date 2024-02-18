#pragma once

#include "../../common/types.h"
#include "string.h"

/**
 * Converts an integer into a string.
 * @return A new string instance, representing the given integer value.
 */
String intToString (Int integer) asm ("\"Standard.Conversion~intToString\"");

/**
 * Convert a string into an integer.
 * @return The integer value the given string represents.
 */
Int stringToInt (const String string) asm ("\"Standard.Conversion~stringToInt\"");
