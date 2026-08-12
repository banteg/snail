// vector_magnitude @ 0x44ccf0 (thiscall) — tVector::Magnitude() const

#include "vector3.h"

float Sqrt(float value);

float tVector::Magnitude() const
{
    float magnitude = Sqrt(x * x + y * y + z * z);
    return magnitude;
}
