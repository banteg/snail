// gRMathRand2 @ 0x44c900

#include "rmath_tables.h"

int gRMathRand2()
{
    g_math_random_index = (g_math_random_index + 1) % RMATH_RANDOM_TABLE_COUNT;
    return g_math_random_table[g_math_random_index];
}
