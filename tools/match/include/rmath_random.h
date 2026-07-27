#ifndef SNAIL_RMATH_RANDOM_H
#define SNAIL_RMATH_RANDOM_H

// Cross-port authored names: RAND(float, char*) and SRAND(float, char*).
// Windows retains the debug tag in its caller ABI even though these two
// release-build bodies do not read it.
float __cdecl random_float_below(float upper_bound, char* tag);
float __cdecl random_signed_float_below(float upper_bound, char* tag);
void __cdecl initialize_math_random_table();
void __cdecl initialize_trigonometry_tables();

#endif
