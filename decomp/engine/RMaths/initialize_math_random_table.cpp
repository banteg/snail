// gRMathRand2Init @ 0x44c8d0 (cdecl)

#include <stdlib.h>

#include "rmath_random.h"

#include "rmath_tables.h"

void gRMathRand2Init()
{
    int* cursor = g_math_random_table;
    int result;

    do {
        result = rand();
        *cursor++ = result;
    } while ((int)cursor < (int)&g_math_random_table[RMATH_RANDOM_TABLE_COUNT]);

    g_math_random_index = 0;
}
