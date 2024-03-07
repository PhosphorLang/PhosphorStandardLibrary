#pragma once

#include "../../common/types.h"

void randomise () asm ("\"Standard.Random~randomise\"");

Integer getRandom (Integer range) asm ("\"Standard.Random~getRandom\"");
