#pragma once

#include "../../common/types.h"

void randomise () asm ("Standard.Random.randomise");

Int getRandom (Int range) asm ("Standard.Random..getRandom");
