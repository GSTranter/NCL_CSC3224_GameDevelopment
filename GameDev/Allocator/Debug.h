// NOT WRITTEN BY GEORGE TRANTER FOR GAME DEV. THIS IS ALLOCATOR MIDDLEWARE \\

#ifndef DEBUG_H
#define DEBUG_H

#if !_DEBUG
#define NDEBUG
#endif

#include <assert.h>

#define ASSERT assert

#endif