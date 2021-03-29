#pragma once

#include "types.h"

void* alloc (UInt size);
void free (void* address, UInt size);
void copy (UInt8* destination, const UInt8* source, UInt size);
