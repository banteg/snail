#ifndef SNAIL_RMATH_RANDOM_H
#define SNAIL_RMATH_RANDOM_H

short __cdecl MathType32to16(float value, float scale);
float __cdecl MathType16to32(short value, float scale);
void __cdecl gRMathRand2Init();
int __cdecl gRMathRand2();
void __cdecl RMathInit();
void __cdecl RandSeed(int seed);
float __cdecl Cos(float angle);
float __cdecl Sin(float angle);
float __cdecl ACos(float value);
float __cdecl ATan(float y, float x);
float __cdecl Sqrt(float value);

// Windows retains the debug tag in its RAND/SRAND caller ABI even though the
// release-build bodies do not read it.
float __cdecl RAND(float upper_bound, char* tag);
float __cdecl SRAND(float upper_bound, char* tag);

#endif
