#pragma once

#include "../../common/types.h"
#include "../../common/string.h"

String createString (const UInt8* data, UInt size);

String concatenate (const String string1, const String string2);

String getIndex (const String string, const UInt index);
void setIndex (const String string, const UInt index, const String character);

Int getIndexByte (const String string, const UInt index);
void setIndexByte (const String string, const UInt index, const Int value);

UInt getLength (const String string);
