#pragma once

#include "../../common/memory.h"
#include "../../common/types.h"

void* allocate (UInt size) asm ("\"Standard.Memory~allocate\"");
void free (const void* address, UInt size);
