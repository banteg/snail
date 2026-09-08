// Storage for the source-object integration build. These are the verified
// native array extents; their linked placement does not reproduce the EXE's BSS.
#include "rmath_tables.h"

float g_cosine_table[RMATH_TRIG_TABLE_COUNT];
float g_sine_table[RMATH_TRIG_TABLE_COUNT];
int g_math_random_index;
int g_math_random_table[RMATH_RANDOM_TABLE_COUNT];

// Integration evidence, not native game data: let the compiler report each
// source type's extent independently of section alignment and symbol ordering.
extern "C" const unsigned int rmath_storage_sizes[] = {
    sizeof(g_cosine_table), sizeof(g_sine_table),
    sizeof(g_math_random_table), sizeof(g_math_random_index)
};
