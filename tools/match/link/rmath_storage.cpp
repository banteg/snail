// Storage for the source-object integration build. These are the verified
// native array extents; their linked placement does not reproduce the EXE's BSS.
#include "rmath_tables.h"

float g_cosine_table[RMATH_TRIG_TABLE_COUNT];
float g_sine_table[RMATH_TRIG_TABLE_COUNT];
int g_math_random_index;
int g_math_random_table[RMATH_RANDOM_TABLE_COUNT];
