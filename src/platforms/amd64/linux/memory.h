#pragma once

#include "../../common/memory.h"
#include "../../common/types.h"

void* allocate (Cardinal size) asm ("\"Standard.Memory~allocate\"");
void free (const void* address, Cardinal size) asm ("\"Standard.Memory~free\"");
