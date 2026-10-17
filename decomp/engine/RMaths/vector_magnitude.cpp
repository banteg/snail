// vector_magnitude @ 0x44ccf0 (thiscall) — tVector::Magnitude() const

#include "rmath_random.h"
#include "vector3.h"

float tVector::Magnitude() const
{
    float magnitude = Sqrt(x * x + y * y + z * z);
    return magnitude;
}
