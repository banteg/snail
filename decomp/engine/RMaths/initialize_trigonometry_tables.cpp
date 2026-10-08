// RMathInit @ 0x44c930 (cdecl)

#include "rmath_random.h"

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);
#include "rmath_tables.h"

void RMathInit()
{
    for (int index = 0; index < RMATH_TRIG_TABLE_COUNT; ++index) {
#ifdef SNAIL_PORT
        // VC6 keeps this float in an x87 register and never rounds it, and
        // RMathInit runs before Direct3D 8 lowers the x87 to 24-bit precision,
        // so the angle the tables use is the C runtime's 53-bit double.
        double angle = (float)index * 0.00012207031f;
#else
        float angle = (float)index * 0.00012207031f;
#endif
        angle = angle * 6.2831855f;
        g_cosine_table[index] = (float)cos(angle);
        g_sine_table[index] = (float)sin(angle);
    }
    gRMathRand2Init();
}
