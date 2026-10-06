// RMathInit @ 0x44c930 (cdecl)

#include "rmath_random.h"

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);
#include "rmath_tables.h"

void RMathInit()
{
    for (int index = 0; index < RMATH_TRIG_TABLE_COUNT; ++index) {
        float angle = (float)index * 0.00012207031f;
        angle = angle * 6.2831855f;
        g_cosine_table[index] = (float)cos(angle);
        g_sine_table[index] = (float)sin(angle);
    }
    gRMathRand2Init();
}
