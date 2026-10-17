// C runtime behaviour the recovered code relies on, and small runtime shims.

#include <stdarg.h>
#include <stdio.h>

#include "axis.h"
#include "quaternion.h"

// The MSVC C runtime's rand(). Track generation reseeds it with
// RandSeed(runtime_build_seed), so the sequence must be the original's exactly.
namespace {
unsigned int g_msvc_rand_state = 1;
}

extern "C" void srand(unsigned int seed)
{
    g_msvc_rand_state = seed;
}

extern "C" int rand(void)
{
    g_msvc_rand_state = g_msvc_rand_state * 214013u + 2531011u;
    return (int)((g_msvc_rand_state >> 16) & 0x7fff);
}

unsigned int msvc_rand_seed()
{
    return g_msvc_rand_state;
}

// The shipped build compiled debug output away (debug_report_stub @ 0x44b7c0
// is empty). The port prints it, which changes no game state.
int debug_report_stub(char* format, ...)
{
    va_list args;
    va_start(args, format);
    int written = vfprintf(stderr, format, args);
    va_end(args);
    return written;
}

// Header-declared default constructors with no recovered body: the originals
// leave the members uninitialized.
tQuaternian::tQuaternian() {}
tAxis::tAxis() {}
