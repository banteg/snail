#ifndef SNAIL_RMATH_TABLES_H
#define SNAIL_RMATH_TABLES_H

enum {
    RMATH_TRIG_TABLE_COUNT = 0x2000,
    RMATH_RANDOM_TABLE_COUNT = 0x1fff,
};

// RMathInit writes exactly indices 0..8191. VC6 advances its loop index
// before the stores, encoding the array symbol with a -4 byte addend.
// That relocation base is not a separately allocated object.
extern float g_cosine_table[RMATH_TRIG_TABLE_COUNT]; // @ 0x777f3c
extern float g_sine_table[RMATH_TRIG_TABLE_COUNT];   // @ 0x77ff8c

extern int g_math_random_index; // @ 0x77ff3c
extern int g_math_random_table[RMATH_RANDOM_TABLE_COUNT]; // @ 0x787f8c

#endif
