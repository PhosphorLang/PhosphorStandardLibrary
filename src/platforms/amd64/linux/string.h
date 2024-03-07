#pragma once

#include "../../common/types.h"
#include "../../common/string.h"

String createString (const Cardinal8* data, Cardinal size);

String concatenate (const String string1, const String string2);

String getIndex (const String string, const Cardinal index);
void setIndex (const String string, const Cardinal index, const String character);

Integer getIndexByte (const String string, const Cardinal index);
void setIndexByte (const String string, const Cardinal index, const Integer value);

Cardinal getLength (const String string);
