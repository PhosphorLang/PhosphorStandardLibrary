#pragma once

#include "../../common/types.h"
#include "../../common/string.h"

String createString (const UInt8* data, UInt size);

String concatenate (const String string1, const String string2);

String getIndex (const String string, const UInt index);
String setIndex (const String string, const UInt index, const String character);

UInt getLength (const String string);
