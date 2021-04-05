#pragma once

#include "../../common/memory.h"
#include "../../common/types.h"

void* alloc (UInt size);
void free (void* address, UInt size);
