#pragma once

#include <cassert>

// Function declaration keywords.
#define Inline inline

// Compile-time assert.
#define StaticAssert(x) static_assert(x)

// Assert the breaks execution.
#define Assert(x) assert(x)

// Debug-only asserts that don't do anything in release.
#if defined(_DEBUG)
#define DebugAssert(x) Assert(x)
#else
#define DebugAssert(x)
#endif